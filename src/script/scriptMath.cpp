/* 
 * File:   scriptMath.cpp
 * Author: hammy
 * 
 * Created on December 27, 2014, 1:53 AM
 */

#include <cmath>

#include "lightsky/script/scriptMath.h"

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
LS_SCRIPT_DEFINE_FUNC(addInts, scriptVar_int, scriptVar_int, scriptVar_int) {
    LS_SCRIPT_PARAM(0, int) = LS_SCRIPT_PARAM(1, int) + LS_SCRIPT_PARAM(2, int);
};

/*
 * Subtraction
 */
LS_SCRIPT_DEFINE_FUNC(subInts, scriptVar_int, scriptVar_int, scriptVar_int) {
    LS_SCRIPT_PARAM(0, int) = LS_SCRIPT_PARAM(1, int) - LS_SCRIPT_PARAM(2, int);
};

/*
 * Multiplication
 */
LS_SCRIPT_DEFINE_FUNC(mulInts, scriptVar_int, scriptVar_int, scriptVar_int) {
    LS_SCRIPT_PARAM(0, int) = LS_SCRIPT_PARAM(1, int) * LS_SCRIPT_PARAM(2, int);
};

/*
 * Division
 */
LS_SCRIPT_DEFINE_FUNC(divInts, scriptVar_int, scriptVar_int, scriptVar_int) {
    LS_SCRIPT_PARAM(0, int) = LS_SCRIPT_PARAM(1, int) / LS_SCRIPT_PARAM(2, int);
};

/*
 * Modulus
 */
LS_SCRIPT_DEFINE_FUNC(modInts, scriptVar_int, scriptVar_int, scriptVar_int) {
    LS_SCRIPT_PARAM(0, int) = LS_SCRIPT_PARAM(1, int) % LS_SCRIPT_PARAM(2, int);
};

/*-----------------------------------------------------------------------------
 Floats
-----------------------------------------------------------------------------*/
/*
 * Addition
 */
LS_SCRIPT_DEFINE_FUNC(addFloats, scriptVar_float, scriptVar_float, scriptVar_float) {
    LS_SCRIPT_PARAM(0, float) = LS_SCRIPT_PARAM(1, float) + LS_SCRIPT_PARAM(2, float);
};

/*
 * Subtraction
 */
LS_SCRIPT_DEFINE_FUNC(subFloats, scriptVar_float, scriptVar_float, scriptVar_float) {
    LS_SCRIPT_PARAM(0, float) = LS_SCRIPT_PARAM(1, float) - LS_SCRIPT_PARAM(2, float);
};

/*
 * Multiplication
 */
LS_SCRIPT_DEFINE_FUNC(mulFloats, scriptVar_float, scriptVar_float, scriptVar_float) {
    LS_SCRIPT_PARAM(0, float) = LS_SCRIPT_PARAM(1, float) * LS_SCRIPT_PARAM(2, float);
};

/*
 * Division
 */
LS_SCRIPT_DEFINE_FUNC(divFloats, scriptVar_float, scriptVar_float, scriptVar_float) {
    LS_SCRIPT_PARAM(0, float) = LS_SCRIPT_PARAM(1, float) / LS_SCRIPT_PARAM(2, float);
};

/*
 * Modulus
 */
LS_SCRIPT_DEFINE_FUNC(modFloats, scriptVar_float, scriptVar_float, scriptVar_float) {
    LS_SCRIPT_PARAM(0, float) = std::fmod(LS_SCRIPT_PARAM(1, float), LS_SCRIPT_PARAM(2, float));
};

} // end script namespace
} // end ls namespace
