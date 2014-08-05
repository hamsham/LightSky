/* 
 * File:   lsDepthObject.h
 * Author: miles
 *
 * Created on August 4, 2014, 8:29 PM
 */

#ifndef __LS_DEPTH_OBJECT_H__
#define	__LS_DEPTH_OBJECT_H__

#include <GL/glew.h>

#include "lsColor.h"
#include "lsSetup.h"

//-----------------------------------------------------------------------------
//      Enumerations
//-----------------------------------------------------------------------------
enum ls_compare_func_t : int {
    LS_DEPTH_ALWAYS     = GL_ALWAYS,
    LS_DEPTH_NEVER      = GL_NEVER,
    LS_DEPTH_LESS       = GL_LESS,
    LS_DEPTH_EQUAL      = GL_EQUAL,
    LS_DEPTH_LEQUAL     = GL_LEQUAL,
    LS_DEPTH_GEQUAL     = GL_GEQUAL,
    LS_DEPTH_NEQUAL     = GL_NOTEQUAL
};

//-----------------------------------------------------------------------------
//      Classes
//-----------------------------------------------------------------------------
/**
 * The depth object id an artificial wrapper for depth buffer manipulation
 * within OpenGL. through this object, you can change the depth buffer's
 * state and parameters.
 */
class lsDepthObject {
    private:
        /**
         * Determine if depth testing should be enabled or disabled.
         */
        bool enabled = GL_FALSE;
        
        /**
         * clearVal is used to set the value of the depth buffer when it has
         * been cleared using "glClear(GL_DEPTH_BUFFER_BIT)." This value is
         * always clamped to a value between 0 and 1, according to the OpenGL
         * documentation.
         */
        double depthClearVal = 1.0;
        
        /**
         * Used to determine the if currently rendered fragment should be kept
         * by comparing it to the one rendered before. This member is applied
         * to the function "glDepthFunc()"
         */
        ls_compare_func_t depthFunc = LS_DEPTH_LESS;
        
        /**
         * A GLboolean flag that, used with glDepthMask(), determines if a
         * fragment should write to the depth buffer.
         */
        bool depthMask = GL_TRUE;
        
        /**
         * The near value that should be used by OpenGL's depth buffer. This
         * value will be clamped between 0.0 and 1.0. This helps determine if
         * a fragment is within the acceptable range of values that can be
         * rendered to the currently bound framebuffer.
         */
        double depthNear = 0.0;
        
        /**
         * The furthest normalized value that should be used by OpenGL's depth
         * buffer. This value will be clamped between 0.0 and 1.0. This helps
         * determine if a fragment is within the acceptable range of values
         * that can be rendered to the currently bound framebuffer.
         */
        double depthFar = 1.0;
        
    public:
        /**
         * Constructor
         * 
         * Creates an lsDepthObject using the default OpenGL depth parameters.
         */
        lsDepthObject() = default;
        
        /**
         * Copy Constructor
         * 
         * Copies all data from the input parameter into *this.
         * 
         * @param A constant reference to another lsDepthObject.
         */
        lsDepthObject(const lsDepthObject&) = default;
        
        /**
         * Move Constructor
         * 
         * Copies all data from the input parameter into *this.
         * 
         * @param A constant reference to another lsDepthObject.
         */
        lsDepthObject(lsDepthObject&&) = default;
        
        /**
         * Destructor
         * 
         * Does nothing.
         */
        ~lsDepthObject() = default;
        
        /**
         * Copy Operator
         * 
         * Copies all data from the input parameter into *this.
         * 
         * @param An R-Value reference to another lsDepthObject that is about
         * to go out of scope.
         */
        lsDepthObject& operator=(const lsDepthObject&) = default;
        
        /**
         * Move Operator
         * 
         * Copies all data from the input parameter into *this.
         * 
         * @param An R-Value reference to another lsDepthObject that is about
         * to go out of scope.
         */
        lsDepthObject& operator=(lsDepthObject&&) = default;
        
        /**
         * Bind all members to their associated depth parameters.
         */
        void bind() const;
        
        /**
         * Unbind all depth parameters used by *this and restore the default
         * depth parameters to OpenGL.
         * 
         * @note Don't use this function if another depth object is going to
         * be bound immediately afterwards. Doing so may cause a redundant
         * state change within OpenGL.
         */
        void unbind() const;
        
        /**
         * Reset all currently held depth parameters to OpenGL's defaults.
         */
        void reset();
        
        /**
         * Set whether depth testing should be enabled or disabled in the
         * current rendering state.
         * 
         * @param bool
         * A boolean value that will determine if OpenGL should have depth
         * testing enabled or disabled.
         */
        void setState(bool = GL_FALSE);
        
        /**
         * Determine whether depth testing should be enabled or disabled in the
         * current rendering state.
         * 
         * @return bool
         * A boolean value that will determine if OpenGL should have depth
         * testing enabled or disabled.
         */
        bool getState() const;
        
        /**
         * Set the value to be applied to the depth buffer after a call to
         * glClear(LS_DEPTH_BUFFER_BIT).
         * 
         * @param double
         * A double-precision float that will be clamped to the range of 0-1.
         */
        void setClearVal(double);
        
        /**
         * Get the value that's applied to the depth buffer when a call to
         * glClear(LS_DEPTH_BUFFER_BIT) has been made.
         * 
         * @return double
         * A double-precision float that will be clamped to the range of 0-1.
         */
        double getClearVal() const;
        
