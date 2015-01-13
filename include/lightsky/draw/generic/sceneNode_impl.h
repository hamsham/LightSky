
namespace ls {
namespace draw {

/*-------------------------------------
    Get the GPU-Assigned ID associated with this mesh model.
-------------------------------------*/
inline unsigned sceneNode::getId() const {
    return vao.getId();
}

/*-------------------------------------
 Determine if *this is renderable.
-------------------------------------*/
inline bool sceneNode::isValid() const {
    return pMesh && vao.getId();
}

/*-------------------------------------
 Determine if *this has renderable geometry.
-------------------------------------*/
inline bool sceneNode::hasGeometry() const {
    return pMesh != nullptr;
}

/*-------------------------------------
    Get the mesh that is currently used by this model
-------------------------------------*/
inline const geometry* sceneNode::getGeometry() const {
    return pMesh;
}

/*-------------------------------------
    Get the texture that is currently used by this model
-------------------------------------*/
inline unsigned sceneNode::getNumTextures() const {
    return textureList.size();
}

/*-------------------------------------
    Get the texture that is currently used by this model
-------------------------------------*/
inline const std::vector<const texture*>& sceneNode::getTextures() const {
    return textureList;
}

/*-------------------------------------
    Set the texture ID to be used by this object during a draw operation.
-------------------------------------*/
inline void sceneNode::addTexture(const texture& texRef) {
    if (!texRef.isValid()) {
        return;
    }
    
    for (const texture* const pTex : textureList) {
        if (pTex == &texRef) {
            return;
        }
    }
    textureList.push_back(&texRef);
}

/*-------------------------------------
    Remove a texture from *this.
-------------------------------------*/
inline void sceneNode::removeTexture(unsigned texIndex) {
    LS_DEBUG_ASSERT(texIndex < textureList.size);
    textureList.erase(textureList.begin() + texIndex);
}

/*-------------------------------------
    Determine if this current model is able to be rendered.
-------------------------------------*/
inline bool sceneNode::canDraw() const {
    return pMesh != nullptr && pTexture != nullptr;
}

} // end draw namespace
} // end ls namespace
