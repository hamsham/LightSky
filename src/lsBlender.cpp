/* 
 * File:   lsBlender.cpp
 * Author: miles
 * 
 * Created on August 3, 2014, 6:53 PM
 */

#include "lsBlender.h"

/*
 * Reset all members to their default values.
 */
void lsBlender::reset() {
    blendCol = lsBlank;
    
    rgbBlendEq = LS_BLEND_ADD;
    alphaBlendEq = LS_BLEND_ADD;
    
    srcRgbBlendFunc = LS_ONE;
    dstRgbBlendFunc = LS_ZERO;
    srcAlphaBlendFunc = LS_ONE;
    dstAlphaBlendFunc = LS_ZERO;
}

/*
 * Enable blending and apply blend parameters to OpenGL.
 */
void lsBlender::bind() const {
    glEnable(LS_BLEND);
    
    glBlendColor(blendCol[0], blendCol[1], blendCol[2], blendCol[3]);
    
    glBlendEquationSeparate(rgbBlendEq, alphaBlendEq);
    
    glBlendFuncSeparate(srcRgbBlendFunc, dstRgbBlendFunc, srcAlphaBlendFunc, dstAlphaBlendFunc);
}
