/* 
 * File:   renderStage.cpp
 * Author: hammy
 * 
 * Created on January 20, 2015, 8:57 PM
 */

#include "lightsky/draw/renderStage.h"

namespace ls {
namespace draw {

/*-------------------------------------
 * Destructor
-------------------------------------*/
renderStage::~renderStage() {
}

/*-------------------------------------
 * Scene Gaph traversing for rendering (hierarchial).
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
