
namespace ls {
namespace draw {

/*-------------------------------------
    Get the size, in bytes, of the vertex buffer.
-------------------------------------*/
inline long meshResource::getVertexByteSize() const {
    return numVertices * sizeof(vertex);
}

/*-------------------------------------
    Get the size, in bytes, of the index buffer.
-------------------------------------*/
inline long meshResource::getIndexByteSize() const {
    return numIndices * sizeof(draw_index_t);
}

/*-------------------------------------
    Get the number of loaded vertex variables in a mesh
-------------------------------------*/
inline unsigned meshResource::getNumVertices() const {
    return numVertices;
}

/*-------------------------------------
    Get the array of standard vertex types of a loaded mesh
-------------------------------------*/
inline vertex* meshResource::getVertices() const {
    return pVertices;
}

/*-------------------------------------
    Get the number of loaded indices in a mesh.
-------------------------------------*/
inline unsigned meshResource::getNumIndices() const {
    return numIndices;
}

/*-------------------------------------
    Get the array of vertex index elements of a loaded mesh
-------------------------------------*/
inline draw_index_t* meshResource::getIndices() const {
    return pIndices;
}

/*-------------------------------------
    Get the draw mode that was generated while loading a mesh.
-------------------------------------*/
inline draw_mode_t meshResource::getDrawMode() const {
    return resultDrawMode;
}

/*-------------------------------------
    Get a mesh object's maximum dimensions
-------------------------------------*/
inline const boundingBox& meshResource::getBoundingBox() const {
    return meshBounds;
}
        
/*-------------------------------------
    Triangle primitive loading method
-------------------------------------*/
inline bool meshResource::loadTriangle() {
    return loadPolygon(3);
}
        
/*-------------------------------------
    Load a set of vertices representing a circle.
-------------------------------------*/
inline bool meshResource::loadCircle(unsigned numPoints) {
    return loadPolygon(numPoints);
}

} // end draw namespace
} // end ls namespace
