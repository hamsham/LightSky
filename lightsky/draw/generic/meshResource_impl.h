
namespace ls {
namespace draw {

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
