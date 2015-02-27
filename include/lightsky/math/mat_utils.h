
#ifndef __LS_MATH_MAT_UTILS_H__
#define __LS_MATH_MAT_UTILS_H__

#include "lightsky/math/vec_utils.h"
#include "lightsky/math/mat2.h"
#include "lightsky/math/mat3.h"
#include "lightsky/math/mat4.h"

namespace ls {
namespace math {

/*-----------------------------------------------------------------------------
    2x2 Matrices
-----------------------------------------------------------------------------*/
/**
 *  @brief determinant
 *  Retrieve the determinate for a 2x2 matrix.
 *  
 *  @param m
 *  A constant reference to a 2x2 matrix.
 *  
 *  @return A scalar of type N, which contains the determinate of a 2x2 matrix.
 */
template <typename N> constexpr
N determinant(const mat2_t<N>& m);

/**
 *  @brief transpose
 *  Flip the values of a matrix around its main diagonal.
 *  
 *  @param m
 *  A constant reference to a 2x2 matrix.
 *  
 *  @return the transposition of a matrix.
 */
template <typename N> constexpr
mat2_t<N> transpose(const mat2_t<N>& m);

/**
 *  @brief inverse
 *  Invert a matrix m so that m * m^i = I
 *  
 *  @param m
 *  A constant reference to a 2x2 matrix.
 *  
 *  @return
 *  The inverse of matrix m.
 */
template <typename N> constexpr
mat2_t<N> inverse(const mat2_t<N>& m);

/**
 *  @brief rotate
 *  Rotate a 2x2 matrix by a number of radians.
 *  
 *  @param m
 *  A constant reference to a 2x2 matrix.
 *  
 *  @param radians
 *  The number of radians to rotate a matrix by.
 *  
 *  @return
 *  A the rotation of m by a number of radians.
 */
template <typename N> inline
mat2_t<N> rotate(const mat2_t<N>& m, N radians);

/**
 *  @brief scale
 *  Scale a matrix by modifying the components of its main diagonal. This
 *  method uses additive scaling rather than multiplicative scaling.
 *  
 *  @param m
 *  A constant reference to a 2x2 matrix.
 *  
 *  @param amount
 *  the amount of scaling along each axis of matrix m.
 */
template <typename N> constexpr
mat2_t<N> scale(const mat2_t<N>& m, const vec2_t<N>& amount);

/*-----------------------------------------------------------------------------
    3x3 Matrices
-----------------------------------------------------------------------------*/
/**
 *  @brief determinant
 *  Retrieve the determinate for a 3x3 matrix.
 *  
 *  @param m
 *  A constant reference to a 3x3 matrix.
 *  
 *  @return A scalar of type N, which contains the determinate of a 3x3 matrix.
 */
template <typename N> constexpr
N determinant(const mat3_t<N>& m);

/**
 *  @brief transpose
 *  Flip the values of a matrix around its main diagonal.
 *  
 *  @param m
 *  A constant reference to a 3x3 matrix.
 *  
 *  @return the transposition of a matrix.
 */
template <typename N> constexpr
mat3_t<N> transpose(const mat3_t<N>& m);

/**
 *  @brief inverse
 */
template <typename N> constexpr
mat3_t<N> inverse(const mat3_t<N>& m);

/**
 *  @brief rotate
 *  Rotate a 3x3 matrix by a number of radians.
 *  
 *  @param m
 *  A constant reference to a 3x3 matrix.
 *  
 *  @param axis
 *  The axis in 3D space around which the matrix will be rotated.
 *  
 *  @param radians
 *  The number of radians to rotate a matrix by.
 *  
 *  @return
 *  A the rotation of m by a number of radians.
 */
template <typename N> inline
mat3_t<N> rotate(const mat3_t<N>& m, const vec3_t<N>& axis, N radians);

/**
 *  @brief scale
 *  Scale a matrix by modifying the components of its main diagonal. This
 *  method uses additive scaling rather than multiplicative scaling.
 *  
 *  @param m
 *  A constant reference to a 3x3 matrix.
 *  
 *  @param amount
 *  the amount of scaling along each axis of matrix m.
 */
template <typename N> constexpr
mat3_t<N> scale(const mat3_t<N>& m, const vec3_t<N>& amount);

/**
 *  @brief translate
 *  Translate a 3x3 matrix along a 2D plane.
 *  
 *  @param m
 *  A constant reference to a 3x3 matrix.
 *  
 *  @param amount
 *  A constant reference to a constant 2D vector, indicating how much to move
 *  the matrix by.
 *  
 *  @return a 3x3 matrix that has been translated.
 */
template <typename N> constexpr
mat3_t<N> translate(const mat3_t<N>& m, const vec2_t<N>& amount);

/**
 *  @brief Look at a position in 3D space, but only return a pure rotation
 *  matrix with no positioning.
 *  
 *  @param pos
 *  The position, in 3D space, at which the projection matrix will be placed.
 *  
 *  @param target
 *  The position of the target point, in 3D space, that the projection matrix
 *  will face.
 *  
 *  @param up
 *  The direction of the top of the projection matrix.
 *  
 *  @return A rotation matrix that represents a camera's orientation towards a
 *  target in 3D space.
 */
template <typename N> inline
mat3_t<N> pureLookAt(const vec3_t<N>& pos, const vec3_t<N>& target, const vec3_t<N>& up);

/*-----------------------------------------------------------------------------
    4x4 Matrices
-----------------------------------------------------------------------------*/
/**
 *  @brief determinant
 *  Retrieve the determinate for a 4x4 matrix.
 *  
 *  @param m
 *  A constant reference to a 4x4 matrix.
 *  
 *  @return A scalar of type N, which contains the determinate of a 4x4 matrix.
 */
template <typename N> constexpr
N determinant(const mat4_t<N>& m);

/**
 *  @brief transpose
 *  Flip the values of a matrix around its main diagonal.
 *  
 *  @param m
 *  A constant reference to a 4x4 matrix.
 *  
 *  @return the transposition of a matrix.
 */
template <typename N> constexpr
mat4_t<N> transpose(const mat4_t<N>& m);

/**
 *  @brief inverse
 */
template <typename N> inline
mat4_t<N> inverse(const mat4_t<N>& m);

/**
 *  @brief rotate
 *  Rotate a 4x4 matrix by a number of radians.
 *  
 *  @param m
 *  A constant reference to a 4x4 matrix.
 *  
 *  @param axis
 *  The axis in 3D space around which the matrix will be rotated.
 *  
 *  @param radians
 *  The number of radians to rotate a matrix by.
 *  
 *  @return
 *  A the rotation of m by a number of radians.
 */
template <typename N> inline
mat4_t<N> rotate(const mat4_t<N>& m, const vec3_t<N>& axis, N radians);

/**
 *  @brief scale
 *  Scale a matrix by modifying the components of its main diagonal. This
 *  method uses additive scaling rather than multiplicative scaling.
 *  
 *  @param m
 *  A constant reference to a 4x4 matrix.
 *  
 *  @param amount
 *  the amount of scaling along each axis of matrix m.
 */
template <typename N> constexpr
mat4_t<N> scale(const mat4_t<N>& m, const vec3_t<N>& amount);

/**
 *  @brief translate
 *  Translate a 4x4 matrix along a 3D plane.
 *  
 *  @param m
 *  A constant reference to a 4x4 matrix.
 *  
 *  @param amount
 *  A constant reference to a constant 3D vector, indicating how much to move
 *  the matrix by.
 *  
 *  @return a 4x4 matrix that has been translated.
 */
template <typename N> constexpr
mat4_t<N> translate(const mat4_t<N>& m, const vec3_t<N>& amount);

/**
 *  @brief perspective
 *  Create a 2D perspective projection matrix in 3D space.
 *  
 *  @param fov
 *  The angle, in radians, representing the field of view of the projection
 *  matrix.
 *  
 *  @param aspect
 *  A scalar which represents the aspect ratio of the projection.
 *  
 *  @param zNear
 *  The distance which represents the point at which closely projected points
 *  in 3D space will be discarded from the projection.
 *  
 *  @param zFar
 *  The distance which represents the point at which far away points in 3D
 *  space will be discarded from the projection.
 *  
 *  @return
 *  A 4x4 matrix which allows 3D points to be perspective-projected into a 2D
 *  plane through multiplication.
 */
template <typename N> inline
mat4_t<N> perspective(N fov, N aspect, N zNear, N zFar);

/**
 *  @brief infinitePerspective
 *  Create a 2D perspective projection matrix in 3D space with no far-clipping
 *  plane. This is useful in applications which do not care about the precision
 *  of floating-point values far from the projection matrix.
 *  
 *  @param fov
 *  The angle, in radians, representing the field of view of the projection
 *  matrix.
 *  
 *  @param aspect
 *  A scalar which represents the aspect ratio of the projection.
 *  
 *  @param zNear
 *  The distance which represents the point at which closely projected points
 *  in 3D space will be discarded from the projection.
 *  
 *  @return
 *  A 4x4 perspective-projection matrix with no far plane.
 */
template <typename N> inline
mat4_t<N> infinitePerspective(N fov, N aspect, N zNear);

/**
 *  @brief ortho
 *  Create an orthographic-projection matrix in order to project 3D points
 *  onto a 2D plane. This method will project points without factoring in
 *  distance-scaling.
 *  
 *  @param left
 *  the leftmost clipping point of the projection.
 *  
 *  @param right
 *  the rightmost clipping point of the projection.
 *  
 *  @param top
 *  the topmost clipping point of the projection.
 *  
 *  @param bottom
 *  the bottommost clipping point of the projection.
 *  
 *  @return a 4x4 ortho-projection matrix which allows 3D points to be
 *  projected into a 2D representation without distance-scaling.
 */
template <typename N> inline
mat4_t<N> ortho(N left, N right, N top, N bottom);

/**
 *  @brief ortho
 *  Create an orthographic-projection matrix in order to project 3D points
 *  onto a 2D plane. This method will project points without factoring in
 *  distance-scaling.
 *  
 *  @param left
 *  the leftmost clipping point of the projection.
 *  
 *  @param right
 *  the rightmost clipping point of the projection.
 *  
 *  @param top
 *  the topmost clipping point of the projection.
 *  
 *  @param bottom
 *  the bottommost clipping point of the projection.
 *  
 *  @param zNear
 *  The distance which represents the point at which closely projected points
 *  in 3D space will be discarded from the projection.
 *  
 *  @param zFar
 *  The distance which represents the point at which far away points in 3D
 *  space will be discarded from the projection.
 *  
 *  @return a 4x4 orthographic-projection matrix which allows 3D points to be
 *  projected into a 2D representation without distance-scaling.
 */
template <typename N> inline
mat4_t<N> ortho(N left, N right, N top, N bottom, N near, N far);

/**
 *  @brief frustum
 *  Create a viewing frustum in order to project 3D points into 2D space.
 *  
 *  @param left
 *  the leftmost clipping point of the projection.
 *  
 *  @param right
 *  the rightmost clipping point of the projection.
 *  
 *  @param top
 *  the topmost clipping point of the projection.
 *  
 *  @param bottom
 *  the bottommost clipping point of the projection.
 *  
 *  @param zNear
 *  The distance which represents the point at which closely projected points
 *  in 3D space will be discarded from the projection.
 *  
 *  @param zFar
 *  The distance which represents the point at which far away points in 3D
 *  space will be discarded from the projection.
 *  
 *  @return a 4x4 frustum which allows 3D points to be projected onto a 2D
 *  plane.
 */
template <typename N> inline
mat4_t<N> frustum(N left, N right, N top, N bottom, N near, N far);

/**
 *  @brief lookAt
 *  Direct the far-plane of a projection matrix towards a point in 3D space.
 *  
 *  @param pos
 *  The position, in 3D space, at which the projection matrix will be placed.
 *  
 *  @param target
 *  The position of the target point, in 3D space, that the projection matrix
 *  will face.
 *  
 *  @param up
 *  The direction of the top of the projection matrix.
 *  
 *  @return A rotation matrix that represents a camera's orientation towards a
 *  target in 3D space.
 */
template <typename N> inline
mat4_t<N> lookAt(const vec3_t<N>& pos, const vec3_t<N>& target, const vec3_t<N>& up);

/**
 *  @brief Look at a target from a specific position in 3D space.
 *  
 *  @param pos
 *  The position, in 3D space, at which the projection matrix will be placed.
 *  
 *  @param target
 *  The position of the target point, in 3D space, that the projection matrix
 *  will face.
 *  
 *  @param up
 *  The direction of the top of the projection matrix.
 *  
 *  @return A rotation matrix that represents a camera's orientation towards a
 *  target in 3D space.
 */
template <typename N> inline
mat4_t<N> lookFrom(const vec3_t<N>& pos, const vec3_t<N>& target, const vec3_t<N>& up);

/**
 *  @brief billboard
 *  Retrieve a model matrix in 3D space so that it is oriented towards a
 *  Rotation/View matrix from a certain position.
 *  
 *  @param pos
 *  The position in 3D space that the billboard should be placed at.
 *  
 *  @param viewMatrix
 *  A camera's view matrix which represents both the the position and
 *  orientation that a billboard should rotate towards.
 *  
 *  @return A model matrix at a specified position, which is oriented towards a
 *  camera's view matrix in 3D space.
 */
template <typename N> inline
mat4_t<N> billboard(const vec3_t<N>& pos, const mat4_t<N>& viewMatrix);

} // end math namespace
} // end ls namespace

#include "lightsky/math/generic/mat_utils_impl.h"

#endif    /* __LS_MATH_MAT_UTILS_H__ */
