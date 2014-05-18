/* 
 * File:   renderer.cpp
 * Author: miles
 * 
 * Created on May 17, 2014, 5:34 PM
 */

#include "renderer.h"

/*
 * Renderer initialization
 */
bool renderer::init() {
    LOG_MSG(
        "Initializing Renderer:"
        "\n\tFace Culling:      ", getFaceCulling(),
        "\n\tDepth Testing:     ", getDepthTesting(),
        "\n\tBlending State:    ", getBlending(),
        '\n'
    );
    
    return true;
}

/*
 * Renderer resource termination
 */
void renderer::terminate() {
}
