/* 
 * File:   sceneManager.cpp
 * Author: miles
 * 
 * Created on May 26, 2014, 11:22 AM
 */

#include <utility>

#include "mesh.h"
#include "text.h"
#include "texture.h"
#include "textureAtlas.h"
#include "sceneManager.h"

static const unsigned char checkeredCol[] = {
    255,    0,  255,    255,
    0,      0,  0,      255,
    255,    0,  255,    255,
    0,      0,  0,      255
};

/*
 * Management implementations
 */
LS_DEFINE_CLASS_TYPE(manager, unsigned, mesh);
LS_DEFINE_CLASS_TYPE(manager, unsigned, texture);
LS_DEFINE_CLASS_TYPE(manager, unsigned, textureAtlas);
LS_DEFINE_CLASS_TYPE(manager, unsigned, text);

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
    stringMgr{}
{}

/*
 * Move Constructor
 */
sceneManager::sceneManager(sceneManager&& sm) :
    defaultTex{std::move(sm.defaultTex)},
    texMgr{std::move(sm.texMgr)},
    meshMgr{std::move(sm.meshMgr)},
    atlasMgr{std::move(sm.atlasMgr)},
    stringMgr{std::move(sm.stringMgr)}
{}

/*
 * Move Operator
 */
sceneManager& sceneManager::operator =(sceneManager&& sm) {
    texMgr = std::move(sm.texMgr);
    meshMgr = std::move(sm.meshMgr);
    atlasMgr = std::move(sm.atlasMgr);
    stringMgr = std::move(sm.stringMgr);
    
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
    stringMgr.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Manager retrieval
///////////////////////////////////////////////////////////////////////////////
meshManager::map_t& sceneManager::getMeshManager() {
    return meshMgr.getDataMap();
}

textureManager::map_t& sceneManager::getTextureManager() {
    return texMgr.getDataMap();
}

atlasManager::map_t& sceneManager::getAtlasManager() {
    return atlasMgr.getDataMap();
}

textManager::map_t& sceneManager::getTextManager() {
    return stringMgr.getDataMap();
}

///////////////////////////////////////////////////////////////////////////////
// Manager retrieval (const)
///////////////////////////////////////////////////////////////////////////////
const meshManager::map_t& sceneManager::getMeshManager() const {
    return meshMgr.getDataMap();
}

const textureManager::map_t& sceneManager::getTextureManager() const {
    return texMgr.getDataMap();
}

const atlasManager::map_t& sceneManager::getAtlasManager() const {
    return atlasMgr.getDataMap();
}

const textManager::map_t& sceneManager::getTextManager() const {
    return stringMgr.getDataMap();
}

///////////////////////////////////////////////////////////////////////////////
// Resource "get" methods
///////////////////////////////////////////////////////////////////////////////
mesh* sceneManager::getMesh(unsigned id) const {
    return meshMgr.get(id);
}

texture* sceneManager::getTexture(unsigned id) const {
    return texMgr.get(id);
}

textureAtlas* sceneManager::getAtlas(unsigned id) const {
    return atlasMgr.get(id);
}

text* sceneManager::getText(unsigned id) const {
    return stringMgr.get(id);
}

///////////////////////////////////////////////////////////////////////////////
// Resource deletion methods
///////////////////////////////////////////////////////////////////////////////
void sceneManager::eraseMesh(unsigned id) {
    meshMgr.erase(id);
}

void sceneManager::eraseTexture(unsigned id) {
    texMgr.erase(id);
}

void sceneManager::eraseAtlas(unsigned id) {
    atlasMgr.erase(id);
}

void sceneManager::eraseText(unsigned id) {
    stringMgr.erase(id);
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

unsigned sceneManager::getNumTexts() const {
    return stringMgr.size();
}

///////////////////////////////////////////////////////////////////////////////
// Resource management
///////////////////////////////////////////////////////////////////////////////
unsigned sceneManager::manageMesh(mesh* const pMesh) {
    if (pMesh != nullptr) {
        const unsigned id = pMesh->getId();
        meshMgr.manage(id, pMesh);
        return id;
    }
    
    return INVALID_SCENE_ID;
}

unsigned sceneManager::manageTexture(texture* const pTexture) {
    if (pTexture != nullptr) {
        const unsigned id = pTexture->getId();
        texMgr.manage(id, pTexture);
        return id;
    }
    
    return INVALID_SCENE_ID;
}

unsigned sceneManager::manageAtlas(textureAtlas* const pAtlas) {
    if (pAtlas != nullptr) {
        const unsigned id = pAtlas->getId();
        atlasMgr.manage(id, pAtlas);
        return id;
    }
    
    return INVALID_SCENE_ID;
}

unsigned sceneManager::manageText(text* const pText) {
    if (pText != nullptr) {
        const unsigned id = pText->getId();
        stringMgr.manage(id, pText);
        return id;
    }
    
    return INVALID_SCENE_ID;
}

///////////////////////////////////////////////////////////////////////////////
// Resource un-management
///////////////////////////////////////////////////////////////////////////////
mesh* sceneManager::unManageMesh(unsigned id) {
    return meshMgr.unmanage(id);
}

texture* sceneManager::unManageTexture(unsigned id) {
    return texMgr.unmanage(id);
}

textureAtlas* sceneManager::unManageAtlas(unsigned id) {
    return atlasMgr.unmanage(id);
}

text* sceneManager::unManageText(unsigned id) {
    return stringMgr.unmanage(id);
}

///////////////////////////////////////////////////////////////////////////////
// Resource queries
///////////////////////////////////////////////////////////////////////////////
bool sceneManager::containsMesh(const mesh* const pMesh) const {
    return pMesh != nullptr ? meshMgr.contains(pMesh->getId()) : false;
}

bool sceneManager::containsTexture(const texture* const pTex) const {
    return pTex != nullptr ? texMgr.contains(pTex->getId()) : false;
}

bool sceneManager::containsAtlas(const textureAtlas* const pAtlas) const {
    return pAtlas != nullptr ? atlasMgr.contains(pAtlas->getId()) : false;
}

bool sceneManager::containsText(const text* const pText) const {
    return pText != nullptr ? stringMgr.contains(pText->getId()) : false;
}
