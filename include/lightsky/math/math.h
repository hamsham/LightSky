/* 
 * File:   math/math.h
 * Author: Miles Lacey
 *
 * This file contains all includes for the math module of LightSky.
 */

#ifndef __LS_MATH_H__
#define __LS_MATH_H__

/*
 * NOTES:
 * All angle measurements used by this library are in radians unless specified
 * otherwise.
 * I also use constructors rather than assignments when creating objects and
 * variables, so this might make readability slightly difficult at first.
 */

#include "lightsky/math/setup.h"
#include "lightsky/math/types.h"

#include "lightsky/math/fixed.h"
#include "lightsky/math/mat2.h"
#include "lightsky/math/mat3.h"
#include "lightsky/math/mat4.h"
#include "lightsky/math/quat.h"
#include "lightsky/math/vec2.h"
#include "lightsky/math/vec3.h"
#include "lightsky/math/vec4.h"

#include "lightsky/math/scalar_utils.h"
#include "lightsky/math/quat_utils.h"
#include "lightsky/math/vec_utils.h"
#include "lightsky/math/mat_utils.h"

#include "lightsky/math/perlinNoise.h"

#endif /* __LS_MATH_H__ */
