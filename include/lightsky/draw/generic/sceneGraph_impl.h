/* 
 * File:   sceneGraph_impl.h
 * Author: Miles Lacey
 *
 * Created on January 20, 2015, 8:54 PM
 */

namespace ls {
namespace draw {

/*-------------------------------------
 * Get the root node in *this (const).
-------------------------------------*/
inline const sceneNode& sceneGraph::getRootNode() const {
    return rootNode;
}

/*-------------------------------------
 * Get the root node in *this.
-------------------------------------*/
inline sceneNode& sceneGraph::getRootNode() {
    return rootNode;
}

/*-------------------------------------
 * Camera Selection.
-------------------------------------*/
inline void sceneGraph::setActiveCameraIndex(unsigned cameraIndex) {
    activeCamera = cameraIndex;
}

/*-------------------------------------
 * Camera Selection.
-------------------------------------*/
inline unsigned sceneGraph::getActiveCameraIndex() const {
    return activeCamera;
}

/*-------------------------------------
 * Camera Retrieval (const).
-------------------------------------*/
inline const camera& sceneGraph::getActiveCamera() const {
    return cameraList[activeCamera];
}

/*-------------------------------------
 * Camera Retrieval
-------------------------------------*/
inline camera& sceneGraph::getActiveCamera() {
    return cameraList[activeCamera];
}

/*-------------------------------------
 * Get the list of cameras (const).
-------------------------------------*/
inline const std::deque<camera>& sceneGraph::getCameraList() const {
    return cameraList;
}

/*-------------------------------------
 * Get the list of cameras.
-------------------------------------*/
inline std::deque<camera>& sceneGraph::getCameraList() {
    return cameraList;
}

/*-------------------------------------
 * Get the list of textures used in *this (const).
-------------------------------------*/
inline const std::vector<texture*>& sceneGraph::getTextureList() const {
    return textureList;
}

/*-------------------------------------
 * Get the list of textures used in *this
-------------------------------------*/
inline std::vector<texture*>& sceneGraph::getTextureList() {
    return textureList;
}

/*-------------------------------------
 * Get the list of geometry used in *this (const).
-------------------------------------*/
inline const std::vector<geometry*>& sceneGraph::getGeometryList() const {
    return geometryList;
}

/*-------------------------------------
 * Get the list of geometry used in *this
-------------------------------------*/
inline std::vector<geometry*>& sceneGraph::getGeometryList() {
    return geometryList;
}

/*-------------------------------------
 * Get the list of meshes used in *this (const).
-------------------------------------*/
inline const std::vector<sceneMesh*>& sceneGraph::getMeshList() const {
    return meshList;
}

/*-------------------------------------
 * Get the list of meshes used in *this
-------------------------------------*/
inline std::vector<sceneMesh*>& sceneGraph::getMeshList() {
    return meshList;
}

/*-------------------------------------
 * Get the list of nodes used in *this (const).
-------------------------------------*/
inline const scene_node_list_t& sceneGraph::getNodeList() const {
    return nodeList;
}

/*-------------------------------------
 * Get the list of nodes used in *this.
-------------------------------------*/
inline scene_node_list_t& sceneGraph::getNodeList() {
    return nodeList;
}

} // end draw namepsace
} // end ls namespace
