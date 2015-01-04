
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
    rotateFunction{&camera::rotateLockedY, &camera::rotateOrbitLockedY},
    updateFunction{&camera::updateNormal, &camera::updateOrbit},
    viewMode{VIEW_NORMAL},
    fov{DEFAULT_VIEW_ANGLE},
    aspectW{DEFAULT_ASPECT_WIDTH},
    aspectH{DEFAULT_ASPECT_HEIGHT},
    zNear{DEFAULT_Z_NEAR},
    zFar{DEFAULT_Z_FAR},
    orbitDist{1.f},
    pos{0.f},
    target{0.f},
    xAxis{1.f, 0.f, 0.f},
    yAxis{0.f, 1.f, 0.f},
    zAxis{0.f, 0.f, -1.f},
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
    rotateFunction[0] = &camera::rotateLockedY;
    rotateFunction[1] = &camera::rotateOrbitLockedY;
    updateFunction[0] = &camera::updateNormal;
    updateFunction[1] = &camera::updateOrbit;
    viewMode = c.viewMode;
    fov = c.fov;
    aspectW = c.aspectW;
    aspectH = c.aspectH;
    zNear = c.zNear;
    zFar = c.zFar;
    orbitDist = c.orbitDist;
    pos = c.pos;
    target = c.target;
    xAxis = c.xAxis;
    yAxis = c.yAxis;
    zAxis = c.zAxis;
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
    rotateFunction[VIEW_NORMAL] = (isLocked)
        ? &camera::rotateLockedY
        : &camera::rotateUnlockedY;

    rotateFunction[VIEW_ORBIT] = (isLocked)
        ? &camera::rotateOrbitLockedY
        : &camera::rotateOrbitUnlockedY;

}

/*-------------------------------------
 * Looking at targets
-------------------------------------*/
void camera::lookAt(const math::vec3& eye, const math::vec3& point, const math::vec3& up) {
    pos = eye;
    target = point;

    zAxis = math::normalize(pos - target);
    xAxis = math::normalize(math::cross(up, zAxis));
    yAxis = math::normalize(math::cross(zAxis, xAxis));

    viewMatrix[0][0] = xAxis.v[0];
    viewMatrix[1][0] = xAxis.v[1];
    viewMatrix[2][0] = xAxis.v[2];

    viewMatrix[0][1] = yAxis.v[0];
    viewMatrix[1][1] = yAxis.v[1];
    viewMatrix[2][1] = yAxis.v[2];

    viewMatrix[0][2] = zAxis.v[0];
    viewMatrix[1][2] = zAxis.v[1];
    viewMatrix[2][2] = zAxis.v[2];

    orientation = math::matToQuat(viewMatrix);
}

/*-------------------------------------
 * Basic Movement and Rotation
-------------------------------------*/
void camera::move(const math::vec3& amount) {
    pos -= xAxis * amount[0];
    pos -= yAxis * amount[1];
    pos -= zAxis * amount[2];
}

/*-------------------------------------
 * FPS rotation (locked Y axis)
-------------------------------------*/
void camera::rotateLockedY(const math::vec3& amount) {
    orientation
        = math::fromAxisAngle(zAxis, -amount[2])
        * math::fromAxisAngle(math::vec3{0.f, 1.f, 0.f}, -amount[1])
        * math::fromAxisAngle(xAxis, -amount[0])
        * orientation;
}

/*-------------------------------------
 * Orbital rotation (unlocked Y axis)
-------------------------------------*/
void camera::rotateOrbitUnlockedY(const math::vec3& amount) {
    pos -= xAxis * amount[0];
    pos -= yAxis * amount[1];
    pos -= zAxis * amount[2];
}

/*-------------------------------------
 * Orbital rotation (locked Y axis)
-------------------------------------*/
void camera::rotateOrbitLockedY(const math::vec3& amount) {
    rotateOrbitUnlockedY(amount);
    lookAt(pos, target, math::vec3{0.f, 1.f, 0.f});
}

/*-------------------------------------
 * Unrolling the camera
-------------------------------------*/
void camera::unroll() {
    if (viewMode == VIEW_ORBIT) {
        lookAt(pos, target, math::vec3{0.f, 1.f, 0.f});
    }
    else {
        lookAt(pos, pos - zAxis, math::vec3{0.f, 1.f, 0.f});
    }
}

/*-------------------------------------
 * Update Camera (FPS Style)
-------------------------------------*/
void camera::updateNormal() {
    viewMatrix = math::quatToMat4(orientation);

    xAxis = math::vec3{viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]};
    yAxis = math::vec3{viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]};
    zAxis = math::vec3{viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]};
}

/*-------------------------------------
 * Update Camera (Orbital)
-------------------------------------*/
void camera::updateOrbit() {
    pos = math::normalize(pos - target) * orbitDist;
    lookAt(target);
}

/*-------------------------------------
 * Update Implementation
-------------------------------------*/
void camera::update() {
    (this->*updateFunction[viewMode])();
    viewMatrix[3][0] = -math::dot(xAxis, pos);
    viewMatrix[3][1] = -math::dot(yAxis, pos);
    viewMatrix[3][2] = -math::dot(zAxis, pos);
}

} // end draw namespace
} // end ls namespace
