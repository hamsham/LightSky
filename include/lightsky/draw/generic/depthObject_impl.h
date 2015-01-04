
namespace ls {
namespace draw {

/*-------------------------------------
    Set whether depth testing should be enabled or disabled in the current
    rendering state.
-------------------------------------*/
inline void depthObject::setState(bool state) {
    enabled = state;
}

/*-------------------------------------
    Determine whether this depth object should tell OpenGL to enable or disable
    the use of depth testing.
---------------------------------------*/
inline bool depthObject::getState() const {
    return enabled;
}

/*-------------------------------------
    Set the value to be applied to the depth buffer after a call to
    glClear(LS_DEPTH_BUFFER_BIT).
---------------------------------------*/
inline void depthObject::setClearVal(float clear) {
    depthClearVal = math::clamp(clear, 0.f, 1.f);
}

/*-------------------------------------
    Get the value that's applied to the depth buffer when a call to
    glClear(LS_DEPTH_BUFFER_BIT) has been made.
---------------------------------------*/
inline float depthObject::getClearVal() const {
    return depthClearVal;
}

/*-------------------------------------
    Set the function to be used when rendering fragments from the pixel shader.
---------------------------------------*/
inline void depthObject::setDepthFunc(compare_func_t func) {
    depthFunc = func;
}

/*-------------------------------------
    Get the depth-comparison function used by this depth object.
---------------------------------------*/
inline compare_func_t depthObject::getDepthFunc() const {
    return depthFunc;
}

/*-------------------------------------
    Set whether to enable writes to the depth buffer.
---------------------------------------*/
inline void depthObject::setDepthMask(bool mask) {
    depthMask = mask;
}

/*-------------------------------------
    Determine if writes to the depth buffer are enabled.
---------------------------------------*/
inline bool depthObject::getDepthMask() const {
    return depthMask;
}

/*-------------------------------------
    Set the near value that will be used by OpenGL's depth buffer.
---------------------------------------*/
inline void depthObject::setDepthNear(float near) {
    depthNear = math::clamp(near, 0.f, 1.f);
}

/*-------------------------------------
    Get the near value that will be used by OpenGL's depth buffer.
---------------------------------------*/
inline float depthObject::getDepthNear() const {
    return depthNear;
}

/*-------------------------------------
    Set the far value that will be used by OpenGL's depth buffer.
---------------------------------------*/
inline void depthObject::setDepthFar(float far) {
    depthFar = math::clamp(far, 0.f, 1.f);
}

/*-------------------------------------
    Get the far value that will be used by OpenGL's depth buffer.
---------------------------------------*/
inline float depthObject::getDepthFar() {
    return depthFar;
}

/*-------------------------------------
    Set both the the near and far values that will be used by OpenGL's
    depth buffer to determine if a fragment is of renderable depth.
---------------------------------------*/
inline void depthObject::setDepthRange(float near, float far) {
    depthNear = math::clamp(near, 0.f, 1.f);
    depthFar = math::clamp(far, 0.f, 1.f);
}

} // end draw namespace
} // end ls namespace
