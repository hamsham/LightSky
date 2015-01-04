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
#include "lightsky/draw/vertexBuffer.h"

namespace ls {
namespace draw {

/**----------------------------------------------------------------------------
 * Draw modes for renderable types.
-----------------------------------------------------------------------------*/
enum class draw_mode_t : int {
    POINTS      = GL_POINTS,
    
    LINE_STRIP  = GL_LINE_STRIP,
    LINE_LOOP   = GL_LINE_LOOP,
    LINES       = GL_LINES,
    
    TRI_STRIP   = GL_TRIANGLE_STRIP,
    TRI_FAN     = GL_TRIANGLE_FAN,
    TRIANGLES   = GL_TRIANGLES,
    
    DEFAULT     = GL_TRIANGLES
};

/**----------------------------------------------------------------------------
 * Draw modes for renderable types.
-----------------------------------------------------------------------------*/
enum class draw_type_t : int {
    UINT    = GL_UNSIGNED_INT,
    USHORT  = GL_UNSIGNED_SHORT,
    
    DEFAULT = GL_UNSIGNED_SHORT
};

/**----------------------------------------------------------------------------
 * Index type for draw calls
-----------------------------------------------------------------------------*/
typedef unsigned short draw_index_t;

/**----------------------------------------------------------------------------
 * Draw Parameter Identifiers
-----------------------------------------------------------------------------*/
enum class draw_command_t : int {
    ARRAYS,
    ARRAYS_INSTANCED,
    
    ELEMENTS,
    ELEMENTS_RANGED,
    ELEMENTS_INSTANCED
};

/*-----------------------------------------------------------------------------
 * Draw Command Parameters
-----------------------------------------------------------------------------*/
/**------------------------------------
 * glDrawArrays(...)
-------------------------------------*/
struct drawArrays {
    int first;
    int count;
};

/**------------------------------------
 * glDrawArraysInstanced(...)
-------------------------------------*/
struct drawArraysInstanced {
    int first;
    int count;
    unsigned primCount;
};

/**------------------------------------
 * glDrawElements(...)
-------------------------------------*/
struct drawElements {
    int count;
    draw_type_t type;
    const void* offset;
};

/**------------------------------------
 * glDrawRangeElements(...)
-------------------------------------*/
struct drawElementsRanged {
    unsigned start;
    unsigned end;
    int count;
    draw_type_t type;
    const void* offset;
};

/**------------------------------------
 * glDrawElementsInstanced(...)
-------------------------------------*/
struct drawElementsInstanced {
    int count;
    draw_type_t type;
    const void* offset;
    unsigned primCount;
};

/**----------------------------------------------------------------------------
 * Draw Function used to bind commands.
-----------------------------------------------------------------------------*/
union drawFunction {
    drawArrays              da;
    drawElements            de;
    drawElementsRanged      der;
    drawArraysInstanced     dai;
    drawElementsInstanced   dei;
};

/**----------------------------------------------------------------------------
 * Draw Commands to use arrays or drawn elements.
-----------------------------------------------------------------------------*/
class drawCommand {
    private:
        draw_mode_t      mode           = draw_mode_t::DEFAULT;
        draw_command_t  command         = draw_command_t::ARRAYS;
        unsigned        numInstances    = 1;
        drawFunction    drawFunc;
        
        /**
         * Render a set of vertices.
         */
        void draw() const;
        
    public:
        /**
         * @brief Reset all parameters in *this to their default values.
         */
        void reset();
        
        /**
         * @brief Set the method to draw primitives on the GPU (such as lines,
         * points, or triangles).
         * 
         * @param drawMode
         * An enumeration to indicate what type of primitive should be drawn
         * on the GPU.
         */
        void setDrawMode(draw_mode_t drawMode);
        
        /**
         * @brief Get the currently used draw mode.
         * 
         * @return An enumeration, indicating the current rendering method for
         * polygon primitives.
         */
        draw_mode_t getDrawMode() const;
        
        /**
         * @brief Get the currently used drawing command.
         * 
         * @return An enumeration, indicating what function is used to render
         * polygons in OpenGL.
         */
        draw_command_t getDrawCommand() const;
        
        /**
         * @brief get the draw function to be used by *this/
         * 
         * @return A constant reference to the draw function used to render
         * vertex data through OpenGL.
         */
        const drawFunction& getDrawFunction() const;
        
        /**
         * @brief Determine how many instances are going to be rendered when
         * this draw command is used.
         * 
         * @param instanceCount
         * An unsigned integral type, determining how many copies of each
         * vertex batch are to be rendered.
         */
        void setNumInstances(unsigned instanceCount);
        
