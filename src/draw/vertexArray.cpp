/* 
 * File:   vertexArray.cpp
 * Author: Miles Lacey
 * 
 * Created on February 7, 2014, 8:01 PM
 */

#include "lightsky/draw/vertexArray.h"

namespace ls {
namespace draw {

/*-------------------------------------
    Constructor
-------------------------------------*/
vertexArray::vertexArray() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
vertexArray::vertexArray(vertexArray&& va) :
    vao{va.vao}
{
    va.vao = 0;
}

/*-------------------------------------
    Destructor
-------------------------------------*/
vertexArray::~vertexArray() {
    terminate();
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
vertexArray& vertexArray::operator=(vertexArray&& va) {
    vao = va.vao;
    va.vao = 0;
    return *this;
}

/*-------------------------------------
    Array initialization.
-------------------------------------*/
bool vertexArray::init() {
    if (vao != 0) {
        terminate();
    }

    glGenVertexArrays(1, &vao);
    return vao != 0;
}

} // end draw namespace
} // end ls namespace
