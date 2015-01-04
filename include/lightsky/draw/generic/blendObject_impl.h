
namespace ls {
namespace draw {

/*-------------------------------------
    Set whether blending should be enabled or disabled in the current rendering
    state.
-------------------------------------*/
inline void blendObject::setState(bool state) {
    enabled = state;
}

/*-------------------------------------
    Determine whether this blending object should tell OpenGL to enable or
    disable the use of blending.
-------------------------------------*/
inline bool blendObject::getState() const {
    return enabled;
}

/*-------------------------------------
    Set the blend Equation
-------------------------------------*/
inline void blendObject::setBlendEquation(blend_equ_t rgbaMode) {
    setBlendEquation(rgbaMode, rgbaMode);
}

/*-------------------------------------
    Set the blend Equation but with different values for RGB and Alpha
-------------------------------------*/
inline void blendObject::setBlendEquation(blend_equ_t rgbMode, blend_equ_t alphaMode) {
    rgbBlendEq = rgbMode;
    alphaBlendEq = alphaMode;
}

/*-------------------------------------
    Get the blending equation for the RGB channels.
-------------------------------------*/
inline blend_equ_t blendObject::getBlendEquationRgb() const {
    return rgbBlendEq;
}

/*-------------------------------------
    Get the blending equation for the alpha channel.
-------------------------------------*/
inline blend_equ_t blendObject::getBlendEquationAlpha() const {
    return alphaBlendEq;
}

/*-------------------------------------
    Set the source and destination blending function/
-------------------------------------*/
inline void blendObject::setBlendFunction(
    blend_func_t srcFactor, blend_func_t dstFactor
) {
    setBlendFunction(srcFactor, dstFactor, srcFactor, dstFactor);
}

/*-------------------------------------
    Set the source and destination blending function, with separate RGB
    and alpha functions.
-------------------------------------*/
inline void blendObject::setBlendFunction(
    blend_func_t srcRgb,     blend_func_t dstRgb,
    blend_func_t srcAlpha,   blend_func_t dstAlpha
) {
    srcRgbBlendFunc   = srcRgb;
    dstRgbBlendFunc   = dstRgb;
    srcAlphaBlendFunc = srcAlpha;
    dstAlphaBlendFunc = dstAlpha;
}

/*-------------------------------------
    Get the current blend function from the source RGB channel
-------------------------------------*/
inline blend_func_t blendObject::getBlendFunctionSrcRgb() const {
    return srcRgbBlendFunc;
}

/*-------------------------------------
    Get the current blend function from the source alpha channel
-------------------------------------*/
inline blend_func_t blendObject::getBlendFunctionSrcAlpha() const {
    return srcAlphaBlendFunc;
}

/*-------------------------------------
    Get the current blend function from the destination RGB channel
-------------------------------------*/
inline blend_func_t blendObject::getBlendFunctionDstRgb() const {
    return dstRgbBlendFunc;
}

/*-------------------------------------
    Get the current blend function from the destination alpha channel
-------------------------------------*/
inline blend_func_t blendObject::getBlendFunctionDstAlpha() const {
    return dstAlphaBlendFunc;
}

/*-------------------------------------
    Set the color that should be used for blending operations in OpenGL.
-------------------------------------*/
inline void blendObject::setBlendColor(const color::color& rgba) {
    blendCol = rgba;
}

/*-------------------------------------
    Get the current color that OpenGL is using for blending operations.
-------------------------------------*/
inline color::color blendObject::getBlendColor() const {
    return blendCol;
}

} // end draw namespace
} // end ls namespace
