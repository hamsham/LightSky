/* 
 * File:   text.cpp
 * Author: miles
 * 
 * Created on February 17, 2014, 5:12 PM
 */

#include <cstddef> /* used for offsetof */
#include <utility>
#include "text.h"

using hamLibs::math::vec3;
using hamLibs::math::vec2;

/**
 * Utility function to get all of the non-whitespace characters in a string
 */
int getDrawableCharCount(const char* const str) {
    int charCount = 0;
    
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
text::text(text&& t) :
    vao{std::move(t.vao)},
    vbo{std::move(t.vbo)},
    numGlyphs{t.numGlyphs}
{
    t.numGlyphs = 0;
}

/*
 * Move Operator
 */
text& text::operator=(text&& t) {
    vao = std::move(t.vao);
    vbo = std::move(t.vbo);
    
    numGlyphs = t.numGlyphs;
    t.numGlyphs = 0;
    
    return *this;
}

/*
 * Unload all used resources
 */
void text::terminate() {
    vao.terminate();
    vbo.terminate();
    
    numGlyphs = 0;
}

/*
 * Generate buffer data for the text to be used on the GPU
 */
bool text::generateBufferData(int numChars) {
    if (!vao.isValid()) {
        if (!vao.init()) {
            LOG_ERR("Unable to create a vao for text.");
            return false;
        }
    }
    
    if (!vbo.isValid()) {
        if (!vbo.init()) {
            LOG_ERR("Unable to create a vbo for text.");
            vao.terminate();
            return false;
        }
    }
    
    vao.bind();
    
    vbo.bind();
    vbo.setData(VERTICES_PER_GLYPH*numChars*sizeof(textVertex), nullptr, DYNAMIC_DRAW);
    
    vao.enableAttrib(LS_VERTEX_POSITION_ATTRIB);
    vao.enableAttrib(LS_VERTEX_TEXTURE_ATTRIB);
    
    vao.setAttribOffset(
        LS_VERTEX_POSITION_ATTRIB, LS_ARRAY_SIZE(textVertex::pos.v),
        GL_FLOAT, GL_FALSE, sizeof(textVertex), (GLvoid*)offsetof(textVertex, pos.v)
    );
    
    vao.setAttribOffset(
        LS_VERTEX_TEXTURE_ATTRIB, LS_ARRAY_SIZE(textVertex::uv.v),
        GL_FLOAT, GL_FALSE, sizeof(textVertex), (GLvoid*)offsetof(textVertex, uv.v)
    );
    
    return true;
}

/*
 * Text loading operation
 */
bool text::init(const char* str, const textureAtlas& ta) {
    const int numChars = getDrawableCharCount(str);
    
    LOG_GL_ERR();
    
    if (!generateBufferData(numChars)) {
        LOG_ERR("Unable to allocate space on the GPU for text data.");
        return false;
    }
    
    // Attempt to get a pointer to an unsynchronized memory buffer
    textVertex* pData = (textVertex*) vbo.mapData(
        0, VERTICES_PER_GLYPH*numChars*sizeof(textVertex),
        (buffer_access_t)(MAP_WRITE_BIT | MAP_UNSYNCHRONIZED_BIT | MAP_INVALIDATE_RANGE_BIT)
    );
    LOG_GL_ERR();
    
    if (pData == nullptr) {
        LOG_ERR("An error occurred while attempting to setup DMA for a text string.");
        terminate();
        return false;
    }
    
    // Get pointers to the buffer data that will be filled with quads
    const atlasEntry* const pGlyphs = ta.getEntries();
    // The y-origin was found using a lot of testing. This was for resolution independence
    float yPos = -((pGlyphs['\n'].bearing[1]*2.f)+pGlyphs['\n'].bearing[1]-pGlyphs['\n'].size[1]);
    float xPos = 0.f;
    
    for (unsigned i = 0; str[i]; ++i) {
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
            pData->pos = {xOffset, yOffset+rGlyph.size[1], 0.f};
            pData->uv = {rGlyph.uv[0][0], rGlyph.uv[0][1]};
            ++pData;
            
            pData->pos = {xOffset, yOffset, 0.f};
            pData->uv = {rGlyph.uv[0][0], rGlyph.uv[1][1]};
            ++pData;
            
            pData->pos = {xOffset+rGlyph.size[0], yOffset+rGlyph.size[1], 0.f};
            pData->uv = {rGlyph.uv[1][0], rGlyph.uv[0][1]};
            ++pData;
            
            // 2nd triangle
            pData->pos = {xOffset+rGlyph.size[0], yOffset+rGlyph.size[1], 0.f};
            pData->uv = {rGlyph.uv[1][0], rGlyph.uv[0][1]};
            ++pData;
            
            pData->pos = {xOffset+rGlyph.size[0],yOffset, 0.f};
            pData->uv = {rGlyph.uv[1][0], rGlyph.uv[1][1]};
            ++pData;
            
            pData->pos = {xOffset, yOffset, 0.f};
            pData->uv = {rGlyph.uv[0][0], rGlyph.uv[1][1]};
            ++pData;
            
            LOG_GL_ERR();
        }
    }
    
    if (!vbo.unmapData()) {
        LOG_ERR("Unable to unmap the current text buffer.");
    }
    LOG_GL_ERR();
    
    numGlyphs = numChars*VERTICES_PER_GLYPH;
    
    vao.unbind();
    
    return true;
}

