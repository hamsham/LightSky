/* 
 * File:   scriptMath.h
 * Author: hammy
 *
 * Created on December 27, 2014, 1:53 AM
 */

#ifndef __LS_SCRIPT_MATH_H__
#define	__LS_SCRIPT_MATH_H__

#include "lightsky/math/vec2.h"
#include "lightsky/math/vec3.h"
#include "lightsky/math/vec4.h"
#include "lightsky/math/mat2.h"
#include "lightsky/math/mat3.h"
#include "lightsky/math/mat4.h"
#include "lightsky/math/quat.h"

#include "lightsky/script/scriptVariable.h"
#include "lightsky/script/scriptFunctor.h"

/*-----------------------------------------------------------------------------
    Built-In Math Types
-----------------------------------------------------------------------------*/
namespace ls {
namespace script {

/*-----------------------------------------------------------------------------
 Vector Types
-----------------------------------------------------------------------------*/
 // 2D vector
LS_SCRIPT_OVERRIDE_VAR_LOAD(math::vec2);
LS_SCRIPT_OVERRIDE_VAR_SAVE(math::vec2);
LS_SCRIPT_DECLARE_VAR(vec2, math::vec2);

 // 3D vector
LS_SCRIPT_OVERRIDE_VAR_LOAD(math::vec3);
LS_SCRIPT_OVERRIDE_VAR_SAVE(math::vec3);
LS_SCRIPT_DECLARE_VAR(vec3, math::vec3);

 // 4D vector
LS_SCRIPT_OVERRIDE_VAR_LOAD(math::vec4);
LS_SCRIPT_OVERRIDE_VAR_SAVE(math::vec4);
LS_SCRIPT_DECLARE_VAR(vec4, math::vec4);

 // 2D Matrix
LS_SCRIPT_OVERRIDE_VAR_LOAD(math::mat2);
LS_SCRIPT_OVERRIDE_VAR_SAVE(math::mat2);
LS_SCRIPT_DECLARE_VAR(mat2, math::mat2);

 // 3D Matrix
LS_SCRIPT_OVERRIDE_VAR_LOAD(math::mat3);
LS_SCRIPT_OVERRIDE_VAR_SAVE(math::mat3);
LS_SCRIPT_DECLARE_VAR(mat3, math::mat3);

 // 4D Matrix
LS_SCRIPT_OVERRIDE_VAR_LOAD(math::mat4);
LS_SCRIPT_OVERRIDE_VAR_SAVE(math::mat4);
LS_SCRIPT_DECLARE_VAR(mat4, math::mat4);

 // Quaternion
LS_SCRIPT_OVERRIDE_VAR_LOAD(math::quat);
LS_SCRIPT_OVERRIDE_VAR_SAVE(math::quat);
LS_SCRIPT_DECLARE_VAR(quat, math::quat);

/*-----------------------------------------------------------------------------
    Built-In Math Functions
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 Integers
-----------------------------------------------------------------------------*/
/*
 * Addition
 */
LS_SCRIPT_DECLARE_FUNC(addInts, scriptVar_int, scriptVar_int, scriptVar_int);

/*
 * Subtraction
 */
LS_SCRIPT_DECLARE_FUNC(subInts, scriptVar_int, scriptVar_int, scriptVar_int);

/*
 * Multiplication
 */
LS_SCRIPT_DECLARE_FUNC(mulInts, scriptVar_int, scriptVar_int, scriptVar_int);

/*
 * Division
 */
LS_SCRIPT_DECLARE_FUNC(divInts, scriptVar_int, scriptVar_int, scriptVar_int);

/*
 * Modulus
 */
LS_SCRIPT_DECLARE_FUNC(modInts, scriptVar_int, scriptVar_int, scriptVar_int);

/*-----------------------------------------------------------------------------
 Floating-Point Numbers
-----------------------------------------------------------------------------*/
/*
 * Addition
 */
LS_SCRIPT_DECLARE_FUNC(addFloats, scriptVar_float, scriptVar_float, scriptVar_float);

/*
 * Subtraction
 */
LS_SCRIPT_DECLARE_FUNC(subFloats, scriptVar_float, scriptVar_float, scriptVar_float);

/*
 * Multiplication
 */
LS_SCRIPT_DECLARE_FUNC(mulFloats, scriptVar_float, scriptVar_float, scriptVar_float);

/*
 * Division
 */
LS_SCRIPT_DECLARE_FUNC(divFloats, scriptVar_float, scriptVar_float, scriptVar_float);

/*
 * Modulus
 */
LS_SCRIPT_DECLARE_FUNC(modFloats, scriptVar_float, scriptVar_float, scriptVar_float);

} // end script namespace
} // end ls namespace

#endif	/* __LS_SCRIPT_MATH_H__ */

