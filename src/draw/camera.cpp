
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
    pos{0.f},
    orientation{0.f, 0.f, 0.f, 1.f},
    viewMatrix{1.f},
    projMatrix{math::perspective(
        DEFAULT_VIEW_ANGLE,
        DEFAULT_ASPECT_WIDTH/DEFAULT_ASPECT_HEIGHT,
        DEFAULT_Z_NEAR,
        DEFAULT_Z_FAR
    )}
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
    pos = c.pos;
    orientation = c.orientation;
    viewMatrix = c.viewMatrix;
    projMatrix = c.projMatrix;

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
    return math::getAxisZ(orientation);
}

/*-------------------------------------
 * Set the camera's direction
-------------------------------------*/
void camera::setDirection(const math::vec3& d) {
    orientation = math::lookAt(d, math::vec3{0.f, 0.f, 1.f});
}

/*-------------------------------------
 * Retrieve the camera's up vector
-------------------------------------*/
math::vec3 camera::getUpDirection() const {
    return math::getAxisY(orientation);
}

/*-------------------------------------
 * Determine which direction is up
-------------------------------------*/
void camera::setUpDirection(const math::vec3& up) {
    if (viewMode == camera_mode_t::FIRST_PERSON) {
        lookAt(pos, getDirection(), up);
    }
    else {
        lookAt(pos, target, up);
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
    pos = (viewMode == camera_mode_t::FIRST_PERSON) ? eye : -eye;
    target = point;
    
    orientation = math::matToQuat(math::lookAt(pos, target, up));
}

/*-------------------------------------
 * Basic Movement and Rotation
-------------------------------------*/
void camera::move(const math::vec3& amount) {
    if (viewMode == camera_mode_t::FIRST_PERSON) {
        pos[0] -= math::dot(math::getAxisX(orientation), amount);
        pos[1] -= math::dot(math::getAxisY(orientation), amount);
        pos[2] -= math::dot(math::getAxisZ(orientation), amount);
    }
    else {
        pos += amount;
    }
}

/*-------------------------------------
 * FPS Rotation (unlocked Y axis)
-------------------------------------*/
inline void camera::rotateUnlockedY(const math::vec3& amount) {
    // Always lerp to the new mouse position
    const math::quat&& lerpX = math::lerp(
        math::quat{0.f, 0.f, 0.f, 1.f},
        math::quat{amount[1], 0.f, 0.f, 1.f},
        1.f
    );
    
    const math::quat&& lerpY = math::lerp(
        math::quat{0.f, 0.f, 0.f, 1.f},
        math::quat{0.f, amount[0], 0.f, 1.f},
        1.f
    );
    
    orientation = math::normalize(orientation * lerpY * lerpX);
}

/*-------------------------------------
 * FPS rotation (locked Y axis)
-------------------------------------*/
void camera::rotateLockedY(const math::vec3& amount) {
    orientation = math::normalize(
        math::quat{0.f, amount[0], 0.f, 1.f} *
        orientation *
        math::quat{amount[1], 0.f, 0.f, 1.f}
    );
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
    if (viewMode == camera_mode_t::FIRST_PERSON) {
        viewMatrix = math::quatToMat4(orientation);
        const math::vec3&& xAxis = math::vec3{viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]};
        const math::vec3&& yAxis = math::vec3{viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]};
        const math::vec3&& zAxis = math::vec3{viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]};

        viewMatrix[3][0] = -math::dot(xAxis, pos);
        viewMatrix[3][1] = -math::dot(yAxis, pos);
        viewMatrix[3][2] = -math::dot(zAxis, pos);
    }
    else {
        const math::quat&& o = math::conjugate(orientation);
        const math::vec3&& x = math::getAxisX(o);
        const math::vec3&& y = math::getAxisY(o);
        const math::vec3&& z = math::getAxisZ(o);
        const math::vec3&& v = pos-target;
        const math::vec3&& p = {(x*v[0]) + (y*v[1]) + (z*v[2])};
        viewMatrix = math::lookAt(p+target, target, y);
    }
}

} // end draw namespace
} // end ls namespace
