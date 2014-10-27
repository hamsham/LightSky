
namespace ls {
namespace draw {

/*-------------------------------------
    Set the position and size of the viewport.
-------------------------------------*/
inline void renderer::setViewport(const math::vec2i& pos, const math::vec2i& size) {
    glViewport(pos[0], pos[1], size[0], size[1]);
}

/*-------------------------------------
    Set the polygon winding order.
-------------------------------------*/
inline void renderer::setWindingOrder(winding_order_t wo) {
    glFrontFace(wo);
    LOG_GL_ERR();
}

/*-------------------------------------
    Retrieve the current winding order.
-------------------------------------*/
inline winding_order_t renderer::getWindingOrder() const {
    int wo;
    glGetIntegerv(FACE_CULL_FRONT, &wo);
    return (winding_order_t)wo;
}

/*-------------------------------------
    Set the face culling mode.
-------------------------------------*/
inline void renderer::setFaceCulling(bool fc) {
    fc == true ? glEnable(FACE_CULL) : glDisable(FACE_CULL);
    LOG_GL_ERR();
}

/*-------------------------------------
    Retrieve the current face culling mode.
-------------------------------------*/
inline bool renderer::getFaceCulling() const {
    bool faceCull;
    glGetBooleanv(FACE_CULL, (GLboolean*)&faceCull);
    LOG_GL_ERR();
    return faceCull;
}

/*-------------------------------------
    Enable/Disable depth testing
-------------------------------------*/
inline void renderer::setDepthTesting(bool dt) {
    dt == true ? glEnable(RENDER_TEST_DEPTH) : glDisable(RENDER_TEST_DEPTH);
}

/*-------------------------------------
    Determine if depth testing is enabled/disabled.
-------------------------------------*/
inline bool renderer::getDepthTesting() const {
    bool depthTest;
    glGetBooleanv(RENDER_TEST_DEPTH, (GLboolean*)&depthTest);
    LOG_GL_ERR();
    return depthTest;
}

} // end draw namespace
} // end ls namespace
