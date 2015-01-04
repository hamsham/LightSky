
namespace ls {
namespace draw {

/*-------------------------------------
 * Get the GPU-Assigned ID that this object references.
-------------------------------------*/
inline unsigned renderbuffer::getId() const {
    return rboId;
}

/*-------------------------------------
 * Bind the current renderbuffer to OpenGL
-------------------------------------*/
inline void renderbuffer::bind() const {
    glBindFramebuffer(GL_RENDERBUFFER, rboId);
}

/*-------------------------------------
 * Unbind the current renderbuffer to OpenGL
-------------------------------------*/
inline void renderbuffer::unbind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

} // end draw namespace
} // end ls namespace
