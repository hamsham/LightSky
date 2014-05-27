/* 
 * File:   renderer.h
 * Author: miles
 *
 * Created on May 17, 2014, 5:34 PM
 */

#ifndef __LS_RENDERER_H__
#define	__LS_RENDERER_H__

#include <Gl/glew.h>
#include "main.h"

enum draw_mode : int {
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
    
    DEFAULT_DRAW_MODE           = GL_TRIANGLES
};

enum winding_order : int {
    WINDING_ORDER_CW        = GL_CW,
    WINDING_ORDER_CCW       = GL_CCW,
    
    DEFAULT_WINDING_ORDER   = GL_CCW
};

enum blend_equation : int {
    BLEND_ADD               = GL_FUNC_ADD,
    BLEND_SUBTRACT          = GL_FUNC_SUBTRACT,
    BLEND_REVERSE_SUBTRACT  = GL_FUNC_REVERSE_SUBTRACT,
    BLEND_MIN               = GL_MIN,
    BLEND_MAX               = GL_MAX,
    
    DEFAULT_BLEND_EQUATION  = GL_FUNC_ADD
};

enum blend_func : int {
    BLEND_FUNC_ZERO                     = GL_ZERO,
    BLEND_FUNC_ONE                      = GL_ONE,
    BLEND_FUNC_SRC_COLOR                = GL_SRC_COLOR,
    BLEND_FUNC_ONE_MINUS_SRC_COLOR      = GL_ONE_MINUS_SRC_COLOR,
    BLEND_FUNC_DST_COLOR                = GL_DST_COLOR,
    BLEND_FUNC_ONE_MINUS_DST_COLOR      = GL_ONE_MINUS_DST_COLOR,
    BLEND_FUNC_SRC_ALPHA                = GL_SRC_ALPHA,
    BLEND_FUNC_ONE_MINUS_SRC_ALPHA      = GL_ONE_MINUS_SRC_ALPHA,
    BLEND_FUNC_DST_ALPHA                = GL_DST_ALPHA,
    BLEND_FUNC_ONE_MINUS_DST_ALPHA      = GL_ONE_MINUS_DST_ALPHA,
    BLEND_FUNC_CONST_COLOR              = GL_CONSTANT_COLOR,
    BLEND_FUNC_ONE_MINUS_CONST_COLOR    = GL_ONE_MINUS_CONSTANT_COLOR,
    BLEND_FUNC_CONST_ALPHA              = GL_CONSTANT_ALPHA,
    BLEND_FUNC_ONE_MINUS_CONST_ALPHA    = GL_ONE_MINUS_CONSTANT_ALPHA
};

/**
 * Renderer Object
 * On desktop platforms, this object strictly represents an OpenGL 3.3 context.
 * 
 * Only state-specific options are kept within this object.
 */
class renderer final {
    public:
        constexpr renderer() {
        }
        
        renderer(const renderer&) = delete;
        renderer(renderer&&) = delete;
        
        ~renderer() {
            terminate();
        }
        
        renderer& operator=(const renderer&) = delete;
        renderer& operator=(renderer&&) = delete;
        
        bool init();
        void terminate();
        
        void setWindingOrder(winding_order);
        winding_order getWindingOrder() const;
        
        void setFaceCulling(bool);
        bool getFaceCulling() const;
        
        void setDepthTesting(bool dt);
        bool getDepthTesting() const;
        
        void setBlending(bool d);
        bool getBlending() const;
        
        void setBlendEquation(blend_equation);
        void setBlendEquationSeparate(blend_equation rgbMode, blend_equation alphaMode);
        blend_equation getBlendEquationRgb() const;
        blend_equation getBlendEquationAlpha() const;
        
        void setBlendFunction(blend_func srcFactor, blend_func dstFactor);
        void setBlendFunctionSeparate(
            blend_func srcRgb, blend_func dstRgb, blend_func srcAlpha, blend_func dstAlpha
        );
        blend_func getBlendFunctionSrcRgb() const;
        blend_func getBlendFunctionSrcAlpha() const;
        blend_func getBlendFunctionDstRgb() const;
        blend_func getBlendFunctionDstAlpha() const;
        
        void setBlendColor(const math::vec4& rgba = math::vec4{0.f, 0.f, 0.f, 0.f});
        math::vec4 getBlendColor() const;
        
