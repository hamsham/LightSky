/* 
 * File:   scriptMath.cpp
 * Author: hammy
 * 
 * Created on December 27, 2014, 1:53 AM
 */

#include <cmath>

#include "lightsky/script/scriptFactory.h"
#include "lightsky/script/scriptMath.h"

/*-----------------------------------------------------------------------------
    Built-In Math Types
-----------------------------------------------------------------------------*/
namespace ls {
namespace script {

/*-----------------------------------------------------------------------------
 Vector Types
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Ugly Vector and quaternion saving
-------------------------------------*/
#define LS_SCRIPT_SAVE_VECTOR( varType ) LS_SCRIPT_OVERRIDE_VAR_SAVE( varType ) { \
    for (unsigned i = 0; i < LS_ARRAY_SIZE(data); ++i) { \
        if (i) { \
            ostr << ' '; \
        } \
        ostr << data[i]; \
    } \
    return ostr.good(); \
}

/*-------------------------------------
 * Ugly Vector, matrix, quaternion loading
-------------------------------------*/
#define LS_SCRIPT_LOAD_VECTOR( varType ) LS_SCRIPT_OVERRIDE_VAR_LOAD( varType ) { \
    (void)varImporter; \
    (void)funcImporter; \
    for (unsigned i = 0; i < LS_ARRAY_SIZE(data); ++i) { \
        istr >> data[i]; \
    } \
    return istr.good() || istr.eof(); \
}

/*-------------------------------------
 * Ugly matrix saving
-------------------------------------*/
#define LS_SCRIPT_SAVE_MATRIX( varType, x, y ) LS_SCRIPT_OVERRIDE_VAR_SAVE( varType ) { \
    for (unsigned i = 0; i < x; ++i) { \
        for (unsigned j = 0; j < y; ++j) { \
            if (i) { \
                ostr << ' '; \
            } \
            ostr << data[i][j]; \
        } \
    } \
    return ostr.good(); \
}

/*-------------------------------------
 * Ugly Vector, matrix, quaternion loading
-------------------------------------*/
#define LS_SCRIPT_LOAD_MATRIX( varType, x, y ) LS_SCRIPT_OVERRIDE_VAR_LOAD( varType ) { \
    (void)varImporter; \
    (void)funcImporter; \
    for (unsigned i = 0; i < x; ++i) { \
        for (unsigned j = 0; j < y; ++j) { \
            istr >> data[i][j]; \
        } \
    } \
    return istr.good() || istr.eof(); \
}

/*-------------------------------------
 * 2D Vector
-------------------------------------*/
LS_SCRIPT_DEFINE_VAR(vec2, math::vec2);
LS_SCRIPT_SAVE_VECTOR(math::vec2)
LS_SCRIPT_LOAD_VECTOR(math::vec2)

/*-------------------------------------
 * 3D Vector
-------------------------------------*/
LS_SCRIPT_DEFINE_VAR(vec3, math::vec3);
LS_SCRIPT_SAVE_VECTOR(math::vec3)
LS_SCRIPT_LOAD_VECTOR(math::vec3)

/*-------------------------------------
 * 4D Vector
-------------------------------------*/
LS_SCRIPT_DEFINE_VAR(vec4, math::vec4);
LS_SCRIPT_SAVE_VECTOR(math::vec4)
LS_SCRIPT_LOAD_VECTOR(math::vec4)

/*-------------------------------------
 * 2D Matrix
-------------------------------------*/
LS_SCRIPT_DEFINE_VAR(mat2, math::mat2);
LS_SCRIPT_SAVE_MATRIX(math::mat2, 2, 2)
LS_SCRIPT_LOAD_MATRIX(math::mat2, 2, 2)

/*-------------------------------------
 * 3D Matrix
-------------------------------------*/
LS_SCRIPT_DEFINE_VAR(mat3, math::mat3);
LS_SCRIPT_SAVE_MATRIX(math::mat3, 3, 3)
LS_SCRIPT_LOAD_MATRIX(math::mat3, 3, 3)

/*-------------------------------------
 * 4D Matrix
-------------------------------------*/
LS_SCRIPT_DEFINE_VAR(mat4, math::mat4);
LS_SCRIPT_SAVE_MATRIX(math::mat4, 4, 4)
LS_SCRIPT_LOAD_MATRIX(math::mat4, 4, 4)

/*-------------------------------------
 * Quaternion
-------------------------------------*/
LS_SCRIPT_DEFINE_VAR(quat, math::quat);
LS_SCRIPT_SAVE_VECTOR(math::quat)
LS_SCRIPT_LOAD_VECTOR(math::quat)

#undef LS_SCRIPT_SAVE_VECTOR
#undef LS_SCRIPT_LOAD_VECTOR
#undef LS_SCRIPT_SAVE_MATRIX
#undef LS_SCRIPT_LOAD_MATRIX

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
