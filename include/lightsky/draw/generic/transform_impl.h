
namespace ls {
namespace draw {

/*-------------------------------------
 * Check if the model matrix needs updating
-------------------------------------*/
inline bool transform::isDirty() const {
    return dirtyFlag;
}

/*-------------------------------------
 * Make the current transform require updating
-------------------------------------*/
inline void transform::setDirty() {
    dirtyFlag = true;
}

/*-------------------------------------
 * Get the current positionvoid
-------------------------------------*/
inline const math::vec3& transform::getPosition() const {
    return position;
}

/*-------------------------------------
 * Get the current scalevoid
-------------------------------------*/
inline const math::vec3& transform::getScale() const {
    return scaling;
}

/*-------------------------------------
 * Get the current orientationvoid
-------------------------------------*/
inline const math::quat& transform::getOrientation() const {
    return orientation;
}

/*-------------------------------------
 * Get the current model matrixvoid
-------------------------------------*/
inline const math::mat4& transform::getTransform() const {
    return modelMatrix;
}

} // end draw namespace
} // end ls namespace
