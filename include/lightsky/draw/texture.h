/* 
 * File:   draw/texture.h
 * Author: Miles Lacey
 *
 * Created on January 27, 2014, 8:35 PM
 */

#ifndef __LS_DRAW_TEXTURE_H__
#define	__LS_DRAW_TEXTURE_H__

#include "lightsky/draw/setup.h"
#include "lightsky/draw/color.h"
#include "lightsky/draw/imageResource.h"

namespace ls {
namespace draw {

/**----------------------------------------------------------------------------
 * Parameters for creating or modifying texture objects.
-----------------------------------------------------------------------------*/
enum tex_param_t : int {
    TEX_PARAM_INVALID       = -1,

    TEX_PARAM_MIN_FILTER    = GL_TEXTURE_MIN_FILTER,
    TEX_PARAM_MAG_FILTER    = GL_TEXTURE_MAG_FILTER,
    
    TEX_PARAM_MIN_LOD       = GL_TEXTURE_MIN_LOD,
    TEX_PARAM_MAX_LOD       = GL_TEXTURE_MAX_LOD,

    TEX_PARAM_WRAP_S        = GL_TEXTURE_WRAP_S,
    TEX_PARAM_WRAP_T        = GL_TEXTURE_WRAP_T,
    TEX_PARAM_WRAP_R        = GL_TEXTURE_WRAP_R,
    
    TEX_PARAM_CLAMP_EDGE    = GL_CLAMP_TO_EDGE,
    TEX_PARAM_REPEAT        = GL_REPEAT,
};

/**----------------------------------------------------------------------------
 * Framebuffer filtering specifiers
-----------------------------------------------------------------------------*/
enum tex_filter_t : int {
    TEX_FILTER_NEAREST           = GL_NEAREST,
    TEX_FILTER_LINEAR            = GL_LINEAR,
    
    TEX_FILTER_NEAREST_NEAREST   = GL_NEAREST_MIPMAP_NEAREST,
    TEX_FILTER_NEAREST_LINEAR    = GL_NEAREST_MIPMAP_LINEAR,
            
    TEX_FILTER_LINEAR_NEAREST    = GL_LINEAR_MIPMAP_NEAREST,
    TEX_FILTER_LINEAR_LINEAR     = GL_LINEAR_MIPMAP_LINEAR
};

/**----------------------------------------------------------------------------
 * Descriptors for different texture types
-----------------------------------------------------------------------------*/
enum tex_desc_t : int {
    TEX_DESC_2D         = GL_TEXTURE_2D,
    TEX_DESC_2D_ARRAY   = GL_TEXTURE_2D_ARRAY,
    TEX_DESC_3D         = GL_TEXTURE_3D,
    TEX_DESC_CUBE       = GL_TEXTURE_CUBE_MAP,
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
         * Create an OpenGL texture with no data.
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init();

        /**
         * @brief Create a 1D OpenGL texture in a similar manner as a
         * renderbuffer.
         *
         * This function delegates texture initialization by filling in default
         * parameters required by other functions.
         *
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(pixel_format_t internalFormat, int size);

        /**
         * @brief Create a 1D OpenGL texture in a similar manner as a
         * renderbuffer.
         *
         * This function delegates texture initialization by filling in default
         * parameters required by other functions.
         *
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(pixel_format_t internalFormat, const math::vec2i& size);

        /**
         * @brief Create a 3D OpenGL texture in a similar manner as a
         * renderbuffer.
         *
         * This function delegates texture initialization by filling in default
         * parameters required by other functions.
         *
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(pixel_format_t internalFormat, const math::vec3i& size);
        
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
            const math::vec2i& size,
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
            const math::vec3i& size,
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
        bool init(int mipmapLevel, const math::vec2i& size, const imageResource&);
        
        /**
         * Create an OpenGL texture by using preexisting image data.
         * 
         * @see OpenGL's documentation for glTexImage()
         * 
         * @return true if the operation was successful. False if otherwise.
         */
        bool init(int mipmapLevel, const math::vec3i& size, const imageResource&);
        
        /**
         * Modify the internal data of a texture.
         * 
         * @see OpenGL's documentation for glTexImage()
         */
        inline void modify(int offset, int size, int format, int dataType, void* data);
        
        /**
         * Modify the internal data of a texture.
         */
        inline void modify(const math::vec2i& offset, const math::vec2i& size, int format, int dataType, void* data);
        
        /**
         * Modify the internal data of a texture.
         */
        inline void modify(const math::vec3i& offset, const math::vec3i& size, int format, int dataType, void* data);
        
        /**
         * Release all memory referenced by *this.
         */
        inline void terminate();
        
        /**
         * Get the texture type of that this texture uses in OpenGL.
         * 
         * @return the GPU-descriptor that's used to apply *this texture object
         * onto polygons.
         */
        inline tex_desc_t getTexType() const;
        
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
