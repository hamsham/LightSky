/* 
 * File:   blendObject.h
 * Author: Miles Lacey
 *
 * Created on August 3, 2014, 6:53 PM
 */

#ifndef __LS_DRAW_BLEND_OBJECT_H__
#define	__LS_DRAW_BLEND_OBJECT_H__

#include <GL/glew.h>

#include "lightsky/draw/setup.h"
#include "lightsky/draw/color.h"

namespace ls {
namespace draw {

/*-----------------------------------------------------------------------------
    Enumerations
-----------------------------------------------------------------------------*/
/**
 * Blending equations that can be used when rendering.
 */
enum : int {
    LS_BLEND = GL_BLEND
};

/**
 * Blending colors
 */
enum blend_color_t : int {
    LS_BLEND_COLOR = GL_BLEND_COLOR
};

/**
 * Blending equations
 */
enum blend_equ_t : int {
    LS_BLEND_ADD            = GL_FUNC_ADD,
    LS_BLEND_SUB            = GL_FUNC_SUBTRACT,
    LS_BLEND_REV_SUB        = GL_FUNC_REVERSE_SUBTRACT,
    LS_BLEND_MIN            = GL_MIN,
    LS_BLEND_MAX            = GL_MAX,
    LS_DEFAULT_BLEND_EQU    = GL_FUNC_ADD
};

/**
 * Blending Equation Color
 */
enum blend_equ_color_t : int {
    LS_BLEND_EQUATION_RGB   = GL_BLEND_EQUATION_RGB,
    LS_BLEND_EQUATION_ALPHA = GL_BLEND_EQUATION_ALPHA
};

/**
 * Blend functions which help determine the type of blending that's applied to
 * a renderable object.
 */
enum blend_func_t : int {
    LS_ZERO                     = GL_ZERO,
    LS_ONE                      = GL_ONE,
    LS_SRC_COLOR                = GL_SRC_COLOR,
    LS_ONE_MINUS_SRC_COLOR      = GL_ONE_MINUS_SRC_COLOR,
    LS_DST_COLOR                = GL_DST_COLOR,
    LS_ONE_MINUS_DST_COLOR      = GL_ONE_MINUS_DST_COLOR,
    LS_SRC_ALPHA                = GL_SRC_ALPHA,
    LS_ONE_MINUS_SRC_ALPHA      = GL_ONE_MINUS_SRC_ALPHA,
    LS_DST_ALPHA                = GL_DST_ALPHA,
    LS_ONE_MINUS_DST_ALPHA      = GL_ONE_MINUS_DST_ALPHA,
    LS_CONST_COLOR              = GL_CONSTANT_COLOR,
    LS_ONE_MINUS_CONST_COLOR    = GL_ONE_MINUS_CONSTANT_COLOR,
    LS_CONST_ALPHA              = GL_CONSTANT_ALPHA,
    LS_ONE_MINUS_CONST_ALPHA    = GL_ONE_MINUS_CONSTANT_ALPHA
};

/**
 * Blending Function Color
 */
enum blend_func_color_t : int {
    LS_BLEND_SRC_RGB    = GL_BLEND_SRC_RGB,
    LS_BLEND_DST_RGB    = GL_BLEND_DST_RGB,
    LS_BLEND_SRC_ALPHA  = GL_BLEND_SRC_ALPHA,
    LS_BLEND_DST_ALPHA  = GL_BLEND_DST_ALPHA
};

/**----------------------------------------------------------------------------
 * The blend object manages the current blend state within OpenGL.
-----------------------------------------------------------------------------*/
class blendObject {
    private:
        /**
         * Determine if blending should be enabled or disabled. If blending is
         * disabled, no other blending parameters will be sent through the
         * rendering pipeline.
         */
        bool enabled = GL_FALSE;
        
        /**
         * The color to be used when performing blending operations in OpenGL.
         */
        color blendCol = lsBlank;
        
        /**
         * Class Member that's used to set the RGB blending equation in OpenGL.
         */
        blend_equ_t rgbBlendEq = LS_BLEND_ADD;
        
        /**
         * Class Member that's used to set the alpha blending equation in OpenGL
         */
        blend_equ_t alphaBlendEq = LS_BLEND_ADD;
        
        /**
         * Class Member that's used to set the source RGB blending function in
         * OpenGL.
         */
        blend_func_t srcRgbBlendFunc = LS_ONE;
        
        /**
         * Class Member that's used to set the destination RGB blending function
         * in OpenGL.
         */
        blend_func_t dstRgbBlendFunc = LS_ZERO;
        
        /**
         * Class Member that's used to set the source alpha blending function in
         * OpenGL.
         */
        blend_func_t srcAlphaBlendFunc = LS_ONE;
        
        /**
         * Class Member that's used to set the destination alpha blending
         * function in OpenGL.
         */
        blend_func_t dstAlphaBlendFunc = LS_ZERO;

    public:
        /**
         * @brief Constructor
         * 
         * Creates an blendObject using the default OpenGL blending
         * parameters.
         */
        blendObject() = default;
        
        /**
         * @brief Copy Constructor
         * 
         * Copies all data from the input parameter into *this.
         * 
         * @param A constant reference to another blendObject.
         */
        blendObject(const blendObject&) = default;
        
