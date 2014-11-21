/* 
 * File:   draw/sceneManager.cpp
 * Author: Miles Lacey
 * 
 * Created on May 26, 2014, 11:22 AM
 */

#include <utility>

#include "lightsky/draw/color.h"
#include "lightsky/draw/sceneManager.h"

/*-------------------------------------
 * Extern Template Types
-------------------------------------*/
template class std::deque<ls::draw::mesh*>;
template class std::deque<ls::draw::meshModel*>;
template class std::deque<ls::draw::texture*>;
template class std::deque<ls::draw::atlas*>;

namespace ls {
namespace draw {

/*
 * Destructor
 */
sceneManager::~sceneManager() {
    terminate();
}

/*
 * Constructor
 */
sceneManager::sceneManager() :
    defaultTex{tex_desc_t::TEX_DESC_2D},
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
    defaultTex = std::move(sm.defaultTex);
    texMgr = std::move(sm.texMgr);
    meshMgr = std::move(sm.meshMgr);
    atlasMgr = std::move(sm.atlasMgr);
    drawMgr = std::move(sm.drawMgr);
    
    return *this;
}

/*
 * Scene initialization
 */
bool sceneManager::init() {
    LS_LOG_MSG("Attempting to initialize a scene manager.");
    terminate();
    
    // Ensuring that there is always a texture to draw with
    if (!initDefaultTexture()) {
        LS_LOG_ERR("Unable to initialize a default texture for the sene manager.");
        return false;
    }
    
    LS_LOG_MSG("\tSuccessfully initialized a scene manager.");
    return true;
}

/*
 * Resource termination
 */
void sceneManager::terminate() {
    defaultTex.terminate();
    
    for (mesh* pMesh : meshMgr) {
        delete pMesh;
    }
    meshMgr.clear();
    
    for (texture* pTex : texMgr) {
        delete pTex;
    }
    texMgr.clear();
    
    for (atlas* pAtlas : atlasMgr) {
        delete pAtlas;
    }
    atlasMgr.clear();
    
    for (meshModel* pModel : drawMgr) {
        delete pModel;
    }
    drawMgr.clear();
}

//-----------------------------------------------------------------------------
//      Static Implementations
//-----------------------------------------------------------------------------
// Default Texture color
static constexpr color checkeredCol[] = {
    lsMagenta,  lsBlack,
    lsBlack,    lsMagenta
};

/*
 * Initialization of the default gray and magic pink textures
 */
bool sceneManager::initDefaultTexture() {
    if (defaultTex.getId()) {
        return true;
    }
    
    if (!defaultTex.init(
        0, COLOR_FMT_RGBA_32F,
        math::vec2i{2},
        COLOR_LAYOUT_RGBA, COLOR_TYPE_FLOAT,
        (void*)checkeredCol)
    ) {
        LS_LOG_ERR("\tUnable to initialize a default texture for draw models.");
        LOG_GL_ERR();
        
        return false;
    }
    else {
        defaultTex.setParameter(TEX_PARAM_MIN_FILTER, TEX_FILTER_NEAREST);
        defaultTex.setParameter(TEX_PARAM_MAG_FILTER, TEX_FILTER_NEAREST);
        defaultTex.setParameter(TEX_PARAM_WRAP_S, TEX_PARAM_REPEAT);
        defaultTex.setParameter(TEX_PARAM_WRAP_T, TEX_PARAM_REPEAT);
        LOG_GL_ERR();
    }
    
    return true;
}

//-----------------------------------------------------------------------------
//      Manager retrieval
//-----------------------------------------------------------------------------
meshList& sceneManager::getMeshList() {
    return meshMgr;
}

textureList& sceneManager::getTextureList() {
    return texMgr;
}

atlasList& sceneManager::getAtlasList() {
    return atlasMgr;
}

drawList& sceneManager::getModelList() {
    return drawMgr;
}

//-----------------------------------------------------------------------------
//      Manager retrieval (const)
//-----------------------------------------------------------------------------
const meshList& sceneManager::getMeshList() const {
    return meshMgr;
}

const textureList& sceneManager::getTextureList() const {
    return texMgr;
}

const atlasList& sceneManager::getAtlasList() const {
    return atlasMgr;
}

const drawList& sceneManager::getModelList() const {
    return drawMgr;
}

//-----------------------------------------------------------------------------
//      Resource "get" methods
//-----------------------------------------------------------------------------
mesh* sceneManager::getMesh(unsigned index) const {
    LS_DEBUG_ASSERT(index < meshMgr.size());
    return meshMgr[index];
}

texture* sceneManager::getTexture(unsigned index) const {
    LS_DEBUG_ASSERT(index < texMgr.size());
    return texMgr[index];
}

atlas* sceneManager::getAtlas(unsigned index) const {
    LS_DEBUG_ASSERT(index < atlasMgr.size());
    return atlasMgr[index];
}

meshModel* sceneManager::getModel(unsigned index) const {
    LS_DEBUG_ASSERT(index < drawMgr.size());
    return drawMgr[index];
}

//-----------------------------------------------------------------------------
//      Resource deletion methods
//-----------------------------------------------------------------------------
void sceneManager::eraseMesh(unsigned index) {
    mesh* pMesh = meshMgr[index];
    delete pMesh;
    meshMgr.erase(meshMgr.begin()+index);
}

void sceneManager::eraseTexture(unsigned index) {
    texture* pTex = texMgr[index];
    delete pTex;
    texMgr.erase(texMgr.begin()+index);
}

void sceneManager::eraseAtlas(unsigned index) {
    atlas* pAtlas = atlasMgr[index];
    delete pAtlas;
    atlasMgr.erase(atlasMgr.begin()+index);
}

void sceneManager::eraseModel(unsigned index) {
    meshModel* pDrawModel = drawMgr[index];
    delete pDrawModel;
    drawMgr.erase(drawMgr.begin()+index);
}

//-----------------------------------------------------------------------------
//      Resource counts
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//      Resource management
//-----------------------------------------------------------------------------
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

unsigned sceneManager::manageModel(meshModel* const pText) {
    if (pText != nullptr && this->containsModel(pText) == false) {
        const unsigned index = pText->getId();
        drawMgr.push_back(pText);
        return index;
    }
    
    return INVALID_SCENE_ID;
}

//-----------------------------------------------------------------------------
//      Resource un-management
//-----------------------------------------------------------------------------
mesh* sceneManager::unManageMesh(unsigned index) {
    LS_DEBUG_ASSERT(index < meshMgr.size());
    mesh* const pMesh = meshMgr[index];
    meshMgr.erase(meshMgr.begin() + index);
    return pMesh;
}

texture* sceneManager::unManageTexture(unsigned index) {
    LS_DEBUG_ASSERT(index < texMgr.size());
    texture* const pTex = texMgr[index];
    texMgr.erase(texMgr.begin() + index);
    return pTex;
}

atlas* sceneManager::unManageAtlas(unsigned index) {
    LS_DEBUG_ASSERT(index < atlasMgr.size());
    atlas* const pAtlas = atlasMgr[index];
    atlasMgr.erase(atlasMgr.begin() + index);
    return pAtlas;
}

meshModel* sceneManager::unManageModel(unsigned index) {
    LS_DEBUG_ASSERT(index < drawMgr.size());
    meshModel* const pText = drawMgr[index];
    drawMgr.erase(drawMgr.begin() + index);
    return pText;
}

//-----------------------------------------------------------------------------
//      Resource queries
//-----------------------------------------------------------------------------
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

bool sceneManager::containsModel(const meshModel* const pText) const {
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

} // end draw namespace
} // end draw namespace
