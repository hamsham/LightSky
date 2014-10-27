/* 
 * File:   math/vec_utils.h
 * Author: Miles Lacey
 *
 * Created on January 8, 2013, 3:14 PM
 */

#ifndef __LS_MATH_VEC_UTILS_H__
#define __LS_MATH_VEC_UTILS_H__

#include "lightsky/math/types.h"
#include "lightsky/math/scalar_utils.h"

#include "lightsky/math/types.h"
#include "lightsky/math/vec2.h"
#include "lightsky/math/vec3.h"
#include "lightsky/math/vec4.h"

namespace ls {
namespace math {

/*-----------------------------------------------------------------------------
    2D Vectors
-----------------------------------------------------------------------------*/
/**
 *  @brief dot
 *  Retrieve the dot product of a 2D vector.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return the 2D dot product of v1 & v2.
 */
template <typename N> constexpr
N dot(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief cross
 *  Retrieve the cross product of two 2D vectors.
 *  This method was developed my Allen Chou:
 *      http://allenchou.net/2013/07/cross-product-of-2d-vectors/
 *  This is useful in determining if the second vector is on the left or right
 *  side of the first.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return a scalar which can determine if v2 is on the left or right side of
 *  v1. If the returned value is positive, v2 is on the left of v1, if it's
 *  negative, v2 is on the right of v1.
 */
template <typename N> constexpr
N cross(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief normalize
 *  Normalize the vector v so that its points lie within a unit-sphere.
 *  
 *  @param v
 *  
 *  @return a normalized 2D vector.
 */
template <typename N> inline
vec2_t<N> normalize(const vec2_t<N>& v);

/**
 *  @brief lengthSquared
 *  Retrieve the square of the length/magnitude of a 2D vector. This is faster
 *  than calling length() as no square roots are performed.
 *  
 *  @param v
 *  A 2D vector.
 *  
 *  @return The square of the length/magnitude of a 2D vector.
 */
template <typename N> constexpr
N lengthSquared(const vec2_t<N>& v);

/**
 *  @brief length
 *  Retrieve the length/magnitude of a 2D vector.
 *  
 *  @param v
 *  A 2D vector.
 *  
 *  @return The length/magnitude of a 2D vector.
 */
template <typename N> inline
N length(const vec2_t<N>& v);

/**
 *  @brief rotate
 *  Rotate a 2D vector by a number of radians.
 *  
 *  @param v
 *  A 2D vector that is to be rotated.
 *  
 *  @param angle
 *  The number of radians that a 2D vector is to be rotated by.
 *  
 *  @return A rotated 2D vector.
 */
template <typename N> inline
vec2_t<N> rotate(const vec2_t<N>& v, N angle);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two 2D vectors placed around the origin
 *  of the Cartesian coordinate plane.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angleBetween(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two points in 2D space, with a
 *  specified origin.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @param origin
 *  The point in 2D space that two points use as their origin.
 *  
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angleBetween(const vec2_t<N>& v1, const vec2_t<N>& v2, const vec2_t<N>& origin);

/**
 *  @brief min
 *  Determine which of two vectors has the smallest length/magnitude.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The vector, either v1 or v2, which has the smallest
 *  length/magnitude.
 */
template <typename N> constexpr
vec2_t<N> min(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief mix
 *  Retrieve the linear interpolation of one vector towards another, moved by
 *  a certain percentage.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @param percent
 *  The percentage (clamped from [0, 1]) to which v2 should be interpolated
 *  towards v2.
 *  
 *  @return The vector, either v1 or v2, which has the smallest
 *  length/magnitude.
 */
template <typename N> constexpr
vec2_t<N> mix(const vec2_t<N>& v1, const vec2_t<N>& v2, N percent);

/**
 *  @brief max
 *  Determine which of two vectors has the largest length/magnitude.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The vector, either v1 or v2, which has the greatest
 *  length/magnitude.
 */
template <typename N> constexpr
vec2_t<N> max(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief project
 *  Project one vector onto another and retrieve the result.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The vector projection of v1 onto v2.
 */
template <typename N> inline
vec2_t<N> project(const vec2_t<N>& v1, const vec2_t<N>& v2);

/**
 *  @brief reflect
 *  Reflect a vector v around a normal vector.
 *  
 *  @param v
 *  
 *  @param norm
 *  The normal vector from which v will be reflected.
 *  
 *  @return
 *  The reflection of v around the normal vector 'norm'.
 */
template <typename N> inline
vec2_t<N> reflect(const vec2_t<N>& v, const vec2_t<N>& norm);

/**
 *  @brief mid
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return the midpoint between v1 and v2.
 */
template <typename N> constexpr
vec2_t<N> mid(const vec2_t<N>& v1, const vec2_t<N>& v2);

/*-----------------------------------------------------------------------------
    3D Vectors
-----------------------------------------------------------------------------*/
/**
 *  @brief dot
 *  Retrieve the dot product of a 3D vector.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return the 3D dot product of v1 & v2.
 */
template <typename N> constexpr
N dot(const vec3_t<N>& v1, const vec3_t<N>& v2);

/**
 *  @brief cross
 *  Retrieve the cross product of two 3D vectors. This result is perpendicular
 *  to the two input vectors.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return A 3D vector which represents the axis of rotation of two 3D
 *  vectors.
 */
template <typename N> constexpr
vec3_t<N> cross(const vec3_t<N>& v1, const vec3_t<N>& v2);

/**
 *  @brief normalize
 *  Normalize the vector v so that its points lie within a unit-sphere.
 *  
 *  @param v
 *  
 *  @return a normalized 4D vector.
 */
template <typename N> inline
vec3_t<N> normalize(const vec3_t<N>& v);

/**
 *  @brief lengthSquared
 *  Retrieve the square of the length/magnitude of a 3D vector. This is faster
 *  than calling length() as no square roots are performed.
 *  
 *  @param v
 *  A 3D vector.
 *  
 *  @return The square of the length/magnitude of a 3D vector.
 */
template <typename N> constexpr
N lengthSquared(const vec3_t<N>& v);

/**
 *  @brief length
 *  Retrieve the length/magnitude of a 3D vector.
 *  
 *  @param v
 *  A 3D vector.
 *  
 *  @return The length/magnitude of a 3D vector.
 */
template <typename N> inline
N length(const vec3_t<N>& v);

/**
 *  @brief xRotation
 *  Retrieve a unit vector that has been rotated around the cartesian X-Axis
 *  by a certain number of radians.
 *  
 *  @param angle
 *  The number of radians that a 3D vector is to be rotated by.
 *  
 *  @return A 3D vector rotated by 'angle' radians around the cartesian X-Axis.
 */
template <typename N> inline
vec3_t<N> xRotation(N angle);

/**
 *  @brief xRotation
 *  Retrieve a unit vector that has been rotated around the cartesian Y-Axis
 *  by a certain number of radians.
 *  
 *  @param angle
 *  The number of radians that a 3D vector is to be rotated by.
 *  
 *  @return A 3D vector rotated by 'angle' radians around the cartesian Y-Axis.
 */
template <typename N> inline
vec3_t<N> yRotation(N angle);

/**
 *  @brief xRotation
 *  Retrieve a unit vector that has been rotated around the cartesian Z-Axis
 *  by a certain number of radians.
 *  
 *  @param angle
 *  The number of radians that a 3D vector is to be rotated by.
 *  
 *  @return A 3D vector rotated by 'angle' radians around the cartesian Z-Axis.
 */
template <typename N> inline
vec3_t<N> zRotation(N angle);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two 3D vectors placed around the origin
 *  of the Cartesian coordinate plane.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angleBetween(const vec3_t<N>& v1, const vec3_t<N>& v2);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two points in 3D space, with a
 *  specified origin.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @param origin
 *  The point in 3D space that two points use as their origin.
 *  
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angleBetween(const vec3_t<N>& v1, const vec3_t<N>& v2, const vec3_t<N>& origin);

/**
 *  @brief min
 *  Determine which of two vectors has the smallest length/magnitude.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The vector, either v1 or v2, which has the smallest
 *  length/magnitude.
 */
template <typename N> constexpr
vec3_t<N> min(const vec3_t<N>&, const vec3_t<N>&);

/**
 *  @brief mix
 *  Retrieve the linear interpolation of one vector towards another, moved by
 *  a certain percentage.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @param percent
 *  The percentage (clamped from [0, 1]) to which v2 should be interpolated
 *  towards v2.
 *  
 *  @return The vector, either v1 or v2, which has the smallest
 *  length/magnitude.
 */
template <typename N> constexpr
vec3_t<N> mix(const vec3_t<N>&, const vec3_t<N>&, N);

/**
 *  @brief max
 *  Determine which of two vectors has the largest length/magnitude.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The vector, either v1 or v2, which has the greatest
 *  length/magnitude.
 */
template <typename N> constexpr
vec3_t<N> max(const vec3_t<N>&, const vec3_t<N>&);

/**
 *  @brief project
 *  Project one vector onto another and retrieve the result.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The vector projection of v1 onto v2.
 */
template <typename N> inline
vec3_t<N> project(const vec3_t<N>& v1, const vec3_t<N>& v2);

/**
 *  @brief reflect
 *  Reflect a vector v around a normal vector.
 *  
 *  @param v
 *  
 *  @param norm
 *  The normal vector from which v will be reflected.
 *  
 *  @return
 *  The reflection of v around the normal vector 'norm'.
 */
template <typename N> inline
vec3_t<N> reflect(const vec3_t<N>& v1, const vec3_t<N>& norm);

/**
 *  @brief mid
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return the midpoint between v1 and v2.
 */
template <typename N> constexpr
vec3_t<N> mid(const vec3_t<N>& v1, const vec3_t<N>& v2);

/*-----------------------------------------------------------------------------
    4D Vectors
-----------------------------------------------------------------------------*/
/**
 *  @brief dot
 *  Retrieve the dot product of two 4D vectors.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return the 4D dot product of v1 & v2.
 */
template <typename N> constexpr
N dot(const vec4_t<N>&, const vec4_t<N>& v);

/**
 *  @brief normalize
 *  Normalize the vector v so that its points lie within a unit-sphere.
 *  
 *  @param v
 *  
 *  @return a normalized 4D vector.
 */
template <typename N> inline
vec4_t<N> normalize(const vec4_t<N>& v);

/**
 *  @brief lengthSquared
 *  Retrieve the square of the length/magnitude of a 4D vector. This is faster
 *  than calling length() as no square roots are performed.
 *  
 *  @param v
 *  A 4D vector.
 *  
 *  @return The square of the length/magnitude of a 4D vector.
 */
template <typename N> constexpr
N lengthSquared(const vec4_t<N>& v);

/**
 *  @brief length
 *  Retrieve the length/magnitude of a 4D vector.
 *  
 *  @param v
 *  A 4D vector.
 *  
 *  @return The length/magnitude of a 4D vector.
 */
template <typename N> inline
N length(const vec4_t<N>& v);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two 4D vectors placed around the origin
 *  of the Cartesian coordinate plane.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angleBetween(const vec4_t<N>& v1, const vec4_t<N>& v2);

/**
 *  @brief angleBetween
 *  Determine the angle, in radians of two points in 4D space, with a
 *  specified origin.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @param origin
 *  The point in 4D space that two points use as their origin.
 *  
 *  @return The number of radians in between v1 & v2.
 */
template <typename N> inline
N angleBetween(const vec3_t<N>& v1, const vec3_t<N>& v2, const vec3_t<N>& origin);

/**
 *  @brief min
 *  Determine which of two vectors has the smallest length/magnitude.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The vector, either v1 or v2, which has the smallest
 *  length/magnitude.
 */
template <typename N> constexpr
vec4_t<N> min(const vec4_t<N>& v1, const vec4_t<N>& v2);

/**
 *  @brief mix
 *  Retrieve the linear interpolation of one vector towards another, moved by
 *  a certain percentage.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @param percent
 *  The percentage (clamped from [0, 1]) to which v2 should be interpolated
 *  towards v2.
 *  
 *  @return The vector, either v1 or v2, which has the smallest
 *  length/magnitude.
 */
template <typename N> constexpr
vec4_t<N> mix(const vec4_t<N>& v1, const vec4_t<N>& v2, N percent);

/**
 *  @brief max
 *  Determine which of two vectors has the largest length/magnitude.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The vector, either v1 or v2, which has the greatest
 *  length/magnitude.
 */
template <typename N> constexpr
vec4_t<N> max(const vec4_t<N>& v1, const vec4_t<N>& v2);

/**
 *  @brief project
 *  Project one vector onto another and retrieve the result.
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return The vector projection of v1 onto v2.
 */
template <typename N> inline
vec4_t<N> project(const vec4_t<N>& v1, const vec4_t<N>& v2);

/**
 *  @brief reflect
 *  Reflect a vector v around a normal vector.
 *  
 *  @param v
 *  
 *  @param norm
 *  The normal vector from which v will be reflected.
 *  
 *  @return
 *  The reflection of v around the normal vector 'norm'.
 */
template <typename N> inline
vec4_t<N> reflect(const vec4_t<N>& v1, const vec4_t<N>& norm);

/**
 *  @brief mid
 *  
 *  @param v1
 *  
 *  @param v2
 *  
 *  @return the midpoint between v1 and v2.
 */
template <typename N> constexpr
vec4_t<N> mid(const vec4_t<N>& v1, const vec4_t<N>& v2);

} // end math namespace
} // end ls namespace

#include "lightsky/math/generic/vec_utils_impl.h"

#endif /* __LS_MATH_VEC_UTILS_H__ */
