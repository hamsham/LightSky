
namespace ls {
namespace draw {

/*-------------------------------------
    Get the GPU-Assigned ID associated with this mesh model.
-------------------------------------*/
inline unsigned meshModel::getId() const {
    return vao.getId();
}

/*-------------------------------------
    Get the mesh that is currently used by this model
-------------------------------------*/
inline const geometry& meshModel::getMesh() const {
    return *pMesh;
}

/*-------------------------------------
    Get the texture that is currently used by this model
-------------------------------------*/
inline const texture& meshModel::getTexture() const {
    return *pTexture;
}

/*-------------------------------------
    Set the texture ID to be used by this object during a draw operation.
-------------------------------------*/
inline void meshModel::setTexture(const texture& texRef) {
    pTexture = &texRef;
}

/*-------------------------------------
    Determine if this current model is able to be rendered.
-------------------------------------*/
inline bool meshModel::canDraw() const {
    return pMesh != nullptr && pTexture != nullptr;
}

/*-------------------------------------
    Render all instances of the currently bound mesh to OpenGL.
-------------------------------------*/
inline void meshModel::draw() const {
    pTexture->bind();
    drawParams.draw(vao);
    pTexture->unbind();
}

} // end draw namespace
} // end ls namespace
