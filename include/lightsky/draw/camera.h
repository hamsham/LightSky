
#ifndef __LS_DRAW_CAMERA_H__
#define __LS_DRAW_CAMERA_H__

#include "lightsky/math/math.h"

namespace ls {
namespace draw {

/**----------------------------------------------------------------------------
 * @brief Camera Perspective Modes
-----------------------------------------------------------------------------*/
enum camera_view_t : unsigned {
    VIEW_NORMAL = 0,
    VIEW_ORBIT  = 1,

    VIEW_MAX    = 2
};

/**----------------------------------------------------------------------------
 * @brief Camera transformation class
-----------------------------------------------------------------------------*/
class camera {
    public:
        /**
         * @brief Default Camera aspect width.
         */
        static constexpr float DEFAULT_ASPECT_WIDTH = 4.f;

        /**
         * @brief Default Camera aspect height.
         */
        static constexpr float DEFAULT_ASPECT_HEIGHT = 3.f;

        /**
         * @brief Default near-plane distance
         */
        static constexpr float DEFAULT_Z_NEAR = 0.1f;

        /**
         * @brief Default far plane distance
         */
        static constexpr float DEFAULT_Z_FAR = 100.f;

        /**
         * @brief Default angle for the field-of-view
         */
        static constexpr float DEFAULT_VIEW_ANGLE = 60.f;

        /**
         * @brief Default Perspective-projection matrix.
         */
        static const math::mat4 DEFAULT_PERSPECTIVE;

    private:
        /**
         * @brief rotationFunction is an array of class method pointers. This
         * will help keep camera's rotation method just between FPS/arcball
         * rotations with either a locked or unlocked Yaw axis.
         */
        void (camera::*rotateFunction[VIEW_MAX])(const math::vec3&);

        /**
         * @brief updateFunction is an array of class method pointers. This
         * will help keep camera's update method just between FPS/arcball
         * rotations with either a locked or unlocked Yaw axis.
         */
        void (camera::*updateFunction[VIEW_MAX])();

        /**
         * @brief viewMode sets the view mode in *this to wither use FPS or
         * arcball rotations.
         */
        camera_view_t viewMode = VIEW_NORMAL;

        /**
         * @brief fov Determines the angle of vision for the camera.
         */
        float fov = DEFAULT_VIEW_ANGLE;

        /**
         * @brief Helps to determine the aspect ratio for perspective and
         * orthographic camera modes.
         */
        float aspectW = DEFAULT_ASPECT_WIDTH;

        /**
         * @brief aspectH Helps to determine the aspect ratio for perspective
         * and orthographic camera modes.
         */
        float aspectH = DEFAULT_ASPECT_HEIGHT;

        /**
         * @brief Distance to the nearby occlusion plane.
         */
        float zNear = DEFAULT_Z_NEAR;

        /**
         * @brief Distance to the far occlusion plane.
         */
        float zFar = DEFAULT_Z_FAR;

        /**
         * @brief Distance for orbiting around a target.
         */
        float orbitDist = 1.f;

        /**
         * @brief Camera Position
         */
        math::vec3 pos;

        /**
         * @brief Orbit Target
         */
        math::vec3 target;

        /**
         * @brief Left/right direction
         */
        math::vec3 xAxis;

        /**
         * @brief Up Direction
         */
        math::vec3 yAxis;

        /**
         * @brief forward direction
         */
        math::vec3 zAxis;

        /**
         * @brief Quaternion rotation, converted from the rotation angles.
         */
        math::quat orientation;

        /**
         * @brief viewMatrix contains the camera's rotation after being
         * transformed.
         */
        math::mat4 viewMatrix;

        /**
         * @brief projMatrix contains only the projection parameters of the
         * camera which make up a viewing frustum.
         */
        math::mat4 projMatrix;

        /**
         * @brief rotateUnlockedY
         * Function to rotate the camera with an unlocked Y axis; This method
         * allows the camera to roll.
         *
         * @param amount
         * The amount, in radians, that the camera should rotate by. These
         * angles correspond to Pitch, Yaw, and Roll, respectively.
         */
        void rotateUnlockedY(const math::vec3& amount);

        /**
         * @brief rotateLockedY
         * Function to rotate the camera with a locked Y axis; This method
         * prevents the camera from rolling.
         *
         * @param amount
         * The amount, in radians, that the camera should rotate by. These
         * angles correspond to Pitch, Yaw, and Roll, respectively.
         */
        void rotateLockedY(const math::vec3& amount);

