/* 
 * File:   renderer.h
 * Author: miles
 *
 * Created on May 17, 2014, 5:34 PM
 */

#ifndef __LS_RENDERER_H__
#define	__LS_RENDERER_H__

#include <Gl/glew.h>

#include "lsSetup.h"
#include "lsColor.h"
#include "lsDisplay.h"

//-----------------------------------------------------------------------------
//      Enumerations
//-----------------------------------------------------------------------------
/**
 * Draw modes for renderable types.
 */
enum ls_draw_t : int {
    LS_POINTS                   = GL_POINTS,
    
    LS_LINE_STRIP               = GL_LINE_STRIP,
    LS_LINE_LOOP                = GL_LINE_LOOP,
    LS_LINES                    = GL_LINES,
    LS_LINE_STRIP_ADJACENCY     = GL_LINE_STRIP_ADJACENCY,
    LS_LINES_ADJACENCY          = GL_LINES_ADJACENCY,
    LS_TRIANGLE_STRIP           = GL_TRIANGLE_STRIP,
    LS_TRIANGLE_FAN             = GL_TRIANGLE_FAN,
    LS_TRIANGLES                = GL_TRIANGLES,
    LS_TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
    LS_TRIANGLES_ADJACENCY      = GL_TRIANGLES_ADJACENCY,
    
    LS_DEFAULT_DRAW_MODE        = GL_TRIANGLES
};

/**
 * Winding order for polygons.
 * This also helps determine which faces won't be rendered if face culling is
 * enabled.
 */
enum ls_winding_t : int {
    LS_CW                       = GL_CW,
    LS_CCW                      = GL_CCW,
    LS_DEFAULT_WINDING          = GL_CCW
};

/**
 * Blending equations that can be used when rendering.
 */
enum : int {
    LS_BLEND                    = GL_BLEND
};

/**
 * Blending colors
 */
enum ls_blend_color_t : int {
    LS_BLEND_COLOR              = GL_BLEND_COLOR
};

/**
 * Blending equations
 */
enum ls_blend_eq_t : int {
    LS_BLEND_ADD                = GL_FUNC_ADD,
    LS_BLEND_SUB                = GL_FUNC_SUBTRACT,
    LS_BLEND_REV_SUB            = GL_FUNC_REVERSE_SUBTRACT,
    LS_BLEND_MIN                = GL_MIN,
    LS_BLEND_MAX                = GL_MAX,
    LS_DEFAULT_BLEND_EQU        = GL_FUNC_ADD
};

/**
 * Blending Equation Color
 */
enum ls_blend_equ_color_t : int {
    LS_BLEND_EQUATION_RGB       = GL_BLEND_EQUATION_RGB,
    LS_BLEND_EQUATION_ALPHA     = GL_BLEND_EQUATION_ALPHA
};

/**
 * Blend functions which help determine the type of blending that's applied to
 * a renderable object.
 */
enum ls_blend_func_t : int {
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
enum ls_blend_func_color_t : int {
    LS_BLEND_SRC_RGB            = GL_BLEND_SRC_RGB,
    LS_BLEND_DST_RGB            = GL_BLEND_DST_RGB,
    LS_BLEND_SRC_ALPHA          = GL_BLEND_SRC_ALPHA,
    LS_BLEND_DST_ALPHA          = GL_BLEND_DST_ALPHA
};

/**
 * Face culling modes for polygons.
 */
enum ls_cull_t : int {
    LS_CULL_FACE                = GL_CULL_FACE,
    LS_FRONT_FACE               = GL_FRONT,
    LS_BACK_FACE                = GL_BACK
};

/**
 * Display tests
 */
enum ls_test_t : int {
    LS_DEPTH_TEST               = GL_DEPTH_TEST,
    LS_STENCIL_TEST             = GL_STENCIL_TEST
};

//-----------------------------------------------------------------------------
//      Forward declarations
//-----------------------------------------------------------------------------
class lsDisplay;

//-----------------------------------------------------------------------------
//      Classes
//-----------------------------------------------------------------------------
/**
 * Renderer Object
 * On desktop platforms, this object strictly represents an OpenGL 3.3 context.
 * 
 * Only state-specific options are kept within this object.
 */
class lsRenderer final {
    public:
        
        /**
         * Set the size of the active viewport within the currently bound
         * framebuffer.
         * 
         * @param pos
         * The lower-left hand cornet of the active framebuffer.
         * 
         * @param size
         * The width and height of the desired viewport.
         */
        void setViewport(const math::vec2i& pos, const math::vec2i& size);
        
        void setWindingOrder(ls_winding_t);
        ls_winding_t getWindingOrder() const;
        
        void setFaceCulling(bool);
        bool getFaceCulling() const;
        
        void setDepthTesting(bool dt);
        bool getDepthTesting() const;
        
        void setBlending(bool d);
        bool getBlending() const;
        
        void setBlendEquation(ls_blend_eq_t);
        void setBlendEquationSeparate(ls_blend_eq_t rgbMode, ls_blend_eq_t alphaMode);
        ls_blend_eq_t getBlendEquationRgb() const;
        ls_blend_eq_t getBlendEquationAlpha() const;
        
