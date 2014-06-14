/* 
 * File:   vertex.h
 * Author: miles
 *
 * Created on April 30, 2014, 8:51 PM
 */

#ifndef __LS_VERTEX_H__
#define	__LS_VERTEX_H__

#include "lsSetup.h"

/*
 * Vertex types and identifiers.
 * This header describes the vertex types that can be used throughout the LS
 * framework. Additional vertex types are added and updated as necessary.
 */

/**
 * Basic vertex building block in LS.
 * This vertex type contains enough information to light a textured mesh.
 */
struct lsVertex {
    math::vec3 pos;
    math::vec2 uv;
    math::vec3 norm;
};

/*
 * These global macros that van be used to describe vertex layouts to Vertex
 * Array Objects.
 */
#ifndef LS_VERTEX_POSITION_ATTRIB
    #define LS_VERTEX_POSITION_ATTRIB 0
#endif

#ifndef LS_VERTEX_TEXTURE_ATTRIB
    #define LS_VERTEX_TEXTURE_ATTRIB 1
#endif

#ifndef LS_VERTEX_NORMAL_ATTRIB
    #define LS_VERTEX_NORMAL_ATTRIB 2
#endif

#ifndef LS_MODEL_MATRIX_ATTRIB
    #define LS_MODEL_MATRIX_ATTRIB
    #define LS_MODEL_MATRIX_ATTRIB0 3 /* Row 1 */
    #define LS_MODEL_MATRIX_ATTRIB1 4 /* Row 2 */
    #define LS_MODEL_MATRIX_ATTRIB2 5 /* Row 3 */
    #define LS_MODEL_MATRIX_ATTRIB3 6 /* Row 4 */
#endif

#endif	/* __LS_VERTEX_H__ */

