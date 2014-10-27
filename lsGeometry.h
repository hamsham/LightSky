/* 
 * File:   geometry.h
 * Author: miles
 *
 * Created on April 6, 2014, 5:08 PM
 */

#ifndef __LS_GEOMETRY_H__
#define	__LS_GEOMETRY_H__

#include "main.h"

namespace geometry {
    /**
     * Helper function to calculate a vertex normal from 3 vertices.
     * 
     * @param v0
     * @param v1
     * @param v2
     * 
     * @return A 3-dimensional vector that represents a vertex normal.
     */
    math::vec3 calcNormal(
        const math::vec3& v0,
        const math::vec3& v1,
        const math::vec3& v2
    );
    
    /**
     * Calculate the tangents for a set of triangles (placed in a vertex array).
     * @param vertCount
     * The number of vertices in the arrays.
     * 
     * @param vertCount
     * The number of vertices that need tangents calculated
     * 
     * @param positions
     * @param uvs
     * @param tangents
     * @param bitangents
     */
    void calcTangents(
        unsigned vertCount,
        math::vec3* positions,
        math::vec2* uvs,
        math::vec3* tangents,
        math::vec3* bitangents
    );
}

#endif	/* __LS_GEOMETRY_H__ */

