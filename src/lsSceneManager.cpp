/* 
 * File:   lsSceneManager.cpp
 * Author: miles
 * 
 * Created on May 26, 2014, 11:22 AM
 */

#include <algorithm>
#include <utility>

#include "lsColor.h"
#include "lsSceneManager.h"

// Default Texture color
static const unsigned char checkeredCol[] = {
    0,    0,    0,    255
};

//-----------------------------------------------------------------------------
//      Scene Manager Class
//-----------------------------------------------------------------------------
/*
 * Destructor
 */
lsSceneManager::~lsSceneManager() {
    terminate();
}

/*
 * Constructor
 */
lsSceneManager::lsSceneManager() :
    defaultTex{ls_tex_desc_t::LS_TEX_2D},
    texMgr{},
    meshMgr{},
    atlasMgr{},
    drawMgr{}
{}

/*
 * Move Constructor
 */
lsSceneManager::lsSceneManager(lsSceneManager&& sm) :
    defaultTex{std::move(sm.defaultTex)},
    texMgr{std::move(sm.texMgr)},
    meshMgr{std::move(sm.meshMgr)},
    atlasMgr{std::move(sm.atlasMgr)},
    drawMgr{std::move(sm.drawMgr)}
{}

/*
 * Move Operator
 */
lsSceneManager& lsSceneManager::operator =(lsSceneManager&& sm) {
    texMgr = std::move(sm.texMgr);
    meshMgr = std::move(sm.meshMgr);
    atlasMgr = std::move(sm.atlasMgr);
    drawMgr = std::move(sm.drawMgr);
    
    return *this;
}

/*
 * Initialization of the default gray and magic pink textures
 */
bool lsSceneManager::initDefaultTexture() {
    if (!defaultTex.init(0, GL_RED, math::vec2i{1}*sizeof(lsWhite), GL_RED, GL_FLOAT, (void*)&lsWhite)) {
        LS_LOG_ERR("\tUnable to initialize a default texture for the scene manager.");
        return false;
    }
    
    return true;
}

/*
 * Scene initialization
 */
bool lsSceneManager::init() {
    terminate();
    
    LS_LOG_MSG("Attempting to initialize a scene manager.");
    
    if (!initDefaultTexture()) {
        LS_LOG_ERR("\tUnable to initialize a scene manager.");
        return false;
    }
    
    LS_LOG_MSG("\tSuccessfully initialized a scene manager.");
    return true;
}

/*
 * Resource termination
 */
void lsSceneManager::terminate() {
    clear();
    defaultTex.terminate();
}

/*
 * Management release
 */