        /**
         * @brief rotateOrbitUnlockedY
         * Function to rotate the camera around a target with an unlocked Y
         * axis; This method allows the camera to roll.
         *
         * @param amount
         * The amount, in radians, that the camera should rotate by. These
         * angles correspond to Pitch, Yaw, and Roll, respectively.
         */
        void rotateOrbitUnlockedY(const math::vec3& amount);

        /**
         * @brief rotateOrbitUnlockedY
         * Function to rotate the camera around a target with a locked Y
         * axis; This method prevents the camera from rolling.
         *
         * @param amount
         * The amount, in radians, that the camera should rotate by. These
         * angles correspond to Pitch, Yaw, and Roll, respectively.
         */
        void rotateOrbitLockedY(const math::vec3& amount);

        /**
         * @brief Update the camera's projection parameters using FPS-mode.
         */
        void updateNormal();

        /**
         * @brief Update the camera's projection parameters using an arcball
         * rotation mode.
         */
        void updateOrbit();

    public:
        /**
         * @brief Destructor
         */
        ~camera();
        
        /**
         * @brief Constructor
         */
        camera();

        /**
         * @brief Copy Constructor
         */
        camera(const camera&);

        /**
         * @brief Move Constructor
         */
        camera(camera&&);

        /**
         * @brief Copy Operator
         */
        camera& operator = (const camera&);

        /**
         * @brief Move Operator
         */
        camera& operator = (camera&&);

        /**
         * @brief Reconstruct the projection matrix in *this so it uses
         * orthographic projection.
         */
        void makeOrtho();

        /**
         * @brief Reconstruct the projection matrix in *this so it uses
         * perspective projection.
         */
        void makePerspective();

        /**
         * @brief Store a set of perspective-projection parameters in *this so
         * the next call to *makeOrtho()" or "makePerspective()" will adjust
         * according to the input parameters.
         * 
         * @param inFov
         * Determines the horizontal viewing angle of the projection matrix.
         * 
         * @param aspectWidth
         * Determines the width, in user-defined units, of the camera's
         * projection matrix.
         * 
         * @param aspectHeight
         * Determines the height, in user-defined units, of the camera's
         * projection matrix.
         * 
         * @param near
         * Determines the internal projection's clipping distance for nearby
         * objects.
         * 
         * @param far
         * Determines the internal projection's clipping distance for distant
         * objects.
         */
        void setProjectionParams(
            float inFov         = DEFAULT_VIEW_ANGLE,
            float aspectWidth   = DEFAULT_ASPECT_WIDTH,
            float aspectHeight  = DEFAULT_ASPECT_HEIGHT,
            float near          = DEFAULT_Z_NEAR,
            float far           = DEFAULT_Z_FAR
        );

        /**
         * @brief Get the distance that the camera will be when using orbit
         * mode.
         * 
         * @return A floating-point number, using user-defined units,
         * determining how far the camera is from a desired target.
         */
        float getOrbitDist() const;

        /**
         * @brief Sets the distance that the camera will be orbiting a target.
         * 
         * @param d
         * A floating-point number, using user-defined units, determining how
         * far the camera will be from a desired target.
         */
        void setOrbitDist(float d);

        /**
         * @brief Get the current position of the camera in 3D cartesian space.
         * 
         * @return A 3D vector, containing the X, Y, and Z position of the
         * camera's view matrix.
         */
        const math::vec3& getPosition() const;

        /**
         * @brief Set the position of the camera in 3D cartesian space.
         * 
         * @param p
         * A 3D vector, containing the desired X, Y, and Z position of the
         * camera.
         */
        void setPosition(const math::vec3& p);

        /**
         * @brief Retrieve the current direction that the camera is facing.
         * 
         * @return A 3D unit vector containing the view matrix Z-axis.
         */
        const math::vec3& getDirection() const;

        /**
         * @brief Set the direction that the internal view matrix is oriented
         * towards.
         * 
         * @param d
         * a 3D unit vector, determining the direction in 3D cartesian space
         * that the camera should face.
         */
        void setDirection(const math::vec3& d);

        /**
         * @brief Get the orbit target of the camera.
         * 
         * @return a 3D vector, containing the position in 3D space of a point
         * that the camera will orbit around, (or look at in FPS mode).
         */
        const math::vec3& getTarget() const;

        /**
         * @brief Set the orbit target of the camera.
         * 
         * @param t
         * A 3D vector containing the position in 3D space of a point that the
         * camera will orbit around, (or look at in FPS mode).
         */
        void setTarget(const math::vec3& t);

        /**
         * @brief Get the camera's normal vector.
         * 
         * @return a 3D vector, used to determine which direction is upwards.
         */
        const math::vec3& getUpDirection() const;

