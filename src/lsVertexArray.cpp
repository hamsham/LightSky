/* 
 * File:   vertexArray.cpp
 * Author: hammy
 * 
 * Created on February 7, 2014, 8:01 PM
 */

#include "lsVertexArray.h"

lsVertexArray::lsVertexArray() {
}
        
/*
 * Move Constructor
 */
lsVertexArray::lsVertexArray(lsVertexArray&& va) :
    vao{va.vao}
{
    va.vao = 0;
}
        
/*
 * Destructor
 */
lsVertexArray::~lsVertexArray() {
    terminate();
}
        
/*
 * Move Operator
 */
lsVertexArray& lsVertexArray::operator=(lsVertexArray&& va) {
    vao = va.vao;
    va.vao = 0;
    return *this;
}
        
/*
 * Array initialization.
 */
bool lsVertexArray::init() {
    if (vao != 0) {
        terminate();
    }

    glGenVertexArrays(1, &vao);
    return vao != 0;
}
