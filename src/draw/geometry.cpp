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
    // clear all non-used data before continuing
    ibo.terminate();
    
    bool ret = true;
    if (meshData.getIndices().empty()) {
        ret = init(
            meshData.getVertices().data(),
            meshData.getVertices().size(),
            meshData.getDrawMode(),
            &meshData.getBoundingBox()
        );
    }
    else {
        ret = init(
            meshData.getVertices().data(),
            meshData.getVertices().size(),
            meshData.getIndices().data(),
            meshData.getIndices().size(),
            index_element_t::INDEX_TYPE_DEFAULT,
            meshData.getDrawMode(),
            &meshData.getBoundingBox()
        );
    }
    
    if (!ret) {
        return false;
    }
    
    submeshes.reserve(meshData.getNumMeshes());
    for (const sceneResource::resourceMesh& rSubMesh : meshData.getMeshes()) {
        submeshes.push_back(rSubMesh.indices);
    }

    return true;
}

/*-------------------------------------
    Vertex Buffer initialization
-------------------------------------*/
bool geometry::init(
    const vertex* const pVertices,
    const unsigned numVertices,
    const draw_mode_t renderMode,
    const boundingBox* const pBounds
) {
    // vbos are resized when any new data is pushed into them
    LOG_GL_ERR();
    LS_LOG_MSG("Attempting to send geometry vertices to the GPU.");

    if (!initBufferObject<vbo_use_t::VBO_BUFFER_ARRAY>(vbo, numVertices, sizeof(vertex))) {
        LS_LOG_ERR("\tUnable to initialize a geometry vertex buffer.\n");
        terminate();
        return false;
    }

    vbo.setSubData(0, numVertices*sizeof(vertex), pVertices);
    vbo.unbind();

    LOG_GL_ERR();
    
    drawParams.mode = renderMode;
    drawParams.first = 0;
    drawParams.count = numVertices;
    
    if (pBounds) {
        bounds = *pBounds;
    }
    else {
        // TODO: find out if this is undefined for mapped vertex buffers
        for (unsigned i = 0; i < numVertices; ++i) {
            bounds.compareAndUpdate(pVertices[i].pos);
        }
    }
    
    submeshes.push_back(draw_index_pair_t{0, numVertices});
    
    return true;
}

/*-------------------------------------
    Vertex Buffer + index buffer initialization
-------------------------------------*/
bool geometry::init(
    const vertex* const pVertices, const unsigned numVertices,
    const void* const pIndices, const unsigned numIndices,
    const index_element_t indexType,
    const draw_mode_t renderMode,
    const boundingBox* const pBounds
) {
    if (!init(pVertices, numVertices, renderMode, pBounds)) {
        return false;
    }
    
    LOG_GL_ERR();
    LS_LOG_MSG("Attempting to send geometry indices to the GPU.");
    
    LS_DEBUG_ASSERT(indexType != index_element_t::INDEX_TYPE_NONE);
    const unsigned indexElementSize = (indexType == index_element_t::INDEX_TYPE_UBYTE)
        ? sizeof(unsigned char)
        : (indexType == index_element_t::INDEX_TYPE_USHORT)
            ? sizeof(unsigned short)
            : sizeof(unsigned int);

    if (!initBufferObject<vbo_use_t::VBO_BUFFER_ELEMENT>(ibo, numIndices, indexElementSize)) {
        LS_LOG_ERR("\tUnable to initialize a geometry index buffer.\n");
        terminate();
        return false;
    }

    ibo.setSubData(0, numIndices*indexElementSize, pIndices);
    ibo.unbind();

    LOG_GL_ERR();
    
    drawParams.mode = renderMode;
    drawParams.count = numIndices;
    drawParams.indexType = indexType;
    
    // override the entry placed by the vertex buffer initialization
    submeshes.back() = draw_index_pair_t{0, numIndices};
    
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
    const unsigned numVerts = numChars * MESH_VERTS_PER_GLYPH;
    vertex* pVerts = mapBufferData<vertex, vbo_use_t::VBO_BUFFER_ARRAY>(vbo, numVerts, "vertices");
    if (pVerts == nullptr) {
        LS_LOG_ERR("\tUnable to send text vertex data to the GPU through a DMA transfer.\n");
        vbo.unmapData();
        terminate();
        return false;
    }
    
    // Attempt to get a pointer to an unsynchronized memory buffer
    const unsigned numIndices = numChars * MESH_INDICES_PER_GLYPH;
    draw_index_t* pIndices = mapBufferData<draw_index_t, vbo_use_t::VBO_BUFFER_ELEMENT>(ibo, numIndices, "indices");
    if (pIndices == nullptr) {
        LS_LOG_ERR("\tUnable to send text index data to the GPU through a DMA transfer.\n");
        vbo.unmapData();
        ibo.unmapData();
        terminate();
        return false;
    }
    
    genTextData(ta, str, pVerts, pIndices);
    
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
void geometry::genTextData(
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
            genTextVertices(xOffset, yOffset, rGlyph, pVerts);
            pVerts += MESH_VERTS_PER_GLYPH;
            
            *(pIndices++) = indexOffset+0;
            *(pIndices++) = indexOffset+1;
            *(pIndices++) = indexOffset+2;
            *(pIndices++) = indexOffset+2;
            *(pIndices++) = indexOffset+1;
            *(pIndices++) = indexOffset+3;
            indexOffset += MESH_VERTS_PER_GLYPH;
        }
    }
}

/*-------------------------------------
    Private helper function to upload a set of text vertices (or one
    glyph) to the GPU.
-------------------------------------*/
void geometry::genTextVertices(
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
    ++pVerts;
}

} // end draw namespace
} // end ls namespace
