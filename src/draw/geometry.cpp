/*
 * File:   draw/geometry.cpp
 * Author: Miles Lacey
 * 
 * Created on April 6, 2014, 12:36 AM
 */

#include <utility>

#include "lightsky/utils/assertions.h"

#include "lightsky/draw/geometry.h"

namespace ls {
namespace draw {

/*-------------------------------------
    Constructor
-------------------------------------*/
geometry::geometry() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
geometry::geometry(geometry&& g) :
    vbo{std::move(g.vbo)},
    ibo{std::move(g.ibo)},
    drawParams{std::move(g.drawParams)}
{}

/*-------------------------------------
    Move Operator
-------------------------------------*/
geometry& geometry::operator=(geometry&& g) {
    vbo = std::move(g.vbo);
    
    ibo = std::move(g.ibo);
    
    drawParams = g.drawParams;
    g.drawParams.reset();
    
    return *this;
}

/*-------------------------------------
    Destructor
-------------------------------------*/
geometry::~geometry() {
    terminate();
}

/*-------------------------------------
    Unload all GPU-based resource that are used by *this;
-------------------------------------*/
void geometry::terminate() {
    terminate_buffer(vbo);
    terminate_buffer(ibo);
    drawParams.reset();
}

/*-------------------------------------
 * Initialize a geometry object using a preexisting VBO.
-------------------------------------*/
void geometry::init(const BufferObject& v, const drawCommand& d) {
    terminate_buffer_object(vbo);
    vbo = v;
    drawParams = d;
}

/*-------------------------------------
 * @brief Initialize a geometry object using a preexisting VBO.
-------------------------------------*/
void geometry::init(BufferObject&& v, drawCommand&& d) {
    terminate_buffer_object(vbo);
    vbo = std::move(v);
    drawParams = std::move(d);
}

/*-------------------------------------
 * Initialize a geometry object using a preexisting VBO.
-------------------------------------*/
void geometry::init(
    const BufferObject& v,
    const BufferObject& i,
    const drawCommand& d
) {
    init(v, d);
    
    terminate_buffer_object(ibo);
    ibo = i;
}

/*-------------------------------------
 * Initialize a geometry object using a preexisting VBO.
-------------------------------------*/
void geometry::init(
    BufferObject&& v,
    BufferObject&& i,
    drawCommand&& d
) {
    init(v, d);
    
    terminate_buffer_object(ibo);
    ibo = std::move(i);
}

} // end draw namespace
} // end ls namespace
