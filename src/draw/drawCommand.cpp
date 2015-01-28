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

/*------------------------------------
    Reset the current members.
-------------------------------------*/
void drawCommand::reset() {
    *this = drawCommand{};
}

/*-------------------------------------
    Bind Vertex Attributes
-------------------------------------*/
void drawCommand::bindAttribs() const {
    glEnableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_POS));
    glEnableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_TEX));
    glEnableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_NORM));
}

/*-------------------------------------
    Unbind Vertex Attributes
-------------------------------------*/
void drawCommand::unbindAttribs() const {
    glDisableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_POS));
    glDisableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_TEX));
    glDisableVertexAttribArray(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_NORM));
}

/*-------------------------------------
    Set Vertex Attributes
-------------------------------------*/
void drawCommand::setAttribPointers() const {
    // Vertex positions
    glVertexAttribPointer(
        LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_POS),
        LS_ARRAY_SIZE(vertex::pos.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex),
        (GLvoid*)LS_ENUM_VAL(vertex_desc_t::ELEMENT_COUNT_POS)
    );

    // Vertex UVs
    glVertexAttribPointer(
        LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_TEX),
        LS_ARRAY_SIZE(vertex::uv.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex),
        (GLvoid*)LS_ENUM_VAL(vertex_desc_t::ELEMENT_COUNT_TEX)
    );

    // Vertex normals
    glVertexAttribPointer(
        LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_NORM),
        LS_ARRAY_SIZE(vertex::norm.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex),
        (GLvoid*)LS_ENUM_VAL(vertex_desc_t::ELEMENT_COUNT_NORM)
    );
}

/*------------------------------------
    Render a standard VBO
-------------------------------------*/
void drawCommand::draw(const vertexBuffer& vbo) const {
    vbo.bind();

    bindAttribs();
    setAttribPointers();

    glDrawArrays(LS_ENUM_VAL(mode), first, count);
    unbindAttribs();

    vbo.unbind();
}

/*------------------------------------
    Render a VBO+IBO
-------------------------------------*/
void drawCommand::draw(const vertexBuffer& vbo, const indexBuffer& ibo) const {
    vbo.bind();
    ibo.bind();

    bindAttribs();
    setAttribPointers();

    const uintptr_t offset = first;
    glDrawElements(LS_ENUM_VAL(mode), count, indexType, (const void*)offset);

    unbindAttribs();
    LOG_GL_ERR();

    ibo.unbind();
    vbo.unbind();
}

/*------------------------------------
    Render a standard VAO
-------------------------------------*/
void drawCommand::draw(const vertexArray& vao) const {
    vao.bind();
    
    if (indexType == INDEX_TYPE_NONE) {
        glDrawArrays(LS_ENUM_VAL(mode), first, count);
    }
    else {
        const uintptr_t offset = first;
        glDrawElements(LS_ENUM_VAL(mode), count, indexType, (const void*)offset);
    }

    LOG_GL_ERR();
    
    vao.unbind();
}

/*------------------------------------
    Render a standard VAO
-------------------------------------*/
void drawCommand::draw(const vertexArray& vao, unsigned instanceCount) const {
    vao.bind();
    
    if (indexType == INDEX_TYPE_NONE) {
        glDrawArraysInstanced(LS_ENUM_VAL(mode), first, count, instanceCount);
    }
    else {
        const uintptr_t offset = first;
        glDrawElementsInstanced(LS_ENUM_VAL(mode), count, indexType, (const void*)offset, instanceCount);
    }
    
    LOG_GL_ERR();
    
    vao.unbind();
}

} // end draw namespace
} // end ls namespace

