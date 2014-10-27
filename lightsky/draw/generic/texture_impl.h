
namespace ls {
namespace draw {

/*-------------------------------------
    Get the GPU-Assigned ID used by *this.
-------------------------------------*/
inline unsigned texture::getId() const {
    return texId;
}

/*-------------------------------------
    Bind the current texture to OpenGL
-------------------------------------*/
inline void texture::bind() const {
    glBindTexture(dimensions, texId);
}

/*-------------------------------------
    Unbind the current texture to OpenGL
-------------------------------------*/
inline void texture::unbind() const {
    glBindTexture(dimensions, 0);
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
inline bool texture::init(int mipmapLevel, int size, const imageResource& resource) {
    return init(
        mipmapLevel,
        resource.getInternalFormat(),
        size,
        resource.getExternalFormat(),
        resource.getPixelType(),
        resource.getData()
    );
}

/*-------------------------------------
    Create an OpenGL texture by using preexisting image data.
-------------------------------------*/
inline bool texture::init(int mipmapLevel, math::vec2i size, const imageResource& resource) {
    return init(
        mipmapLevel,
        resource.getInternalFormat(),
        size,
        resource.getExternalFormat(),
        resource.getPixelType(),
        resource.getData()
    );
}

/*-------------------------------------
    Create an OpenGL texture by using preexisting image data.
-------------------------------------*/
inline bool texture::init(int mipmapLevel, math::vec3i size, const imageResource& resource) {
    return init(
        mipmapLevel,
        (pixel_format_t)resource.getInternalFormat(),
        size,
        (pixel_layout_t)resource.getExternalFormat(),
        (color_type_t)resource.getPixelType(),
        resource.getData()
    );
}

/*-------------------------------------
    Modify the internal data of a texture.
-------------------------------------*/
inline void texture::modify(int offset, int size, int format, int dataType, void* data) {
    glTexSubImage1D(getTextType(), 0, offset, size, format, dataType, data);
    LOG_GL_ERR();
}

/*-------------------------------------
    Modify the internal data of a texture.
-------------------------------------*/
inline void texture::modify(math::vec2i offset, math::vec2i size, int format, int dataType, void* data) {
    glTexSubImage2D(getTextType(), 0, offset[0], offset[1], size[0], size[1], format, dataType, data);
    LOG_GL_ERR();
}

/*-------------------------------------
    Modify the internal data of a texture.
-------------------------------------*/
inline void texture::modify(math::vec3i offset, math::vec3i size, int format, int dataType, void* data) {
    glTexSubImage3D(getTextType(), 0, offset[0], offset[1], offset[2], size[0], size[1], size[2], format, dataType, data);
    LOG_GL_ERR();
}

/*-------------------------------------
    Release all memory referenced by *this.
-------------------------------------*/
inline void texture::terminate() {
    glDeleteTextures(1, &texId);
    texId = 0;
}

/*-------------------------------------
    Get the width of the texture referenced by texId
-------------------------------------*/
inline unsigned texture::getWidth() const {
    int w = 0;
    glGetTexLevelParameteriv(dimensions, 0, LS_TEX_WIDTH, &w);
    return w;
}

/*-------------------------------------
    Get the height of the texture referenced by texId
-------------------------------------*/
inline unsigned texture::getHeight() const {
    int h = 0;
    glGetTexLevelParameteriv(dimensions, 0, LS_TEX_HEIGHT, &h);
    return h;
}

/*-------------------------------------
    Get the depth of the texture referenced by texId
-------------------------------------*/
inline unsigned texture::getDepth() const {
    int d = 0;
    glGetTexLevelParameteriv(dimensions, 0, LS_TEX_DEPTH, &d);
    return d;
}

/*-------------------------------------
    Get the texture type of that this texture uses in OpenGL
-------------------------------------*/
inline ls_tex_desc_t texture::getTextType() const {
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
