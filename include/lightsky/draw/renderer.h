/* 
 * File:   draw/renderer.h
 * Author: Miles Lacey
 *
 * Created on May 17, 2014, 5:34 PM
 */

#ifndef __LS_DRAW_RENDERER_H__
#define	__LS_DRAW_RENDERER_H__

#include "lightsky/draw/setup.h"
#include "lightsky/draw/color.h"

namespace ls {
namespace draw {

/**----------------------------------------------------------------------------
 * @brief Winding order for polygons.
 * This also helps determine which faces won't be rendered if face culling is
 * enabled.
-----------------------------------------------------------------------------*/
enum winding_order_t : int {
    WINDING_ORDER_CW        = GL_CW,
    WINDING_ORDER_CCW       = GL_CCW,
    WINDING_ORDER_DEFAULT   = GL_CCW
};

/**----------------------------------------------------------------------------
 * Face culling modes for polygons.
-----------------------------------------------------------------------------*/
enum face_cull_t : int {
    FACE_CULL       = GL_CULL_FACE,
    FACE_CULL_FRONT = GL_FRONT,
    FACE_CULL_BACK  = GL_BACK
};

/**
 * Display tests
 */
enum render_test_t : int {
    RENDER_TEST_DEPTH   = GL_DEPTH_TEST,
    RENDER_TEST_STENCIL = GL_STENCIL_TEST
};

/*-----------------------------------------------------------------------------
    Forward declarations
-----------------------------------------------------------------------------*/
class display;

/**----------------------------------------------------------------------------
 * @brief Renderer Object
 * On desktop platforms, this object strictly represents an OpenGL 3.3 context.
 * 
 * Only state-specific options are kept within this object.
-----------------------------------------------------------------------------*/
class renderer final {
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
        
        /**
         * Set the winding order for all rendered polygons.
         * 
         * @param wo
         * An enumeration of winding_order_t, indicating whether polygons are
         * to be rendered with their front faces as clockwise or counter-
         * clockwise.
         */
        void setWindingOrder(winding_order_t wo);
        
        /**
         * Retrieve the current winding order of rendered polygons.
         * 
         * @return
         * An enumeration of winding_order_t, indicating whether polygons are
         * to be rendered with their front faces as clockwise or counter-
         * clockwise.
         */
        winding_order_t getWindingOrder() const;
        
        /**
         * Set a boolean flag to determine if the current renderer should cull
         * polygon faces or not.
         * 
         * @param shouldCull
         * A boolean flag that determines whether the renderer should cull
         * rendered polygon faces or not.
         */
        void setFaceCulling(bool shouldCull);
        
        /**
         * Get a boolean flag which tells if the current renderer is culling
         * polygon faces or not.
         * 
         * @return a boolean flag that determines whether the renderer is
         * culling polygon faces or not.
         */
        bool getFaceCulling() const;
        
        /**
         * Enable depth testing of rendered polygons. Depth testing can be used
         * to render close polygons in front of distant ones.
         * 
         * @param dt
         * A boolean flag which can be used to enable depth testing (if TRUE)
         * or disable it.
         */
        void setDepthTesting(bool dt);
        
        /**
         * Determine if depth testing is enabled for all rendered polygons.
         * 
         * @return a boolean flag which can be used to determine if depth
         * testing is enabled (if TRUE) or disabled.
         */
        bool getDepthTesting() const;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/renderer_impl.h"

#endif	/* __LS_DRAW_RENDERER_H__ */
