/* 
 * File:   lsTexture.cpp
 * Author: hammy
 * 
 * Created on January 27, 2014, 8:35 PM
 */

#include <Gl/glew.h>
#include "lsSetup.h"
#include "lsTexture.h"


/**
 * Simple helper function that can help reduce a few lines of code
 * during texture initialization.
 * 
 * @return TRUE if the texture was created properly, FALSE if not.
 */
bool getGpuHandle(unsigned& texId) {
    if (!texId) {
        glGenTextures(1, &texId);
        LOG_GL_ERR();
        
        if (texId == 0) {
            LS_LOG_ERR("Unable to generate a texture object");
            return false;
        }
    }
    return true;
}

/*
 * Constructor
 */
lsTexture::lsTexture(ls_tex_desc_t td) :
    dimensions{td},
    texId{0}
{}

/*
 * Move Constructor
 */
lsTexture::lsTexture(lsTexture&& t) :
    dimensions{t.dimensions},
    texId{t.texId}
{
    t.texId = 0;
}
        
/**
 * Destructor
 */
lsTexture::~lsTexture() {
    terminate();
}

/*
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
    int                 mipmapLevel,
    ls_pixel_format_t   internalFormat,
    int                 size,
    ls_pixel_layout_t   format,
    ls_color_type_t     dataType,
    void* const         data
) {
    if (!getGpuHandle(texId)) {
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
    int                 mipmapLevel,
    ls_pixel_format_t   internalFormat,
    math::vec2i         size,
    ls_pixel_layout_t   format,
    ls_color_type_t     dataType,
    void* const         data
) {
    if (!getGpuHandle(texId)) {
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
    int                 mipmapLevel,
    ls_pixel_format_t   internalFormat,
    math::vec3i         size,
    ls_pixel_layout_t   format,
    ls_color_type_t     dataType,
    void* const         data
) {
    if (!getGpuHandle(texId)) {
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
