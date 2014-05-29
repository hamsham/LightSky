/* 
 * File:   sceneManager.cpp
 * Author: miles
 * 
 * Created on May 26, 2014, 11:22 AM
 */

#include <utility>
#include "sceneManager.h"

sceneManager::sceneManager() :
    texMgr{},
    meshMgr{}
{}

sceneManager::sceneManager(sceneManager&& sm) :
    texMgr{std::move(sm.texMgr)},
    meshMgr{std::move(sm.meshMgr)}
{}

sceneManager::~sceneManager() {
}

sceneManager& sceneManager::operator =(sceneManager&& sm) {
    texMgr = std::move(sm.texMgr);
    meshMgr = std::move(sm.meshMgr);
    
    return *this;
}

