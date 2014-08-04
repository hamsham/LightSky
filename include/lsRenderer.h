/* 
 * File:   lsRenderer.h
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

#endif	/* __LS_RENDERER_H__ */

