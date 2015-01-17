
namespace ls {
namespace draw {

/*-------------------------------------
    Get the size, in bytes, of the vertex buffer.
-------------------------------------*/
inline long sceneResource::getVertexByteSize() const {
    return getNumVertices() * sizeof(vertex);
}

/*-------------------------------------
    Get the size, in bytes, of the index buffer.
-------------------------------------*/
inline long sceneResource::getIndexByteSize() const {
    return getNumIndices() * sizeof(draw_index_t);
}

/*-------------------------------------
    Get the number vertex count.
-------------------------------------*/
inline unsigned sceneResource::getNumVertices() const {
    return vertexList.size();
}

/*-------------------------------------
    Get the vertex array
-------------------------------------*/
inline const std::vector<vertex>& sceneResource::getVertices() const {
    return vertexList;
}

/*-------------------------------------
    Get the index count.
-------------------------------------*/
inline unsigned sceneResource::getNumIndices() const {
    return indexList.size();
}

/*-------------------------------------
    Get the index array.
-------------------------------------*/
inline const std::vector<draw_index_t>& sceneResource::getIndices() const {
    return indexList;
}

/*-------------------------------------
    Get the number of resource nodes.
-------------------------------------*/
inline unsigned sceneResource::getNumNodes() const {
    return nodeList.size();
}

/*-------------------------------------
    Get the node array
-------------------------------------*/
inline const std::vector<sceneResource::resourceNode>& sceneResource::getNodes() const {
    return nodeList;
}

/*-------------------------------------
    Get the sub-mesh count.
-------------------------------------*/
inline unsigned sceneResource::getNumMeshes() const {
    return meshList.size();
}

/*-------------------------------------
    Get the array index pairs for a mesh.
-------------------------------------*/
inline const draw_index_list_t& sceneResource::getMeshes() const {
    return meshList;
}

/*-------------------------------------
    Get the draw mode that was generated while loading a mesh.
-------------------------------------*/
inline draw_mode_t sceneResource::getDrawMode() const {
    return resultDrawMode;
}

/*-------------------------------------
    Get a mesh object's maximum dimensions
-------------------------------------*/
inline const boundingBox& sceneResource::getBoundingBox() const {
    return totalBounds;
}
        
/*-------------------------------------
    Triangle primitive loading method
-------------------------------------*/
inline bool sceneResource::loadTriangle() {
    return loadPolygon(3);
}
        
/*-------------------------------------
    Load a set of vertices representing a circle.
-------------------------------------*/
inline bool sceneResource::loadCircle(unsigned numPoints) {
    return loadPolygon(numPoints);
}

} // end draw namespace
} // end ls namespace
