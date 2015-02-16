
namespace ls {
namespace draw {

/*-------------------------------------
 * Initialization Delegation
-------------------------------------*/
inline bool pickingBuffer::init(const math::vec2i& size) {
    return init(size[0], size[1]);
}

/*-------------------------------------
 * FBO Binding
-------------------------------------*/
inline void pickingBuffer::bind() const {
    fbo.bind();
}

/*-------------------------------------
 * FBO Releasing
-------------------------------------*/
inline void pickingBuffer::unbind() const {
    fbo.unbind();
}

} // end draw namepsace
} // end ls namespace
