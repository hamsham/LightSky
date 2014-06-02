/* 
 * File:   text.cpp
 * Author: miles
 * 
 * Created on June 1, 2014, 9:25 PM
 */

#include <utility>
#include "text.h"

/**
 * Utility function to get all of the non-whitespace characters in a string
 */
int getDrawableCharCount(const char* const str);

/*
 * Move Constructor
 */
text::text(text&& m) :
    vao{std::move(m.vao)},
    vbo{std::move(m.vbo)},
    modelVbo{std::move(m.modelVbo)},
    numVertices{m.numVertices}
{
    m.numVertices = 0;
    m.numInstances = 0;
}

/*
 * Move Operator
 */
text& text::operator=(text&& m) {
    vao = std::move(m.vao);
    vbo = std::move(m.vbo);
    modelVbo = std::move(m.modelVbo);
    
    numVertices = m.numVertices;
    m.numVertices = 0;
    
    numInstances = m.numInstances;
    m.numInstances = 0;
    
    return *this;
}

/*
 * Helper function to initialize all vertex buffers & arrays
 */
bool text::initVertices(unsigned numVerts) {
    if (numVerts == 0) {
        LOG_ERR("\tInvalid vertex count in the text loader. Aborting GPU load.");
        terminate();
        return false;
    }
    
    vao.terminate();
    if (!vao.init()) {
        LOG_ERR("\tUnable to initialize a text VAO.");
        return false;
    }
    
    if (vbo.isValid() == false) {
        if (!vbo.init()) {
            LOG_ERR("\tUnable to initialize a text VBO.");
            terminate();
            return false;
        }
    }
    
    if (modelVbo.isValid() == false) {
        if (!modelVbo.init()) {
            LOG_ERR("\tUnable to initialize a model matrix buffer.");
            terminate();
            return false;
        }
    }
    
    LOG_MSG("\tVertex Count: ", numVerts);
    return true;
}

/*
 * Helper function to ensure all vertex attributes are setup properly.
 */
void text::setVertexAttribs() {
    vao.bind();
    vbo.bind();
    
    // Vertex positions
    vao.enableAttrib(LS_VERTEX_POSITION_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_POSITION_ATTRIB, LS_ARRAY_SIZE(vertex::pos.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, pos.v)
    );
    
    // Vertex UVs
    vao.enableAttrib(LS_VERTEX_TEXTURE_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_TEXTURE_ATTRIB, LS_ARRAY_SIZE(vertex::uv.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, uv.v)
    );
    
    // Vertex normals
    vao.enableAttrib(LS_VERTEX_NORMAL_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_NORMAL_ATTRIB, LS_ARRAY_SIZE(vertex::norm.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, norm.v)
    );
    
    LOG_GL_ERR();
    
    // setup the VBO/VAO for instancing
    modelVbo.bind();
    for (unsigned i = 0; i < 4; ++i) {
        vao.enableAttrib(LS_MODEL_MATRIX_ATTRIB+i);
        vao.setAttribOffset(
            LS_MODEL_MATRIX_ATTRIB+i, 4, GL_FLOAT, GL_FALSE,
            sizeof(math::mat4), (const GLvoid*)(sizeof(float)*i*4)
        );
        vao.setAttribInstanceRate(LS_MODEL_MATRIX_ATTRIB+i, 1);
    }
    
    LOG_GL_ERR();
    
    vao.unbind();
    vbo.unbind();
    modelVbo.unbind();
    
    LOG_GL_ERR();
}

/*
 * Text/String initialization
 */
bool text::init(const textureAtlas& ta, const std::string& str) {
    LOG_MSG("Attempting to load a text mesh.");
    
    // determine the number of non-whitespace characters
    const unsigned numChars = getDrawableCharCount(str.c_str());
    const unsigned numVerts = numChars*text_properties::VERTICES_PER_GLYPH;
    const unsigned numBytes = numVerts * sizeof(vertex);
    
    if (!initVertices(numVerts)) {
        LOG_ERR("\tAn error occurred while initializing a text mesh.\n");
        return false;
    }
    
    vbo.bind();
    vbo.setData(numBytes, nullptr, buffer_usage_t::STREAM_DRAW);
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
            yPos -= ((rGlyph.bearing[1]*2.f)+vertHang)*text_properties::SPACES_PER_TAB;
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
            // 0--------2,3
            // |     /  |
            // |   /    |
            // | /      |
            // 1,4------5
            const float yOffset = yPos+vertHang;
            const float xOffset = xPos+rGlyph.bearing[0];
            xPos += rGlyph.advance[0];
            
            // 1st triangle
            pVerts->pos = {xOffset, yOffset+rGlyph.size[1], 0.f};
            pVerts->uv = {rGlyph.uv[0][0], rGlyph.uv[0][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
            
            pVerts->pos = {xOffset, yOffset, 0.f};
            pVerts->uv = {rGlyph.uv[0][0], rGlyph.uv[1][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
            
            pVerts->pos = {xOffset+rGlyph.size[0], yOffset+rGlyph.size[1], 0.f};
            pVerts->uv = {rGlyph.uv[1][0], rGlyph.uv[0][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
            
            // 2nd triangle
            pVerts->pos = {xOffset+rGlyph.size[0], yOffset+rGlyph.size[1], 0.f};
            pVerts->uv = {rGlyph.uv[1][0], rGlyph.uv[0][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
            
            pVerts->pos = {xOffset, yOffset, 0.f};
            pVerts->uv = {rGlyph.uv[0][0], rGlyph.uv[1][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
            
            pVerts->pos = {xOffset+rGlyph.size[0],yOffset, 0.f};
            pVerts->uv = {rGlyph.uv[1][0], rGlyph.uv[1][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
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
    
    setVertexAttribs();
    const math::mat4 identityMat = {1.f};
    setNumInstances(1, &identityMat);
    
    numVertices = numVerts;
    
    LOG_MSG("\tSuccessfully sent a string of ", numVertices, " vertices to the GPU.\n");
    
    return true;
}

void text::setNumInstances(int instanceCount, const math::mat4* const modelMatrices) {
    modelVbo.bind();
    modelVbo.setData(sizeof(math::mat4)*instanceCount, modelMatrices, buffer_usage_t::DYNAMIC_DRAW);
    modelVbo.unbind();
    
    numInstances = instanceCount;
}

void text::modifyInstance(int index, const math::mat4& modelMatrix) {
    modelVbo.bind();
    modelVbo.setSubData(sizeof(math::mat4)*index, sizeof(math::mat4), &modelMatrix);
    modelVbo.unbind();
}
