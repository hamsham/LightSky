
#ifndef __LS_MATH_QUAT_UTILS_H__
#define __LS_MATH_QUAT_UTILS_H__

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/vec3.h"
#include "lightsky/math/vec4.h"
#include "lightsky/math/mat3.h"
#include "lightsky/math/mat4.h"
#include "lightsky/math/quat.h"
#include "lightsky/math/vec_utils.h"

namespace ls {
namespace math {

/*-----------------------------------------------------------------------------
    Quaternion-Specific Functions
-----------------------------------------------------------------------------*/
/**
 *  @brief dot
 *  Retrieve the dot product of two quaternions.
 *  
 *  @param q1
 *  
 *  @param q2
 *  
 *  @return the dot product of q1 & q2.
 */
template <typename N> constexpr
N dot(const quat_t<N>&, const quat_t<N>&);

/**
 *  @brief lengthSquared
 *  Retrieve the square of the length/magnitude of a quaternion. This is faster
 *  than calling length() as no square roots are performed.
 *  
 *  @param q
 *  
 *  @return The square of the length/magnitude of a quaternion.
 */
template <typename N> constexpr
N lengthSquared(const quat_t<N>&);

/**
 *  @brief length
 *  Retrieve the length/magnitude of a quaternion.
 *  
 *  @param q
 *  
 *  @return The length/magnitude of a quaternion.
 */
template <typename N> inline
N length(const quat_t<N>&);

/**
 *  @brief inverse
 *  Retrieve the geometric inverse of the quaternion.
 *  
 *  @param q
 *  
 *  @return the geometric inverse of the quaternion q, within a unit sphere.
 */
template <typename N> inline
quat_t<N> inverse(const quat_t<N>& q);

/**
 *  @brief conjugate
 *  Get the complex-conjugate of a quaternion.
 *  
 *  @param q
 *  
 *  @return the complex conjugate of the quaternion q.
 */
template <typename N> constexpr
quat_t<N> conjugate(const quat_t<N>& q);

/**
 *  @brief normalize
 *  Normalize the quaternion q so that its points lie within a unit-sphere.
 *  
 *  @param q
 *  
 *  @return a normalized quaternion.
 */
template <typename N> inline
quat_t<N> normalize(const quat_t<N>&);

/**
 * @brief Rotate a vector by the orientation specified by a quaternion.
 * 
 * This method was adapted (aggressively) from Laurent Couvidou's StackExchange
 * post regarding vector rotation:
 * http://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
 * 
 * @param v
 * A constant reference to the vector which is to be rotated.
 * 
 * @param q
 * A constant reference to the quaternion which contains an orientation that
 * will be used to manipulate "v".
 * 
 * @return A 3D vector rotated by the quaternion "q".
 */
template <typename N> inline
vec3_t<N> rotate(const vec3_t<N>& v, const quat_t<N>& q);

/**
 *  @brief
 *  Linearly interpolate a quaternion towards another by some percentage. This
 *  is the same as calling "ls::math::mix()" for a vector or scalar.
 *  
 *  @param q1
 *  The quaternion to be interpolated.
 *  
 *  @param q2
 *  The reference quaternion that q1 should interpolate to.
 *  
 *  @param percent
 *  The percentage that q1 should move towards q2.
 *  
 *  @return a linear interpolation of q1 towards q2 by some percent.
 */
template <typename N> constexpr
quat_t<N> lerp(const quat_t<N>& q1, const quat_t<N>& q2, N percent);

/**
 *  @brief
 *  Linearly interpolate a quaternion towards another by some percentage and
 *  normalize the result.
 *  
 *  @param q1
 *  The quaternion to be interpolated.
 *  
 *  @param q2
 *  The reference quaternion that q1 should interpolate to.
 *  
 *  @param percent
 *  The percentage that q1 should move towards q2.
 *  
 *  @return a normalized linear interpolation of q1 towards q2 by some percent.
 */
template <typename N> constexpr
quat_t<N> nlerp(const quat_t<N>& q1, const quat_t<N>& q2, N percent);

/**
 *  @brief SLERP
 *  Perform a spherical-interpolation of q1 towards q2 by some percentage.
 *  
 *  This method has been adapted from Professor W. Randolph Franklin
 *  Rensselaer Polytechnic Institute:
 *  http://www.ecse.rpi.edu/Homepages/wrf/pmwiki/pmwiki.php
 *  http://www.ecse.rpi.edu/~wrf/wiki/ComputerGraphicsFall2012/guha/Code/quaternionAnimation.cpp
 * 
 *  Request from the true author must be granted prior to use in commercial
 *  products.
 *  
 *  @param q1
 *  The quaternion to be interpolated.
 *  
 *  @param q2
 *  The reference quaternion that q1 should interpolate to.
 *  
 *  @param percent
 *  The percentage that q1 should move towards q2.
 *  
 *  @return a spherical interpolation of q1 towards q2 by some percent.
 */
template <typename N> inline
quat_t<N> slerp(const quat_t<N>&, const quat_t<N>&, N);

/**
 * Quaternion LookAt
 * 
 * @param target
 * A vec3 type used to determine the orientation of the returned quaternion.
 * 
 * @param dir
 * A unit vector, giving the axis of rotation for the returned orientation.
 * This should typically be vec3{0, 0, 1} to indicate that the returned
 * quaternion should point its forwards axis in the Z-direction.
 * 
 * @return A quaternion, oriented in the direction of a target.
 */
template <typename N> inline
quat_t<N> lookAt(const vec3_t<N>& target, const vec3_t<N>& dir);

/*-----------------------------------------------------------------------------
    Quaternions & Matrices
-----------------------------------------------------------------------------*/
/**
 *  @brief quatToMat3
 *  Convert a quaternion into a 3x3 rotational matrix.
 *  
 *  @param q
 *  
 *  @return a 3x3 rotation matrix.
 */
template <typename N> inline
mat3_t<N> quatToMat3(const quat_t<N>& q);

/**
 *  @brief quatToMat4
 *  Convert a quaternion into a 4x4 rotational matrix.
 *  
 *  @param q
 *  
 *  @return a 4x4 rotation matrix.
 */
template <typename N> inline
mat4_t<N> quatToMat4(const quat_t<N>& q);

/**
 *  @brief matToQuat
 *  Convert a 3x3 rotation matrix into a quaternion.
 *  
 *  @param m
 *  
 *  @return a quaternion that represents a 3x3 rotation matrix.
 */
template <typename N> inline
quat_t<N> matToQuat(const mat3_t<N>& m);

/**
 *  @brief matToQuat
 *  Convert a 4x4 rotation matrix into a quaternion.
 *  
 *  @param m
 *  
 *  @return a quaternion that represents a 4x4 rotation matrix.
 */
template <typename N> inline
quat_t<N> matToQuat(const mat4_t<N>& m);

/*-----------------------------------------------------------------------------
    Quaternions & Euler Angles
-----------------------------------------------------------------------------*/
/**
 *  @brief getAxisX
 *  Retrieve the "x-axis" of a quaternion. This is a short-circuited method of
 *  converting a quaternion into a rotation matrix, then extracting the axis of
 *  rotation along the x-axis.
 *  
 *  @param q
 *  
 *  @return the rotational x-axis of a quaternion in R^3
 */
template <typename N> constexpr
vec3_t<N> getAxisX(const quat_t<N>& q); // Right-Vector

/**
 *  @brief getAxisY
 *  Retrieve the "y-axis" of a quaternion. This is a short-circuited method of
 *  converting a quaternion into a rotation matrix, then extracting the axis of
 *  rotation along the y-axis.
 *  
 *  @param q
 *  
 *  @return the rotational y-axis of a quaternion in R^3
 */
template <typename N> constexpr
vec3_t<N> getAxisY(const quat_t<N>& q); // Up-Vector

/**
 *  @brief getAxisZ
 *  Retrieve the "z-axis" of a quaternion. This is a short-circuited method of
 *  converting a quaternion into a rotation matrix, then extracting the axis of
 *  rotation along the z-axis.
 *  
 *  @param q
 *  
 *  @return the rotational z-axis of a quaternion in R^3
 */
template <typename N> constexpr
vec3_t<N> getAxisZ(const quat_t<N>& q); // Forwards Vector

/**
 *  @brief getAngle
 *  Retrieve the angle of rotation (i.e. the real-component) of a quaternion,
 *  in R^3.
 *  
 *  @param q
 *  
 *  @return The angle of rotation of a quaternion, clamped to be within 2*PI
 *  radians.
 */
template <typename N> inline
N getAngle(const quat_t<N>& q);

/**
 *  @brief toEuler
 *  Convert a unit quaternion into 3 Euler angles, pitch, yaw, and roll.
 *  
 *  @oaram q
 *  
 *  @return a 3D vector which contains the pitch, yaw, and roll of a
 *  quaternion, respectively.
 */
template <typename N> inline
vec3_t<N> toEuler(const quat_t<N>& q);

/**
 *  @brief fromEuler
 *  Convert three Euler angles into a rotational quaternion. These angles must
 *  be in the order of pitch, yaw, and roll, respectively.
 *  
 *  @param pyr
 *  A 3D vector containing the angles of pitch, yaw, and roll.
 *  
 *  @return q rotational quaternion representing the three input rotation
 *  angles.
 */
template <typename N> inline
quat_t<N> fromEuler(const vec3_t<N>& pyr);

/**
 *  @brief fromEuler
 *  Convert three Euler angles into a rotational quaternion. These angles must
 *  be in the order of pitch, yaw, and roll, respectively.
 *  
 *  @param pitch
 *  The angle of rotation along a point's X-Axis
 *  
 *  @param yaw
 *  The angle of rotation along a point's Y-Axis
 *  
 *  @param roll
 *  The angle of rotation along a point's Z-Axis
 *  
 *  @return q rotational quaternion representing the three input rotation
 *  angles.
 */
template <typename N> inline
quat_t<N> fromEuler(N pitch, N yaw, N roll);

/**
 *  @brief toAxisAngle
 *  Convert a rotational quaternion into Axis-Angle representation.
 *  
 *  @param q
 *  A rotational quaternion.
 *  
 *  @param outAxis
 *  A 3D vector which will represent the quaternion's axis of rotation in R^3.
 *  
 *  @param outAngle
 *  An angle, in radians, representing the quaternion's angle of rotation
 *  around a 3D axis in R^3.
 */
template <typename N> inline
void toAxisAngle(const quat_t<N>& q, vec3_t<N>& outAaxis, N& outAngle);

/**
 *  @brief toAxisAngle
 *  Convert a rotational quaternion into Axis-Angle representation.
 *  
 *  @param q
 *  A rotational quaternion.
 *  
 *  @return A 4D vector, representing the quaternion's axis of rotation in R^3
 *  and angle of rotation around the axis.
 *  The first 3 components are the converted X, Y, & Z points along a unit
 *  sphere, the last component of this vector is the angle.
 */
template <typename N> inline
vec4_t<N> toAxisAngle(const quat_t<N>& q);

/**
 *  @brief fromAxisAngle
 *  Convert a 3D axis, plus angle of rotation, into a rotational quaternion.
 *  
 *  @param axis
 *  A 3D vector, representing an axis of rotation.
 *  
 *  @param angle
 *  An angle, in radians, which represents the amount of rotation around the
 *  input axis.
 *  
 *  @return a rotational quaternion, converted from the input axis and angle.
 */
template <typename N> inline
quat_t<N> fromAxisAngle(const vec3_t<N>& axis, N angle);

/**
 *  @brief fromAxisAngle
 *  Convert a 4D axis-angle into a rotational quaternion.
 *  
 *  @param axisAngle
 *  A 4D vector in Axis-Angle format. The first 3 components of this vector
 *  are the X, Y, & Z components of the axis. The fourth component represents
 *  the angle.
 *  
 *  @return a rotational quaternion, converted from the input axis-angle
 *  vector.
 */
template <typename N> inline
quat_t<N> fromAxisAngle(const vec4_t<N>& axisAngle);

} // end math namespace
} // end ls namespace

#include "lightsky/math/generic/quat_utils_impl.h"

#endif /* __LS_MATH_QUAT_UTILS_H__ */
