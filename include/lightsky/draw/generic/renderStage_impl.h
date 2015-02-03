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
    draw(scene, scene.getMainCamera().getVPMatrix());
}

/*-------------------------------------
 * Scene Gaph traversing for rendering.
-------------------------------------*/
inline void renderStage::draw(const sceneGraph& scene, const math::mat4&) {
    for (const sceneNode& node : scene.getNodeList()) {
        drawSceneNode(scene, node);
    }
}

/*-------------------------------------
 * Scene Node Rendering.
-------------------------------------*/
inline void renderStage::drawSceneNode(const sceneGraph&, const sceneNode& node) {
    for (const sceneMesh* const pMesh : node.nodeMeshes) {
        drawNodeMesh(node, *pMesh);
    }
}

/*-------------------------------------
 * Scene Mesh Rendering.
-------------------------------------*/
inline void renderStage::drawNodeMesh(const sceneNode&, const sceneMesh& mesh) {
    mesh.draw();
}

} // end draw namespace
} // end ls namespace
