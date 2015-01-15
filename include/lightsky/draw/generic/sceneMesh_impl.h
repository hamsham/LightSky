
namespace ls {
namespace draw {

/*-------------------------------------
 * Set the subset of vertices to render
-------------------------------------*/
inline void sceneMesh::setIndices(const draw_index_pair_t& indices) {
    submeshIndices = indices;
}

/*-------------------------------------
 * Get the subset of vertices to render (const)
-------------------------------------*/
inline const draw_index_pair_t& sceneMesh::getIndices() const {
    return submeshIndices;
}

/*-------------------------------------
 * Get the subset of vertices to render
-------------------------------------*/
inline draw_index_pair_t& sceneMesh::getIndices() {
    return submeshIndices;
}

/*-------------------------------------
    Get the GPU-Assigned ID associated with this mesh model.
-------------------------------------*/
inline unsigned sceneMesh::getId() const {
    return vao.getId();
}

/*-------------------------------------
 Determine if *this is renderable.
-------------------------------------*/
inline bool sceneMesh::isValid() const {
    return pGeometry && vao.getId();
}

/*-------------------------------------
 Determine if *this has renderable geometry.
-------------------------------------*/
inline bool sceneMesh::hasGeometry() const {
    return pGeometry != nullptr;
}

/*-------------------------------------
    Get the mesh that is currently used by this model
-------------------------------------*/
inline const geometry* sceneMesh::getGeometry() const {
    return pGeometry;
}

/*-------------------------------------
    Determine if this current model is able to be rendered.
-------------------------------------*/
inline bool sceneMesh::canDraw() const {
    return pGeometry != nullptr;
}

} // end draw namespace
} // end ls namespace
