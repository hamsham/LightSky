/* 
 * File:   meshManager.cpp
 * Author: miles
 * 
 * Created on May 26, 2014, 11:23 AM
 */

#include <utility>
#include "meshManager.h"

meshManager::meshManager() :
    manager{}
{}

meshManager::meshManager(meshManager&& mm) :
    manager{std::move(mm)}
{}

meshManager::~meshManager() {
}

meshManager& meshManager::operator=(meshManager&& mm) {
    manager::operator=(std::move(mm));
    return *this;
}
