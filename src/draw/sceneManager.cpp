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
template class std::deque<ls::draw::geometry*>;
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
    geometryMgr{},
    atlasMgr{},
    drawMgr{}
{}

/*
 * Move Constructor
 */
sceneManager::sceneManager(sceneManager&& sm) :
defaultTex{std::move(sm.defaultTex)},
    texMgr{std::move(sm.texMgr)},
    geometryMgr{std::move(sm.geometryMgr)},
    atlasMgr{std::move(sm.atlasMgr)},
    drawMgr{std::move(sm.drawMgr)}
{}

/*
 * Move Operator
 */
sceneManager& sceneManager::operator =(sceneManager&& sm) {
    defaultTex = std::move(sm.defaultTex);
    texMgr = std::move(sm.texMgr);
    geometryMgr = std::move(sm.geometryMgr);
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
    
    for (geometry* pGeometry : geometryMgr) {
        delete pGeometry;
    }
    geometryMgr.clear();
    
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
geometryList& sceneManager::getGeometryList() {
    return geometryMgr;
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
const geometryList& sceneManager::getGeometryList() const {
    return geometryMgr;
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
geometry* sceneManager::getGeometry(unsigned index) const {
    LS_DEBUG_ASSERT(index < geometryMgr.size());
    return geometryMgr[index];
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
void sceneManager::eraseGeometry(unsigned index) {
    geometry* pGeometry = geometryMgr[index];
    delete pGeometry;
    geometryMgr.erase(geometryMgr.begin()+index);
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
unsigned sceneManager::getNumGeometries() const {
    return geometryMgr.size();
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
unsigned sceneManager::manageGeometry(geometry* const pGeometry) {
    if (pGeometry != nullptr && this->containsGeometry(pGeometry) == false) {
        const unsigned index = pGeometry->getId();
        geometryMgr.push_back(pGeometry);
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
geometry* sceneManager::unManageGeometry(unsigned index) {
    LS_DEBUG_ASSERT(index < geometryMgr.size());
    geometry* const pGeometry = geometryMgr[index];
    geometryMgr.erase(geometryMgr.begin() + index);
    return pGeometry;
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
bool sceneManager::containsGeometry(const geometry* const pGeometry) const {
    if (pGeometry == nullptr) {
        return false;
    }
    else {
        geometryList::const_iterator iter = geometryMgr.begin();
        while (iter != geometryMgr.end()) {
            if (pGeometry->getId() == (*iter)->getId()) {
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
