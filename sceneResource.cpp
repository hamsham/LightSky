/* 
 * File:   sceneResource.cpp
 * Author: miles
 * 
 * Created on May 16, 2014, 9:57 PM
 */

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "sceneResource.h"

sceneResource::sceneResource(sceneResource&& sr) :
    numMeshes{sr.numMeshes}
{
    sr.numMeshes = 0;
}

sceneResource& sceneResource::operator =(sceneResource&& sr) {
    numMeshes = sr.numMeshes;
    sr.numMeshes = 0;
    
    return *this;
}

/*
 * Load a mesh from a file using ASSIMP
 */
bool sceneResource::loadFile(const char*) {
    return false;
}
