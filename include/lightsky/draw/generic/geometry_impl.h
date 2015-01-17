
namespace ls {
namespace draw {


/*-------------------------------------
    Helper function to initialize vertex buffers objects
-------------------------------------*/
template <vbo_use_t vbo_type>
bool geometry::initBufferObject(
    vertexBuffer_t<vbo_type>& vbo,
    unsigned numItems,
    unsigned elementSize,
    vbo_rw_t usage
) {
    if (numItems == 0) {
        LS_LOG_ERR("\tInvalid buffer object count in a geometry loader. Aborting GPU load.");
        return false;
    }
    
    if (vbo.isValid() == false) {
        if (vbo.init() == false) {
            LS_LOG_ERR("\tUnable to initialize a geometry VBO.");
            return false;
        }
    }
    
    vbo.bind();
    vbo.setData(numItems*elementSize, nullptr, usage);
    
    LS_LOG_MSG("\tInitialized a geometry buffer object with ", numItems, " items.");
    return true;
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
    tempCommand.first = indexPair.first;
    tempCommand.count = indexPair.count;

    ibo.isValid() ? drawParams.draw(vbo, ibo) : drawParams.draw(vbo);
}

} // end draw namespace
} // end ls namespace
