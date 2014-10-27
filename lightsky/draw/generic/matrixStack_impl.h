
namespace ls {
namespace draw {

/*-------------------------------------
 * Multiply the selected matrix with the one passed into the function.
-------------------------------------*/
inline void matrixStack::multMatrix(matrix_use_t mt, const math::mat4& m) {
    stacks[mt].top() = m * stacks[mt].top();
}

/*-------------------------------------
 * Multiply the matrix stack
-------------------------------------*/
inline void matrixStack::constructMvp() {
    this->constructVp();
    mvpMatrix = vpMatrix * stacks[MATRIX_USE_MODEL].top();
}

/*-------------------------------------
 * Multiply the view and projection stacks
-------------------------------------*/
inline void matrixStack::constructVp() {
    vpMatrix = stacks[MATRIX_USE_PROJECTION].top() * stacks[MATRIX_USE_VIEW].top();
}

/*-------------------------------------
 * Get the current model matrix
-------------------------------------*/
inline const math::mat4& matrixStack::getMatrix(matrix_use_t mt) const {
    return stacks[mt].top();
}

/*-------------------------------------
 * Get the MVP Matrix
-------------------------------------*/
inline const math::mat4& matrixStack::getMvpMatrix() const {
    return mvpMatrix;
}

/*-------------------------------------
 * Get the VP Matrix
-------------------------------------*/
inline const math::mat4& matrixStack::getVpMatrix() const {
    return vpMatrix;
}

/*-------------------------------------
 * Clear a specific Stack
-------------------------------------*/
inline unsigned matrixStack::size(matrix_use_t mt) {
    return stacks[mt].size();
}

} // end draw namespace
} // end ls namespace
