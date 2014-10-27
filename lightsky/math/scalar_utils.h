/* 
 * File:   math/scalar_utils.h
 * Author: Miles Lacey
 *
 * Created on March 6, 2014, 10:04 PM
 */

#ifndef __LS_MATH_SCALAR_UTILS_H__
#define __LS_MATH_SCALAR_UTILS_H__

#include "lightsky/math/setup.h"
#include "lightsky/math/types.h"

namespace ls {
namespace math {

/**
 * @brief max
 * Get the minimum of two single numbers
 * This function can be run at compile-time.
 * 
 * @param a
 * 
 * @param b
 * 
 * @return The largest number of the two parameters a and b.
 */
template <typename scalar_t>
constexpr scalar_t min(scalar_t a, scalar_t b);

/**
 * @brief mix
 * Perform a linear interpolation of x between the two scalars a, b
 * @param a
 * @param b
 * 
 * @return The linear "mix" of a and b.
 */
template <typename scalar_t> constexpr
scalar_t mix(scalar_t a, scalar_t b, scalar_t percent);

/**
 * @brief max
 * Get the maximum of two single numbers.
 * This function can be run at compile-time.
 * 
 * @param a
 * 
 * @param b
 * 
 * @return The largest number of the two parameters a and b.
 */
template <typename scalar_t>
constexpr scalar_t max(scalar_t a, scalar_t b);

/**
 * @brief clamp
 * Bind a number to within a certain range.
 * 
 * @param n
 * A number that should be constrained to be within a specific range.
 * 
 * @param minVal
 * The minimum allowable value that 'n' can be.
 * 
 * @param maxVal
 * The maximum allowable value that 'n' can be.
 * 
 * @return a number, such that minVal <= n <= maxVal
 */
template <typename scalar_t>
constexpr scalar_t clamp(scalar_t n, scalar_t minVal, scalar_t maxVal);

/**
 * @brief smoothstep
 * Perform a smooth interpolation of a number along the sub-sequence [a, b].
 * 
 * @param a
 * A number within the same sub-sequence that x lies on.
 * 
 * @param b
 * A number within the same sub-sequence that x lies on.
 * 
 * @return The smooth linear interpolation of x in between the interval a and b.
 */
template <typename scalar_t> inline
scalar_t smoothstep(scalar_t a, scalar_t b, scalar_t x);

/**
 * @brief fastSqrt
 * Perform a square root on a single number without using the standard library.
 * This method uses IEEE floating point arithmetic. Use only if the input
 * argument uses this format.
 * 
 * @param a number whose square root should be obtained.
 * 
 * @return The square root of the input number.
 */
template <typename scalar_t>
inline scalar_t fastSqrt(scalar_t);

/**
 * @brief fastSqrt
 * Perform a square root on a single number without using the standard library.
 * This method uses IEEE floating point arithmetic. Use only if the input
 * argument uses this format.
 * 
 * @param a number whose square root should be obtained.
 * 
 * @return The square root of the input number.
 */
template <>
inline float fastSqrt<float>(float);

/**
 * @brief fastInvSqrt
 * Get the inverse square root of a number.
 * This method uses IEEE floating point arithmetic. Use only if the input
 * argument uses this format.
 * 
 * @param a number whose square root should be obtained.
 * 
 * @return The inverse square root (1/sqrt(x)) of the input number.
 */
template <typename scalar_t>
inline scalar_t fastInvSqrt(scalar_t);

/**
 * @brief fastInvSqrt
 * Get the inverse square root of a number.
 * This method uses IEEE floating point arithmetic. Use only if the input
 * argument uses this format.
 * 
 * @param a number whose square root should be obtained.
 * 
 * @return The inverse square root (1/sqrt(x)) of the input number.
 */
template <>
inline float fastInvSqrt<float>(float);

/**
 * @brief degToRad
 * Convert a number from degrees to radians.
 * 
 * @param the value of an angle, in degrees.
 * 
 * @return the value of an angle, in radians.
 */
template <typename scalar_t>
constexpr scalar_t degToRad(scalar_t);

/**
 * @brief radToDeg
 * Convert a number from radians to degrees.
 * This function can be run at compile-time.
 * 
 * @param the value of an angle, in radians.
 * 
 * @return the value of an angle, in degrees.
 */
template <typename scalar_t>
constexpr scalar_t radToDeg(scalar_t);

/**
 * @brief fastLog2
 * Calculate the log-base2 of a number
 *
 * @param a number
 *
 * @return the log-base2 of a number, using IEEE floating point arithmetic
 */
template <typename scalar_t>
inline scalar_t fastLog2(scalar_t);

/**
 * @brief fastLog2
 * Calculate the log-base2 of a number
 *
 * @param a number
 *
 * @return the log-base2 of a number, using IEEE floating point arithmetic
 */
template <>
inline float fastLog2<float>(float);

/**
 * @brief fastLog
 * Calculate the log-base10 of a number
 *
 * @param a number
 *
 * @return the log-base10 of a number, using IEEE floating point arithmetic
 */
template <typename scalar_t>
inline scalar_t fastLog(scalar_t);

/**
 * @brief fastLogBase
 * Calculate the log-base2 of a number
 *
 * @param a number
 *
 * @return the log-baseN of a number, using IEEE floating point arithmetic
 */
template <typename scalar_t>
inline scalar_t fastLogN(scalar_t baseN, scalar_t);

/**
 * @brief nextPow2
 * Find the next (greater) power of two that is closest to the value of a number
 * 
 * @param An unsigned integral type
 * 
 * @return The next greatest power of two.
 */
inline unsigned nextPow2(unsigned);

/**
 * @brief nextPow2
 * Find the next (greater) power of two that is closest to the value of a number
 * 
 * @param A signed integral type
 * 
 * @return The next greatest power of two.
 */
inline int nextPow2(int);

/**
 * @brief prevPow2
 * Find the previous (lesser) power of two that is closest to the value of a number
 * 
 * @param An unsigned integral type
 * 
 * @return The next lesser power of two.
 */
inline unsigned prevPow2(unsigned);

/**
 * @brief prevPow2
 * Find the previous (lesser) power of two that is closest to the value of a number
 * 
 * @param A signed integral type
 * 
 * @return The next lesser power of two.
 */
inline int prevPow2(int);

/**
 * @brief nearPow2
 * Find the closest power of two to a number. This may either be greater than
 * or less than the input number.
 * 
 * @param An unsigned integral type
 * 
 * @return The closest power of two to a number.
 */
inline unsigned nearPow2(unsigned);

/**
 * @brief nearPow2
 * Find the closest power of two to a number. This may either be greater than
 * or less than the input number.
 * 
 * @param A signed integral type
 * 
 * @return The closest power of two to a number.
 */
inline int nearPow2(int);

/**
 * @brief isPow2
 * Determine if a number is a power of two or not.
 * 
 * @param A number who's value should be evaluated.
 * 
 * @return True if the number is a poiwer of two.
 * False if the number is not a power of two.
 */
constexpr bool isPow2(unsigned);

/**
 * @brief isPow2
 * Determine if a number is a power of two or not.
 * 
 * @param A number who's value should be evaluated.
 * 
 * @return True if the number is a poiwer of two.
 * False if the number is not a power of two.
 */
constexpr bool isPow2(int);

/**
 * @brief factorial
 * Retrieve the factorial of a number
 * 
 * @param A number who's factorial is to be calculated.
 * 
 * @return The factorial of a given number.
 */
template <typename scalar_t>
constexpr scalar_t factorial(scalar_t);

/**
 * @brief pow
 * Evaluate a number to a given power.
 * 
 * @param A number who's power is to be evaluated.
 * 
 * @param The degree to which the first parameter's power should be evaluated.
 * 
 * @return A number, raised to a given power.
 */
template <typename scalar_t, typename int_t>
constexpr scalar_t pow(scalar_t, int_t);

/**
 * @brief const_sin
 * Evaluate the sine of an angle at compile-time.
 * 
 * @param An angle, in radians, who's sine value is to be calculated.
 * 
 * @return The sine of a given angle.
 */
template <typename scalar_t>
constexpr scalar_t const_sin(scalar_t);

/**
 * @brief const_cos
 * Evaluate the cosine of an angle at compile-time.
 * 
 * @param An angle, in radians, who's cosine value is to be calculated.
 * 
 * @return The cosine of a given angle.
 */
template <typename scalar_t>
constexpr scalar_t const_cos(scalar_t);

/**
 * @brief const_tan
 * Evaluate the tangent of an angle at compile-time.
 * 
 * @param An angle, in radians, who's tangent value is to be calculated.
 * 
 * @return The tangent of a given angle.
 */
template <typename scalar_t>
constexpr scalar_t const_tan(scalar_t);

/**
 * @brief sum
 * Evaluate the sum of a series of numbers at compile-time.
 * 
 * @param A set of numbers who's values are to be added together.
 * 
 * @return The sum of a set of numbers.
 */
template <typename scalar_t>
constexpr scalar_t sum(const scalar_t&);

/**
 * @brief sum
 * Evaluate the sum of a series of numbers at compile-time.
 * 
 * @param A set of numbers who's values are to be added together.
 * 
 * @return The sum of a set of numbers.
 */
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t sum(const scalar_t& num, const scalars_t&... nums);

/**
 * @brief average
 * Evaluate the average of a series of numbers at compile-time.
 * 
 * @param A set of numbers who's values are to be averaged.
 * 
 * @return The average of a set of numbers.
 */
template <typename scalar_t>
constexpr scalar_t average();

/**
 * @brief average
 * Evaluate the average of a series of numbers at compile-time.
 * 
 * @param A set of numbers who's values are to be averaged.
 * 
 * @return The average of a set of numbers.
 */
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t average(const scalar_t& num, const scalars_t&... nums);

} // end math namespace
} // end ls namespace

#include "lightsky/math/generic/scalar_utils_impl.h"

#endif /* __LS_MATH_SCALAR_UTILS_H__ */
