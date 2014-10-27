
namespace ls {
namespace draw {

/*-------------------------------------
    Get an general identification to be used for this object
-------------------------------------*/
inline unsigned mesh::getId() const {
    return vbo.getId();
}

/*-------------------------------------
    Unload all GPU-based resource that are used by *this;
-------------------------------------*/
inline void mesh::terminate() {
    vbo.terminate();
    numVertices = 0;
}

/*-------------------------------------
    Get the number of vertices contained within this mesh object's VBO.
-------------------------------------*/
inline unsigned mesh::getNumVertices() const {
    return numVertices;
}

/*-------------------------------------
    Get the current Draw Mode for this mesh.
-------------------------------------*/
inline draw_mode_t mesh::getDrawMode() const {
    return drawMode;
}

/*-------------------------------------
    Set the method of drawing that should be used for this mesh.
-------------------------------------*/
inline void mesh::setDrawMode(draw_mode_t dm) {
    drawMode = dm;
}

/*-------------------------------------
    Get the maximum vertex bounds for this mesh.
-------------------------------------*/
inline const boundingBox& mesh::getBounds() const {
    return bounds;
}

} // end draw namespace
} // end ls namespace
