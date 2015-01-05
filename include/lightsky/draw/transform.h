
#ifndef __LS_DRAW_TRANSFORM_H__
#define __LS_DRAW_TRANSFORM_H__

#include "lightsky/math/math.h"

namespace ls {
namespace draw {

/**
 * @brief The transform class is used to contain transformations of an object
 * in both rendering and physical simulation.
 *
 * This class is primarily intended to contain the transformations of renderable
 * objects, as well as simplify the management of their model matrices.
 */
class transform {
    private:
        /**
         * @brief position
         *
         * Represents the position of a point in 3D catersian coordinates.
         */
        math::vec3 position;

        /**
         * @brief scaling
         *
         * Represents the size of an object in 3D space.
         */
        math::vec3 scaling;

        /**
         * @brief position
         *
         * Represents the orientation of a point in both 3D and 4D space.
         */
        math::quat orientation;

        /**
         * @brief modelMatrix
         *
         * Contains the position, size, and rotation of an object in 3D space.
         */
        math::mat4 modelMatrix;

        /**
         * @brief dirtyFlag
         *
         * A boolean object to determine if the internal model matrix in *this
         * needs to be readjusted.
         */
        bool dirtyFlag;

    public:
        /**
         * @brief Destructor
         */
        ~transform();

        /**
         * @brief Constructor
         */
        transform();

        /**
         * @brief Copy Constructor
         *
         * @param t
         * A constant reference to another transform object
         */
        transform(const transform& t);

        /**
         * @brief Move Constructor
         *
         * @param t
         * An r-value reference to another transform object
         */
        transform(transform&& t);

        /**
         * @brief Copy Operator
         *
         * @param t
         * A constant reference to another transform object
         */
        transform& operator=(const transform& t);

        /**
         * @brief Move Operator
         *
         * @param t
         * An r-value reference to another transform object
         */
        transform& operator=(transform&& t);

        /**
         * @brief Check if the current transformation object needs to be
         * updated.
         *
         * Dirty transformations must have the "applyTransforms()" method
         * called in order to update the internal model matrix.
         *
         * @return TRUE if *this object had the position, scale, or orientation
         * adjusted, FALSE otherwise.
         */
        bool isDirty() const;

        /**
         * @brief Make the current transform appear to require an update.
         *
         * Dirty transformations must have the "applyTransforms()" method
         * called in order to update the internal model matrix.
         */
        void setDirty();

        /**
         * @brief Apply any pending adjustments to the internal model matrix.
         *
         * This method is implicitly called if the internal model matrix has
         * been modified manually.
         */
        void applyTransforms();

        /**
         * @brief Adjust *this transformation object's internal position.
         *
         * Calling this method will cause the "isDirty()" function to return
         * TRUE until "applyTransforms()" is called.
         *
         * @param deltaPos
         * A 3D vector which will determine how much to move *this
         * transformation in 3D space.
         *
         * @param relative
         * If set to true, all movements will be performed relative to the
         * transformation's current orientation. If false, the movement will be
         * performed according to the global cartesian coordinate system.
         */
        void move(const math::vec3& deltaPos, bool relative = false);

        /**
         * @brief Set *this transformation object's internal position.
         *
         * Calling this method will cause the "isDirty()" function to return
         * TRUE until "applyTransforms()" is called.
         *
         * @param newPos
         * A constant reference to a 3D vector which will adjust the internal
         * position of *this in 3D cartesian space.
         */
        void setPosition(const math::vec3& newPos);

        /**
         * @brief Retrieve the current position of *this.
         *
         * @return a reference to a 3D vector, representing the position of a
         * point in 3D cartesian space.
         */
        const math::vec3& getPosition() const;

        /**
         * @brief Adjust *this transformation object's internal size.
         *
         * Calling this method will cause the "isDirty()" function to return
         * TRUE until "applyTransforms()" is called.
         *
         * @param deltaScale
         * A 3D vector which will determine how much to resize *this
         * transformation in 3D space.
         */
        void scale(const math::vec3& deltaScale);

        /**
         * @brief Set *this transformation object's internal scaling.
         *
         * Calling this method will cause the "isDirty()" function to return
         * TRUE until "applyTransforms()" is called.
         *
         * @param newScale
         * A constant reference to a 3D vector which will adjust the internal
         * size of *this in 3D cartesian space.
         */
        void setScale(const math::vec3& newScale);

        /**
         * @brief Retrieve the current scaling of *this.
         *
         * @return a reference to a 3D vector, representing the scale of a
         * point in 3D cartesian space.
         */
        const math::vec3& getScale() const;

        /**
         * @brief Adjust *this transformation object's internal orientation.
         *
         * Calling this method will cause the "isDirty()" function to return
         * TRUE until "applyTransforms()" is called.
         *
         * @param deltaRotation
         * A quaternion which will determine how much to move *this
         * transformation in 3D space.
         */
        void rotate(const math::quat& deltaRotation);

        /**
         * @brief Set *this transformation object's internal orientation.
         *
         * Calling this method will cause the "isDirty()" function to return
         * TRUE until "applyTransforms()" is called.
         *
         * @param newRotation
         * A constant reference to a quaternion which will adjust the internal
         * orientation of *this in 3D cartesian space.
         */
        void setOrientation(const math::quat& newRotation);

        /**
         * @brief Retrieve the current orientation of *this.
         *
         * @return a reference to a quaternion, representing the orientation of
         * a point in 3D cartesian space.
         */
        const math::quat& getOrientation() const;

        /**
         * @brief Multiply *this by another 4x4 homogenous transformation
         * matrix.
         *
         * The model matrix contained within *this is modified as such:
         * this->modelMatrix = this->modelMatrix * deltaTransform.
         *
         * Calling this method will apply all pending transformations, making
         * firther calls to "isDirty()" to return false.
         *
         * @param deltaTransform
         * A 3x3 transformation matrix which will determine how much to adjust
         * *this transformation in 3D space.
         */
        void preTransform(const math::mat4& deltaTransform);

        /**
         * @brief Multiply *this by another 4x4 homogenous transformation
         * matrix.
         *
         * The model matrix contained within *this is modified as such:
         * this->modelMatrix = deltaTransform * this->modelMatrix.
         *
         * Calling this method will apply all pending transformations, making
         * firther calls to "isDirty()" to return false.
         *
         * @param deltaTransform
         * A 3x3 transformation matrix which will determine how much to adjust
         * *this transformation in 3D space.
         */
        void postTransform(const math::mat4& deltaTransform);

        /**
         * @brief Set *this transformation object's internal model matrix.
         *
         * Calling this method will apply all pending transformations, making
         * further calls to "isDirty()" return FALSE.
         *
         * @param newTransform
         * A constant reference to a 4x4 matrix which, representing the
         * position, scale, and orientation of a point in 3D space.
         */
        void setTransform(const math::mat4& newTransform);

        /**
         * @brief Retrieve the current model matrix of *this.
         *
         * @return a reference to a 4x4 matrix, representing the position,
         * scale, and orientation of a point in 3D cartesian space.
         */
        const math::mat4& getTransform() const;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/transform_impl.h"

#endif // __LS_DRAW_TRANSFORM_H__
