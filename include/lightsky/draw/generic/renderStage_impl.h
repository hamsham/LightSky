/* 
 * File:   renderStage_impl.h
 * Author: hammy
 *
 * Created on January 20, 2015, 9:21 PM
 */

namespace ls {
namespace draw {

/*-------------------------------------
 * Scene Gaph traversing for rendering.
-------------------------------------*/
inline void renderStage::draw(const sceneGraph& scene) {
    // Linearly iterate through the scene nodes as they should already have
    // their accumulated transformations
    for (const sceneNode& node : scene.getNodeList()) {
        drawSceneNode(scene, node);
    }
}

/*-------------------------------------
 * Scene Node Rendering.
-------------------------------------*/
inline void renderStage::drawSceneNode(const sceneGraph& scene, const sceneNode& node) {
    (void)scene;
    for (const sceneMesh* const pMesh : node.nodeMeshes) {
        drawNodeMesh(node, *pMesh);
    }
}

/*-------------------------------------
 * Scene Mesh Rendering.
-------------------------------------*/
inline void renderStage::drawNodeMesh(const sceneNode& node, const sceneMesh& mesh) {
    (void)node;
    mesh.draw();
}

} // end draw namespace
} // end ls namespace
