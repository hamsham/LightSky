/* 
 * File:   texture.cpp
 * Author: hammy
 * 
 * Created on January 27, 2014, 8:35 PM
 */

#include <Gl/glew.h>
#include "lsSetup.h"
#include "lsTexture.h"

/**
 * Move Constructor
 * Reassigns the texture ID at *this to the one referenced by the
 * source operand. Resets the source operand to 0.
 */
lsTexture::lsTexture(lsTexture&& t) :
    dimensions{t.dimensions},
    texId{t.texId}
{
    t.texId = 0;
}

/**
 * Move Operator
 */
lsTexture& lsTexture::operator=(lsTexture&& t) {
    HL_DEBUG_ASSERT(t.dimensions == dimensions);
    
    texId = t.texId;
    t.texId = 0;
    
    return *this;
}

/*
 * Load 1D Textures
 */
bool lsTexture::init(
    int mipmapLevel, int internalFormat,
    int size, int format, int dataType, void* data
) {
    if (!texId) {
        glGenTextures(1, &texId);
        LOG_GL_ERR();
    }
    
    if (texId == 0) {
        LS_LOG_ERR("Unable to generate a texture object");
        return false;
    }
    
    glBindTexture(dimensions, texId);
    LOG_GL_ERR();
    
    glTexImage1D(dimensions, mipmapLevel, internalFormat, size, 0, format, dataType, data);
    LOG_GL_ERR();
    
    return true;
}

/*
 * Load 2D Textures
 */
bool lsTexture::init(
    int mipmapLevel, int internalFormat,
    math::vec2i size, int format, int dataType, void* data
) {
    if (!texId) {
        glGenTextures(1, &texId);
        LOG_GL_ERR();
    }
    
    if (texId == 0) {
        LS_LOG_ERR("Unable to generate a texture object");
        return false;
    }
    
    glBindTexture(dimensions, texId);
    LOG_GL_ERR();
    
    glTexImage2D(
        dimensions, mipmapLevel, internalFormat,
        size[0], size[1], 0, format, dataType, data
    );
    LOG_GL_ERR();
    
    return true;
}

/*
 * Load 3D Textures
 */
bool lsTexture::init(
    int mipmapLevel, int internalFormat,
    math::vec3i size, int format, int dataType, void* data
) {
    if (!texId) {
        glGenTextures(1, &texId);
        LOG_GL_ERR();
    }
    
    if (texId == 0) {
        LS_LOG_ERR("Unable to generate a texture object");
        return false;
    }
    
    glBindTexture(dimensions, texId);
    LOG_GL_ERR();
    
    glTexImage3D(
        dimensions, mipmapLevel, internalFormat,
        size[0], size[1], size[2], 0, format, dataType,
        data
    );
    LOG_GL_ERR();
    
    return true;
}
