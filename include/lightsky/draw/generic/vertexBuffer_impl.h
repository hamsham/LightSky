
namespace ls {
namespace draw {

/*-------------------------------------
    Constructor
-------------------------------------*/
template <vbo_use_t bufferType>
vertexBuffer_t<bufferType>::vertexBuffer_t() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
template <vbo_use_t bufferType>
vertexBuffer_t<bufferType>::vertexBuffer_t(vertexBuffer_t&& vb) :
    vbo{vb.vbo}
{
    vb.vbo = 0;
}

/*-------------------------------------
    Destructor
-------------------------------------*/
template <vbo_use_t bufferType>
vertexBuffer_t<bufferType>::~vertexBuffer_t() {
    terminate();
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
template <vbo_use_t bufferType>
vertexBuffer_t<bufferType>& vertexBuffer_t<bufferType>::operator=(vertexBuffer_t&& vb) {
    vbo = vb.vbo;
    vb.vbo = 0;
    return *this;
}

/*-------------------------------------
    Buffer initialization
-------------------------------------*/
template <vbo_use_t bufferType>
inline bool vertexBuffer_t<bufferType>::init() {
    if (!vbo) {
        glGenBuffers(1, &vbo);
    }
    return vbo != 0;
}

/*-------------------------------------
    Terminate the vertex buffer and release all of its resources back to
    the GPU.
-------------------------------------*/
template <vbo_use_t bufferType>
inline void vertexBuffer_t<bufferType>::terminate() {
    glDeleteBuffers(1, &vbo);
    vbo = 0;
}

/*-------------------------------------
    Get the GPU-assigned handle of this buffer object
-------------------------------------*/
template <vbo_use_t bufferType>
inline unsigned vertexBuffer_t<bufferType>::getId() const {
    return vbo;
}

/*-------------------------------------
    Determine if there is data used by this object
-------------------------------------*/
template <vbo_use_t bufferType>
inline bool vertexBuffer_t<bufferType>::isValid() const {
    return vbo != 0;
}

/*-------------------------------------
    Bind this vertex buffer to the current global rendering context.
-------------------------------------*/
template <vbo_use_t bufferType>
inline void vertexBuffer_t<bufferType>::bind() const {
    glBindBuffer(bufferType, vbo);
}

/*-------------------------------------
    Unbind this vertex buffer object from the current render context.
-------------------------------------*/
template <vbo_use_t bufferType>
inline void vertexBuffer_t<bufferType>::unbind() const {
    glBindBuffer(bufferType, 0);
}

/*-------------------------------------
    Set the data within the buffer to whatever is set at "pData."
-------------------------------------*/
template <vbo_use_t bufferType>
inline void vertexBuffer_t<bufferType>::setData(
    GLsizeiptr size,
    const void* pData,
    vbo_rw_t
    usage
) {
    glBufferData(bufferType, size, pData, usage);
}

/*-------------------------------------
    Modify the data within a buffer to contain whatever is in "pData."
    at an offset of a specified amount of bytes.
-------------------------------------*/
template <vbo_use_t bufferType>
inline void vertexBuffer_t<bufferType>::setSubData(
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
template <vbo_use_t bufferType>
inline void* vertexBuffer_t<bufferType>::mapData(
    ptrdiff_t offset,
    ptrdiff_t range,
    vbo_map_t access
) {
    return glMapBufferRange(bufferType, offset, range, access);
}

/*-------------------------------------
    Notify the GPU that all data has been uploaded to the requested
    location in memory and that the DMA transfer can now be performed.
-------------------------------------*/
template <vbo_use_t bufferType>
inline bool vertexBuffer_t<bufferType>::unmapData() {
    return glUnmapBuffer(bufferType);
}

} // end draw namespace
} // end ls namespace
