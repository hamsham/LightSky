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

enum ls_winding_t : int {
    LS_CW   = GL_CW,
    LS_CCW  = GL_CCW,
    
    LS_DEFAULT_WINDING = GL_CCW
};

enum ls_blend_eq_t : int {
    BLEND_ADD               = GL_FUNC_ADD,
    BLEND_SUBTRACT          = GL_FUNC_SUBTRACT,
    BLEND_REVERSE_SUBTRACT  = GL_FUNC_REVERSE_SUBTRACT,
    BLEND_MIN               = GL_MIN,
    BLEND_MAX               = GL_MAX,
    
    DEFAULT_BLEND_EQUATION  = GL_FUNC_ADD
};

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

/*
 * Forward declarations
 */
class lsDisplay;

/**
 * Renderer Object
 * On desktop platforms, this object strictly represents an OpenGL 3.3 context.
 * 
 * Only state-specific options are kept within this object.
 */
class lsRenderer final {
    
    friend class lsDisplay;
    
    private:
        const lsDisplay* pDisplay = nullptr;
        void* pContext = nullptr;
    
    public:
        constexpr lsRenderer() {}
        
        lsRenderer(const lsRenderer&) = delete;
        lsRenderer(lsRenderer&&);
        
        ~lsRenderer() {
            terminate();
        }
        
        lsRenderer& operator=(const lsRenderer&) = delete;
        lsRenderer& operator=(lsRenderer&&);
        
        bool init(const lsDisplay&);
        void terminate();
        
        inline void setViewport(const math::vec2i& pos, const math::vec2i& size) {
            glViewport(pos[0], pos[1], size[0], size[1]);
        }
        
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

///////////////////////////////////////////////////////////////////////////////
//      Polygon winding order
///////////////////////////////////////////////////////////////////////////////
inline void lsRenderer::setWindingOrder(ls_winding_t wo) {
    glFrontFace(wo);
    LOG_GL_ERR();
}

inline ls_winding_t lsRenderer::getWindingOrder() const {
    int wo;
    glGetIntegerv(GL_FRONT_FACE, &wo);
    return (ls_winding_t)wo;
}

///////////////////////////////////////////////////////////////////////////////
//      Face Culling
///////////////////////////////////////////////////////////////////////////////
inline void lsRenderer::setFaceCulling(bool fc) {
    fc == true ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    LOG_GL_ERR();
}

inline bool lsRenderer::getFaceCulling() const {
    bool faceCull;
    glGetBooleanv(GL_CULL_FACE, (GLboolean*)&faceCull);
    LOG_GL_ERR();
    return faceCull;
}

///////////////////////////////////////////////////////////////////////////////
//      Depth Testing
///////////////////////////////////////////////////////////////////////////////
inline void lsRenderer::setDepthTesting(bool dt) {
    dt == true ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

inline bool lsRenderer::getDepthTesting() const {
    bool depthTest;
    glGetBooleanv(GL_DEPTH_TEST, (GLboolean*)&depthTest);
    LOG_GL_ERR();
    return depthTest;
}

///////////////////////////////////////////////////////////////////////////////
// Blending
///////////////////////////////////////////////////////////////////////////////
/*
 * Determine the blending state
 */
inline void lsRenderer::setBlending(bool b) {
    b == true ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
}

inline bool lsRenderer::getBlending() const {
    bool blend;
    glGetBooleanv(GL_BLEND, (GLboolean*)&blend);
    LOG_GL_ERR();
    return blend;
}

/*
 * Determine the blend Equation
 */
inline void lsRenderer::setBlendEquation(ls_blend_eq_t be) {
    glBlendEquation(be);
}

inline void lsRenderer::setBlendEquationSeparate(ls_blend_eq_t rgbMode, ls_blend_eq_t alphaMode) {
    glBlendEquationSeparate(rgbMode, alphaMode);
}

inline ls_blend_eq_t lsRenderer::getBlendEquationRgb() const {
    int blendRgb;
    glGetIntegerv(GL_BLEND_EQUATION_RGB, &blendRgb);
    return (ls_blend_eq_t)blendRgb;
}

inline ls_blend_eq_t lsRenderer::getBlendEquationAlpha() const {
    int blendAlpha;
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &blendAlpha);
    return (ls_blend_eq_t)blendAlpha;
}

/*
 * Determine the blending function
 */
inline void lsRenderer::setBlendFunction(ls_blend_func_t srcFactor, ls_blend_func_t dstFactor) {
    glBlendFunc(srcFactor, dstFactor);
}

inline void lsRenderer::setBlendFunctionSeparate(
    ls_blend_func_t srcRgb, ls_blend_func_t dstRgb, ls_blend_func_t srcAlpha, ls_blend_func_t dstAlpha
) {
    glBlendFuncSeparate(srcRgb, dstRgb, srcAlpha, dstAlpha);
}

inline ls_blend_func_t lsRenderer::getBlendFunctionSrcRgb() const {
    int srcRgbFunc;
    glGetIntegerv(GL_BLEND_SRC_RGB, &srcRgbFunc);
    return (ls_blend_func_t)srcRgbFunc;
}

inline ls_blend_func_t lsRenderer::getBlendFunctionSrcAlpha() const {
    int srcAlphaFunc;
    glGetIntegerv(GL_BLEND_SRC_ALPHA, &srcAlphaFunc);
    return (ls_blend_func_t)srcAlphaFunc;
}

inline ls_blend_func_t lsRenderer::getBlendFunctionDstRgb() const {
    int dstRgbFunc;
    glGetIntegerv(GL_BLEND_DST_RGB, &dstRgbFunc);
    return (ls_blend_func_t)dstRgbFunc;
}

inline ls_blend_func_t lsRenderer::getBlendFunctionDstAlpha() const {
    int dstAlphaFunc;
    glGetIntegerv(GL_BLEND_DST_ALPHA, &dstAlphaFunc);
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
    glGetFloatv(GL_BLEND_COLOR, col.v);
    return col;
}

///////////////////////////////////////////////////////////////////////////////
//      Textures
///////////////////////////////////////////////////////////////////////////////
inline int lsRenderer::getMaxTextureSize() const {
    int maxTexSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
    return maxTexSize;
}

#endif	/* __LS_RENDERER_H__ */

