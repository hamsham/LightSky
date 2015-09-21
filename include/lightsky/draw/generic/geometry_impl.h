
namespace ls {
namespace draw {


/*-------------------------------------
    Helper function to initialize vertex buffers objects
-------------------------------------*/
template <buffer_use_t vboType>
bool geometry::initBufferObject(
    BufferObject& bo,
    unsigned numItems,
    unsigned elementSize,
    vbo_rw_t usage
) {
    if (numItems == 0) {
        LS_LOG_ERR("\tInvalid buffer object count in a geometry loader. Aborting GPU load.");
        return false;
    }
    
    if (init_buffer(bo) == false) {
        LS_LOG_ERR("\tUnable to initialize a geometry buffer object.");
        return false;
    }
    
    bo.bufferType = vboType;
    bind_buffer(bo);
    set_buffer_data(bo, numItems*elementSize, nullptr, usage);
    
    LS_LOG_MSG("\tInitialized a geometry buffer object with ", numItems, " items.");
    return true;
}

/*-------------------------------------
    Text/String buffer object initialization helper
-------------------------------------*/
template <buffer_use_t vboType>
void* geometry::mapBufferData(
    BufferObject& bo,
    const unsigned elementCount,
    const char* const bufferStr
) {
    const unsigned bytesPerVert = get_vertex_byte_size(attribs);
    
    init_buffer(bo);
    if (!initBufferObject<vboType>(bo, elementCount, bytesPerVert, vbo_rw_t::VBO_STREAM_DRAW)) {
        LS_LOG_ERR("\tAn error occurred while initializing text geometry ", bufferStr, ".\n");
        return nullptr;
    }
    LOG_GL_ERR();
    
    // Attempt to get a pointer to an unsynchronized memory buffer
    void* const pBuffer = map_buffer_data(
        bo, 0, elementCount*bytesPerVert
        (buffer_map_t)(VBO_MAP_BIT_INVALIDATE_RANGE | VBO_MAP_BIT_WRITE | VBO_MAP_BIT_UNSYNCHRONIZED)
    );
    LOG_GL_ERR();
    
    return pBuffer;
}

/*-------------------------------------
    Determine if *this is renderable.
-------------------------------------*/
inline bool geometry::isValid() const {
    return vbo.getId();
}

/*-------------------------------------
    Get an general identification to be used for this object
-------------------------------------*/
inline unsigned geometry::getId() const {
    return vbo.getId();
}

/*-------------------------------------
 * Get the internal vertex buffer used by *this.
-------------------------------------*/
inline const vertexBuffer& geometry::getVertexBuffer() const {
    return vbo;
}

/*-------------------------------------
 * Get the internal index buffer used by *this.
-------------------------------------*/
inline const indexBuffer& geometry::getIndexBuffer() const {
    return ibo;
}

/*-------------------------------------
    Get the current Draw parameters for this geometry.
-------------------------------------*/
inline const drawCommand& geometry::getDrawCommand() const {
    return drawParams;
}

/*-------------------------------------
    Get the available sub-geometry in *this.
-------------------------------------*/
inline const draw_index_list_t& geometry::getSubGeometry() const {
    return submeshes;
}

/*-------------------------------------
    Get the maximum vertex bounds for this geometry.
-------------------------------------*/
inline const boundingBox& geometry::getBounds() const {
    return bounds;
}

/*-------------------------------------
 * Draw the geometry contained within *this.
-------------------------------------*/
inline void geometry::draw() const {
    ibo.isValid() ? drawParams.draw(vbo, ibo) : drawParams.draw(vbo);
}

/*-------------------------------------
    Render an sub-mesh
-------------------------------------*/
inline void geometry::draw(const draw_index_pair_t& indexPair) const {
    drawCommand tempCommand = drawParams;
    tempCommand.indices = indexPair;

    ibo.isValid() ? tempCommand.draw(vbo, ibo) : tempCommand.draw(vbo);
}

} // end draw namespace
} // end ls namespace