        void setBlendFunction(ls_blend_func_t srcFactor, ls_blend_func_t dstFactor);
        void setBlendFunctionSeparate(
            ls_blend_func_t srcRgb, ls_blend_func_t dstRgb, ls_blend_func_t srcAlpha, ls_blend_func_t dstAlpha
        );
        ls_blend_func_t getBlendFunctionSrcRgb() const;
        ls_blend_func_t getBlendFunctionSrcAlpha() const;
        ls_blend_func_t getBlendFunctionDstRgb() const;
        ls_blend_func_t getBlendFunctionDstAlpha() const;
        
        void setBlendColor(const lsColor& rgba = lsBlank);
        lsColor getBlendColor() const;
        
        int getMaxTextureSize() const;
};

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/*
 * Set the active viewport size
 */        
inline void lsRenderer::setViewport(const math::vec2i& pos, const math::vec2i& size) {
    glViewport(pos[0], pos[1], size[0], size[1]);
}

inline void lsRenderer::setWindingOrder(ls_winding_t wo) {
    glFrontFace(wo);
    LOG_GL_ERR();
}

inline ls_winding_t lsRenderer::getWindingOrder() const {
    int wo;
    glGetIntegerv(LS_FRONT_FACE, &wo);
    return (ls_winding_t)wo;
}

inline void lsRenderer::setFaceCulling(bool fc) {
    fc == true ? glEnable(LS_CULL_FACE) : glDisable(LS_CULL_FACE);
    LOG_GL_ERR();
}

inline bool lsRenderer::getFaceCulling() const {
    bool faceCull;
    glGetBooleanv(LS_CULL_FACE, (GLboolean*)&faceCull);
    LOG_GL_ERR();
    return faceCull;
}

inline void lsRenderer::setDepthTesting(bool dt) {
    dt == true ? glEnable(LS_DEPTH_TEST) : glDisable(LS_DEPTH_TEST);
}

inline bool lsRenderer::getDepthTesting() const {
    bool depthTest;
    glGetBooleanv(LS_DEPTH_TEST, (GLboolean*)&depthTest);
    LOG_GL_ERR();
    return depthTest;
}

/*
 * Determine the blending state
 */
inline void lsRenderer::setBlending(bool b) {
    b == true ? glEnable(LS_BLEND) : glDisable(LS_BLEND);
}

inline bool lsRenderer::getBlending() const {
    bool blend;
    glGetBooleanv(LS_BLEND, (GLboolean*)&blend);
    LOG_GL_ERR();
    return blend;
}

/*
 * Determine the blend Equation
 */
inline void lsRenderer::setBlendEquation(ls_blend_eq_t be) {
    glBlendEquation(be);
}

inline void lsRenderer::setBlendEquationSeparate(
    ls_blend_eq_t rgbMode, ls_blend_eq_t alphaMode
) {
    glBlendEquationSeparate(rgbMode, alphaMode);
}

inline ls_blend_eq_t lsRenderer::getBlendEquationRgb() const {
    int blendRgb;
    glGetIntegerv(LS_BLEND_EQUATION_RGB, &blendRgb);
    return (ls_blend_eq_t)blendRgb;
}

inline ls_blend_eq_t lsRenderer::getBlendEquationAlpha() const {
    int blendAlpha;
    glGetIntegerv(LS_BLEND_EQUATION_ALPHA, &blendAlpha);
    return (ls_blend_eq_t)blendAlpha;
}

/*
 * Determine the blending function
 */
inline void lsRenderer::setBlendFunction(
    ls_blend_func_t srcFactor, ls_blend_func_t dstFactor
) {
    glBlendFunc(srcFactor, dstFactor);
}

inline void lsRenderer::setBlendFunctionSeparate(
    ls_blend_func_t srcRgb, ls_blend_func_t dstRgb,
    ls_blend_func_t srcAlpha, ls_blend_func_t dstAlpha
) {
    glBlendFuncSeparate(srcRgb, dstRgb, srcAlpha, dstAlpha);
}

inline ls_blend_func_t lsRenderer::getBlendFunctionSrcRgb() const {
    int srcRgbFunc;
    glGetIntegerv(LS_BLEND_SRC_RGB, &srcRgbFunc);
    return (ls_blend_func_t)srcRgbFunc;
}

inline ls_blend_func_t lsRenderer::getBlendFunctionSrcAlpha() const {
    int srcAlphaFunc;
    glGetIntegerv(LS_BLEND_SRC_ALPHA, &srcAlphaFunc);
    return (ls_blend_func_t)srcAlphaFunc;
}

inline ls_blend_func_t lsRenderer::getBlendFunctionDstRgb() const {
    int dstRgbFunc;
    glGetIntegerv(LS_BLEND_DST_RGB, &dstRgbFunc);
    return (ls_blend_func_t)dstRgbFunc;
}

inline ls_blend_func_t lsRenderer::getBlendFunctionDstAlpha() const {
    int dstAlphaFunc;
    glGetIntegerv(LS_BLEND_DST_ALPHA, &dstAlphaFunc);
    return (ls_blend_func_t)dstAlphaFunc;
}

/*
 * Determine the blending color
 */
inline void lsRenderer::setBlendColor(const lsColor& rgba) {
    glBlendColor(rgba[0], rgba[1], rgba[2], rgba[3]);
}

inline lsColor lsRenderer::getBlendColor() const {
    lsColor col;
    glGetFloatv(LS_BLEND_COLOR, col.v);
    return col;
}

#endif	/* __LS_RENDERER_H__ */

