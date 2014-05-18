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
    LS_TRIANGLES_ADJACENCY      = GL_TRIANGLES_ADJACENCY
};

enum winding_order : int {
    WINDING_ORDER_CW    = GL_CW,
    WINDING_ORDER_CCW   = GL_CCW,
    WINDING_ORDER_NONE  = -1
};

struct drawParams {
    draw_mode drawMode;
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
        
        void setFaceCulling(bool);
        bool getFaceCulling() const;
        
        void setDepthTesting(bool dt);
        bool getDepthTesting() const;
        
        void setBlending(bool d);
        bool getBlending() const;
};

inline void renderer::setWindingOrder(winding_order wo) {
    glFrontFace(wo);
    LOG_GL_ERR();
}

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

inline void renderer::setDepthTesting(bool dt) {
    dt == true ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

inline bool renderer::getDepthTesting() const {
    bool depthTest;
    glGetBooleanv(GL_DEPTH_TEST, (GLboolean*)&depthTest);
    LOG_GL_ERR();
    return depthTest;
}

inline void renderer::setBlending(bool b) {
    b == true ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
}

inline bool renderer::getBlending() const {
    bool blend;
    glGetBooleanv(GL_BLEND, (GLboolean*)&blend);
    LOG_GL_ERR();
    return blend;
}

#endif	/* __LS_RENDERER_H__ */

