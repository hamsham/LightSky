/* 
 * File:   texture.cpp
 * Author: hammy
 * 
 * Created on January 27, 2014, 8:35 PM
 */

#include <Gl/glew.h>
#include "main.h"
#include "texture.h"

/**
 * Move Constructor
 * Reassigns the texture ID at *this to the one referenced by the
 * source operand. Resets the source operand to 0.
 */
texture::texture(texture&& t) :
    dimensions{t.dimensions},
    texId{t.texId}
{
    t.texId = 0;
}

/**
 * Move Operator
 */
texture& texture::operator=(texture&& t) {
    #ifdef LS_DEBUG
        HL_ASSERT(t.dimensions == dimensions);
    #endif
    
    texId = t.texId;
    t.texId = 0;
    
    return *this;
}

/*
 * Load 1D Textures
 */
bool texture::init(
    int mipmapLevel, int internalFormat,
    int size, int format, int dataType, void* data
) {
    if (!texId) {
        glGenTextures(1, &texId);
        LOG_GL_ERR();
    }
    
    if (texId == 0) {
        LOG_ERR("Unable to generate a texture object");
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
bool texture::init(
    int mipmapLevel, int internalFormat,
    math::vec2i size, int format, int dataType, void* data
) {
    if (!texId) {
        glGenTextures(1, &texId);
        LOG_GL_ERR();
    }
    
    if (texId == 0) {
        LOG_ERR("Unable to generate a texture object");
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
bool texture::init(
    int mipmapLevel, int internalFormat,
    math::vec3i size, int format, int dataType, void* data
) {
    if (!texId) {
        glGenTextures(1, &texId);
        LOG_GL_ERR();
    }
    
    if (texId == 0) {
        LOG_ERR("Unable to generate a texture object");
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
