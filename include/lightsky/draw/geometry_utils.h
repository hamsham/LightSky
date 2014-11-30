/* 
 * File:   draw/geometry.h
 * Author: Miles Lacey
 *
 * Created on April 6, 2014, 5:08 PM
 */

#ifndef __LS_DRAW_GEOMETRY_UTILS_H__
#define	__LS_DRAW_GEOMETRY_UTILS_H__

#include "lightsky/draw/setup.h"

namespace ls {
namespace draw {

    /**------------------------------------------------------------------------
     * Helper function to calculate a vertex normal from 3 vertices.
     * 
     * @param v0
     * @param v1
     * @param v2
     * 
     * @return A 3-dimensional vector that represents a vertex normal.
    -------------------------------------------------------------------------*/
    math::vec3 calcNormal(
        const math::vec3& v0,
        const math::vec3& v1,
        const math::vec3& v2
    );
    
    /**------------------------------------------------------------------------
     * Calculate the tangents for a set of triangles (placed in a vertex array).
     * 
     * @param vertCount
     * The number of vertices in the input arrays.
     * 
     * @param positions
     * A pointer to an array (of size 'vertCount') of 3D vectors, representing
     * the positions of a set of triangles.
     * 
     * @param uvs
     * A pointer to an array (of size 'vertCount') of 3D vectors, representing
     * the uvs of a set of triangles.
     * 
     * @param tangents
     * A pointer to an array (of size 'vertCount') of 3D vectors, representing
     * the tangents of a set of triangles.
     * 
     * @param bitangents
     * A pointer to an array (of size 'vertCount') of 3D vectors, representing
     * the bitangents of a set of triangles.
     * 
    -------------------------------------------------------------------------*/
    void calcTangents(
        unsigned vertCount,
        const math::vec3* const positions,
        const math::vec2* const uvs,
        math::vec3* tangents,
        math::vec3* bitangents
    );

} // end draw namespace
} // end ls namespace

#endif	/* __LS_DRAW_GEOMETRY_UTILS_H__ */

