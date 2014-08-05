/* 
 * File:   lsBlendObject.cpp
 * Author: miles
 * 
 * Created on August 3, 2014, 6:53 PM
 */

#include "lsBlendObject.h"

/*
 * Enable blending and apply blend parameters to OpenGL.
 */
void lsBlendObject::bind() const {
    if (!enabled) {
        glDisable(LS_BLEND);
        return;
    }
    
    glEnable(LS_BLEND);
    
    glBlendColor(blendCol[0], blendCol[1], blendCol[2], blendCol[3]);
    
    glBlendEquationSeparate(rgbBlendEq, alphaBlendEq);
    
    glBlendFuncSeparate(srcRgbBlendFunc, dstRgbBlendFunc, srcAlphaBlendFunc, dstAlphaBlendFunc);
}

/*
 * Disable OpenGL blending
 */
void lsBlendObject::unbind() const {
    // the default constructor already has default OpenGL params.
    lsBlendObject blender{};
    blender.bind();
}

/*
 * Reset all members to their default values.
 */
void lsBlendObject::reset() {
    *this = lsBlendObject{};
}
