/* 
 * File:   sceneManager.cpp
 * Author: miles
 * 
 * Created on May 26, 2014, 11:22 AM
 */

#include <algorithm>
#include <utility>

#include "sceneManager.h"

static const unsigned char checkeredCol[] = {
    255,    0,  255,    255,
    0,      0,  0,      255,
    255,    0,  255,    255,
    0,      0,  0,      255
};

///////////////////////////////////////////////////////////////////////////////
// Scene Manager Class
///////////////////////////////////////////////////////////////////////////////
/*
 * Constructor
 */
sceneManager::sceneManager() :
    defaultTex{tex_desc::TEX_2D},
    texMgr{},
    meshMgr{},
    atlasMgr{},
    drawMgr{}
{}

/*
 * Move Constructor
 */
sceneManager::sceneManager(sceneManager&& sm) :
    defaultTex{std::move(sm.defaultTex)},
    texMgr{std::move(sm.texMgr)},
    meshMgr{std::move(sm.meshMgr)},
    atlasMgr{std::move(sm.atlasMgr)},
    drawMgr{std::move(sm.drawMgr)}
{}

/*
 * Move Operator
 */
sceneManager& sceneManager::operator =(sceneManager&& sm) {
    texMgr = std::move(sm.texMgr);
    meshMgr = std::move(sm.meshMgr);
    atlasMgr = std::move(sm.atlasMgr);
    drawMgr = std::move(sm.drawMgr);
    
    return *this;
}

/*
 * Initialization of the default gray and magic pink textures
 */
bool sceneManager::initDefaultTexture() {
    if (!defaultTex.init(
        0, GL_RED, math::vec2i{2, 2}, GL_RED, GL_UNSIGNED_BYTE, (void*)checkeredCol
    )) {
        LOG_ERR("\tUnable to initialize a default texture for the scene manager.");
        return false;
    }
    
    return true;
}

/*
 * Scene initialization
 */
bool sceneManager::init() {
    terminate();
    
    LOG_MSG("Attempting to initialize a scene manager.");
    
    if (!initDefaultTexture()) {
        LOG_ERR("\tUnable to initialize a scene manager.");
        return false;
    }
    
    LOG_MSG("\tSuccessfully initialized a scene manager.");
    return true;
}

/*
 * Resource termination
 */
void sceneManager::terminate() {
    clear();
    defaultTex.terminate();
}

/*
 * Management release
 */
