/* 
 * File:   draw/drawCommand.h
 * Author: miles
 *
 * Created on November 27, 2014, 10:57 PM
 */

#ifndef __LS_DRAW_DRAW_COMMAND_H__
#define	__LS_DRAW_DRAW_COMMAND_H__

#include "lightsky/setup/macros.h"

#include "lightsky/draw/vertexArray.h"

namespace ls {
namespace draw {

/**----------------------------------------------------------------------------
 * Draw modes for renderable types.
-----------------------------------------------------------------------------*/
enum class draw_mode_t : int {
    POINTS                = GL_POINTS,

    LINE_STRIP            = GL_LINE_STRIP,
    LINE_LOOP             = GL_LINE_LOOP,
    LINES                 = GL_LINES,
    TRI_STRIP             = GL_TRIANGLE_STRIP,
    TRI_FAN               = GL_TRIANGLE_FAN,
    TRIS                  = GL_TRIANGLES,

    DEFAULT               = GL_TRIANGLES
};

/**----------------------------------------------------------------------------
 * Data type for the indices used during an indexed draw command.
-----------------------------------------------------------------------------*/
typedef unsigned int draw_index_t;

enum : int {
    INDEX_DATA_UBYTE    = GL_UNSIGNED_BYTE,
    INDEX_DATA_USHORT   = GL_UNSIGNED_SHORT,
    INDEX_DATA_UINT     = GL_UNSIGNED_INT,
    
    INDEX_DATA_DEFAULT  = GL_UNSIGNED_INT,
    INDEX_DATA_INVALID  = -1,
};

/**------------------------------------
 * @brief draw_index_pair_t
 *
 * Contains the index of the first vertex to be drawn in an OpenGL draw call
 * and the total number of vertices to be rendered. Only glDrawArrays() and
 * glDrawElements() are suppported as they pretty much cover 90% of typical
 * render use cases.
 *
 * For a call to glDrawArrays(...), this pair specifies the "first" and "count"
 * parameters, respectively.
 *
 * For a call to glDrawElements(...), this pair indicates the "indices*" and
 * "count" parameters, in that order.
-------------------------------------*/
struct draw_index_pair_t {
    unsigned first;
    unsigned count;
};

enum index_element_t : int {
    INDEX_TYPE_UBYTE = GL_UNSIGNED_BYTE,
    INDEX_TYPE_USHORT = GL_UNSIGNED_SHORT,
    INDEX_TYPE_UINT = GL_UNSIGNED_INT,
    
    INDEX_TYPE_DEFAULT = GL_UNSIGNED_INT
};

/**------------------------------------
 * @brief draw_index_list_t
 *
 * Mappings of mesh indices to their rendering parameters (first/count
 * or index0/indexN).
-------------------------------------*/
typedef std::vector<draw_index_pair_t> draw_index_list_t;

/**----------------------------------------------------------------------------
 * @brief Draw commands for rendering OpenGL Meshes.
 *
 * The draw command is a simple class which contains the basic information
 * required to render an object within OpenGL. For example, it determines if
 * the functions "glDrawElements()" or "glDrawArrays()" be used.It will also
 * determine if GL_TRIANGLES will be used versus GL_TRIANGLE_STRIP.
-----------------------------------------------------------------------------*/
struct drawCommand {
    draw_mode_t mode = draw_mode_t::DEFAULT;

    unsigned first = 0;

    unsigned count = 1;
    
    index_element_t indexType = INDEX_TYPE_DEFAULT;

    void draw(const vertexArray& vao) const;
};

} // end draw namespace
} // end ls namespace

#endif	/* __LS_DRAW_DRAW_COMMAND_H__ */