        /**
         * Retrieve the number of instances which are currently being drawn.
         * 
         * @return an unsigned integral type which determines how many copies
         * of each instance are to be drawn.
         */
        unsigned getNumInstances() const;
        
        /**
         * @brief Draw a set of points from an array of vertices.
         * 
         * @param first
         * Specifies the first element in the array of vertices to be drawn.
         * 
         * @param count
         * Specifies the total number of vertices which are to be drawn.
         */
        void paramsArrays(int first, int count);
        
        /**
         * @brief Draw a set of points from an array of vertices. This will
         * draw each set of vertices multiple times.
         * 
         * @param first
         * Specifies the first element in the array of vertices to be drawn.
         * 
         * @param count
         * Specifies the total number of vertices which are to be drawn.
         * 
         * @param instanceCount
         * Indicates the number of times to repeat the drawing of "count"
         * vertices.
         */
        void paramsArraysInstanced(int first, int count, int instanceCount);
        
        /**
         * @brief Draw vertices using index values.
         * 
         * @param count The number of vertices to be drawn.
         * 
         * @param indexType Determines if the elements are specified using
         * unsigned integers or unsigned short integers.
         * 
         * @param pElements
         * A pointer which specifies the offset of the first index element.
         */
        void paramsElements(int count, draw_type_t indexType, const void* const pElements);
        
        /**
         * @brief Draw vertices using index values. This method also specifies
         * the maximum and minimum values for all indices.
         * 
         * @param count The number of vertices to be drawn.
         * 
         * @param indexType Determines if the elements are specified using
         * unsigned integers or unsigned short integers.
         * 
         * @param pElements
         * A pointer which specifies the offset of the first index element.
         * 
         * @param rangeStart
         * Determines the minimum values contained within the currently bound
         * index buffer.
         * 
         * @param rangeEnd
         * Determines the maximum values contained within the currently bound
         * index buffer.
         */
        void paramsElementsRanged(int count, draw_type_t indexType, const void* const pElements, unsigned rangeStart, unsigned rangeEnd);
        
        /**
         * @brief Draw instanced vertices using index values.
         * 
         * @param count The number of vertices to be drawn.
         * 
         * @param indexType Determines if the elements are specified using
         * unsigned integers or unsigned short integers.
         * 
         * @param pElements
         * A pointer which specifies the offset of the first index element.
         * 
         * @param instanceCount
         * The number of duplicate vertices which will be drawn through OpenGL.
         */
        void paramsElementsInstanced(int count, draw_type_t indexType, const void* const pElements, int instanceCount);
        
        /**
         * Render a set of vertices using a VAO.
         * 
         * @param vao
         * A constant reference to a vertex array object.
         */
        void draw(const vertexArray& vao) const;
        
        /**
         * Render a set of vertices using a VBO.
         * 
         * @param vbo
         * A constant reference to a vertex buffer object.
         */
        void draw(const vertexBuffer& vbo) const;
        
        /**
         * Render a set of vertices using a VBO + IBO.
         * 
         * @param vbo
         * A constant reference to a vertex buffer object.
         * 
         * @param ibo
         * A constant reference to an index buffer object.
         */
        void draw(const vertexBuffer& vbo, const indexBuffer& ibo) const;
};

/*-------------------------------------
 * Set the method to draw primitives on the GPU (such as lines,
 * points, or triangles).
-------------------------------------*/
inline void drawCommand::setDrawMode(draw_mode_t drawMode) {
    mode = drawMode;
}

/*-------------------------------------
 * Get the currently used draw mode.
-------------------------------------*/
inline draw_mode_t drawCommand::getDrawMode() const {
    return mode;
}

/*-------------------------------------
 * Get the currently used drawing command.
-------------------------------------*/
inline draw_command_t drawCommand::getDrawCommand() const {
    return command;
}

/*-------------------------------------
 * Get the draw function used by *this.
-------------------------------------*/
inline const drawFunction& drawCommand::getDrawFunction() const {
    return drawFunc;
}

/*-------------------------------------
 * Draw geometry using a single VAO
-------------------------------------*/
inline void drawCommand::draw(const vertexArray& vao) const {
    vao.bind();
    draw();
    vao.unbind();
}

/*-------------------------------------
 * Draw geometry using a VBO + VAO
-------------------------------------*/
inline void drawCommand::draw(const vertexBuffer& vbo, const indexBuffer& ibo) const {
    ibo.bind();
    draw(vbo);
    ibo.unbind();
}

} // end draw namespace
} // end ls namespace

#endif	/* __LS_DRAW_DRAW_COMMAND_H__ */

