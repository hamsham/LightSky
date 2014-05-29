/* 
 * File:   textureManager.cpp
 * Author: miles
 * 
 * Created on May 26, 2014, 11:23 AM
 */

#include <utility>
#include "textureManager.h"

// TODO: Implement a way of notifying the scene manager that the textureManager
// node has been moved.
textureManager::textureManager() :
    texMgr{}
{}

// TODO: Implement a way of notifying the scene manager that the textureManager
// node has been moved.
textureManager::textureManager(textureManager&& mm) :
    texMgr{std::move(mm.texMgr)}
{}

textureManager::~textureManager() {
}

// TODO: Implement a way of notifying the scene manager that the textureManager
// node has been moved.
textureManager& textureManager::operator=(textureManager&& mm) {
    texMgr = std::move(mm.texMgr);
    return *this;
}

