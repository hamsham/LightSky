/* 
 * File:   lsColor.h
 * Author: miles
 *
 * Created on June 2, 2014, 8:12 PM
 */

#ifndef __LS_COLOR_H__
#define	__LS_COLOR_H__

#include <GL/glew.h>

#include "lsSetup.h"

//-----------------------------------------------------------------------------
//      Enumerations
//-----------------------------------------------------------------------------
/**
 * Data types used within each pixel of a texture or framebuffer
 */
enum ls_color_type_t : int {
    LS_BYTE             = GL_BYTE,
    LS_SHORT            = GL_SHORT,
    LS_INT              = GL_INT,
    
    LS_FLOAT            = GL_FLOAT,
    LS_DOUBLE           = GL_DOUBLE,
    
    LS_UNSIGNED_BYTE    = GL_UNSIGNED_BYTE,
    LS_UNSIGNED_SHORT   = GL_UNSIGNED_SHORT,
    LS_UNSIGNED_INT     = GL_UNSIGNED_INT,
    
    LS_DEFAULT_COLOR_TYPE = GL_UNSIGNED_BYTE,
    LS_INVALID_COLOR_TYPE = -1
};

/**
 * GPU-side pixel formats.
 * OpenGL refers to these as the "format" parameter when using operations such
 * as "glTexImage()."
 */
enum ls_pixel_layout_t : int {
    LS_GRAY             = GL_DEPTH_COMPONENT,
    LS_RG               = GL_RG,
    LS_RGB              = GL_BGR,
    LS_RGBA             = GL_BGRA,
    
    LS_DEFAULT_PIXEL_LAYOUT = GL_BGR,
    LS_INVALID_PIXEL_LAYOUT = -1
};

/**
 * CPU-Side pixel formats.
 * OpenGL refers to these types as the "internalFormat" parameter in functions
 * such as "glRenderbufferStorage()" and "glTexImage()"
 */
enum ls_pixel_format_t : int {
    LS_GRAY_8           = GL_DEPTH_COMPONENT,
    LS_RG_8             = GL_RG8,
    LS_RGB_8            = GL_RGB8,
    LS_RGBA_8           = GL_RGBA8,
    
    LS_GRAY_16I         = GL_DEPTH_COMPONENT16,
    LS_RG_16I           = GL_RG16I,
    LS_RGB_16I          = GL_RGB16I,
    LS_RGBA_16I         = GL_RGBA16I,
    
    LS_GRAY_16U         = GL_DEPTH_COMPONENT16,
    LS_RG_16U           = GL_RG16UI,
    LS_RGB_16U          = GL_RGB16UI,
    LS_RGBA_16U         = GL_RGBA16UI,
    
    LS_GRAY_32I         = GL_DEPTH_COMPONENT32,
    LS_RG_32I           = GL_RG32I,
    LS_RGB_32I          = GL_RGB32I,
    LS_RGBA_32I         = GL_RGBA32I,
    
    LS_GRAY_32U         = GL_DEPTH_COMPONENT32,
    LS_RG_32U           = GL_RG32UI,
    LS_RGB_32U          = GL_RGB32UI,
    LS_RGBA_32U         = GL_RGBA32UI,
    
    LS_GRAY_16F         = GL_R16F,
    LS_RG_16F           = GL_RG16F,
    LS_RGB_16F          = GL_RGB16F,
    LS_RGBA_16F         = GL_RGBA16F,
    
    LS_GRAY_32F         = GL_DEPTH_COMPONENT32F,
    LS_RG_32F           = GL_RG32F,
    LS_RGB_32F          = GL_RGB32F,
    LS_RGBA_32F         = GL_RGBA32F,
    
    LS_DEFAULT_PIXEL_FORMAT = GL_RGB,
    LS_INVALID_PIXEL_FORMAT = -1
};

//-----------------------------------------------------------------------------
//      Typedefs
//-----------------------------------------------------------------------------
typedef math::vec4_t<unsigned char>     lsColorub;
typedef math::vec4_t<unsigned short>    lsColorus;
typedef math::vec4_t<unsigned int>      lsColorui;
typedef math::vec4_t<float>             lsColorf;

typedef lsColorf lsColor;

//-----------------------------------------------------------------------------
//      Color Types
//-----------------------------------------------------------------------------
#define lsBlank         lsColor{0.f, 0.f, 0.f, 0.f}

// Primary Colors
#define lsRed           lsColor{1.f, 0.f, 0.f, 1.f}
#define lsGreen         lsColor{0.f, 1.f, 0.f, 1.f}
#define lsBlue          lsColor{0.f, 0.f, 1.f, 1.f}

//Secondary Colors
#define lsMagenta       lsColor{1.f, 0.f, 1.f, 1.f}
#define lsYellow        lsColor{1.f, 1.f, 0.f, 1.f}
#define lsCyan          lsColor{0.f, 1.f, 1.f, 1.f}

// Monochrome
#define lsBlack         lsColor{0.f, 0.f, 0.f, 1.f}
#define lsWhite         lsColor{1.f, 1.f, 1.f, 1.f}
#define lsGray          lsColor{0.5f, 0.5f, 0.5f, 1.f}

#endif	/* __LS_COLOR_H__ */

