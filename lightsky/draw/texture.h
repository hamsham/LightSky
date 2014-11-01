/* 
 * File:   draw/texture.h
 * Author: Miles Lacey
 *
 * Created on January 27, 2014, 8:35 PM
 */

#ifndef __LS_DRAW_TEXTURE_H__
#define	__LS_DRAW_TEXTURE_H__

#include <GL/glew.h>

#include "lightsky/draw/color.h"
#include "lightsky/draw/imageResource.h"
#include "lightsky/draw/setup.h"

namespace ls {
namespace draw {

/**----------------------------------------------------------------------------
 * Parameters for creating or modifying texture objects.
-----------------------------------------------------------------------------*/
enum tex_param_t : int {
    TEX_PARAM_INVALID       = -1,

    TEX_PARAM_WIDTH         = GL_TEXTURE_WIDTH,
    TEX_PARAM_HEIGHT        = GL_TEXTURE_HEIGHT,
    TEX_PARAM_DEPTH         = GL_TEXTURE_DEPTH,

    TEX_PARAM_MIN_FILTER    = GL_TEXTURE_MIN_FILTER,
    TEX_PARAM_MAG_FILTER    = GL_TEXTURE_MAG_FILTER,

    TEX_PARAM_WRAP_S        = GL_TEXTURE_WRAP_S,
    TEX_PARAM_WRAP_T        = GL_TEXTURE_WRAP_T,
    TEX_PARAM_WRAP_R        = GL_TEXTURE_WRAP_R,
    
    TEX_PARAM_CLAMP_EDGE    = GL_CLAMP_TO_EDGE,
    TEX_PARAM_CLAMP_BORDER  = GL_CLAMP_TO_BORDER,
    TEX_PARAM_REPEAT        = GL_REPEAT,
};

/**----------------------------------------------------------------------------
 * Framebuffer filtering specifiers
-----------------------------------------------------------------------------*/
enum tex_filter_t : int {
    TEX_FILTER_LINEAR            = GL_LINEAR,
    TEX_FILTER_NEAREST           = GL_NEAREST,
    
    TEX_FILTER_LINEAR_NEAREST    = GL_LINEAR_MIPMAP_NEAREST,
    TEX_FILTER_NEAREST_NEAREST   = GL_NEAREST_MIPMAP_NEAREST,
    
    TEX_FILTER_LINEAR_LINEAR     = GL_LINEAR_MIPMAP_LINEAR,
    TEX_FILTER_NEAREST_LINEAR    = GL_NEAREST_MIPMAP_LINEAR
};

/**----------------------------------------------------------------------------
 * Descriptors for different texture types
-----------------------------------------------------------------------------*/
enum tex_desc_t : int {
    TEX_DESC_1D     = GL_TEXTURE_1D,
    TEX_DESC_2D     = GL_TEXTURE_2D,
    TEX_DESC_3D     = GL_TEXTURE_3D,
    TEX_DESC_RECT   = GL_TEXTURE_RECTANGLE,
};

/**----------------------------------------------------------------------------
 * Texture Objects
-----------------------------------------------------------------------------*/
class texture {
    private:
        /**
         * Dimension is a constant which is initialized upon construction of
         * a texture object. This provides information to the GPU in order to
         * determine if *this is a 1D, 2D, 3D texture, and so on.
         */
        tex_desc_t dimensions;
        
        /**
         * Texture ID
         * The handle to the current texture used by OpenGL.
         */
        unsigned texId = 0;
        
    public:
        /**
         * @brief Constructor
         */
        texture(tex_desc_t td = TEX_DESC_2D);
        
        /**
         * @brief Copy Constructor -- DELETED
         */
        texture(const texture&) = delete;
        
        /**
         * @brief Move Constructor
         * 
         * Reassigns the texture ID at *this to the one referenced by the
         * source operand. Resets the source operand to 0.
         * 
         * @param t
         * An r-value reference to another texture object.
         */
        texture(texture&& t);
        
        /**
         * @brief Destructor
         * 
         * Releases all memory referenced by texId
         */
        ~texture();
        
        /**
         * @brief Copy Operator -- DELETED
         */
        texture& operator=(const texture&) = delete;
        
        /**
         * @brief Move Operator -- DELETED
         */
        texture& operator=(texture&& t);
        
        /**
         * Get the GPU-Assigned ID used by *this.
         * 
         * @return An unsigned integral type that correlates to a texture on
         * the GPU.
         */
        inline unsigned getId() const;
        
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
         * 
         * @param paramName
         * The name/type of texture parameter which should be modified on the
         * GPU.
         * 
         * @param param
         * The particular texture setting to use for *this.
         */
        inline void setParameter(int paramName, int param) const;
        
        /**
         * @brief Set a float texture parameter.
         * 
         * Make sure that "bind()" has been called before using this method.
         * 
         * @param paramName
         * The name/type of texture parameter which should be modified on the
         * GPU.
         * 
         * @param param
         * The particular texture setting to use for *this.
         */
        inline void setParameter(int paramName, float param) const;
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(
            int             mipmapLevel,
            pixel_format_t  internalFormat,
            int             size,
            pixel_layout_t  format,
            color_type_t    dataType,
            void* const     data
        );
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(
            int             mipmapLevel,
            pixel_format_t  internalFormat,
            math::vec2i     size,
            pixel_layout_t  format,
            color_type_t    dataType,
            void* const     data
        );
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(
            int              mipmapLevel,
            pixel_format_t   internalFormat,
            math::vec3i      size,
            pixel_layout_t   format,
            color_type_t     dataType,
            void* const      data
        );
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, int size, const imageResource&);
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, math::vec2i size, const imageResource&);
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, math::vec3i size, const imageResource&);
        
        /**
         * Modify the internal data of a texture.
         * 
         * @see OpenGL's documentation for glTexImage()
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
         * 
         * @return an unsigned integral type which indicates the size, in
         * pixels of the texture width used by *this.
         */
        inline unsigned getWidth() const;
        
        /**
         * Get the height of the texture referenced by texId.
         * 
         * @return an unsigned integral type which indicates the size, in
         * pixels of the texture height used by *this.
         */
        inline unsigned getHeight() const;
        
        /**
         * Get the depth of the texture referenced by texId.
         * 
         * @return an unsigned integral type which indicates the size, in
         * pixels of the texture depth used by *this.
         */
        inline unsigned getDepth() const;
        
        /**
         * Get the texture type of that this texture uses in OpenGL.
         * 
         * @return the GPU-descriptor that's used to apply *this texture object
         * onto polygons.
         */
        inline tex_desc_t getTextType() const;
        
        /**
         * Get the maximum texture size supported by OpenGL.
         * 
         * @return an integral type which can be used to determine the maximum
         * byte size of a texture supported by the GPU.
         */
        static int getMaxTextureSize();
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/texture_impl.h"

#endif	/* __LS_DRAW_TEXTURE_H__ */
