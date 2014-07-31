/* 
 * File:   texture.h
 * Author: hammy
 *
 * Created on January 27, 2014, 8:35 PM
 */

#ifndef __LS_TEXTURE_H__
#define	__LS_TEXTURE_H__

#include <GL/glew.h>

#include "lsSetup.h"
#include "lsImageResource.h"

/**
 * Parameters for creating or modifying texture objects.
 */
enum ls_tex_param_t : int {
    LS_TEX_INVALID      = -1,

    LS_TEX_WIDTH        = GL_TEXTURE_WIDTH,
    LS_TEX_HEIGHT       = GL_TEXTURE_HEIGHT,
    LS_TEX_DEPTH        = GL_TEXTURE_DEPTH,

    LS_TEX_MIN_FILTER   = GL_TEXTURE_MIN_FILTER,
    LS_TEX_MAG_FILTER   = GL_TEXTURE_MAG_FILTER,

    LS_TEX_WRAP_S       = GL_TEXTURE_WRAP_S,
    LS_TEX_WRAP_T       = GL_TEXTURE_WRAP_T,
    LS_TEX_WRAP_R       = GL_TEXTURE_WRAP_R,
    
    LS_TEX_CLAMP        = GL_CLAMP,
    LS_TEX_REPEAT       = GL_REPEAT,

    LS_LINEAR_FILTER    = GL_LINEAR,
    LS_NEAREST_FILTER   = GL_NEAREST
};

/**
 * Descriptors for different texture types
 */
enum ls_tex_desc_t : int {
    LS_TEX_1D           = GL_TEXTURE_1D,
    LS_TEX_2D           = GL_TEXTURE_2D,
    LS_TEX_3D           = GL_TEXTURE_3D,
    LS_TEX_RECT         = GL_TEXTURE_RECTANGLE,
};

/******************************************************************************
 * Texture Template
******************************************************************************/
class lsTexture {
    private:
        const ls_tex_desc_t dimensions;
        
        /**
         * Texture ID
         * The handle to the current texture used by OpenGL.
         */
        unsigned texId = 0;
        
    public:
        /**
         * Constructor
         */
        lsTexture(ls_tex_desc_t td = LS_TEX_2D) :
            dimensions{td}
        {}
        
        /**
         * Copy Constructor -- DELETED
         */
        lsTexture(const lsTexture&) = delete;
        
        /**
         * Move Constructor
         * Reassigns the texture ID at *this to the one referenced by the
         * source operand. Resets the source operand to 0.
         */
        lsTexture(lsTexture&& t);
        
        /**
         * Destructor
         * Releases all memory referenced by texId
         */
        ~lsTexture() {
            terminate();
        }
        
        /**
         * Copy Operator -- DELETED
         */
        lsTexture& operator=(const lsTexture&) = delete;
        
        /**
         * Move Operator -- DELETED
         */
        lsTexture& operator=(lsTexture&& t);
        
        inline unsigned getId() const {
            return texId;
        }
        
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
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, int internalFormat, int size, int format, int dataType, void* data);
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, int internalFormat, math::vec2i size, int format, int dataType, void* data);
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, int internalFormat, math::vec3i size, int format, int dataType, void* data);
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, int size, const lsImageResource&);
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, math::vec2i size, const lsImageResource&);
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, math::vec3i size, const lsImageResource&);
        
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
        inline ls_tex_desc_t getTextType() const;
        
        /**
         * Get the maximum texture size supported by OpenGL
         */
        static int getMaxTextureSize();
};

/******************************************************************************
 * Texture Data
 *****************************************************************************/
/**
 * Bind the current texture to OpenGL
 */

inline void lsTexture::bind() const {
    glBindTexture(dimensions, texId);
}

/**
 * Unbind the current texture to OpenGL
 */

inline void lsTexture::unbind() const {
    glBindTexture(dimensions, 0);
}

/**
 * Set a integer texture parameter.
 * Make sure that "bind()" has been called before using this method.
 */

inline void lsTexture::setParameter(int paramName, int param) const {
    glTexParameteri(dimensions, paramName, param);
}

/**
 * Set a float texture parameter.
 * Make sure that "bind()" has been called before using this method.
 */

inline void lsTexture::setParameter(int paramName, float param) const {
    glTexParameterf(dimensions, paramName, param);
}

/*
 * Create an OpenGL texture by using preexisting image data.
 */
inline bool lsTexture::init(int mipmapLevel, int size, const lsImageResource& resource) {
    return init(
        mipmapLevel, resource.getInternalFormat()[0], size,
        resource.getInternalFormat()[1], resource.getFormat(), resource.getData()
    );
}

/*
 * Create an OpenGL texture by using preexisting image data.
 */
inline bool lsTexture::init(int mipmapLevel, math::vec2i size, const lsImageResource& resource) {
    return init(
        mipmapLevel, resource.getInternalFormat()[0], size,
        resource.getInternalFormat()[1], resource.getFormat(), resource.getData()
    );
}

/*
 * Create an OpenGL texture by using preexisting image data.
 */
inline bool lsTexture::init(int mipmapLevel, math::vec3i size, const lsImageResource& resource) {
    return init(
        mipmapLevel, resource.getInternalFormat()[0], size,
        resource.getInternalFormat()[1], resource.getFormat(), resource.getData()
    );
}

/**
 * Modify the internal data of a texture.
 */

inline void lsTexture::modify(int offset, int size, int format, int dataType, void* data) {
    glTexSubImage1D(getTextType(), 0, offset, size, format, dataType, data);
    LOG_GL_ERR();
}

/**
 * Modify the internal data of a texture.
 */

inline void lsTexture::modify(math::vec2i offset, math::vec2i size, int format, int dataType, void* data) {
    glTexSubImage2D(getTextType(), 0, offset[0], offset[1], size[0], size[1], format, dataType, data);
    LOG_GL_ERR();
}

/**
 * Modify the internal data of a texture.
 */

inline void lsTexture::modify(math::vec3i offset, math::vec3i size, int format, int dataType, void* data) {
    glTexSubImage3D(getTextType(), 0, offset[0], offset[1], offset[2], size[0], size[1], size[2], format, dataType, data);
    LOG_GL_ERR();
}

/**
 * Release all memory referenced by *this.
 */

inline void lsTexture::terminate() {
    glDeleteTextures(1, &texId);
    texId = 0;
}

/**
 * Get the width of the texture referenced by texId
 */

inline unsigned lsTexture::getWidth() const {
    int w = 0;
    glGetTexLevelParameteriv(dimensions, 0, LS_TEX_WIDTH, &w);
    return w;
}

/**
 * Get the height of the texture referenced by texId
 */

inline unsigned lsTexture::getHeight() const {
    int h = 0;
    glGetTexLevelParameteriv(dimensions, 0, LS_TEX_HEIGHT, &h);
    return h;
}

/**
 * Get the depth of the texture referenced by texId
 */

inline unsigned lsTexture::getDepth() const {
    int d = 0;
    glGetTexLevelParameteriv(dimensions, 0, LS_TEX_DEPTH, &d);
    return d;
}

/**
 * Get the texture type of that this texture uses in OpenGL
 */

inline ls_tex_desc_t lsTexture::getTextType() const {
    return dimensions;
}

/**
 * Get the maximum texture size supported by OpenGL
 */

inline int lsTexture::getMaxTextureSize() {
    int maxTexSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
    return maxTexSize;
}

#endif	/* __LS_TEXTURE_H__ */
