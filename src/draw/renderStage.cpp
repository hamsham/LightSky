/* 
 * File:   renderStage.cpp
 * Author: hammy
 * 
 * Created on January 20, 2015, 8:57 PM
 */

#include <cstring>

#include "lightsky/draw/renderStage.h"
#include "lightsky/draw/shaderObject.h"
#include "lightsky/draw/shaderProgram.h"

namespace ls {
namespace draw {

/*-------------------------------------
 * Destructor
-------------------------------------*/
renderStage::~renderStage() {
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
renderStage::renderStage() :
    blendParams{},
    depthParams{},
    vertShader{},
    fragShader{},
    shaderBinary{}
{}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
renderStage::renderStage(renderStage&& rs) :
    blendParams{std::move(rs.blendParams)},
    depthParams{std::move(rs.depthParams)},
    vertShader{std::move(rs.vertShader)},
    fragShader{std::move(rs.fragShader)},
    shaderBinary{std::move(rs.shaderBinary)}
{}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
renderStage& renderStage::operator=(renderStage&& rs) {
    blendParams = std::move(rs.blendParams);
    depthParams = std::move(rs.depthParams);
    vertShader = std::move(rs.vertShader);
    fragShader = std::move(rs.fragShader);
    shaderBinary = std::move(rs.shaderBinary);

    return *this;
}

/*-------------------------------------
 * Shader Compilation
-------------------------------------*/
bool renderStage::compileShaders(const char* const vertShaderData, const char* const fragShaderData) {
    if (shaderBinary.getId() != 0) {
        terminateShaders();
    }
    
    LOG_GL_ERR();

    if (!vertShader.init(vertShaderData, strlen(vertShaderData))) {
        LS_LOG_ERR("ERROR: Unable to initialize the default vertex shader.");
        return false;
    }
    
    LOG_GL_ERR();

    if (!fragShader.init(fragShaderData, strlen(fragShaderData))) {
        LS_LOG_ERR("ERROR: Unable to initialize the default fragment shader.");
        vertShader.terminate();
        return false;
    }
    
    LOG_GL_ERR();

    if (!shaderBinary.init(vertShader, fragShader)) {
        LS_LOG_ERR("ERROR: Unable to initialize the default shader binary.");
        vertShader.terminate();
        fragShader.terminate();
        return false;
    }
    
    LOG_GL_ERR();
    
    return true;
}

/*-------------------------------------
 * Shader Linking
-------------------------------------*/
bool renderStage::linkShaders() {
    LS_DEBUG_ASSERT(shaderBinary.getId() != 0);
    
    if (!shaderBinary.link()) {
        LS_LOG_ERR("ERROR: Unable to link the default shader binary.");
        return false;
    }

    LOG_GL_ERR();
    
    return true;
}

/*-------------------------------------
 * Shader Termination
-------------------------------------*/
void renderStage::terminateShaders() {
    vertShader.terminate();
    fragShader.terminate();
    shaderBinary.terminate();
}

/*-------------------------------------
 * Draw Parameter Termination
-------------------------------------*/
void renderStage::resetDrawParameters() {
    blendParams.reset();
    depthParams.reset();
}

/*-------------------------------------
 * Draw a scene (linear) using indices.
-------------------------------------*/
void renderStage::draw(
    const sceneGraph& scene,
    const math::mat4&,
    const std::vector<unsigned>& nodeIndices
) {
    const scene_node_list_t& nodes = scene.getNodeList();
    for (unsigned index : nodeIndices) {
        drawSceneNode(scene, nodes[index]);
    }
}

/*-------------------------------------
 * Scene Graph traversing for rendering (hierarchial).
-------------------------------------*/
/*
void renderStage::draw(const sceneGraph& scene) {
    // seed the node stack
    sceneNode* const pRoot = const_cast<sceneNode*>(scene.getRootNode());

    if (pRoot) {
        const math::mat4& pRootTrans = pRoot->nodeTransform.getTransform();
        renderStack.emplace(renderStackInfo{pRoot, 0, pRootTrans});
    }

    // iterate rather than recurse.
    while (!renderStack.empty()) {

        // pull off the top sceneNode and model matrix for rendering.
        renderStackInfo& currentIter = renderStack.top();
        const sceneNode* pNode = currentIter.pNode;

        // get the indices used to reference a subset of *this scene's geometry.
        const draw_index_list_t& indices = pNode->meshIndices;
        const geometry& renderableMesh = scene.getSceneGeometry()[pNode->geometryId];

        // render all sub-meshes in the scene node's specified geometry
        for (const draw_index_pair_t& indexPair : indices) {
            drawSceneNode(indexPair, renderableMesh, pNode);
        }

        // get a reference to the index of the currently selected child node.
        unsigned& nextChildIndex = currentIter.childIter;

        // check if the child node is valid, remove the current node if not
        if (nextChildIndex < pNode->nodeChildren.size()) {
            // increment the child reference to the next node.
            sceneNode* pChild = pNode->nodeChildren[nextChildIndex++];

            // push the next child node's matrix onto the stack
            // augment it by the parent transform
            const math::mat4& modelMat = renderStack.top().modelMatrix;
            const math::mat4& childModelMat = pChild->nodeTransform.getTransform();

            // stack the currently used node and push its next child onto the stack
            (void)modelMat;
            renderStack.emplace(renderStackInfo{pChild, 0, childModelMat});
        }
        else {
            renderStack.pop();
        }
    }

    LS_DEBUG_ASSERT(renderStack.empty());
}
*/

} // end draw namepsace
} // end ls namespace
