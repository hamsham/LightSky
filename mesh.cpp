/*
 * File:   mesh.cpp
 * Author: miles
 * 
 * Created on April 6, 2014, 12:36 AM
 */

#include <utility>

#include "assert.h"

#include "atlas.h"
#include "mesh.h"
#include "meshResource.h"
#include "resource.h"

/**
 * Utility function to get all of the non-whitespace characters in a string
 */
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

/*
 * Move Constructor
 */
mesh::mesh(mesh&& m) :
    vbo{std::move(m.vbo)},
    numVertices{m.numVertices},
    drawMode{m.drawMode},
    bounds{std::move(m.bounds)}
{
    m.numVertices = 0;
    m.drawMode = draw_mode::DEFAULT_DRAW_MODE;
}

/*
 * Move Operator
 */
mesh& mesh::operator=(mesh&& m) {
    vbo = std::move(m.vbo);
    
    numVertices = m.numVertices;
    m.numVertices = 0;
    
    drawMode = m.drawMode;
    m.drawMode = draw_mode::DEFAULT_DRAW_MODE;
    
    bounds = std::move(m.bounds);
    
    return *this;
}

/*
 * Helper function to initialize all vertex buffers & arrays
 */
bool mesh::initVertices(unsigned numVerts) {
    if (numVerts == 0) {
        LOG_ERR("\tInvalid vertex count in the mesh loader. Aborting GPU load.");
        terminate();
        return false;
    }
    
    if (vbo.isValid() == false) {
        if (!vbo.init()) {
            LOG_ERR("\tUnable to initialize a mesh VBO.");
            terminate();
            return false;
        }
    }
    else {
        vbo.setData(numVerts*sizeof(vertex), nullptr, buffer_usage_t::STREAM_DRAW);
        bounds = boundingBox{};
    }
    
    LOG_MSG("\tVertex Count: ", numVerts);
    return true;
}

/*
 * Load the data contained within a mesh loader onto the GPU
 */
bool mesh::init(const meshResource& ml) {
    LOG_MSG("Attempting to send mesh vertex data to the GPU.");
    
    if (!initVertices(ml.getNumVertices())) {
        return false;
    }
    
    vbo.bind();
    vbo.setSubData(0, ml.getByteSize(), ml.getVertices());
    LOG_GL_ERR();
    
    numVertices = ml.getNumVertices();
    drawMode = ml.getDrawMode();
    bounds = ml.getBoundingBox();
    
    LOG_MSG("\tSuccessfully sent a mesh of ", numVertices, " vertices to the GPU.\n");
    
    return true;
}

/*
 * Text/String initialization
 */
bool mesh::init(const atlas& ta, const std::string& str) {
    LOG_MSG("Attempting to load a text mesh.");
    
    // determine the number of non-whitespace characters
    const unsigned numChars = getDrawableCharCount(str.c_str());
    const unsigned numVerts = numChars*VERTICES_PER_GLYPH;
    const unsigned numBytes = numVerts * sizeof(vertex);
    
    if (!initVertices(numVerts)) {
        LOG_ERR("\tAn error occurred while initializing a text mesh.\n");
        return false;
    }
    
    vbo.bind();
    LOG_GL_ERR();
    
    // Attempt to get a pointer to an unsynchronized memory buffer
    vertex* pVerts = (vertex*)vbo.mapData(
        0, numBytes,
        (buffer_access_t)(MAP_INVALIDATE_RANGE_BIT | MAP_WRITE_BIT | MAP_UNSYNCHRONIZED_BIT)
    );
    LOG_GL_ERR();
    
    if (pVerts == nullptr) {
        LOG_ERR("\tUnable to send text data to the GPU through a DMA transfer.");
        terminate();
        return false;
    }
    
    // Get pointers to the buffer data that will be filled with quads
    const atlasEntry* const pGlyphs = ta.getEntries();
    // The y-origin was found using a lot of testing. This was for resolution independence
    float yPos = -((pGlyphs['\n'].bearing[1]*2.f)+pGlyphs['\n'].bearing[1]-pGlyphs['\n'].size[1]);
    float xPos = 0.f;
    
    for (unsigned i = 0; i < str.size(); ++i) {
        const unsigned currChar = (unsigned)str[i];
        const atlasEntry& rGlyph = pGlyphs[currChar];
        const float vertHang = (rGlyph.bearing[1]-rGlyph.size[1]);
        
        if (currChar == '\n') {
            yPos -= (rGlyph.bearing[1]*2.f)+vertHang; // formula found through trial and error
            xPos = 0.f;
        }
        else if (currChar == '\v') {
            yPos -= ((rGlyph.bearing[1]*2.f)+vertHang)*SPACES_PER_TAB;
            xPos = 0.f;
        }
        else if (currChar == '\r') {
            xPos = 0.f;
        }
        else if (currChar == ' ') {
            xPos += rGlyph.advance[0];
        }
        else if (currChar == '\t') {
            xPos += rGlyph.advance[0]*text_properties::SPACES_PER_TAB;
        }
        else {
            const float yOffset = yPos+vertHang;
            const float xOffset = xPos+rGlyph.bearing[0];
            xPos += rGlyph.advance[0];
            uploadTextGlyph(xOffset, yOffset, rGlyph, pVerts);
            pVerts += VERTICES_PER_GLYPH;
        }
    }
    
    if (!vbo.unmapData()) {
        LOG_ERR(
            "\tAn error occurred while attempting to end a DMA transmission of text."
        );
        terminate();
        return false;
    }
    LOG_GL_ERR();
    
    numVertices = numVerts;
    drawMode = draw_mode::LS_TRIANGLES;
    
    LOG_MSG("\tSuccessfully sent a string of ", numVertices, " vertices to the GPU.\n");
    
    return true;
}

/*
 * Private helper function to upload a set of text vertices (or one
 * glyph) to the GPU.
 */
void mesh::uploadTextGlyph(float xOffset, float yOffset, const atlasEntry& rGlyph, vertex* pVerts) {
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

    // 2nd triangle
    pVerts->pos = {xOffset+rGlyph.size[0], yOffset+rGlyph.size[1], 0.f};
    pVerts->uv = {rGlyph.uv[1][0], rGlyph.uv[0][1]};
    pVerts->norm = {0.f, 0.f, 1.f};
    bounds.compareAndUpdate(pVerts->pos);
    ++pVerts;

    pVerts->pos = {xOffset, yOffset, 0.f};
    pVerts->uv = {rGlyph.uv[0][0], rGlyph.uv[1][1]};
    pVerts->norm = {0.f, 0.f, 1.f};
    bounds.compareAndUpdate(pVerts->pos);
    ++pVerts;

    pVerts->pos = {xOffset+rGlyph.size[0],yOffset, 0.f};
    pVerts->uv = {rGlyph.uv[1][0], rGlyph.uv[1][1]};
    pVerts->norm = {0.f, 0.f, 1.f};
    bounds.compareAndUpdate(pVerts->pos);
    ++pVerts;
}
