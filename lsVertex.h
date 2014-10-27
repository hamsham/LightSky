/* 
 * File:   vertex.h
 * Author: miles
 *
 * Created on April 30, 2014, 8:51 PM
 */

#ifndef __LS_VERTEX_H__
#define	__LS_VERTEX_H__

#include "main.h"

/*
 * Vertex types and identifiers.
 * This header describes the vertex types that can be used throughout the LS
 * framework. Additional vertex types are added and updated as necessary.
 */

/**
 * Basic vertex building block in LS.
 * This vertex type contains enough information to light a textured mesh.
 */
struct litVertex {
    math::vec3 pos;
    math::vec2 uv;
    math::vec3 norm;
};

/**
 * A simple vertex which only contains positions and texture coords
 */
struct plainVertex {
    math::vec3 pos;
    math::vec2 uv;
};

enum vertex_type {
    PLAIN_VERTEX,
    LIT_VERTEX
};

/*
 * Global vertex typedefs
 */
typedef litVertex vertex;
typedef plainVertex textVertex;
typedef plainVertex texturedVertex;

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
    #define LS_MODEL_MATRIX_ATTRIB 3
    #define LS_MODEL_MATRIX0_ATTRIB 3 /* Row 1 */
    #define LS_MODEL_MATRIX1_ATTRIB 4 /* Row 2 */
    #define LS_MODEL_MATRIX2_ATTRIB 5 /* Row 3 */
    #define LS_MODEL_MATRIX3_ATTRIB 6 /* Row 4 */
#endif

#endif	/* __LS_VERTEX_H__ */

