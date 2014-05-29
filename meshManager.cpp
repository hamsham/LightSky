/* 
 * File:   meshManager.cpp
 * Author: miles
 * 
 * Created on May 26, 2014, 11:23 AM
 */

#include <utility>
#include "meshManager.h"

// TODO: Implement a way of notifying the scene manager that the meshManager
// node has been moved.
meshManager::meshManager() :
    vboMgr{}
{}

// TODO: Implement a way of notifying the scene manager that the meshManager
// node has been moved.
meshManager::meshManager(meshManager&& mm) :
    vboMgr{std::move(mm.vboMgr)}
{}

meshManager::~meshManager() {
}

// TODO: Implement a way of notifying the scene manager that the meshManager
// node has been moved.
meshManager& meshManager::operator=(meshManager&& mm) {
    vboMgr = std::move(mm.vboMgr);
    return *this;
}