        /**
         * @brief Set the camera's normal vector.
         * 
         * @param up
         * A 3D vector, used to determine which direction is upwards.
         */
        void setUpDirection(const math::vec3& up);

        /**
         * @brief Retrieve the camera's view matrix for external use.
         * 
         * @return A 4x4 rotation matrix which is used for the camera's
         * internal orientation.
         */
        const math::mat4& getViewMatrix() const;

        /**
         * @brief Retrieve the camera's projection matrix for external use.
         * 
         * @return A 4x4 projection matrix which is used by *this for
         * projecting geometry data.
         */
        const math::mat4& getProjMatrix() const;

        /**
         * @brief Calculate the combined view-projection matrix of the camera.
         * 
         * @return The view and projection matrices, multiplied together to
         * create a VP matrix.
         */
        math::mat4 getVPMatrix() const ;

        /**
         * @brief Get the internal orientation of the camera.
         * 
         * @return A quaternion used internally to represent the camera's
         * 3D orientation.
         */
        const math::quat& getOrientation() const;

        /**
         * @brief Set the internal orientation of the camera.
         * 
         * @param o
         * A quaternion that will be used to represent the camera's 3D
         * orientation.
         */
        void setOrientation(const math::quat& o);

        /**
         * @brief Set the aspect ration of the internal camera.
         * 
         * @param w
         * The width of the projection matrix frustum.
         * 
         * @param h
         * The height of the projection matrix frustum.
         */
        void setAspectRatio(float w, float h);

        /**
         * @brief Get the aspect ratio of the camera's projection matrix.
         * 
         * @return A floating-point value, representing the width of the
         * projection matrix frustum, divided by its height.
         */
        float getAspectRatio() const;

        /**
         * @brief Set the distance to the camera's near-clipping plane.
         * 
         * @param inZnear
         * A floating point value, representing the distance to the camera's
         * near-clipping plane.
         */
        void setNearPlane(float inZNear);

        /**
         * @brief Get the distance to the camera's near-clipping plane.
         * 
         * @return A floating point value, representing the distance to the
         * camera's near-clipping plane.
         */
        float getNearPlane() const;

        /**
         * @brief Set the distance to the camera's far-clipping plane.
         * 
         * @param inZfar
         * A floating point value, representing the distance to the camera's
         * far-clipping plane.
         */
        void setFarPlane(float inZFar);

        /**
         * @brief Get the distance to the camera's far-clipping plane.
         * 
         * @return A floating point value, representing the distance to the
         * camera's far-clipping plane.
         */
        float getFarPlane() const;

        /**
         * @brief Set the view mode of the camera (FPS or orbit mode).
         * 
         * @param m
         * The mode in which the camera should be operated in.
         */
        void setViewMode(camera_view_t m);

        /**
         * @brief Get the view mode of the camera.
         * 
         * @return camera_view_t
         * An enumeration that determines of the camera should be in FPS or
         * orbit mode.
         */
        camera_view_t  getViewMode() const;

        /**
         * @brief Set whether or not the Y axis of the camera should be locked.
         * 
         * @param shouldLock
         * A boolean value, determining if the camera should be permitted to
         * roll.
         */
        void lockYAxis(bool shouldLock);

        /**
         * @brief Make the camera frustum face in the direction of a target.
         * 
         * @param eye
         * The desired position of the camera.
         * 
         * @param point
         * The point at which the view/projection frustum should face.
         * 
         * @param up
         * The direction which determines which way is upwards.
         */
        void lookAt(const math::vec3& eye, const math::vec3& point, const math::vec3& up);

        /**
         * @brief Look at a point using the camera's current position and
         * normal vector.
         * 
         * @param point
         * A point that the camera should look at.
         */
        void lookAt(const math::vec3& point);

        /**
         * @brief Modify the camera's current position by a given amount.
         * 
         * @param amount
         * The distance that the camera's current position should be modified
         * by.
         */
        void move(const math::vec3& amount);

        /**
         * @brief Modify the camera's current orientation by a given amount.
         * 
         * @param amount
         * The rotation delta which should be applied to the camera's current
         * rotation.
         */
        void rotate(const math::vec3& amount);

        /**
         * @brief Reset the camera's current orientation to it's normal vector
         * is at {0, 1, 0}.
         */
        void unroll();

        /**
         * @brief Apply all pending updates to the camera's view+projection
         * matrix.
         */
        void update();
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/camera_impl.h"

#endif // __LS_DRAW_CAMERA_H__
