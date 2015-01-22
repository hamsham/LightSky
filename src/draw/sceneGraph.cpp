/* 
 * File:   sceneGraph.cpp
 * Author: Miles Lacey
 * 
 * Created on January 19, 2015, 10:08 PM
 */

#include <algorithm>
#include <utility>

#include "lightsky/draw/setup.h"
#include "lightsky/draw/camera.h"
#include "lightsky/draw/geometry.h"
#include "lightsky/draw/sceneMesh.h"
#include "lightsky/draw/sceneResource.h"
#include "lightsky/draw/sceneGraph.h"
#include "lightsky/draw/texture.h"

namespace ls {
namespace draw {

/*-------------------------------------
 * Destructor
-------------------------------------*/
sceneGraph::~sceneGraph() {
    terminate();
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
sceneGraph::sceneGraph() {
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
sceneGraph::sceneGraph(sceneGraph&& s) :
    rootNode{std::move(s.rootNode)},
    cameraList{std::move(s.cameraList)},
    textureList{std::move(s.textureList)},
    geometryList{std::move(s.geometryList)},
    meshList{std::move(s.meshList)},
    nodeList{std::move(s.nodeList)}
{}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
sceneGraph& sceneGraph::operator=(sceneGraph&& s) {
    rootNode = std::move(s.rootNode);
    cameraList = std::move(s.cameraList);
    textureList = std::move(s.textureList);
    geometryList = std::move(s.geometryList);
    meshList = std::move(s.meshList);
    nodeList = std::move(s.nodeList);

    return *this;
}

/*-------------------------------------
 * Scene Loading
-------------------------------------*/
bool sceneGraph::init(const sceneResource& r, bool append) {
    if (append == false) {
        terminate();
    }
    
    LS_LOG_MSG("Attempting to initialize a scene graph from a scene resource.");
    
    if (!importGeometry(r)) {
        LS_LOG_ERR("\tFailed to load geometry data from a scene resource.\n");
        terminate();
        return false;
    }
    
    const unsigned meshOffset = meshList.size();
    if (r.getNumMeshes()) {
        if (!importMeshes(r)) {
            LS_LOG_ERR("\tFailed to load mesh data from a scene resource.\n");
            terminate();
            return false;
        }
    }
    
    if (!importNodes(r, meshOffset)) {
        LS_LOG_ERR("\tFailed to load node data from a scene resource.\n");
        terminate();
        return false;
    }
    
    if (cameraList.empty()) {
        camera* pCamera = new camera{};
        cameraList.push_back(pCamera);
    }
    
    LS_LOG_MSG("\tSuccessfully initialized a scene graph from a scene resource.");
    
    return true;
}

/*-------------------------------------
 * Scene Geometry Loading
-------------------------------------*/
bool sceneGraph::importGeometry(const sceneResource& r) {
    geometry* const pGeometry = new geometry{};
    
    if (!pGeometry) {
        LS_LOG_ERR("\tUnable to allocate geometry data while importing a scene resource.");
        return false;
    }
    else {
        // add the geometry data the the back of geometryList in the event of
        // an appended import.
        geometryList.push_back(pGeometry);
    }
    
    if (!pGeometry->init(r)) {
        LS_LOG_ERR("\tUnable to load geometry data while importing a scene resource.");
        return false;
    }
    
    return true;
}

/*-------------------------------------
 * Scene Mesh Loading
-------------------------------------*/
bool sceneGraph::importMeshes(const sceneResource& r) {
    if (geometryList.empty()) {
        return true;
    }

    const draw_index_list_t& rIndexList = r.getMeshes();
    meshList.reserve(meshList.size() + rIndexList.size());
    
    for (const draw_index_pair_t& rIndices : rIndexList) {
        sceneMesh* const pMesh = new sceneMesh{};

        if (!pMesh) {
            LS_LOG_ERR("\tUnable to allocate mesh data while importing a scene resource.");
            return false;
        }
        else {
            meshList.push_back(pMesh);
        }
        
        // retrieve the last geometry object as it will contain the geometry
        // data from an appended import.
        const geometry* const pGeometry = geometryList.back();
        if (!pMesh->init(*pGeometry)) {
            LS_LOG_ERR("\tUnable to initialize mesh data while importing a scene resource.");
            return false;
        }
        else {
            pMesh->setIndices(rIndices);
        }
    }
    
    return true;
}

/*-------------------------------------
 * Scene Node Loading
-------------------------------------*/
bool sceneGraph::importNodes(const sceneResource& r, const unsigned meshOffset) {
    if (!r.getNumNodes() || !r.getNumMeshes()) {
        return true;
    }
    
    const unsigned nodeOffset = nodeList.size();
    nodeList.resize(nodeOffset + r.getNumNodes());
    
    // insert the last node in "nodeList" into the root node
    rootNode.nodeChildren.push_back(&nodeList[nodeOffset]);
    
    nodeList[nodeOffset].nodeParent = &rootNode;
    
    for (unsigned i = 0; i < r.getNumNodes(); ++i) {
        const sceneResource::resourceNode& importNode = r.getNodes()[i];
        sceneNode& newNode = nodeList[nodeOffset + i];
        
        newNode.nodeParent = &nodeList[nodeOffset + importNode.parentIndex];
        newNode.nodeName = importNode.name;
        
        newNode.nodeMeshes.reserve(importNode.meshIndices.size());
        
        for (unsigned meshIndex : importNode.meshIndices) {
            sceneMesh* const pMesh = meshList[meshOffset + meshIndex];
            newNode.nodeMeshes.push_back(pMesh);
        }
        
        newNode.nodeChildren.reserve(importNode.childIndices.size());
        for (unsigned childIndex : importNode.childIndices) {
            newNode.nodeChildren.push_back(&nodeList[nodeOffset + childIndex]);
        }
        
        newNode.nodeTransform.setTransform(importNode.transform);
    }
    
    return true;
}

/*-------------------------------------
 * Scene updating
 *
 * This method updates all nodes and their respective child nodes "recursively"
 * by placing parent nodes into a stack. This is to avoid a severe stack
 * overflow bug that used to occur, causing either a driver crash or kernel
 * panic.
-------------------------------------*/
void sceneGraph::update(uint64_t millisElapsed) {
    for (camera* const pCam : cameraList) {
        pCam->update();
    }
    
    // seed the node stack
    const math::mat4& pRootTrans = rootNode.nodeTransform.getTransform();
    updateStack.emplace(nodeStackInfo{&rootNode, 0, pRootTrans});

    // iterate rather than recurse.
    while (!updateStack.empty()) {

        // pull off the top sceneNode and model matrix for updating.
        nodeStackInfo& currentIter = updateStack.top();
        sceneNode* const pNode = currentIter.pNode;
        
        // Meat & Potatoes
        updateSceneNode(millisElapsed, *pNode);

        // get a reference to the index of the currently selected child node.
        unsigned& nextChildIndex = currentIter.childIter;

        // check if the child node is valid, remove the current node if not
        if (nextChildIndex < pNode->nodeChildren.size()) {
            // increment the child reference to the next node.
            sceneNode* pChild = pNode->nodeChildren[nextChildIndex++];

            // push the next child node's matrix onto the stack
            // augment it by the parent transform
            const math::mat4& modelMat = updateStack.top().modelMatrix;
            const math::mat4& childModelMat = pChild->nodeTransform.getTransform();

            // stack the currently used node and push its next child onto the stack
            updateStack.emplace(nodeStackInfo{pChild, 0, modelMat * childModelMat});
        }
        else {
            updateStack.pop();
        }
    }

    LS_DEBUG_ASSERT(updateStack.empty());
}

/*-------------------------------------
 * Individual node updating
-------------------------------------*/
void sceneGraph::updateSceneNode(uint64_t millisElapsed, sceneNode& node) {
    (void)millisElapsed;
    transform& modelTransform = node.nodeTransform;

    if (modelTransform.isDirty()) {
        modelTransform.applyTransforms();
    }
}

/*-------------------------------------
 * Resource termination helper function.
-------------------------------------*/
template <typename data_t>
struct sceneDeleter {
    void operator()(data_t* const pData) {
        delete pData;
    }
};

/*-------------------------------------
 * Resource termination
-------------------------------------*/
void sceneGraph::terminate() {
    rootNode.reset();
    
    std::for_each(cameraList.begin(),   cameraList.end(),   sceneDeleter<camera>{});
    std::for_each(textureList.begin(),  textureList.end(),  sceneDeleter<texture>{});
    std::for_each(geometryList.begin(), geometryList.end(), sceneDeleter<geometry>{});
    std::for_each(meshList.begin(),     meshList.end(),     sceneDeleter<sceneMesh>{});
    
    nodeList.clear();
}

} // end draw namepsace
} // end ls namespace