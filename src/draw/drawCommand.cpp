/* 
 * File:   draw/drawCommand.cpp
 * Author: miles
 * 
 * Created on November 27, 2014, 10:57 PM
 */

#include "lightsky/draw/vertex.h"
#include "lightsky/draw/drawCommand.h"

namespace ls {
namespace draw {

/*-------------------------------------
 * Reset all parameters in *this to their default values.
-------------------------------------*/
void drawCommand::reset() {
    mode            = draw_mode_t::DEFAULT;
    command         = draw_command_t::ARRAYS;
    numInstances    = 1;
    drawFunc        = drawFunction{};
}

/*-------------------------------------
 * Determine how many instances are going to be rendered when
 * this draw command is used.
-------------------------------------*/
void drawCommand::setNumInstances(unsigned instanceCount) {
    numInstances = instanceCount;
    
    if (instanceCount > 1) {
        
    }
}

/*-------------------------------------
 * Retrieve the number of instances which are currently being drawn.
-------------------------------------*/
unsigned drawCommand::getNumInstances() const {
    return numInstances;
}

/*-------------------------------------
 * glDrawArrays(...)
-------------------------------------*/
void drawCommand::paramsArrays(int first, int count) {
    command = draw_command_t::ARRAYS;
    drawArrays& da = drawFunc.da;
    da.first = first;
    da.count = count;
}

/*-------------------------------------
 * glDrawArraysInstanced(...)
-------------------------------------*/
void drawCommand::paramsArraysInstanced(int first, int count, int instanceCount) {
    command = draw_command_t::ARRAYS_INSTANCED;
    drawArraysInstanced& dai = drawFunc.dai;
    dai.first = first;
    dai.count = count;
    dai.primCount = instanceCount;
    
}

/*-------------------------------------
 * glDrawElements(...)
-------------------------------------*/
void drawCommand::paramsElements(int count, draw_type_t indexType, const void* const pElements) {
    command = draw_command_t::ELEMENTS;
    drawElements& de = drawFunc.de;
    de.count = count;
    de.type = indexType;
    de.offset = pElements;
}

/*-------------------------------------
 * glDrawRangeElements(...)
-------------------------------------*/
void drawCommand::paramsElementsRanged(int count, draw_type_t indexType, const void* const pElements, unsigned rangeStart, unsigned rangeEnd) {
    command = draw_command_t::ELEMENTS_RANGED;
    drawElementsRanged& der = drawFunc.der;
    der.count = count;
    der.type = indexType;
    der.offset = pElements;
    der.start = rangeStart;
    der.end = rangeEnd;
}

/*-------------------------------------
 * glDrawElementsInstanced(...)
-------------------------------------*/
void drawCommand::paramsElementsInstanced(int count, draw_type_t indexType, const void* const pElements, int instanceCount) {
    command = draw_command_t::ELEMENTS_INSTANCED;
    drawElementsInstanced& dei = drawFunc.dei;
    dei.count = count;
    dei.type = indexType;
    dei.offset = pElements;
    dei.primCount = instanceCount;
}

/*-------------------------------------
 * Draw
-------------------------------------*/
void drawCommand::draw() const {
    const unsigned primRenderMode = LS_ENUM_VAL(mode);
    
    switch(command) {
        case draw_command_t::ARRAYS:
            glDrawArrays(primRenderMode, drawFunc.da.first, drawFunc.da.count);
            break;

        case draw_command_t::ARRAYS_INSTANCED:
            glDrawArraysInstanced(primRenderMode, drawFunc.dai.first, drawFunc.dai.count, drawFunc.dai.primCount);
            break;


        case draw_command_t::ELEMENTS:
            glDrawElements(primRenderMode, drawFunc.de.count, LS_ENUM_VAL(drawFunc.de.type), drawFunc.de.offset);
            break;

        case draw_command_t::ELEMENTS_RANGED:
            glDrawRangeElements(primRenderMode, drawFunc.der.start, drawFunc.der.end, drawFunc.der.count, LS_ENUM_VAL(drawFunc.der.type), drawFunc.der.offset);
            break;
        case draw_command_t::ELEMENTS_INSTANCED:
            glDrawElementsInstanced(primRenderMode, drawFunc.dei.count, LS_ENUM_VAL(drawFunc.dei.type), drawFunc.dei.offset, drawFunc.dei.primCount);
            break;

        default:
            LS_DEBUG_ASSERT(false);
            break;
    }
}

/*-------------------------------------
 * Draw geometry using a single VBO
-------------------------------------*/
void drawCommand::draw(const vertexBuffer& vbo) const {
    vbo.bind();
    
    glEnableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_POS));
    glEnableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_TEX));
    glEnableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_NORM));
    
    glVertexAttribPointer(
        LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_POS),
        LS_ARRAY_SIZE(vertex::pos.v), GL_FLOAT, GL_FALSE, sizeof(vertex),
        (GLvoid*)LS_ENUM_VAL(vertex_desc_t::ELEMENT_COUNT_POS)
    );
    
    glVertexAttribPointer(
        LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_TEX),
        LS_ARRAY_SIZE(vertex::uv.v), GL_FLOAT, GL_FALSE, sizeof(vertex),
        (GLvoid*)LS_ENUM_VAL(vertex_desc_t::ELEMENT_COUNT_TEX)
    );
    
    glVertexAttribPointer(
        LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_NORM),
        LS_ARRAY_SIZE(vertex::norm.v), GL_FLOAT, GL_FALSE, sizeof(vertex),
        (GLvoid*)LS_ENUM_VAL(vertex_desc_t::ELEMENT_COUNT_NORM)
    );
    
    draw();
    
    glDisableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_POS));
    glDisableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_TEX));
    glDisableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_NORM));
    
    vbo.unbind();
}

} // end draw namespace
} // end ls namespace

