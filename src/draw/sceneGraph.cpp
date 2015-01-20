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
bool sceneGraph::init(const sceneResource& r) {
    terminate();
    
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
    
    LS_LOG_MSG("\tSuccessfully initialized a scene graph from a scene resource.");
    
    return true;
}

/*-------------------------------------
 * Scene Geometry Loading
-------------------------------------*/
bool sceneGraph::importGeometry(const sceneResource& r) {
    geometry* const pGeometry = new(std::nothrow) geometry{};
    
    if (!pGeometry) {
        LS_LOG_ERR("\tUnable to allocate geometry data while importing a scene resource.");
        return false;
    }
    else {
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
    meshList.reserve(r.getNumMeshes());
    const draw_index_list_t& rIndexList = r.getMeshes();
    
    for (const draw_index_pair_t& rIndices : rIndexList) {
        sceneMesh* const pMesh = new(std::nothrow) sceneMesh{};

        if (!pMesh) {
            LS_LOG_ERR("\tUnable to allocate mesh data while importing a scene resource.");
            return false;
        }
        else {
            meshList.push_back(pMesh);
        }

        if (geometryList.empty()) {
            continue;
        }
        
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
    const unsigned nodeOffset = nodeList.size();
    nodeList.resize(nodeOffset + r.getNumNodes());
    
    rootNode.nodeChildren.push_back(&nodeList[nodeOffset]);
    nodeList.back().nodeParent = &rootNode;
    
    for (unsigned i = 0; i < r.getNumNodes(); ++i) {
        const sceneResource::resourceNode& rNode = r.getNodes()[i];
        sceneNode& thisNode = nodeList[nodeOffset + i];
        
        thisNode.nodeParent = &nodeList[nodeOffset + rNode.parentIndex];
        thisNode.nodeName = rNode.name;
        
        thisNode.nodeMeshes.reserve(rNode.meshIndices.size());
        for (unsigned meshIndex : rNode.meshIndices) {
            thisNode.nodeMeshes.push_back(meshList[meshOffset + meshIndex]);
        }
        
        thisNode.nodeChildren.reserve(rNode.childIndices.size());
        for (unsigned childIndex : rNode.childIndices) {
            thisNode.nodeChildren.push_back(&nodeList[nodeOffset + childIndex]);
        }
        
        thisNode.nodeTransform.setTransform(rNode.transform);
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
/*
void sceneGraph::updateScene(uint64_t millisElapsed) {
    pCamera->update();

    for (sceneNode& node : this->nodeList) {
        updateSceneNode(millisElapsed, &node);
    }
}
*/

/*-------------------------------------
 * Individual node updating
-------------------------------------*/
/*
void sceneGraph::updateSceneNode(uint64_t, sceneNode* const pNode) {
    transform& modelTransform = pNode->nodeTransform;

    if (modelTransform.isDirty()) {
        modelTransform.applyTransforms();
    }
}
*/

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