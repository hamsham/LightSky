/* 
 * File:   lsDepthObject.cpp
 * Author: miles
 * 
 * Created on August 4, 2014, 8:29 PM
 */

#include "lsDepthObject.h"

void lsDepthObject::bind() const {
    if (enabled) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }
    
    glClearDepth(depthClearVal);
    glDepthFunc(depthFunc);
    glDepthMask(depthMask);
    glDepthRange(depthNear, depthFar);
}

/*
 * Disable OpenGL depth parameters
 */
void lsDepthObject::unbind() const {
    // the default constructor already has default OpenGL params.
    const lsDepthObject depthObj{};
    depthObj.bind();
}

/*
 * Reset all members to their default values.
 */
void lsDepthObject::reset() {
    *this = lsDepthObject{};
}
