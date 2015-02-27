
namespace ls {
namespace draw {

/*-------------------------------------
 * Create an orthographic camera
-------------------------------------*/
inline void camera::makeOrtho() {
    projMatrix = math::ortho(0.f, aspectW, 0.f, aspectH, zNear, zFar);
}

/*-------------------------------------
 * Create an perspective-projection camera
-------------------------------------*/
inline void camera::makePerspective() {
    projMatrix = math::perspective(fov, aspectW/aspectH, zNear, zFar);
}

/*-------------------------------------
 * Get the camera view mode
-------------------------------------*/
inline camera_mode_t camera::getViewMode() const {
    return viewMode;
}

/*-------------------------------------
 * Get the camera position
-------------------------------------*/
inline const math::vec3& camera::getPosition() const {
    return viewTransform.getPosition();
}

/*-------------------------------------
 * Get the absolute view position
-------------------------------------*/
inline math::vec3 camera::getAbsolutePosition() const {
    return viewTransform.getAbsolutePosition();
}

/*-------------------------------------
 * Set the camera position
-------------------------------------*/
inline void camera::setPosition(const math::vec3& p) {
    viewTransform.setPosition(p);
}

/*-------------------------------------
 * Get the camera target
-------------------------------------*/
inline const math::vec3& camera::getTarget() const {
    return target;
}

/*-------------------------------------
 * Set the camera target
-------------------------------------*/
inline void camera::setTarget(const math::vec3& t) {
    target = t;
}

/*-------------------------------------
 * Get the camera view matrix
-------------------------------------*/
inline const math::mat4& camera::getViewMatrix() const {
    return viewTransform.getTransform();
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
    return projMatrix * viewTransform.getTransform();
}

/*-------------------------------------
 * Get the camera's orientation
-------------------------------------*/
inline const math::quat& camera::getOrientation() const {
    return viewTransform.getOrientation();
}

/*-------------------------------------
 * Set the camera's rotation orientation.
-------------------------------------*/
inline void camera::setOrientation(const math::quat& o) {
    viewTransform.setOrientation(o);
}

/*-------------------------------------
 * Set the aspect ratio
-------------------------------------*/
inline void camera::setAspectRatio(float w, float h) {
    aspectW = w;
    aspectH = h;
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
 * Look At function from the current cam position
-------------------------------------*/
inline void camera::lookAt(const math::vec3& point) {
    lookAt(viewTransform.getPosition(), point, getUpDirection());
}

/*-------------------------------------
 * Camera Rotation function
-------------------------------------*/
inline void camera::rotate(const math::vec3& amount) {
    (this->*rotateFunction)(amount);
}

} // end draw namespace
} // end ls namespace
