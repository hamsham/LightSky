/*
 * File:   draw/geometry.cpp
 * Author: Miles Lacey
 * 
 * Created on April 6, 2014, 12:36 AM
 */

#include <utility>

#include "lightsky/utils/assertions.h"

#include "lightsky/draw/atlas.h"
#include "lightsky/draw/geometry.h"
#include "lightsky/draw/sceneResource.h"
#include "lightsky/utils/resource.h"

namespace ls {
namespace draw {

/*-------------------------------------
    Utility function to get all of the non-whitespace characters in a string
-------------------------------------*/
unsigned getDrawableCharCount(const char* const str) {
    unsigned charCount = 0;
    
    for(unsigned i = 0; str[i]; ++i) {
        switch(str[i]) {
            case '\n':
            case '\v':
            case '\f':
            case '\r':
            case '\t':
            case ' ': continue;
            default: ++charCount;
        }
    }
    return charCount;
}

/*-------------------------------------
    Constructor
-------------------------------------*/
geometry::geometry() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
geometry::geometry(geometry&& g) :
    vbo{std::move(g.vbo)},
    ibo{std::move(g.ibo)},
    drawParams{std::move(g.drawParams)},
    submeshes{std::move(g.submeshes)},
    bounds{std::move(g.bounds)}
{}

/*-------------------------------------
    Move Operator
-------------------------------------*/
geometry& geometry::operator=(geometry&& g) {
    vbo = std::move(g.vbo);
    
    ibo = std::move(g.ibo);
    
    drawParams = g.drawParams;
    g.drawParams.reset();;
    
    submeshes = std::move(g.submeshes);
    
    bounds = std::move(g.bounds);
    
    return *this;
}

/*-------------------------------------
    Destructor
-------------------------------------*/
geometry::~geometry() {
    terminate();
}

/*-------------------------------------
    Unload all GPU-based resource that are used by *this;
-------------------------------------*/
void geometry::terminate() {
    vbo.terminate();
    ibo.terminate();
    drawParams.reset();
    submeshes.clear();
    bounds.resetSize();
}

/*-------------------------------------
    Load the data contained within a geometry loader onto the GPU
-------------------------------------*/
bool geometry::init(const sceneResource& meshData) {
    // vbos are resized when any new data is pushed into them

    LOG_GL_ERR();
    LS_LOG_MSG("Attempting to send geometry data to the GPU.");

    if (!vbo.init()) {
        LS_LOG_ERR("\tUnable to initialize a geometry vertex buffer.\n");
        terminate();
        return false;
    }

    const unsigned vertexCount = meshData.getNumVertices();
    const unsigned vertexSize = vertexCount*sizeof(vertex);

    vbo.bind();
    vbo.setData(vertexSize, meshData.getVertices().data(), vbo_rw_t::VBO_STATIC_DRAW);
    vbo.unbind();

    LS_LOG_MSG("\tSuccessfully sent ", vertexCount, " vertices to the GPU.\n");
    LOG_GL_ERR();

    drawParams.mode = meshData.getDrawMode();
    drawParams.first = 0;
    drawParams.count = meshData.getNumVertices();

    // return early if there is no index data to be loaded
    if (meshData.getNumIndices() == 0) {
        return true;
    }

    LS_LOG_MSG("Attempting to send index data to the GPU.");

    // load index data from the mesh resource object
    if (!ibo.init()) {
        LS_LOG_ERR("\tUnable to initialize a geometry index buffer.\n");
        terminate();
        return false;
    }

    // update the index buffer & draw command if there were indices to load.
    const unsigned indexCount = meshData.getNumIndices();
    const unsigned indexSize = indexCount*sizeof(draw_index_t);

    ibo.bind();
    ibo.setData(indexSize, meshData.getIndices().data(), vbo_rw_t::VBO_STATIC_DRAW);
    ibo.unbind();

    LS_LOG_MSG("\tSuccessfully sent ", indexCount, " indices to the GPU.\n");
    LOG_GL_ERR();

    drawParams.count = meshData.getNumIndices();
    drawParams.indexType = index_element_t::INDEX_TYPE_DEFAULT;
    
    submeshes.reserve(meshData.getNumMeshes());
    for (const sceneResource::resourceMesh& rSubMesh : meshData.getMeshes()) {
        submeshes.push_back(rSubMesh.indices);
    }

    return true;
}

/*-------------------------------------
    Text/String initialization
-------------------------------------*/
bool geometry::init(const atlas& ta, const std::string& str) {
    drawParams.reset();
    submeshes.clear();
    bounds.resetSize();
    
    LS_LOG_MSG("Attempting to load text geometry.");
    
    // determine the number of non-whitespace characters
    const unsigned numChars = getDrawableCharCount(str.c_str());
    
    // Attempt to get a pointer to an unsynchronized memory buffer
    const unsigned numVerts = numChars*MESH_VERTS_PER_GLYPH;
    const unsigned numVertBytes = numVerts * sizeof(vertex);
    vertex* pVerts =
        mapBufferData<vertex, vbo_use_t::VBO_BUFFER_ARRAY>(vbo, numVerts, numVertBytes, "vertices");
    if (pVerts == nullptr) {
        LS_LOG_ERR("\tUnable to send text vertex data to the GPU through a DMA transfer.\n");
        vbo.unmapData();
        terminate();
        return false;
    }
    
    // Attempt to get a pointer to an unsynchronized memory buffer
    const unsigned numIndices = numChars * MESH_INDICES_PER_GLYPH;
    const unsigned numIndexBytes = numIndices * sizeof(draw_index_t);
    draw_index_t* pIndices =
        mapBufferData<draw_index_t, vbo_use_t::VBO_BUFFER_ELEMENT>(ibo, numIndices, numIndexBytes, "indices");
    if (pIndices == nullptr) {
        LS_LOG_ERR("\tUnable to send text index data to the GPU through a DMA transfer.\n");
        vbo.unmapData();
        ibo.unmapData();
        terminate();
        return false;
    }
    
    genTextOffsets(ta, str, pVerts, pIndices);
    
    if (!vbo.unmapData() || !ibo.unmapData()) {
        LS_LOG_ERR(
            "\tAn error occurred while attempting to end a DMA transmission of text.\n"
        );
        terminate();
        return false;
    }
    LOG_GL_ERR();
    
    vbo.unbind();
    ibo.unbind();
    
    LS_LOG_MSG(
        "\tSuccessfully sent a string to the GPU.",
        "\n\t\tVertices:    ", numVerts,
        "\n\t\tIndices:     ", numIndices,
        '\n'
    );
    LOG_GL_ERR();
    
    drawParams.mode = draw_mode_t::TRIS;
    drawParams.first = 0;
    drawParams.count = numIndices;
    drawParams.indexType = index_element_t::INDEX_TYPE_UINT;
    submeshes.push_back(draw_index_pair_t{0, numIndices});
    
    return true;
}

/*-------------------------------------
    Text/String Generation
-------------------------------------*/
void geometry::genTextOffsets(
    const atlas& ta,
    const std::string& str,
    vertex* pVerts,
    draw_index_t* pIndices
) {
    
    // Get pointers to the buffer data that will be filled with quads
    const atlasEntry* const pGlyphs = ta.getEntries();
    // The y-origin was found using a lot of testing. This was for resolution independence
    constexpr unsigned nl = (unsigned)'\n';
    float yPos = -((pGlyphs[nl].bearing[1]*2.f)+pGlyphs[nl].bearing[1]-pGlyphs[nl].size[1]);
    float xPos = 0.f;
    unsigned indexOffset = 0;
    
    for (unsigned i = 0; i < str.size(); ++i) {
        const unsigned currChar = (unsigned)str[i];
        const atlasEntry& rGlyph = pGlyphs[currChar];
        const float vertHang = (rGlyph.bearing[1]-rGlyph.size[1]);
        
        if (currChar == '\n') {
            yPos -= (rGlyph.bearing[1]*2.f)+vertHang; // formula found through trial and error
            xPos = 0.f;
        }
        else if (currChar == '\v') {
            yPos -= ((rGlyph.bearing[1]*2.f)+vertHang)*MESH_SPACES_PER_TAB;
            xPos = 0.f;
        }
        else if (currChar == '\r') {
            xPos = 0.f;
        }
        else if (currChar == ' ') {
            xPos += rGlyph.advance[0];
        }
        else if (currChar == '\t') {
            xPos += rGlyph.advance[0]*MESH_SPACES_PER_TAB;
        }
        else {
            const float yOffset = yPos+vertHang;
            const float xOffset = xPos+rGlyph.bearing[0];
            xPos += rGlyph.advance[0];
            uploadTextGlyph(xOffset, yOffset, rGlyph, pVerts);
            pVerts += MESH_VERTS_PER_GLYPH;
            
            *(pIndices++) = indexOffset+0;
            *(pIndices++) = indexOffset+1;
            *(pIndices++) = indexOffset+2;
            *(pIndices++) = indexOffset+2;
            *(pIndices++) = indexOffset+1;
            *(pIndices++) = indexOffset+3;
            indexOffset += MESH_INDICES_PER_GLYPH;
        }
    }
}

/*-------------------------------------
    Private helper function to upload a set of text vertices (or one
    glyph) to the GPU.
-------------------------------------*/
void geometry::uploadTextGlyph(
    float xOffset,
    float yOffset,
    const atlasEntry& rGlyph,
    vertex* pVerts
) {
    // 0--------2,3
    // |     /  |
    // |   /    |
    // | /      |
    // 1,4------5
    
    // 1st triangle
    pVerts->pos = {xOffset, yOffset+rGlyph.size[1], 0.f};
    pVerts->uv = {rGlyph.uv[0][0], rGlyph.uv[0][1]};
    pVerts->norm = {0.f, 0.f, 1.f};
    bounds.compareAndUpdate(pVerts->pos);
    ++pVerts;

    pVerts->pos = {xOffset, yOffset, 0.f};
    pVerts->uv = {rGlyph.uv[0][0], rGlyph.uv[1][1]};
    pVerts->norm = {0.f, 0.f, 1.f};
    bounds.compareAndUpdate(pVerts->pos);
    ++pVerts;

    pVerts->pos = {xOffset+rGlyph.size[0], yOffset+rGlyph.size[1], 0.f};
    pVerts->uv = {rGlyph.uv[1][0], rGlyph.uv[0][1]};
    pVerts->norm = {0.f, 0.f, 1.f};
    bounds.compareAndUpdate(pVerts->pos);
    ++pVerts;

    pVerts->pos = {xOffset+rGlyph.size[0],yOffset, 0.f};
    pVerts->uv = {rGlyph.uv[1][0], rGlyph.uv[1][1]};
    pVerts->norm = {0.f, 0.f, 1.f};
    bounds.compareAndUpdate(pVerts->pos);
}

} // end draw namespace
} // end ls namespace
