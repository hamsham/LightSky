
#include "lightsky/draw/camera.h"

namespace ls {
namespace draw {

/*-------------------------------------
 * Default Camera Perspective
-------------------------------------*/
const math::mat4 camera::DEFAULT_PERSPECTIVE{
    math::perspective(
        DEFAULT_VIEW_ANGLE,
        DEFAULT_ASPECT_WIDTH / DEFAULT_ASPECT_HEIGHT,
        DEFAULT_Z_NEAR,
        DEFAULT_Z_FAR
    )
};

/*-------------------------------------
 * Destructor
-------------------------------------*/
camera::~camera() {
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
camera::camera() :
    viewMode{camera_mode_t::FIRST_PERSON},
    rotateFunction{&camera::rotateLockedY},
    fov{DEFAULT_VIEW_ANGLE},
    aspectW{DEFAULT_ASPECT_WIDTH},
    aspectH{DEFAULT_ASPECT_HEIGHT},
    zNear{DEFAULT_Z_NEAR},
    zFar{DEFAULT_Z_FAR},
    target{0.f, 0.f, 1.f},
    projMatrix{math::perspective(
        DEFAULT_VIEW_ANGLE,
        DEFAULT_ASPECT_WIDTH/DEFAULT_ASPECT_HEIGHT,
        DEFAULT_Z_NEAR,
        DEFAULT_Z_FAR
    )},
    viewTransform{}
{}

/*-------------------------------------
 * Copy Constructor
-------------------------------------*/
camera::camera(const camera& c) {
    *this = c;
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
camera::camera(camera&& c) {
    *this = c;
}

/*-------------------------------------
 * Copy Operator
-------------------------------------*/
camera& camera::operator = (const camera& c) {
    viewMode = c.viewMode;
    rotateFunction = &camera::rotateLockedY;
    fov = c.fov;
    aspectW = c.aspectW;
    aspectH = c.aspectH;
    zNear = c.zNear;
    zFar = c.zFar;
    target = c.target;
    projMatrix = c.projMatrix;
    viewTransform = c.viewTransform;

    return *this;
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
camera& camera::operator =(camera&& c) {
    this->operator=(c);
    return *this;
}

/*-------------------------------------
 * Get the forward direction
-------------------------------------*/
math::vec3 camera::getDirection() const {
    return math::getAxisZ(viewTransform.getOrientation());
}

/*-------------------------------------
 * Set the camera's direction
-------------------------------------*/
void camera::setDirection(const math::vec3& d) {
    viewTransform.setOrientation(math::lookAt(d, math::vec3{0.f, 0.f, 1.f}));
}

/*-------------------------------------
 * Retrieve the camera's up vector
-------------------------------------*/
math::vec3 camera::getUpDirection() const {
    return math::getAxisY(viewTransform.getOrientation());
}

/*-------------------------------------
 * Determine which direction is up
-------------------------------------*/
void camera::setUpDirection(const math::vec3& up) {
    if (viewMode == camera_mode_t::FIRST_PERSON) {
        lookAt(getAbsolutePosition(), getDirection(), up);
    }
    else {
        lookAt(getAbsolutePosition(), target, up);
    }
}

/*-------------------------------------
 * Set the camera's projection parameters
-------------------------------------*/
void camera::setProjectionParams(
    float inFov,
    float aspectWidth, float aspectHeight,
    float near, float far
) {
    fov = inFov;
    aspectW = aspectWidth;
    aspectH = aspectHeight;
    zNear = near;
    zFar = far;
}

/*-------------------------------------
 * Y-Axis Locking
-------------------------------------*/
void camera::lockYAxis(bool isLocked) {
    rotateFunction = (isLocked)
        ? &camera::rotateLockedY
        : &camera::rotateUnlockedY;
}

/*-------------------------------------
 * Looking at targets
-------------------------------------*/
void camera::lookAt(const math::vec3& eye, const math::vec3& point, const math::vec3& up) {
    target = point;
    
    if (viewMode == camera_mode_t::ARCBALL) {
        viewTransform.extractTransforms(math::lookFrom(eye-target, math::vec3{0.f}, up));
    }
    else {
        viewTransform.extractTransforms(math::lookAt(eye-target, math::vec3{0.f}, up));
        viewTransform.setPosition(-eye);
    }
}

/*-------------------------------------
 * Basic Movement and Rotation
-------------------------------------*/
void camera::move(const math::vec3& amount) {
    if (viewMode == camera_mode_t::FIRST_PERSON) {
        viewTransform.move(amount, false);
    }
    else {
        viewTransform.move(amount, true);
    }
}

/*-------------------------------------
 * FPS Rotation (unlocked Y axis)
-------------------------------------*/
void camera::rotateUnlockedY(const math::vec3& amount) {
    const math::quat&& xAxis = math::quat{0.f, amount[0], 0.f, 0.f};
    const math::quat&& yAxis = math::quat{amount[1], 0.f, 0.f, 0.f};
    viewTransform.rotate(xAxis * yAxis);
}

/*-------------------------------------
 * FPS rotation (locked Y axis)
-------------------------------------*/
void camera::rotateLockedY(const math::vec3& amount) {
    const math::quat&  orientation  = viewTransform.getOrientation();
    const math::quat&& xAxis        = math::quat{0.f, amount[0], 0.f, 1.f};
    const math::quat&& yAxis        = math::quat{amount[1], 0.f, 0.f, 1.f};
    const math::quat&& camRotation  = xAxis * orientation * yAxis;
    
    viewTransform.setOrientation(math::normalize(camRotation));
}

/*-------------------------------------
 * Unrolling the camera
-------------------------------------*/
void camera::unroll() {
    setUpDirection(math::vec3{0.f, 1.f, 0.f});
}

/*-------------------------------------
 * Update Implementation
-------------------------------------*/
void camera::update() {
    if (viewMode == camera_mode_t::ARCBALL) {
        viewTransform.applyPreTransforms(math::translate(math::mat4{1.f}, -target));
    }
    else {
        viewTransform.applyTransforms(false);
    }
}

} // end draw namespace
} // end ls namespace