        /**
         * @brief Move Constructor
         * 
         * Moves all data from the input parameter into *this.
         * 
         * @param A constant reference to another blendObject.
         */
        blendObject(blendObject&&) = default;
        
        /**
         * @brief Destructor
         * 
         * Does nothing.
         */
        ~blendObject() = default;
        
        /**
         * @brief Copy Operator
         * 
         * Copies all data from the input parameter into *this.
         * 
         * @param An R-Value reference to another blendObject that is about
         * to go out of scope.
         */
        blendObject& operator=(const blendObject&) = default;
        
        /**
         * @brief Move Operator
         * 
         * Copies all data from the input parameter into *this.
         * 
         * @param An R-Value reference to another blendObject that is about
         * to go out of scope.
         */
        blendObject& operator=(blendObject&&) = default;
        
        /**
         * Enable blending in OpenGL and apply all stored parameters (blending
         * equations, functions, and color).
         */
        void bind() const;
        
        /**
         * @brief Disable Blending in OpenGL.
         * 
         * @note Don't use this function if another depth object is going to
         * be bound immediately afterwards. Doing so may cause a redundant
         * state change within OpenGL.
         */
        void unbind() const;
        
        /**
         * Reset all currently held blend parameters to OpenGL's defaults.
         */
        void reset();
        
        /**
         * Set whether blending should be enabled or disabled in the current
         * rendering state. If blending is disabled, no other blending
         * parameters will be sent through the rendering pipeline.
         * 
         * @param bool
         * A boolean value that will determine if OpenGL should have blending
         * enabled or disabled.
         */
        void setState(bool = GL_FALSE);
        
        /**
         * Determine whether this blending object should tell OpenGL to enable
         * or disable the use of blending.
         * 
         * @return bool
         * A boolean value that will determine if OpenGL should have blending
         * enabled or disabled.
         */
        bool getState() const;
        
        /**
         * Set the blending equation to be used within OpenGL.
         * 
         * @param rgbaMode
         * The blend equation that OpenGL should use internally.
         */
        void setBlendEquation(blend_equ_t rgbaMode = LS_BLEND_ADD);
        
        /**
         * Set the OpenGL blending equation, but with different values for RGB
         * and Alpha.
         * 
         * @param rgbMode
         * The RGB blending equation
         * 
         * @param alphaMode
         * The blending equation for the alpha channel.
         */
        void setBlendEquation(
            blend_equ_t rgbMode = LS_BLEND_ADD,
            blend_equ_t alphaMode = LS_BLEND_ADD
        );
        
        /**
         * Get the blending equation for the RGB channels.
         * 
         * @return blend_eq_t
         */
        blend_equ_t getBlendEquationRgb() const;
        
        /**
         * Get the blending equation for the alpha channel.
         * 
         * @return blend_eq_t
         */
        blend_equ_t getBlendEquationAlpha() const;
        
        /**
         * Set the source and destination blending function.
         * 
         * @param srcFactor
         * The blending function for the source RGBA channels.
         * 
         * @param dstFactor
         * The blending equation for the destination RGBA channels.
         */
        void setBlendFunction(
            blend_func_t srcFactor = LS_ONE,
            blend_func_t dstFactor = LS_ZERO
        );
        
        /**
         * Set the source and destination blending function, with separate RGB
         * and alpha functions.
         * 
         * @param srcFactorRgb
         * The blending function for the source RGB channels.
         * 
         * @param dstFactorRgb
         * The blending equation for the destination RGB channels.
         * 
         * @param srcFactorAlpha
         * The blending function for the source alpha channel.
         * 
         * @param dstFactorAlpha
         * The blending function for the destination alpha channel.
         */
        void setBlendFunction(
            blend_func_t srcFactorRgb = LS_ONE,
            blend_func_t dstFactorRgb = LS_ZERO,
            blend_func_t srcFactorAlpha = LS_ONE,
            blend_func_t dstFactorAlpha = LS_ZERO
        );
        
        /**
         * Get the current blend function from the source RGB channel
         * 
         * @return blend_equ_color_t
         */
        blend_func_t getBlendFunctionSrcRgb() const;
        
        /**
         * Get the current blend function from the source alpha channel
         * 
         * @return blend_equ_color_t
         */
        blend_func_t getBlendFunctionSrcAlpha() const;
        
        /**
         * Get the current blend function from the destination RGB channel
         * 
         * @return blend_equ_color_t
         */
        blend_func_t getBlendFunctionDstRgb() const;
        
        /**
         * Get the current blend function from the destination alpha channel
         * 
         * @return blend_equ_color_t
         */
        blend_func_t getBlendFunctionDstAlpha() const;
        
        /**
         * Set the color that OpenGL should use for blending
         * 
         * @param rgba
         * A constant reference to an color that should be used during
         * blending operations within OpenGL.
         */
        void setBlendColor(const color& rgba = lsBlank);
        
        /**
         * Get the current color that OpenGL is using for blending operations.
         * 
         * @return a group of four floating-point numbers, representing the
         * RGBA colors that OpenGL is using for blending.
         */
        color getBlendColor() const;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/blendObject_impl.h"

#endif	/* __LS_DRAW_BLEND_OBJECT_H__ */

