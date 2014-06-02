/* 
 * File:   sceneManager.cpp
 * Author: miles
 * 
 * Created on May 26, 2014, 11:22 AM
 */

#include <utility>
#include "mesh.h"
#include "texture.h"
#include "textureAtlas.h"
#include "sceneManager.h"

/*
 * Management implementations
 */
LS_DEFINE_CLASS_TYPE(manager, unsigned, mesh);
LS_DEFINE_CLASS_TYPE(manager, unsigned, texture);
LS_DEFINE_CLASS_TYPE(manager, unsigned, textureAtlas);

///////////////////////////////////////////////////////////////////////////////
// Scene Manager Class
///////////////////////////////////////////////////////////////////////////////
/*
 * Constructor
 */
sceneManager::sceneManager() :
    texMgr{},
    meshMgr{}
{}

/*
 * Move Constructor
 */
sceneManager::sceneManager(sceneManager&& sm) :
    texMgr{std::move(sm.texMgr)},
    meshMgr{std::move(sm.meshMgr)}
{}

/*
 * Destructor
 */
sceneManager::~sceneManager() {
    clear();
}

/*
 * Move Operator
 */
sceneManager& sceneManager::operator =(sceneManager&& sm) {
    texMgr = std::move(sm.texMgr);
    meshMgr = std::move(sm.meshMgr);
    
    return *this;
}

void sceneManager::clear() {
    texMgr.clear();
    meshMgr.clear();
}