void lsSceneManager::clear() {
    for (lsMesh* pMesh : meshMgr) {
        delete pMesh;
    }
    meshMgr.clear();
    
    for (lsTexture* pTex : texMgr) {
        delete pTex;
    }
    texMgr.clear();
    
    for (lsAtlas* pAtlas : atlasMgr) {
        delete pAtlas;
    }
    atlasMgr.clear();
    
    for (lsDrawModel* pModel : drawMgr) {
        delete pModel;
    }
    drawMgr.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Manager retrieval
///////////////////////////////////////////////////////////////////////////////
lsMeshList& lsSceneManager::getMeshList() {
    return meshMgr;
}

lsTextureList& lsSceneManager::getTextureList() {
    return texMgr;
}

lsAtlasList& lsSceneManager::getAtlasList() {
    return atlasMgr;
}

lsDrawList& lsSceneManager::getModelList() {
    return drawMgr;
}

///////////////////////////////////////////////////////////////////////////////
// Manager retrieval (const)
///////////////////////////////////////////////////////////////////////////////
const lsMeshList& lsSceneManager::getMeshList() const {
    return meshMgr;
}

const lsTextureList& lsSceneManager::getTextureList() const {
    return texMgr;
}

const lsAtlasList& lsSceneManager::getAtlasList() const {
    return atlasMgr;
}

const lsDrawList& lsSceneManager::getModelList() const {
    return drawMgr;
}

///////////////////////////////////////////////////////////////////////////////
// Resource "get" methods
///////////////////////////////////////////////////////////////////////////////
lsMesh* lsSceneManager::getMesh(unsigned index) const {
    HL_DEBUG_ASSERT(index < meshMgr.size());
    return meshMgr[index];
}

lsTexture* lsSceneManager::getTexture(unsigned index) const {
    HL_DEBUG_ASSERT(index < texMgr.size());
    return texMgr[index];
}

lsAtlas* lsSceneManager::getAtlas(unsigned index) const {
    HL_DEBUG_ASSERT(index < atlasMgr.size());
    return atlasMgr[index];
}

lsDrawModel* lsSceneManager::getModel(unsigned index) const {
    HL_DEBUG_ASSERT(index < drawMgr.size());
    return drawMgr[index];
}

///////////////////////////////////////////////////////////////////////////////
// Resource deletion methods
///////////////////////////////////////////////////////////////////////////////
void lsSceneManager::eraseMesh(unsigned index) {
    lsMesh* pMesh = meshMgr[index];
    delete pMesh;
    meshMgr.erase(meshMgr.begin()+index);
}

void lsSceneManager::eraseTexture(unsigned index) {
    lsTexture* pTex = texMgr[index];
    delete pTex;
    texMgr.erase(texMgr.begin()+index);
}

void lsSceneManager::eraseAtlas(unsigned index) {
    lsAtlas* pAtlas = atlasMgr[index];
    delete pAtlas;
    atlasMgr.erase(atlasMgr.begin()+index);
}

void lsSceneManager::eraseModel(unsigned index) {
    lsDrawModel* pDrawModel = drawMgr[index];
    delete pDrawModel;
    drawMgr.erase(drawMgr.begin()+index);
}

///////////////////////////////////////////////////////////////////////////////
// Resource counts
///////////////////////////////////////////////////////////////////////////////
unsigned lsSceneManager::getNumMeshes() const {
    return meshMgr.size();
}

unsigned lsSceneManager::getNumTextures() const {
    return texMgr.size();
}

unsigned lsSceneManager::getNumAtlases() const {
    return atlasMgr.size();
}

unsigned lsSceneManager::getNumModels() const {
    return drawMgr.size();
}

///////////////////////////////////////////////////////////////////////////////
// Resource management
///////////////////////////////////////////////////////////////////////////////
unsigned lsSceneManager::manageMesh(lsMesh* const pMesh) {
    if (pMesh != nullptr && this->containsMesh(pMesh) == false) {
        const unsigned index = pMesh->getId();
        meshMgr.push_back(pMesh);
        return index;
    }
    
    return LS_INVALID_SCENE_ID;
}

unsigned lsSceneManager::manageTexture(lsTexture* const pTexture) {
    if (pTexture != nullptr && this->containsTexture(pTexture) == false) {
        const unsigned index = pTexture->getId();
        texMgr.push_back(pTexture);
        return index;
    }
    
    return LS_INVALID_SCENE_ID;
}

unsigned lsSceneManager::manageAtlas(lsAtlas* const pAtlas) {
    if (pAtlas != nullptr && this->containsAtlas(pAtlas) == false) {
        const unsigned index = pAtlas->getId();
        atlasMgr.push_back(pAtlas);
        return index;
    }
    
    return LS_INVALID_SCENE_ID;
}

unsigned lsSceneManager::manageModel(lsDrawModel* const pText) {
    if (pText != nullptr && this->containsModel(pText) == false) {
        const unsigned index = pText->getId();
        drawMgr.push_back(pText);
        return index;
    }
    
    return LS_INVALID_SCENE_ID;
}

///////////////////////////////////////////////////////////////////////////////
// Resource un-management
///////////////////////////////////////////////////////////////////////////////
lsMesh* lsSceneManager::unManageMesh(unsigned index) {
    HL_DEBUG_ASSERT(index < meshMgr.size());
    lsMesh* const pMesh = meshMgr[index];
    meshMgr.erase(meshMgr.begin() + index);
    return pMesh;
}

lsTexture* lsSceneManager::unManageTexture(unsigned index) {
    HL_DEBUG_ASSERT(index < texMgr.size());
    lsTexture* const pTex = texMgr[index];
    texMgr.erase(texMgr.begin() + index);
    return pTex;
}

lsAtlas* lsSceneManager::unManageAtlas(unsigned index) {
    HL_DEBUG_ASSERT(index < atlasMgr.size());
    lsAtlas* const pAtlas = atlasMgr[index];
    atlasMgr.erase(atlasMgr.begin() + index);
    return pAtlas;
}

lsDrawModel* lsSceneManager::unManageModel(unsigned index) {
    HL_DEBUG_ASSERT(index < drawMgr.size());
    lsDrawModel* const pText = drawMgr[index];
    drawMgr.erase(drawMgr.begin() + index);
    return pText;
}

///////////////////////////////////////////////////////////////////////////////
// Resource queries
///////////////////////////////////////////////////////////////////////////////
bool lsSceneManager::containsMesh(const lsMesh* const pMesh) const {
    if (pMesh == nullptr) {
        return false;
    }
    else {
        lsMeshList::const_iterator iter = meshMgr.begin();
        while (iter != meshMgr.end()) {
            if (pMesh->getId() == (*iter)->getId()) {
                return true;
            }
            
            ++iter;
        }
    }
    
    return false;
}

bool lsSceneManager::containsTexture(const lsTexture* const pTex) const {
    if (pTex == nullptr) {
        return false;
    }
    else {
        lsTextureList::const_iterator iter = texMgr.begin();
        while (iter != texMgr.end()) {
            if (pTex->getId() == (*iter)->getId()) {
                return true;
            }
            
            ++iter;
        }
    }
    
    return false;
}

bool lsSceneManager::containsAtlas(const lsAtlas* const pAtlas) const {
    if (pAtlas == nullptr) {
        return false;
    }
    else {
        lsAtlasList::const_iterator iter = atlasMgr.begin();
        while (iter != atlasMgr.end()) {
            if (pAtlas->getId() == (*iter)->getId()) {
                return true;
            }
            
            ++iter;
        }
    }
    
    return false;
}

bool lsSceneManager::containsModel(const lsDrawModel* const pText) const {
    if (pText == nullptr) {
        return false;
    }
    else {
        lsDrawList::const_iterator iter = drawMgr.begin();
        while (iter != drawMgr.end()) {
            if (pText->getId() == (*iter)->getId()) {
                return true;
            }
            
            ++iter;
        }
    }
    
    return false;
}
