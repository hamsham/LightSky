/* 
 * File:   renderStage_impl.h
 * Author: hammy
 *
 * Created on January 20, 2015, 9:21 PM
 */

namespace ls {
namespace draw {

/*-------------------------------------
 * Get the internal vertex shader.
-------------------------------------*/
inline vertexShader& renderStage::getVertexShader() {
    return vertShader;
}

/*-------------------------------------
 * Get the internal vertex shader (const).
-------------------------------------*/
inline const vertexShader& renderStage::getVertexShader() const {
    return vertShader;
}

/*-------------------------------------
 * Get the internal fragment shader.
-------------------------------------*/
inline fragmentShader& renderStage::getFragmentShader() {
    return fragShader;
}

/*-------------------------------------
 * Get the internal fragment shader (const).
-------------------------------------*/
inline const fragmentShader& renderStage::getFragmentShader() const {
    return fragShader;
}

/*-------------------------------------
 * Get the internal shader program.
-------------------------------------*/
inline shaderProgram& renderStage::getShaderProgram() {
    return shaderBinary;
}

/*-------------------------------------
 * Get the internal shader program (const).
-------------------------------------*/
inline const shaderProgram& renderStage::getShaderProgram() const {
    return shaderBinary;
}

/*-------------------------------------
 * Compile and link the internal shader data.
-------------------------------------*/
inline bool renderStage::initShaders(const char* const vertShaderData, const char* const fragShaderData) {
    return compileShaders(vertShaderData, fragShaderData) && linkShaders();
}

/*-------------------------------------
 * Bind for rendering
-------------------------------------*/
inline void renderStage::bind() {
    shaderBinary.bind();
}

/*-------------------------------------
 * Unbind from OpenGL
-------------------------------------*/
inline void renderStage::unbind() {
    shaderBinary.unbind();
}

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
