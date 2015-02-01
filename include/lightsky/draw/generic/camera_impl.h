
namespace ls {
namespace draw {

/*-------------------------------------
 * Create an orthographic camera
-------------------------------------*/
inline void camera::makeOrtho() {
    projMatrix = math::ortho(-aspectW, aspectW, -aspectH, aspectH, zNear, zFar);
}

/*-------------------------------------
 * Create an perspective-projection camera
-------------------------------------*/
inline void camera::makePerspective() {
    projMatrix = math::perspective(fov, aspectW/aspectH, zNear, zFar);
}

/*-------------------------------------
 * Get the camera position
-------------------------------------*/
inline const math::vec3& camera::getPosition() const {
    return pos;
}

/*-------------------------------------
 * Set the camera position
-------------------------------------*/
inline void camera::setPosition(const math::vec3& p) {
    pos = p;
}

/*-------------------------------------
 * Get the forward direction
-------------------------------------*/
inline const math::vec3& camera::getDirection() const {
    return zAxis;
}

/*-------------------------------------
 * Set the camera's direction
-------------------------------------*/
inline void camera::setDirection(const math::vec3& d) {
    lookAt(d);
}

/*-------------------------------------
 * Get the view direction (arcball movement)
-------------------------------------*/
inline const math::vec3& camera::getTarget() const {
    return target;
}

/*-------------------------------------
 * Set the camera direction (arcball)
-------------------------------------*/
inline void camera::setTarget(const math::vec3& t) {
    target = t;
}

/*-------------------------------------
 * Retrieve the camera's up vector
-------------------------------------*/
inline const math::vec3& camera::getUpDirection() const {
    return yAxis;
}

/*-------------------------------------
 * Determine which direction is up
-------------------------------------*/
inline void camera::setUpDirection(const math::vec3& up) {
    yAxis = up;
}

/*-------------------------------------
 * Get the camera view matrix
-------------------------------------*/
inline const math::mat4& camera::getViewMatrix() const {
    return viewMatrix;
}

/*-------------------------------------
 * Get the projection matrix
-------------------------------------*/
inline const math::mat4& camera::getProjMatrix() const {
    return projMatrix;
}

/*-------------------------------------
 * Generate and return the View/Projection matrix
-------------------------------------*/
inline math::mat4 camera::getVPMatrix() const {
    return projMatrix*viewMatrix;
}

/*-------------------------------------
 * Get the camera's orientation
-------------------------------------*/
inline const math::quat& camera::getOrientation() const {
    return orientation;
}

/*-------------------------------------
 * Set the camera's rotation orientation.
-------------------------------------*/
inline void camera::setOrientation(const math::quat& o) {
    orientation = o;
}

/*-------------------------------------
 * Set the aspect ratio
-------------------------------------*/
inline void camera::setAspectRatio(float w, float h) {
    aspectW = w; aspectH = h;
}

/*-------------------------------------
 * Get the current aspect ratio.
-------------------------------------*/
inline float camera::getAspectRatio() const {
    return aspectW / aspectH;
}

/*-------------------------------------
 * Get the current aspect width.
-------------------------------------*/
inline float camera::getAspectWidth() const {
    return aspectW;
}

/*-------------------------------------
 * Get the current aspect height.
-------------------------------------*/
inline float camera::getAspectHeight() const {
    return aspectH;
}

/*-------------------------------------
 * Set the near plane distance
-------------------------------------*/
inline void camera::setNearPlane(float inZNear) {
    zNear = inZNear;
}

/*-------------------------------------
 * Get the near plane distance
-------------------------------------*/
inline float camera::getNearPlane() const {
    return zNear;
}

/*-------------------------------------
 * Set the far plane distance
-------------------------------------*/
inline void camera::setFarPlane(float inZFar) {
    zFar = inZFar;
}

/*-------------------------------------
 * Get the distance to the far plane.
-------------------------------------*/
inline float camera::getFarPlane() const {
    return zFar;
}

/*-------------------------------------
 * Set the perspective mode.
-------------------------------------*/
inline void camera::setViewMode(camera_view_t m) {
    viewMode = m;
}

/*-------------------------------------
 * Retrieve the current perspective mode.
-------------------------------------*/
inline camera_view_t camera::getViewMode() const {
    return viewMode;
}

/*-------------------------------------
 * Look At function from the current cam position
-------------------------------------*/
inline void camera::lookAt(const math::vec3& point) {
    lookAt(pos, point, yAxis);
}

/*-------------------------------------
 * Camera Rotation function
-------------------------------------*/
inline void camera::rotate(const math::vec3& amount) {
    (this->*rotateFunction)(amount);
}

} // end draw namespace
} // end ls namespace
