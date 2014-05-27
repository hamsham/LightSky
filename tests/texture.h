/* 
 * File:   texture.h
 * Author: hammy
 *
 * Created on January 27, 2014, 8:35 PM
 */

#ifndef __LS_TEXTURE_H__
#define	__LS_TEXTURE_H__

#include <GL/glew.h>
#include "main.h"

enum tex_param : int {
    TEX_INVALID = -1,

    TEX_WIDTH           = GL_TEXTURE_WIDTH,
    TEX_HEIGHT          = GL_TEXTURE_HEIGHT,
    TEX_DEPTH           = GL_TEXTURE_DEPTH,

    TEX_MIN_FILTER      = GL_TEXTURE_MIN_FILTER,
    TEX_MAG_FILTER      = GL_TEXTURE_MAG_FILTER,

    LINEAR_FILTER       = GL_LINEAR,
    NEAREST_FILTER      = GL_NEAREST
};

enum tex_type : int {
    TEXTURE_TYPE_1D,
    TEXTURE_TYPE_2D,
    TEXTURE_TYPE_3D
};

enum tex_desc : int {
    TEX_1D              = GL_TEXTURE_1D,
    TEX_2D              = GL_TEXTURE_2D,
    TEX_3D              = GL_TEXTURE_3D,
    TEX_RECT            = GL_TEXTURE_RECTANGLE,
};

/******************************************************************************
 * Texture Template
******************************************************************************/
class texture {
    private:
        const tex_desc dimensions;
        
        /**
         * Texture ID
         * The handle to the current texture used by OpenGL.
         */
        unsigned texId = 0;
        
    public:
        /**
         * Constructor
         */
        constexpr texture(tex_desc td) :
            dimensions{td}
        {}
        
        /**
         * Copy Constructor -- DELETED
         */
        texture(const texture&) = delete;
        
        /**
         * Move Constructor
         * Reassigns the texture ID at *this to the one referenced by the
         * source operand. Resets the source operand to 0.
         */
        texture(texture&& t);
        
        /**
         * Destructor
         * Releases all memory referenced by texId
         */
        ~texture() {
            terminate();
        }
        
        /**
         * Copy Operator -- DELETED
         */
        texture& operator=(const texture&) = delete;
        
        /**
         * Move Operator -- DELETED
         */
        texture& operator=(texture&& t);
        
        /**
         * Bind the current texture to OpenGL
         */
        inline void bind() const;
        
        /**
         * Unbind the current texture to OpenGL
         */
        inline void unbind() const;
        
        /**
         * Set a integer texture parameter.
         * Make sure that "bind()" has been called before using this method.
         */
        inline void setParameter(int paramName, int param) const;
        
        /**
         * Set a float texture parameter.
         * Make sure that "bind()" has been called before using this method.
         */
        inline void setParameter(int paramName, float param) const;
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * @see OpenGL's documentation for glTexImage()
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, int internalFormat, int size, int format, int dataType, void* data);
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * @see OpenGL's documentation for glTexImage()
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, int internalFormat, math::vec2i size, int format, int dataType, void* data);
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * @see OpenGL's documentation for glTexImage()
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, int internalFormat, math::vec3i size, int format, int dataType, void* data);
        
        /**
         * Modify the internal data of a texture.
         */
        inline void modify(int offset, int size, int format, int dataType, void* data);
        
        /**
         * Modify the internal data of a texture.
         */
        inline void modify(math::vec2i offset, math::vec2i size, int format, int dataType, void* data);
        
        /**
         * Modify the internal data of a texture.
         */
        inline void modify(math::vec3i offset, math::vec3i size, int format, int dataType, void* data);
        
        /**
         * Release all memory referenced by *this.
         */
        inline void terminate();
        
        /**
         * Get the width of the texture referenced by texId
         */
        inline unsigned getWidth() const;
        
        /**
         * Get the height of the texture referenced by texId
         */
        inline unsigned getHeight() const;
        
        /**
         * Get the depth of the texture referenced by texId
         */
        inline unsigned getDepth() const;
        
        /**
         * Get the texture type of that this texture uses in OpenGL
         */
        constexpr tex_desc getTextType() const;
        
        /**
         * Get the maximum texture size supported by OpenGL
         */
        static int getMaxTextureSize();
};

/******************************************************************************
 * Texture Data
 *****************************************************************************/
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

/**
 * Bind the current texture to OpenGL
 */

inline void texture::bind() const {
    glBindTexture(dimensions, texId);
}

/**
 * Unbind the current texture to OpenGL
 */

inline void texture::unbind() const {
    glBindTexture(dimensions, 0);
}

/**
 * Set a integer texture parameter.
 * Make sure that "bind()" has been called before using this method.
 */

inline void texture::setParameter(int paramName, int param) const {
    glTexParameteri(dimensions, paramName, param);
}

/**
 * Set a float texture parameter.
 * Make sure that "bind()" has been called before using this method.
 */

inline void texture::setParameter(int paramName, float param) const {
    glTexParameterf(dimensions, paramName, param);
}
/*
 * Load 1D Textures
 */

bool texture::init(
    int mipmapLevel, int internalFormat,
    int size, int format, int dataType, void* data
) {
    terminate();
    glGenTextures(1, &texId);
    LOG_GL_ERR();
    
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
    terminate();
    glGenTextures(1, &texId);
    LOG_GL_ERR();
    
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
    terminate();
    glGenTextures(1, &texId);
    LOG_GL_ERR();
    
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

/**
 * Modify the internal data of a texture.
 */

inline void texture::modify(int offset, int size, int format, int dataType, void* data) {
    glTexSubImage1D(getTextType(), 0, offset, size, format, dataType, data);
     LOG_GL_ERR();
}

/**
 * Modify the internal data of a texture.
 */

inline void texture::modify(math::vec2i offset, math::vec2i size, int format, int dataType, void* data) {
    glTexSubImage2D(
        getTextType(), 0,
        offset[0], offset[1], size[0], size[1],
        format, dataType, data
    );
    LOG_GL_ERR();
}

/**
 * Modify the internal data of a texture.
 */

inline void texture::modify(math::vec3i offset, math::vec3i size, int format, int dataType, void* data) {
    glTexSubImage3D(
        getTextType(), 0,
        offset[0], offset[1], offset[2], size[0], size[1], size[2],
        format, dataType, data
    );
    LOG_GL_ERR();
}

/**
 * Release all memory referenced by *this.
 */

inline void texture::terminate() {
    glDeleteTextures(1, &texId);
    texId = 0;
}

/**
 * Get the width of the texture referenced by texId
 */

inline unsigned texture::getWidth() const {
    int w = 0;
    glGetTexLevelParameteriv(dimensions, 0, TEX_WIDTH, &w);
    return w;
}

/**
 * Get the height of the texture referenced by texId
 */

inline unsigned texture::getHeight() const {
    int h = 0;
    glGetTexLevelParameteriv(dimensions, 0, TEX_HEIGHT, &h);
    return h;
}

/**
 * Get the depth of the texture referenced by texId
 */

inline unsigned texture::getDepth() const {
    int d = 0;
    glGetTexLevelParameteriv(dimensions, 0, TEX_DEPTH, &d);
    return d;
}

/**
 * Get the texture type of that this texture uses in OpenGL
 */

constexpr tex_desc texture::getTextType() const {
    return dimensions;
}

/**
 * Get the maximum texture size supported by OpenGL
 */

int texture::getMaxTextureSize() {
    int maxTexSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
    return maxTexSize;
}

#endif	/* __LS_TEXTURE_H__ */
