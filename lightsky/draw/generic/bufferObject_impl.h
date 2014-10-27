
namespace ls {
namespace draw {

/*-------------------------------------
    Constructor
-------------------------------------*/
template <buffer_t bufferType>
bufferObject<bufferType>::bufferObject() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
template <buffer_t bufferType>
bufferObject<bufferType>::bufferObject(bufferObject&& vb) :
    vbo{vb.vbo}
{
    vb.vbo = 0;
}

/*-------------------------------------
    Destructor
-------------------------------------*/
template <buffer_t bufferType>
bufferObject<bufferType>::~bufferObject() {
    terminate();
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
template <buffer_t bufferType>
bufferObject<bufferType>& bufferObject<bufferType>::operator=(bufferObject&& vb) {
    vbo = vb.vbo;
    vb.vbo = 0;
    return *this;
}

/*-------------------------------------
    Buffer initialization
-------------------------------------*/
template <buffer_t bufferType>
inline bool bufferObject<bufferType>::init() {
    if (!vbo) {
        glGenBuffers(1, &vbo);
    }
    return vbo != 0;
}

/*-------------------------------------
    Terminate the vertex buffer and release all of its resources back to
    the GPU.
-------------------------------------*/
template <buffer_t bufferType>
inline void bufferObject<bufferType>::terminate() {
    glDeleteBuffers(1, &vbo);
    vbo = 0;
}

/*-------------------------------------
    Get the GPU-assigned handle of this buffer object
-------------------------------------*/
template <buffer_t bufferType>
inline unsigned bufferObject<bufferType>::getId() const {
    return vbo;
}

/*-------------------------------------
    Determine if there is data used by this object
-------------------------------------*/
template <buffer_t bufferType>
inline bool bufferObject<bufferType>::isValid() const {
    return vbo != 0;
}

/*-------------------------------------
    Bind this vertex buffer to the current global rendering context.
-------------------------------------*/
template <buffer_t bufferType>
inline void bufferObject<bufferType>::bind() const {
    glBindBuffer(bufferType, vbo);
}

/*-------------------------------------
    Unbind this vertex buffer object from the current render context.
-------------------------------------*/
template <buffer_t bufferType>
inline void bufferObject<bufferType>::unbind() const {
    glBindBuffer(bufferType, 0);
}

/*-------------------------------------
    Set the data within the buffer to whatever is set at "pData."
-------------------------------------*/
template <buffer_t bufferType>
inline void bufferObject<bufferType>::setData(
    ptrdiff_t size,
    const void* pData,
    buffer_usage_t
    usage
) {
    glBufferData(bufferType, size, pData, usage);
}

/*-------------------------------------
    Modify the data within a buffer to contain whatever is in "pData."
    at an offset of a specified amount of bytes.
-------------------------------------*/
template <buffer_t bufferType>
inline void bufferObject<bufferType>::setSubData(
    ptrdiff_t offset,
    ptrdiff_t size,
    const void* pData
) {
    glBufferSubData(bufferType, offset, size, pData);
}

/*-------------------------------------
    Map the contents of the buffer into memory in order to perform a DMA
    transfer of data to the GPU.
-------------------------------------*/
template <buffer_t bufferType>
inline void* bufferObject<bufferType>::mapData(
    ptrdiff_t offset,
    ptrdiff_t range,
    buffer_access_t access
) {
    return glMapBufferRange(bufferType, offset, range, access);
}

/*-------------------------------------
    Notify the GPU that all data has been uploaded to the requested
    location in memory and that the DMA transfer can now be performed.
-------------------------------------*/
template <buffer_t bufferType>
inline bool bufferObject<bufferType>::unmapData() {
    return glUnmapBuffer(bufferType);
}

} // end draw namespace
} // end ls namespace
