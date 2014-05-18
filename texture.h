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
template<tex_type superType, tex_desc subType>
class texture {
    private:
        /**
         * Texture ID
         * The handle to the current texture used by OpenGL.
         */
        unsigned texId = 0;
        
    public:
        /**
         * Constructor
         */
        constexpr texture();
        
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
        ~texture();
        
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
 * Texture Typedefs
******************************************************************************/
HL_DECLARE_CLASS_TYPE(texture1d, texture, TEXTURE_TYPE_1D, TEX_1D);
HL_DECLARE_CLASS_TYPE(texture2d, texture, TEXTURE_TYPE_2D, TEX_2D);
HL_DECLARE_CLASS_TYPE(texture3d, texture, TEXTURE_TYPE_3D, TEX_3D);
HL_DECLARE_CLASS_TYPE(textureRect, texture, TEXTURE_TYPE_2D, TEX_RECT);

/******************************************************************************
 * Texture Data
 *****************************************************************************/

/**
 * Constructor
 */
template <tex_type superType, tex_desc subType>
constexpr texture<superType, subType>::texture() {
}

/**
 * Move Constructor
 * Reassigns the texture ID at *this to the one referenced by the
 * source operand. Resets the source operand to 0.
 */
template <tex_type superType, tex_desc subType>
texture<superType, subType>::texture(texture&& t) :
    texId{t.texId}
{
    t.texId = 0;
}

/**
 * Destructor
 * Releases all memory referenced by texId
 */
template <tex_type superType, tex_desc subType>
texture<superType, subType>::~texture() {
    terminate();
}

/**
 * Move Operator
 */
template <tex_type superType, tex_desc subType>
texture<superType, subType>& texture<superType, subType>::operator=(texture<superType, subType>&& t) {
    texId = t.texId;
    t.texId = 0;
    return *this;
}

/**
 * Bind the current texture to OpenGL
 */
template <tex_type superType, tex_desc subType>
inline void texture<superType, subType>::bind() const {
    glBindTexture(subType, texId);
}

/**
 * Unbind the current texture to OpenGL
 */
template <tex_type superType, tex_desc subType>
inline void texture<superType, subType>::unbind() const {
    glBindTexture(subType, 0);
}

/**
 * Set a integer texture parameter.
 * Make sure that "bind()" has been called before using this method.
 */
template <tex_type superType, tex_desc subType>
inline void texture<superType, subType>::setParameter(int paramName, int param) const {
    glTexParameteri(subType, paramName, param);
}

/**
 * Set a float texture parameter.
 * Make sure that "bind()" has been called before using this method.
 */
template <tex_type superType, tex_desc subType>
inline void texture<superType, subType>::setParameter(int paramName, float param) const {
    glTexParameterf(subType, paramName, param);
}
/*
 * Load 1D Textures
 */
template <tex_type superType, tex_desc subType>
bool texture<superType, subType>::init(
    int mipmapLevel, int internalFormat,
    int size, int format, int dataType, void* data
) {
    #ifdef LS_DEBUG
        HL_ASSERT(superType == TEXTURE_TYPE_1D);
    #endif
    
    terminate();
    glGenTextures(1, &texId);
    LOG_GL_ERR();
    
    if (texId == 0) {
        LOG_ERR("Unable to generate a texture object");
        return false;
    }
    
    glBindTexture(subType, texId);
    LOG_GL_ERR();
    
    glTexImage1D(subType, mipmapLevel, internalFormat, size, 0, format, dataType, data);
    LOG_GL_ERR();
    
    return true;
}

/*
 * Load 2D Textures
 */
template <tex_type superType, tex_desc subType>
bool texture<superType, subType>::init(
    int mipmapLevel, int internalFormat,
    math::vec2i size, int format, int dataType, void* data
) {
    #ifdef LS_DEBUG
        HL_ASSERT(superType == TEXTURE_TYPE_2D);
    #endif
    
    terminate();
    glGenTextures(1, &texId);
    LOG_GL_ERR();
    
    if (texId == 0) {
        LOG_ERR("Unable to generate a texture object");
        return false;
    }
    
    glBindTexture(subType, texId);
    LOG_GL_ERR();
    
    glTexImage2D(
        subType, mipmapLevel, internalFormat,
        size[0], size[1], 0, format, dataType, data
    );
    LOG_GL_ERR();
    
    return true;
}

/*
 * Load 3D Textures
 */
template <tex_type superType, tex_desc subType>
bool texture<superType, subType>::init(
    int mipmapLevel, int internalFormat,
    math::vec3i size, int format, int dataType, void* data
) {
    #ifdef LS_DEBUG
        HL_ASSERT(superType == TEXTURE_TYPE_3D);
    #endif
    
    terminate();
    glGenTextures(1, &texId);
    LOG_GL_ERR();
    
    if (texId == 0) {
        LOG_ERR("Unable to generate a texture object");
        return false;
    }
    
    glBindTexture(subType, texId);
    LOG_GL_ERR();
    
    glTexImage3D(
        subType, mipmapLevel, internalFormat,
        size[0], size[1], size[2], 0, format, dataType,
        data
    );
    LOG_GL_ERR();
    
    return true;
}

/**
 * Modify the internal data of a texture.
 */
template <tex_type superType, tex_desc subType>
inline void texture<superType, subType>::modify(int offset, int size, int format, int dataType, void* data) {
    #ifdef LS_DEBUG
        HL_ASSERT(superType == TEXTURE_TYPE_1D);
    #endif
    glTexSubImage1D(getTextType(), 0, offset, size, format, dataType, data);
     LOG_GL_ERR();
}

/**
 * Modify the internal data of a texture.
 */
template <tex_type superType, tex_desc subType>
inline void texture<superType, subType>::modify(math::vec2i offset, math::vec2i size, int format, int dataType, void* data) {
    #ifdef LS_DEBUG
        HL_ASSERT(superType == TEXTURE_TYPE_2D);
    #endif
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
template <tex_type superType, tex_desc subType>
inline void texture<superType, subType>::modify(math::vec3i offset, math::vec3i size, int format, int dataType, void* data) {
    #ifdef LS_DEBUG
        HL_ASSERT(superType == TEXTURE_TYPE_3D);
    #endif
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
template <tex_type superType, tex_desc subType>
inline void texture<superType, subType>::terminate() {
    glDeleteTextures(1, &texId);
    texId = 0;
}

/**
 * Get the width of the texture referenced by texId
 */
template <tex_type superType, tex_desc subType>
inline unsigned texture<superType, subType>::getWidth() const {
    int w = 0;
    glGetTexLevelParameteriv(subType, 0, TEX_WIDTH, &w);
    return w;
}

/**
 * Get the height of the texture referenced by texId
 */
template <tex_type superType, tex_desc subType>
inline unsigned texture<superType, subType>::getHeight() const {
    #ifdef LS_DEBUG
        HL_ASSERT(superType != TEXTURE_TYPE_1D);
    #endif
    int h = 0;
    glGetTexLevelParameteriv(subType, 0, TEX_HEIGHT, &h);
    return h;
}

/**
 * Get the depth of the texture referenced by texId
 */
template <tex_type superType, tex_desc subType>
inline unsigned texture<superType, subType>::getDepth() const {
    #ifdef LS_DEBUG
        HL_ASSERT(superType == TEXTURE_TYPE_3D);
    #endif
    int d = 0;
    glGetTexLevelParameteriv(subType, 0, TEX_DEPTH, &d);
    return d;
}

/**
 * Get the texture type of that this texture uses in OpenGL
 */
template <tex_type superType, tex_desc subType>
constexpr tex_desc texture<superType, subType>::getTextType() const {
    return subType;
}

/**
 * Get the maximum texture size supported by OpenGL
 */
template <tex_type superType, tex_desc subType>
int texture<superType, subType>::getMaxTextureSize() {
    int maxTexSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
    return maxTexSize;
}

#endif	/* __LS_TEXTURE_H__ */