        int getMaxTextureSize() const;
};

///////////////////////////////////////////////////////////////////////////////
//      Polygon winding order
///////////////////////////////////////////////////////////////////////////////
inline void renderer::setWindingOrder(winding_order wo) {
    glFrontFace(wo);
    LOG_GL_ERR();
}

inline winding_order renderer::getWindingOrder() const {
    int wo;
    glGetIntegerv(GL_FRONT_FACE, &wo);
    return (winding_order)wo;
}

///////////////////////////////////////////////////////////////////////////////
//      Face Culling
///////////////////////////////////////////////////////////////////////////////
inline void renderer::setFaceCulling(bool fc) {
    fc == true ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    LOG_GL_ERR();
}

inline bool renderer::getFaceCulling() const {
    bool faceCull;
    glGetBooleanv(GL_CULL_FACE, (GLboolean*)&faceCull);
    LOG_GL_ERR();
    return faceCull;
}

///////////////////////////////////////////////////////////////////////////////
//      Depth Testing
///////////////////////////////////////////////////////////////////////////////
inline void renderer::setDepthTesting(bool dt) {
    dt == true ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

inline bool renderer::getDepthTesting() const {
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
inline void renderer::setBlending(bool b) {
    b == true ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
}

inline bool renderer::getBlending() const {
    bool blend;
    glGetBooleanv(GL_BLEND, (GLboolean*)&blend);
    LOG_GL_ERR();
    return blend;
}

/*
 * Determine the blend Equation
 */
inline void renderer::setBlendEquation(blend_equation be) {
    glBlendEquation(be);
}

inline void renderer::setBlendEquationSeparate(blend_equation rgbMode, blend_equation alphaMode) {
    glBlendEquationSeparate(rgbMode, alphaMode);
}

inline blend_equation renderer::getBlendEquationRgb() const {
    int blendRgb;
    glGetIntegerv(GL_BLEND_EQUATION_RGB, &blendRgb);
    return (blend_equation)blendRgb;
}

inline blend_equation renderer::getBlendEquationAlpha() const {
    int blendAlpha;
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &blendAlpha);
    return (blend_equation)blendAlpha;
}

/*
 * Determine the blending function
 */
inline void renderer::setBlendFunction(blend_func srcFactor, blend_func dstFactor) {
    glBlendFunc(srcFactor, dstFactor);
}

inline void renderer::setBlendFunctionSeparate(
    blend_func srcRgb, blend_func dstRgb, blend_func srcAlpha, blend_func dstAlpha
) {
    glBlendFuncSeparate(srcRgb, dstRgb, srcAlpha, dstAlpha);
}

inline blend_func renderer::getBlendFunctionSrcRgb() const {
    int srcRgbFunc;
    glGetIntegerv(GL_BLEND_SRC_RGB, &srcRgbFunc);
    return (blend_func)srcRgbFunc;
}

inline blend_func renderer::getBlendFunctionSrcAlpha() const {
    int srcAlphaFunc;
    glGetIntegerv(GL_BLEND_SRC_ALPHA, &srcAlphaFunc);
    return (blend_func)srcAlphaFunc;
}

inline blend_func renderer::getBlendFunctionDstRgb() const {
    int dstRgbFunc;
    glGetIntegerv(GL_BLEND_DST_RGB, &dstRgbFunc);
    return (blend_func)dstRgbFunc;
}

inline blend_func renderer::getBlendFunctionDstAlpha() const {
    int dstAlphaFunc;
    glGetIntegerv(GL_BLEND_DST_ALPHA, &dstAlphaFunc);
    return (blend_func)dstAlphaFunc;
}

/*
 * Determine the blending color
 */
inline void renderer::setBlendColor(const math::vec4& rgba) {
    glBlendColor(rgba[0], rgba[1], rgba[2], rgba[3]);
}

inline math::vec4 renderer::getBlendColor() const {
    math::vec4 col;
    glGetFloatv(GL_BLEND_COLOR, col.v);
    return col;
}

///////////////////////////////////////////////////////////////////////////////
//      Textures
///////////////////////////////////////////////////////////////////////////////
inline int renderer::getMaxTextureSize() const {
    int maxTexSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
    return maxTexSize;
}

#endif	/* __LS_RENDERER_H__ */

