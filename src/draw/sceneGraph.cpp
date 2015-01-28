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
#include "lightsky/draw/imageResource.h"
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
    delete pMainCamera;
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
sceneGraph::sceneGraph() :
    rootNode{},
    pMainCamera{new camera{}},
    geometryList{},
    textureList{},
    meshList{},
    nodeList{}
{}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
sceneGraph::sceneGraph(sceneGraph&& s) :
    rootNode{std::move(s.rootNode)},
    pMainCamera{std::move(s.pMainCamera)},
    geometryList{std::move(s.geometryList)},
    textureList{std::move(s.textureList)},
    meshList{std::move(s.meshList)},
    nodeList{std::move(s.nodeList)}
{
    s.pMainCamera = nullptr;
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
sceneGraph& sceneGraph::operator=(sceneGraph&& s) {
    rootNode = std::move(s.rootNode);
    
    pMainCamera = std::move(s.pMainCamera);
    s.pMainCamera = nullptr;
    
    geometryList = std::move(s.geometryList);
    textureList = std::move(s.textureList);
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
    
    const unsigned textureOffset = textureList.size();
    if (!importTextures(r)) {
        LS_LOG_ERR("\tFailed to load texture data from a scene resource.\n");
        // failure to load textures is not an unrecoverable error.
    }
    
    const unsigned meshOffset = meshList.size();
    if (r.getNumMeshes()) {
        if (!importMeshes(r, textureOffset)) {
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
    
    LS_LOG_MSG("\tSuccessfully initialized a scene graph from a scene resource.\n");
    
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
 * Scene Texture Loading
-------------------------------------*/
bool sceneGraph::importTextures(const sceneResource& r) {
    bool ret = true;
    const unsigned textureOffset = textureList.size();
    textureList.reserve(textureList.size() + textureOffset);
    
    imageResource loader{};
    
    for (const std::pair<tex_slot_t, std::vector<sceneResource::resourceTexture>>& rTextureList : r.getTextures()) {
        for (const sceneResource::resourceTexture& rTexture : rTextureList.second) {
            
            const std::string& rTexturePath = rTexture.texPath;
            const tex_slot_t rTexSlot = rTexture.texSlot;
            
            LS_LOG_MSG("Loading texture ", textureList.size(), '.');
            if (rTexturePath.empty()) {
                LS_LOG_ERR("\tUnsupported texture data found within a scene resource.");
                textureList.push_back(nullptr);
                continue;
            }
            
            // the imageLoader class provides logging. no need to add extra.
            if (!loader.loadFile(rTexturePath)) {
                textureList.push_back(nullptr); // non-fatal error
                ret = false;
                continue;
            }
            
            texture* const pTexture = new texture{};
            if (!pTexture) {
                LS_LOG_ERR("\tUnable to allocate texture data while importing a scene resource.");
                textureList.push_back(nullptr); // non-fatal error
                ret = false;
                continue;
            }
            
            // add the geometry data the the back of textureList in the event of
            // an appended import.
            textureList.push_back(pTexture);
            pTexture->setTextureSlot(rTexSlot);

            if (!pTexture->init(loader)) {
                LS_LOG_ERR("\tUnable to load texture data while importing a scene resource.");
                ret = false;
            }
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_BLUE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
            pTexture->setParameter(TEX_PARAM_MIN_FILTER, TEX_FILTER_NEAREST);
            pTexture->setParameter(TEX_PARAM_MAG_FILTER, TEX_FILTER_LINEAR);
            pTexture->setParameter(TEX_PARAM_WRAP_S,     TEX_PARAM_CLAMP_EDGE);
            pTexture->setParameter(TEX_PARAM_WRAP_T,     TEX_PARAM_CLAMP_EDGE);
            LOG_GL_ERR();
            
            pTexture->unbind();
            LOG_GL_ERR();
        }
    }
    
    
    return ret;
}

/*-------------------------------------
 * Scene Mesh Loading
-------------------------------------*/
bool sceneGraph::importMeshes(const sceneResource& r, const unsigned textureOffset) {
    if (geometryList.empty()) {
        return true;
    }

    meshList.reserve(meshList.size() + r.getNumMeshes());
    
    for (const sceneResource::resourceMesh& rMesh : r.getMeshes()) {
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
        
        pMesh->setIndices(rMesh.indices);
        
        if (rMesh.textureIndex != sceneResource::INVALID_SCENE_RESOURCE) {
            texture* const pTex = textureList[textureOffset + rMesh.textureIndex];
            if (pTex != nullptr) {
                pMesh->addTexture(*pTex);
            }
        }
        
        LS_LOG_MSG(
            "\tMesh ", meshList.size()-1,
            " contains texture ",
            rMesh.textureIndex, '-', textureList[textureOffset+rMesh.textureIndex]->isValid()
        );
    }
    
    return true;
}

/*-------------------------------------
 * Scene Node Loading
-------------------------------------*/
bool sceneGraph::importNodes(const sceneResource& r, const unsigned meshOffset) {
    LS_LOG_MSG("Loading scene nodes from a resource object.");
    
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
        
        //newNode.nodeParent = &nodeList[nodeOffset + importNode.parentIndex];
        newNode.nodeParent = &nodeList[nodeOffset + importNode.nodeParentId];
        newNode.nodeName = importNode.nodeName;
        
        newNode.nodeMeshes.reserve(importNode.nodeMeshes.size());
        
        for (unsigned meshIndex : importNode.nodeMeshes) {
            sceneMesh* const pMesh = meshList[meshOffset + meshIndex];
            newNode.nodeMeshes.push_back(pMesh);
        }
        
        newNode.nodeChildren.reserve(importNode.nodeChildren.size());
        for (unsigned childIndex : importNode.nodeChildren) {
            newNode.nodeChildren.push_back(&nodeList[nodeOffset + childIndex]);
        }
        
        newNode.nodeTransform.setTransform(importNode.nodeTransform);
        
        LS_LOG_MSG("\tAdded node \"", newNode.nodeName, "\" to a scene graph.");
    }
    
    LS_LOG_MSG("\tSuccessfully imported ", nodeList.size(), " nodes into a scene graph.");
    
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
void sceneGraph::update(uint64_t millisElapsed) {
    pMainCamera->update();
    
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
            sceneNode* const pChild = pNode->nodeChildren[nextChildIndex++];

            // push the next child node's matrix onto the stack
            // augment it by the parent transform
            const math::mat4& childModelMat = pChild->nodeTransform.getTransform();
            //const math::mat4& accumulatedMatrix = updateStack.top().modelMatrix;

            // stack the currently used node and push its next child onto the stack
            updateStack.emplace(nodeStackInfo{pChild, 0, childModelMat});
        }
        else {
            updateStack.pop();
        }
    }

    LS_DEBUG_ASSERT(updateStack.empty());
}
*/

/*-------------------------------------
 * Scene updating (linear)
-------------------------------------*/
void sceneGraph::update(uint64_t millisElapsed) {
    pMainCamera->update();
    
    for (sceneNode&node : nodeList) {
        updateSceneNode(millisElapsed, node);
    }
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
    
    std::for_each(geometryList.begin(), geometryList.end(), sceneDeleter<geometry>{});
    geometryList.clear();
    geometryList.shrink_to_fit();
    
    std::for_each(textureList.begin(),  textureList.end(),  sceneDeleter<texture>{});
    textureList.clear();
    textureList.shrink_to_fit();
    
    std::for_each(meshList.begin(),     meshList.end(),     sceneDeleter<sceneMesh>{});
    meshList.clear();
    meshList.shrink_to_fit();
    
    nodeList.clear();
    nodeList.shrink_to_fit();
}

} // end draw namepsace
} // end ls namespace