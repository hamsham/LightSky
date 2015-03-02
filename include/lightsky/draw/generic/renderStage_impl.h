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
 * Terminate/Free/Reset all resources.
-------------------------------------*/
inline void renderStage::terminate() {
    resetDrawParameters();
    terminateShaders();
}

/*-------------------------------------
 * Bind for rendering
-------------------------------------*/
inline void renderStage::bind() {
    bindShaderProgram();
    bindDrawParameters();
}

/*-------------------------------------
 * Unbind from OpenGL
-------------------------------------*/
inline void renderStage::unbind() {
    unbindDrawParameters();
    unbindShaderProgram();
}

/*-------------------------------------
 * Get *this object's ID
-------------------------------------*/
inline unsigned renderStage::getId() const {
    return shaderBinary.getId();
}

/*-------------------------------------
 * Determine if *this can be used for rendering
-------------------------------------*/
inline bool renderStage::isValid() const {
    return getId() != 0;
}

/*-------------------------------------
 * Bind the current shader binary
-------------------------------------*/
inline void renderStage::bindShaderProgram() const {
    shaderBinary.bind();
}

/*-------------------------------------
 * unbind the current shader binary
-------------------------------------*/
inline void renderStage::unbindShaderProgram() const {
    shaderBinary.unbind();
}

/*-------------------------------------
 * Bind the current shader binary
-------------------------------------*/
inline void renderStage::bindDrawParameters() const {
    blendParams.bind();
    depthParams.bind();
}

/*-------------------------------------
 * unbind the current shader binary
-------------------------------------*/
inline void renderStage::unbindDrawParameters() const {
    blendParams.unbind();
    depthParams.unbind();
}

/*-------------------------------------
 * Scene Gaph traversing for rendering.
-------------------------------------*/
inline void renderStage::draw(const sceneGraph& scene) {
    draw(scene, scene.getActiveCamera().getVPMatrix());
}

/*-------------------------------------
 * Scene Gaph traversing for rendering.
-------------------------------------*/
inline void renderStage::draw(const sceneGraph& scene, const math::mat4&) {
    for (const sceneNode* const pNode : scene.getNodeList()) {
        drawSceneNode(scene, pNode);
    }
}

/*-------------------------------------
 * Scene Node Rendering.
-------------------------------------*/
inline void renderStage::drawSceneNode(const sceneGraph&, const sceneNode* const pNode) {
    for (const sceneMesh* const pMesh : pNode->nodeMeshes) {
        drawNodeMesh(pNode, pMesh);
    }
}

/*-------------------------------------
 * Scene Mesh Rendering.
-------------------------------------*/
inline void renderStage::drawNodeMesh(const sceneNode* const, const sceneMesh* const pMesh) {
    pMesh->draw();
}

/*-------------------------------------
 * Set the internal blend parameters.
-------------------------------------*/
inline void renderStage::setBlendParameters(const blendObject& blendOptions) {
    blendParams = blendOptions;
}

/*-------------------------------------
 * Get the internal blend parameters (const).
-------------------------------------*/
inline const blendObject& renderStage::getBlendParameters() const {
    return blendParams;
}

/*-------------------------------------
 * Get the internal blend parameters.
-------------------------------------*/
inline blendObject& renderStage::getBlendParameters() {
    return blendParams;
}

/*-------------------------------------
 * Set the internal depth parameters.
-------------------------------------*/
inline void renderStage::setDepthParameters(const depthObject& depthOptions) {
    depthParams = depthOptions;
}

/*-------------------------------------
 * Get the internal depth parameters (const).
-------------------------------------*/
inline const depthObject& renderStage::getDepthParameters() const {
    return depthParams;
}

/*-------------------------------------
 * Get the internal depth parameters.
-------------------------------------*/
inline depthObject& renderStage::getDepthParameters() {
    return depthParams;
}

} // end draw namespace
} // end ls namespace
