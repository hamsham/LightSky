/* 
 * File:   scriptMath.h
 * Author: hammy
 *
 * Created on December 27, 2014, 1:53 AM
 */

#ifndef __LS_SCRIPT_MATH_H__
#define	__LS_SCRIPT_MATH_H__

#include "lightsky/script/variable.h"
#include "lightsky/script/functor.h"

/*-----------------------------------------------------------------------------
    Built-In Math Types
-----------------------------------------------------------------------------*/
namespace ls {
namespace script {

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

