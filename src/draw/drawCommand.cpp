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
    Render a standard VAO
-------------------------------------*/
void drawCommand::draw(const vertexArray& vao) const {
    vao.bind();
    
    if (indexType == INDEX_DATA_INVALID) {
        glDrawArrays(LS_ENUM_VAL(mode), first, count);
    }
    else {
        const uintptr_t offset = first;
        glDrawElements(LS_ENUM_VAL(mode), count, indexType, (const void*)offset);
    }
    
    LS_LOG_GL_ERR();
    
    vao.unbind();
}

} // end draw namespace
} // end ls namespace

