
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
inline const mesh& meshModel::getMesh() const {
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
    Get the number of instances that will be rendered when a call to
    "draw()" is made.
-------------------------------------*/
inline int meshModel::getNumInstances() const {
    return numInstances;
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
    vao.bind();
    glDrawArraysInstanced(pMesh->getDrawMode(), 0, pMesh->getNumVertices(), numInstances);
    vao.unbind();
    pTexture->unbind();
}

/*-------------------------------------
    Render an instanced set of sub-meshes
-------------------------------------*/
inline void meshModel::drawSubMesh(int startPos, int endPos) const {
    pTexture->bind();
    vao.bind();
    glDrawArraysInstanced(pMesh->getDrawMode(), startPos, endPos, numInstances);
    vao.unbind();
    pTexture->unbind();
}

} // end draw namespace
} // end ls namespace
