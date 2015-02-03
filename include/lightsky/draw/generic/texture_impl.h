
namespace ls {
namespace draw {

/*-------------------------------------
    Get the GPU-Assigned ID used by *this.
-------------------------------------*/
inline unsigned texture::getId() const {
    return texId;
}

/*-------------------------------------
 Determine if *this can be used during rendering operations.
-------------------------------------*/
inline bool texture::isValid() const {
    return texId != 0;
}

/*-------------------------------------
    Bind the current texture to OpenGL
-------------------------------------*/
inline void texture::bind() const {
    glActiveTexture(slot);
    glBindTexture(dimensions, texId);
}

/*-------------------------------------
    Unbind the current texture to OpenGL
-------------------------------------*/
inline void texture::unbind() const {
    glActiveTexture(slot);
    glBindTexture(dimensions, 0);
}

/*-------------------------------------
 * Set the active texture slot.
-------------------------------------*/
inline void texture::setTextureSlot(tex_slot_t activeSlot) {
    slot = activeSlot;
}

/*-------------------------------------
 * Get the active texture slot.
-------------------------------------*/
inline tex_slot_t texture::getTextureSlot() const {
    return slot;
}

/*-------------------------------------
    Set a integer texture parameter.
    Make sure that "bind() const" has been called before using this method.
-------------------------------------*/
inline void texture::setParameter(int paramName, int param) const {
    glTexParameteri(dimensions, paramName, param);
}

/*-------------------------------------
    Set a float texture parameter.
    Make sure that "bind() const" has been called before using this method.
-------------------------------------*/
inline void texture::setParameter(int paramName, float param) const {
    glTexParameterf(dimensions, paramName, param);
}

/*-------------------------------------
    Create an OpenGL texture by using preexisting image data.
-------------------------------------*/
inline bool texture::init(const imageResource& resource, int mipmapLevel) {
    return init(
        mipmapLevel,
        resource.getInternalFormat(),
        resource.getPixelSize(),
        resource.getExternalFormat(),
        resource.getPixelType(),
        resource.getData()
    );
}

/*-------------------------------------
    Modify the internal data of a texture.
-------------------------------------*/
inline void texture::modify(int offset, int size, int format, int dataType, void* data) {
    glTexSubImage2D(getTexType(), 0, offset, 0, size, 0, format, dataType, data);
    LOG_GL_ERR();
}

/*-------------------------------------
    Modify the internal data of a texture.
-------------------------------------*/
inline void texture::modify(
    const math::vec2i& offset,
    const math::vec2i& size,
    int format,
    int dataType,
    void* data
) {
    glTexSubImage2D(getTexType(), 0, offset[0], offset[1], size[0], size[1], format, dataType, data);
    LOG_GL_ERR();
}

/*-------------------------------------
    Modify the internal data of a texture.
-------------------------------------*/
inline void texture::modify(
    const math::vec3i& offset,
    const math::vec3i& size,
    int format,
    int dataType,
    void* data
) {
    glTexSubImage3D(getTexType(), 0, offset[0], offset[1], offset[2], size[0], size[1], size[2], format, dataType, data);
    LOG_GL_ERR();
}

/*-------------------------------------
    Release all memory referenced by *this.
-------------------------------------*/
inline void texture::terminate() {
    glDeleteTextures(1, &texId);
    texId = 0;
    slot = tex_slot_t::TEXTURE_SLOT_DEFAULT;
}

/*-------------------------------------
    Get the texture type of that this texture uses in OpenGL
-------------------------------------*/
inline tex_desc_t texture::getTexType() const {
    return dimensions;
}

/*-------------------------------------
    Get the maximum texture size supported by OpenGL
-------------------------------------*/
inline int texture::getMaxTextureSize() {
    int maxTexSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
    return maxTexSize;
}

} // end draw namespace
} // end ls namespace