void sceneManager::clear() {
    texMgr.clear();
    meshMgr.clear();
    atlasMgr.clear();
    drawMgr.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Manager retrieval
///////////////////////////////////////////////////////////////////////////////
meshList& sceneManager::getMeshList() {
    return meshMgr;
}

textureList& sceneManager::getTextureList() {
    return texMgr;
}

atlasList& sceneManager::getAtlasList() {
    return atlasMgr;
}

drawList& sceneManager::getModelManager() {
    return drawMgr;
}

///////////////////////////////////////////////////////////////////////////////
// Manager retrieval (const)
///////////////////////////////////////////////////////////////////////////////
const meshList& sceneManager::getMeshList() const {
    return meshMgr;
}

const textureList& sceneManager::getTextureList() const {
    return texMgr;
}

const atlasList& sceneManager::getAtlasList() const {
    return atlasMgr;
}

const drawList& sceneManager::getModelManager() const {
    return drawMgr;
}

///////////////////////////////////////////////////////////////////////////////
// Resource "get" methods
///////////////////////////////////////////////////////////////////////////////
mesh* sceneManager::getMesh(unsigned index) const {
    HL_DEBUG_ASSERT(index < meshMgr.size());
    return meshMgr[index];
}

texture* sceneManager::getTexture(unsigned index) const {
    HL_DEBUG_ASSERT(index < texMgr.size());
    return texMgr[index];
}

atlas* sceneManager::getAtlas(unsigned index) const {
    HL_DEBUG_ASSERT(index < atlasMgr.size());
    return atlasMgr[index];
}

drawModel* sceneManager::getModel(unsigned index) const {
    HL_DEBUG_ASSERT(index < drawMgr.size());
    return drawMgr[index];
}

///////////////////////////////////////////////////////////////////////////////
// Resource deletion methods
///////////////////////////////////////////////////////////////////////////////
void sceneManager::eraseMesh(unsigned index) {
    meshMgr.erase(meshMgr.begin()+index);
}

void sceneManager::eraseTexture(unsigned index) {
    texMgr.erase(texMgr.begin()+index);
}

void sceneManager::eraseAtlas(unsigned index) {
    atlasMgr.erase(atlasMgr.begin()+index);
}

void sceneManager::eraseModel(unsigned index) {
    drawMgr.erase(drawMgr.begin()+index);
}

///////////////////////////////////////////////////////////////////////////////
// Resource counts
///////////////////////////////////////////////////////////////////////////////
unsigned sceneManager::getNumMeshes() const {
    return meshMgr.size();
}

unsigned sceneManager::getNumTextures() const {
    return texMgr.size();
}

unsigned sceneManager::getNumAtlases() const {
    return atlasMgr.size();
}

unsigned sceneManager::getNumModels() const {
    return drawMgr.size();
}

///////////////////////////////////////////////////////////////////////////////
// Resource management
///////////////////////////////////////////////////////////////////////////////
unsigned sceneManager::manageMesh(mesh* const pMesh) {
    if (pMesh != nullptr && this->containsMesh(pMesh) == false) {
        const unsigned index = pMesh->getId();
        meshMgr.push_back(pMesh);
        return index;
    }
    
    return INVALID_SCENE_ID;
}

unsigned sceneManager::manageTexture(texture* const pTexture) {
    if (pTexture != nullptr && this->containsTexture(pTexture) == false) {
        const unsigned index = pTexture->getId();
        texMgr.push_back(pTexture);
        return index;
    }
    
    return INVALID_SCENE_ID;
}

unsigned sceneManager::manageAtlas(atlas* const pAtlas) {
    if (pAtlas != nullptr && this->containsAtlas(pAtlas) == false) {
        const unsigned index = pAtlas->getId();
        atlasMgr.push_back(pAtlas);
        return index;
    }
    
    return INVALID_SCENE_ID;
}

unsigned sceneManager::manageModel(drawModel* const pText) {
    if (pText != nullptr && this->containsModel(pText) == false) {
        const unsigned index = pText->getId();
        drawMgr.push_back(pText);
        return index;
    }
    
    return INVALID_SCENE_ID;
}

///////////////////////////////////////////////////////////////////////////////
// Resource un-management
///////////////////////////////////////////////////////////////////////////////
mesh* sceneManager::unManageMesh(unsigned index) {
    HL_DEBUG_ASSERT(index < meshMgr.size());
    mesh* const pMesh = meshMgr[index];
    meshMgr.erase(meshMgr.begin() + index);
    return pMesh;
}

texture* sceneManager::unManageTexture(unsigned index) {
    HL_DEBUG_ASSERT(index < texMgr.size());
    texture* const pTex = texMgr[index];
    texMgr.erase(texMgr.begin() + index);
    return pTex;
}

atlas* sceneManager::unManageAtlas(unsigned index) {
    HL_DEBUG_ASSERT(index < atlasMgr.size());
    atlas* const pAtlas = atlasMgr[index];
    atlasMgr.erase(atlasMgr.begin() + index);
    return pAtlas;
}

drawModel* sceneManager::unManageModel(unsigned index) {
    HL_DEBUG_ASSERT(index < drawMgr.size());
    drawModel* const pText = drawMgr[index];
    drawMgr.erase(drawMgr.begin() + index);
    return pText;
}

///////////////////////////////////////////////////////////////////////////////
// Resource queries
///////////////////////////////////////////////////////////////////////////////
bool sceneManager::containsMesh(const mesh* const pMesh) const {
    if (pMesh == nullptr) {
        return false;
    }
    else {
        meshList::const_iterator iter = meshMgr.begin();
        while (iter != meshMgr.end()) {
            if (pMesh->getId() == (*iter)->getId()) {
                return true;
            }
            
            ++iter;
        }
    }
    
    return false;
}

bool sceneManager::containsTexture(const texture* const pTex) const {
    if (pTex == nullptr) {
        return false;
    }
    else {
        textureList::const_iterator iter = texMgr.begin();
        while (iter != texMgr.end()) {
            if (pTex->getId() == (*iter)->getId()) {
                return true;
            }
            
            ++iter;
        }
    }
    
    return false;
}

bool sceneManager::containsAtlas(const atlas* const pAtlas) const {
    if (pAtlas == nullptr) {
        return false;
    }
    else {
        atlasList::const_iterator iter = atlasMgr.begin();
        while (iter != atlasMgr.end()) {
            if (pAtlas->getId() == (*iter)->getId()) {
                return true;
            }
            
            ++iter;
        }
    }
    
    return false;
}

bool sceneManager::containsModel(const drawModel* const pText) const {
    if (pText == nullptr) {
        return false;
    }
    else {
        drawList::const_iterator iter = drawMgr.begin();
        while (iter != drawMgr.end()) {
            if (pText->getId() == (*iter)->getId()) {
                return true;
            }
            
            ++iter;
        }
    }
    
    return false;
}
