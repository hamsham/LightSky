
#include <utility> // std::move

#include "lightsky/draw/transform.h"

namespace ls {
namespace draw {

/*-----------------------------------------------------------------------------
 * Construction/Destruction
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Destructor
-------------------------------------*/
transform::~transform() {
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
transform::transform() :
    position{0.f},
    scaling{0.f},
    orientation{0.f, 0.f, 0.f, 1.f},
    modelMatrix{1.f}
{}

/*-------------------------------------
 * Matrix Constructor
-------------------------------------*/
transform::transform(const math::mat4& modelMat) :
    dirtyFlag{false},
    position{modelMat[3][0], modelMat[3][1], modelMat[3][2]},
    scaling{modelMat[0][0], modelMat[1][1], modelMat[2][2]},
    orientation{math::matToQuat(modelMatrix)},
    modelMatrix{modelMat}
{}

/*-------------------------------------
 * Copy Constructor
-------------------------------------*/
transform::transform(const transform& t) :
    position{t.position},
    scaling{t.scaling},
    orientation{t.orientation},
    modelMatrix{t.modelMatrix}
{}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
transform::transform(transform&& t) :
    position{std::move(t.position)},
    scaling{std::move(t.scaling)},
    orientation{std::move(t.orientation)},
    modelMatrix{std::move(t.modelMatrix)}
{}

/*-------------------------------------
 * Copy Operator
-------------------------------------*/
transform& transform::operator=(const transform& t) {
    position = t.position;
    scaling = t.scaling;
    orientation = t.orientation;
    modelMatrix = t.modelMatrix;

    return *this;
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
transform& transform::operator=(transform&& t) {
    position = std::move(t.position);
    scaling = std::move(t.scaling);
    orientation = std::move(t.orientation);
    modelMatrix = std::move(t.modelMatrix);

    return *this;
}

/*-------------------------------------
 * Apply all transformations to the model matrix
-------------------------------------*/
void transform::applyTransforms() {
    modelMatrix = math::mat4{
        scaling[0],     0.f,            0.f,        0.f,
        0.f,            scaling[1],     0.f,        0.f,
        0.f,            0.f,            scaling[2], 0.f,
        position[0],    position[1],    position[2],1.f
    } * math::quatToMat4(orientation);

    dirtyFlag = false;
}

/*-----------------------------------------------------------------------------
 * Positioning
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Adjust the position
-------------------------------------*/
void transform::move(const math::vec3& deltaPos, bool relative) {
    if (relative == false) {
        const math::mat3&& axes = math::quatToMat3(orientation);
        const math::vec3&& translation = {
            math::dot(axes[0], deltaPos),
            math::dot(axes[1], deltaPos),
            math::dot(axes[2], deltaPos)
        };
        position += translation;
    }
    else {
        position += deltaPos;
    }

    dirtyFlag = true;
}

/*-------------------------------------
 * Set the position
-------------------------------------*/
void transform::setPosition(const math::vec3& newPos) {
    position = newPos;
    dirtyFlag = true;
}

/*-----------------------------------------------------------------------------
 * Scaling
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Adjust the scaling
-------------------------------------*/
void transform::scale(const math::vec3& deltaScale) {
    scaling += deltaScale;
    dirtyFlag = true;
}

/*-------------------------------------
 * Set the scaling
-------------------------------------*/
void transform::setScale(const math::vec3& newScale) {
    scaling = newScale;
    dirtyFlag = true;
}

/*-----------------------------------------------------------------------------
 * Orientation
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Adjust the orientation
-------------------------------------*/
void transform::rotate(const math::quat& deltaRotation) {
    orientation *= deltaRotation;
    dirtyFlag = true;
}

/*-------------------------------------
 * Set the orientation
-------------------------------------*/
void transform::setOrientation(const math::quat& newRotation) {
    orientation = newRotation;
    dirtyFlag = true;
}

/*-----------------------------------------------------------------------------
 * Final Transformations
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Set the model matrix
-------------------------------------*/
void transform::setTransform(const math::mat4& newTransform) {
    modelMatrix = newTransform;

    position[0] = modelMatrix[3][0];
    position[1] = modelMatrix[3][1];
    position[2] = modelMatrix[3][2];
    
    scaling[0] = modelMatrix[0][0];
    scaling[1] = modelMatrix[1][1];
    scaling[2] = modelMatrix[2][2];

    orientation = math::matToQuat(modelMatrix);

    dirtyFlag = false;
}

/*-------------------------------------
 * Pre-transform the matrix
-------------------------------------*/
void transform::preTransform(const math::mat4& deltaTransform) {
    if (this->isDirty()) {
        applyTransforms();
    }
    setTransform(modelMatrix * deltaTransform);
}

/*-------------------------------------
 * Post-transform the matrix
-------------------------------------*/
void transform::postTransform(const math::mat4& deltaTransform) {
    if (this->isDirty()) {
        applyTransforms();
    }
    setTransform(deltaTransform * modelMatrix);
}

} // end draw namespace
} // end ls namespace
