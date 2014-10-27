
namespace ls {
namespace draw {

/*-------------------------------------
    Get the GPU-Assigned ID that this object references.
-------------------------------------*/
inline unsigned framebuffer::getId() const {
    return fboId;
}

/*-------------------------------------
    Get the framebuffer acccess type.
-------------------------------------*/
inline fbo_access_t framebuffer::getAccessType() const {
    return access;
}

/*-------------------------------------
    Set the framebuffer access type.
-------------------------------------*/
inline void framebuffer::setAccessType(fbo_access_t a) {
    access = a;
}

/*-------------------------------------
    Get the maximum number of supported color attachments.
-------------------------------------*/
inline int framebuffer::getMaxNumAttachments() {
    int numAttachments;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &numAttachments);
    return numAttachments;
}

/*-------------------------------------
    Get the status of the current framebuffer.
-------------------------------------*/
inline fbo_status_t framebuffer::getStatus(const framebuffer& fbo) {
    LOG_GL_ERR();
    return (fbo_status_t)glCheckFramebufferStatus(fbo.getAccessType());
}

/*-------------------------------------
    Bind the default read/write buffer
-------------------------------------*/
inline void framebuffer::bindDefaultFramebuffer(fbo_access_t access) {
    glBindFramebuffer(access, 0);
}

/*-------------------------------------
    Bind the current framebuffer to OpenGL
-------------------------------------*/
inline void framebuffer::bind() const {
    glBindFramebuffer(access, fboId);
}

/*-------------------------------------
    Unbind the current framebuffer to OpenGL
-------------------------------------*/
inline void framebuffer::unbind() const {
    glBindFramebuffer(access, 0);
}

/*-------------------------------------
    Blit this framebuffer to the current draw buffer.
-------------------------------------*/
inline void framebuffer::blit(
    const math::vec2i& srcOrig, const math::vec2i& srcSize,
    const math::vec2i& dstOrig, const math::vec2i& dstSize,
    fbo_mask_t mask, ls_tex_filter_t filter
) const {
    glBlitFramebuffer(
        srcOrig[0], srcOrig[1], srcSize[0], srcSize[1],
        dstOrig[0], dstOrig[1], dstSize[0], dstSize[1],
        (GLbitfield)mask, (GLenum)filter
    );
}

/*-------------------------------------
    Clear the color attachment indicated by the input parameter.
-------------------------------------*/
inline void framebuffer::clear(fbo_mask_t mask) const {
    glClear((int)mask);
}

/*-------------------------------------
    Set the current draw targets to be used by this.
-------------------------------------*/
inline void framebuffer::setDrawTargets(unsigned numTargets, const fbo_attach_t* targets) {
    glDrawBuffers(numTargets, (const GLenum*)targets);
}

} // end draw namespace
} // end ls namespace
