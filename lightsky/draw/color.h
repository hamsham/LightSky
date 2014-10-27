/* 
 * File:   draw/color.h
 * Author: Miles Lacey
 *
 * Created on June 2, 2014, 8:12 PM
 */

#ifndef __LS_DRAW_COLOR_H__
#define	__LS_DRAW_COLOR_H__

#include <GL/glew.h>

#include "lightsky/draw/setup.h"

namespace ls {
namespace draw {

/*-----------------------------------------------------------------------------
    Enumerations
-----------------------------------------------------------------------------*/
/**
 * @brief Framebuffer/Texture data types.
 * 
 * These enumerations are used to specify the basic data type each pixel of a
 * texture or framebuffer.
 */
enum color_type_t : int {
    COLOR_TYPE_BYTE             = GL_BYTE,
    COLOR_TYPE_SHORT            = GL_SHORT,
    COLOR_TYPE_INT              = GL_INT,
    
    COLOR_TYPE_FLOAT            = GL_FLOAT,
    COLOR_TYPE_DOUBLE           = GL_DOUBLE,
    
    COLOR_TYPE_UNSIGNED_BYTE    = GL_UNSIGNED_BYTE,
    COLOR_TYPE_UNSIGNED_SHORT   = GL_UNSIGNED_SHORT,
    COLOR_TYPE_UNSIGNED_INT     = GL_UNSIGNED_INT,
    
    COLOR_TYPE_DEFAULT          = GL_UNSIGNED_BYTE,
    COLOR_TYPE_INVALID          = -1
};

/**
 * @brief GPU-side pixel formats.
 * 
 * OpenGL refers to these as the "format" parameter when using operations such
 * as "glTexImage()."
 */
enum pixel_layout_t : int {
    LS_GRAY             = GL_DEPTH_COMPONENT,
    LS_R                = GL_RED,
    LS_RG               = GL_RG,
    LS_RGB              = GL_BGR,
    LS_RGBA             = GL_BGRA,
    
    LS_DEFAULT_PIXEL_LAYOUT = GL_BGR,
    LS_INVALID_PIXEL_LAYOUT = -1
};

/**
 * @brief CPU-Side pixel formats
 * 
 * OpenGL refers to these types as the "internalFormat" parameter in functions
 * such as "glRenderbufferStorage()" and "glTexImage()"
 */
enum pixel_format_t : int {
    LS_GRAY_8           = GL_DEPTH_COMPONENT,
    LS_R_8              = GL_R8,
    LS_RG_8             = GL_RG8,
    LS_RGB_8            = GL_RGB8,
    LS_RGBA_8           = GL_RGBA8,
    
    LS_GRAY_16I         = GL_DEPTH_COMPONENT16,
    LS_R_16I            = GL_R16I,
    LS_RG_16I           = GL_RG16I,
    LS_RGB_16I          = GL_RGB16I,
    LS_RGBA_16I         = GL_RGBA16I,
    
    LS_GRAY_16U         = GL_DEPTH_COMPONENT16,
    LS_R_16U            = GL_R16UI,
    LS_RG_16U           = GL_RG16UI,
    LS_RGB_16U          = GL_RGB16UI,
    LS_RGBA_16U         = GL_RGBA16UI,
    
    LS_GRAY_32I         = GL_DEPTH_COMPONENT32,
    LS_R_32I            = GL_R32I,
    LS_RG_32I           = GL_RG32I,
    LS_RGB_32I          = GL_RGB32I,
    LS_RGBA_32I         = GL_RGBA32I,
    
    LS_GRAY_32U         = GL_DEPTH_COMPONENT32,
    LS_R_32U            = GL_R32UI,
    LS_RG_32U           = GL_RG32UI,
    LS_RGB_32U          = GL_RGB32UI,
    LS_RGBA_32U         = GL_RGBA32UI,
    
    LS_GRAY_16F         = GL_R16F,
    LS_R_8F             = GL_R16F,
    LS_RG_16F           = GL_RG16F,
    LS_RGB_16F          = GL_RGB16F,
    LS_RGBA_16F         = GL_RGBA16F,
    
    LS_GRAY_32F         = GL_DEPTH_COMPONENT32F,
    LS_R_32F            = GL_R32F,
    LS_RG_32F           = GL_RG32F,
    LS_RGB_32F          = GL_RGB32F,
    LS_RGBA_32F         = GL_RGBA32F,
    
    LS_SRGB             = GL_SRGB,
    LS_SRGB_8           = GL_SRGB8,
    LS_SRGBA            = GL_SRGB_ALPHA,
    LS_SRGBA_8          = GL_SRGB8_ALPHA8,
    
    LS_R_C              = GL_COMPRESSED_RED,
    LS_RG_C             = GL_COMPRESSED_RG,
    LS_RGB_C            = GL_COMPRESSED_RGB,
    LS_RGBA_C           = GL_COMPRESSED_RGBA,
    
    LS_DEFAULT_PIXEL_FORMAT = GL_RGB,
    LS_INVALID_PIXEL_FORMAT = -1
};

/*-----------------------------------------------------------------------------
    Useful Typedefs
-----------------------------------------------------------------------------*/
typedef math::vec4_t<unsigned char>     colorub;
typedef math::vec4_t<unsigned short>    colorus;
typedef math::vec4_t<unsigned int>      colorui;
typedef math::vec4_t<float>             colorf;

typedef colorf color;

/*-----------------------------------------------------------------------------
    Color Types
-----------------------------------------------------------------------------*/
static constexpr color lsBlank      = color{0.f, 0.f, 0.f, 0.f};

// Primary Colors
static constexpr color lsRed        = color{1.f, 0.f, 0.f, 1.f};
static constexpr color lsGreen      = color{0.f, 1.f, 0.f, 1.f};
static constexpr color lsBlue       = color{0.f, 0.f, 1.f, 1.f};

//Secondary Colors
static constexpr color lsMagenta    = color{1.f, 0.f, 1.f, 1.f};
static constexpr color lsYellow     = color{1.f, 1.f, 0.f, 1.f};
static constexpr color lsCyan       = color{0.f, 1.f, 1.f, 1.f};

// Monochrome
static constexpr color lsBlack      = color{0.f, 0.f, 0.f, 1.f};
static constexpr color lsWhite      = color{1.f, 1.f, 1.f, 1.f};
static constexpr color lsGray       = color{0.5f, 0.5f, 0.5f, 1.f};

} // end draw namespace
} // end ls namespace

#endif	/* __LS_DRAW_COLOR_H__ */
