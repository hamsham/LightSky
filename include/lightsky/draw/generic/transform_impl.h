
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
 * Get the current position
-------------------------------------*/
inline const math::vec3& transform::getPosition() const {
    return position;
}

/*-------------------------------------
 * Get the absolute position
-------------------------------------*/
inline math::vec3 transform::getAbsolutePosition() const {
    return math::vec3{modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]};
}

/*-------------------------------------
 * Get the current scale
-------------------------------------*/
inline const math::vec3& transform::getScale() const {
    return scaling;
}

/*-------------------------------------
 * Get the current orientation
-------------------------------------*/
inline const math::quat& transform::getOrientation() const {
    return orientation;
}

/*-------------------------------------
 * Get the current model matrix
-------------------------------------*/
inline const math::mat4& transform::getTransform() const {
    return modelMatrix;
}

} // end draw namespace
} // end ls namespace