        /**
         * Set the function to be used when rendering fragments from the pixel
         * shader. This value helps to determine if fragments should be kept or
         * discarded.
         * 
         * @param ls_compare_func_t
         * The comparison function to be used when rendering pixel fragments.
         */
        void setDepthFunc(ls_compare_func_t = LS_DEPTH_LESS);
        
        /**
         * Get the depth-comparison function used by this depth object.
         * 
         * @return ls_compare_func_t
         * The comparison function to be used when rendering pixel fragments.
         */
        ls_compare_func_t getDepthFunc() const;
        
        /**
         * Set whether to enable writes to the depth buffer.
         * 
         * @param bool
         * If TRUE then writes to the depth buffer are enabled, if FALSE then
         * they will be disabled.
         */
        void setDepthMask(bool = GL_TRUE);
        
        /**
         * Determine if writes to the depth buffer are enabled.
         * 
         * @return bool
         * TRUE if depth buffer writes are enabled, or FALSE if not.
         */
        bool getDepthMask() const;
        
        /**
         * Set the near value that will be used by OpenGL's depth buffer.
         * This value will be clamped between 0.0 and 1.0.
         * 
         * @param near
         * Used to set the nearest renderable depth of a fragment output by the
         * pixel shader.
         */
        void setDepthNear(double near = 0.0);
        
        /**
         * Get the near value that will be used by OpenGL's depth buffer.
         * This value will be clamped between 0.0 and 1.0.
         * 
         * @return double
         * A double-precision floating point value that is used to determine if
         * a value is within the screen-space depth buffer.
         */
        double getDepthNear() const;
        
        /**
         * Set the far value that will be used by OpenGL's depth buffer.
         * This value will be clamped between 0.0 and 1.0.
         * 
         * @param double
         * A double-precision floating point value that will be used to
         * determine if a value is within the screen-space depth buffer.
         */
        void setDepthFar(double far = 1.0);
        
        /**
         * Get the far value that will be used by OpenGL's depth buffer.
         * This value will be clamped between 0.0 and 1.0.
         * 
         * @param far
         * Used to set the farthest renderable depth of a fragment output by
         * the pixel shader.
         */
        double getDepthFar();
        
        /**
         * Set both the the near and far values that will be used by OpenGL's
         * depth buffer to determine if a fragment is of renderable depth.
         * These value will be clamped between 0.0 and 1.0.
         * 
         * @param near
         * Used to set the nearest renderable depth of a fragment output by the
         * pixel shader.
         * 
         * @param far
         * Used to set the farthest renderable depth of a fragment output by
         * the pixel shader.
         */
        void setDepthRange(double near = 0.0, double far = 1.0);
};

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/*
 * Set whether depth testing should be enabled or disabled in the current
 * rendering state.
 */
inline void lsDepthObject::setState(bool state) {
    enabled = state;
}

/*
 * Determine whether this depth object should tell OpenGL to enable or disable
 * the use of depth testing.
 */
inline bool lsDepthObject::getState() const {
    return enabled;
}

/*
 * Set the value to be applied to the depth buffer after a call to
 * glClear(LS_DEPTH_BUFFER_BIT).
 */
inline void lsDepthObject::setClearVal(double clear) {
    depthClearVal = math::clamp(clear, 0.0, 1.0);
}

/*
 * Get the value that's applied to the depth buffer when a call to
 * glClear(LS_DEPTH_BUFFER_BIT) has been made.
 */
inline double lsDepthObject::getClearVal() const {
    return depthClearVal;
}

/*
 * Set the function to be used when rendering fragments from the pixel shader.
 */
inline void lsDepthObject::setDepthFunc(ls_compare_func_t func) {
    depthFunc = func;
}

/*
 * Get the depth-comparison function used by this depth object.
 */
inline ls_compare_func_t lsDepthObject::getDepthFunc() const {
    return depthFunc;
}

/*
 * Set whether to enable writes to the depth buffer.
 */
inline void lsDepthObject::setDepthMask(bool mask) {
    depthMask = mask;
}

/*
 * Determine if writes to the depth buffer are enabled.
 */
inline bool lsDepthObject::getDepthMask() const {
    return depthMask;
}

/*
 * Set the near value that will be used by OpenGL's depth buffer.
 */
inline void lsDepthObject::setDepthNear(double near) {
    depthNear = math::clamp(near, 0.0, 1.0);
}

/*
 * Get the near value that will be used by OpenGL's depth buffer.
 */
inline double lsDepthObject::getDepthNear() const {
    return depthNear;
}

/*
 * Set the far value that will be used by OpenGL's depth buffer.
 */
inline void lsDepthObject::setDepthFar(double far) {
    depthFar = math::clamp(far, 0.0, 1.0);
}

/*
 * Get the far value that will be used by OpenGL's depth buffer.
 */
inline double lsDepthObject::getDepthFar() {
    return depthFar;
}

/*
 * Set both the the near and far values that will be used by OpenGL's
 * depth buffer to determine if a fragment is of renderable depth.
 */
inline void lsDepthObject::setDepthRange(double near, double far) {
    depthNear = math::clamp(near, 0.0, 1.0);
    depthFar = math::clamp(far, 0.0, 1.0);
}


#endif	/* __LS_DEPTH_OBJECT_H__ */

