/* 
 * File:   draw/drawCommand.h
 * Author: miles
 *
 * Created on November 27, 2014, 10:57 PM
 */

#ifndef __LS_DRAW_DRAW_COMMAND_H__
#define	__LS_DRAW_DRAW_COMMAND_H__

#include <vector>

#include "lightsky/setup/macros.h"

#include "lightsky/draw/vertex.h"
#include "lightsky/draw/vertexBuffer.h"
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

/**
 * @brief index_element_t helps to determine two things for draw commands:
 *      1. What the data type is for indices stored in the GPU/
 *      2. If a draw command should run use glDrawArrays() or glDrawElements().
 */
enum index_element_t : int {
    INDEX_TYPE_UBYTE = GL_UNSIGNED_BYTE,
    INDEX_TYPE_USHORT = GL_UNSIGNED_SHORT,
    INDEX_TYPE_UINT = GL_UNSIGNED_INT,
    
    INDEX_TYPE_DEFAULT = GL_UNSIGNED_INT,
    INDEX_TYPE_NONE  = -1
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
    unsigned first = 0;
    unsigned count = 0;
    
    constexpr draw_index_pair_t(const unsigned f = 0, const unsigned c = 0);
    
    constexpr draw_index_pair_t(const draw_index_pair_t& drawIndex);
    
    constexpr draw_index_pair_t(draw_index_pair_t&& drawIndex);
    
    draw_index_pair_t& operator = (const draw_index_pair_t& drawIndex);
    
    draw_index_pair_t& operator = (draw_index_pair_t&& drawIndex);
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
    public:
        draw_mode_t mode = draw_mode_t::DEFAULT;

        draw_index_pair_t indices = {0, 0};

        index_element_t indexType = INDEX_TYPE_NONE;

        void reset();

        void draw(const vertexBuffer& vbo) const;

        void draw(const vertexBuffer& vbo, const indexBuffer& ibo) const;

        void draw(const vertexArray& vao) const;

        void draw(const vertexArray& vao, unsigned instanceCount) const;

    private:
        void bindAttribs() const;
        
        void unbindAttribs() const;
        
        void setAttribPointers() const;
};

//bool init_draw_command(const BufferObject& bo, const vertexArray& vao);

//bool init_draw_command(const BufferObject& vbo, const BufferObject& ibo, const vertexArray& vao);

//void terminate_draw_command();

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/drawCommand_impl.h"

#endif	/* __LS_DRAW_DRAW_COMMAND_H__ */

