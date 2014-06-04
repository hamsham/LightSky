/* 
 * File:   meshResource.cpp
 * Author: miles
 * 
 * Created on April 2, 2014, 9:04 PM
 */

#include <functional>
#include <utility>
#include "mesh.h"
#include "geometry.h"
#include "meshResource.h"

/**
 * Utility function to get all of the non-whitespace characters in a string
 */
unsigned getDrawableCharCount(const char* const str) {
    unsigned charCount = 0;
    
    for(unsigned i = 0; str[i]; ++i) {
        switch(str[i]) {
            case '\n':
            case '\v':
            case '\f':
            case '\r':
            case '\t':
            case ' ': continue;
            default: ++charCount;
        }
    }
    return charCount;
}


/*
 * MeshLoader Move Constructor
 */
meshResource::meshResource(meshResource&& ml) :
    resource{},
    numVertices{ml.numVertices},
    pVertices{ml.pVertices},
    resultDrawMode{ml.resultDrawMode}
{
    resource::pData = ml.pData;
    ml.pData = nullptr;
    
    resource::dataSize = ml.dataSize;
    ml.dataSize = 0;
    ml.numVertices = 0;
    ml.pVertices = nullptr;
    ml.resultDrawMode = draw_mode::DEFAULT_DRAW_MODE;
}

/*
 * Mesh Loader move operator
 */
meshResource& meshResource::operator=(meshResource&& ml) {
    resource::pData = ml.pData;
    ml.pData = nullptr;
    
    resource::dataSize = ml.dataSize;
    ml.dataSize = 0;
    
    numVertices = ml.numVertices;
    ml.numVertices = 0;
    
    pVertices = ml.pVertices;
    ml.pVertices = nullptr;
    
    resultDrawMode = ml.resultDrawMode;
    ml.resultDrawMode = draw_mode::DEFAULT_DRAW_MODE;
    
    return *this;
}

/*
 * MeshLoader Destructor
 */
void meshResource::unload() {
    resource::pData = nullptr;
    resource::dataSize = 0;
    
    numVertices = 0;
    
    delete [] pVertices;
    pVertices = nullptr;
}

/*
 * Initialize the arrays that will be used to contain the mesh data.
 */
bool meshResource::initVertices(unsigned vertCount) {
    unload();
    
    pVertices = new(std::nothrow) vertex [vertCount];
    
    if (pVertices == nullptr) {
        LOG_ERR("\tUnable to allocate memory for ", vertCount, " vertices.");
        unload();
        return false;
    }
    else {
        resource::dataSize = sizeof(vertex) * vertCount;
        resource::pData = reinterpret_cast<char*>(pVertices);
        LOG_MSG("\tSuccessfully allocated a ", resource::dataSize, "-byte vertex buffer.");
        numVertices = vertCount;
    }
    
    return true;
}

/**
 * Load a set of meshes from a file
 * TODO
 */
bool meshResource::loadFile(const char* filename) {
    (void)filename;
    unload();
    return false;
}

/*
 * Load a square
 */
bool meshResource::loadQuad() {
    LOG_MSG("Attempting to load a quad mesh.");
    
    if (!initVertices(4)) {
        LOG_ERR("\tAn error occurred while initializing a quad mesh.\n");
        return false;
    }
    
    pVertices[0].pos = math::vec3{1.f, 1.f, 0.f};
    pVertices[0].uv = math::vec2{1.f, 1.f};
    pVertices[0].norm = math::vec3{0.f, 0.f, 1.f};
    
    pVertices[1].pos = math::vec3{-1.f, 1.f, 0.f};
    pVertices[1].uv = math::vec2{0.f, 1.f};
    pVertices[1].norm = math::vec3{0.f, 0.f, 1.f};
    
    pVertices[2].pos = math::vec3{-1.f, -1.f, 0.f};
    pVertices[2].uv = math::vec2{0.f, 0.f};
    pVertices[2].norm = math::vec3{0.f, 0.f, 1.f};
    
    pVertices[3].pos = math::vec3{1.f, -1.f, 0.f};
    pVertices[3].uv = math::vec2{1.f, 0.f};
    pVertices[3].norm = math::vec3{0.f, 0.f, 1.f};
    
    LOG_MSG("\tSuccessfully loaded a quad mesh.\n");
    resultDrawMode = draw_mode::LS_TRIANGLE_FAN;
    return true;
}

/*
 * Load a primitive
 */
bool meshResource::loadPolygon(unsigned numPoints) {
    // make sure there are enough points for a minimal pyramid
    if (numPoints < 3) {
        numPoints = 3;
    }
    
    LOG_MSG("Attempting to load a ", numPoints, "-sided polygon.");
    
    if (!initVertices(numPoints)) {
        LOG_ERR("\tAn error occurred while initializing a ", numPoints, "-sided polygon.\n");
        return false;
    }
    
    for (unsigned i = 0; i < numPoints; ++i) {
        const float theta = -HL_TWO_PI * ((float)i / (float)numPoints);
        const float bc = std::cos(theta);
        const float bs = std::sin(theta);
        vertex* const pVert = pVertices+i;
        pVert->pos = math::vec3{bs, bc, 0.f};
        pVert->uv = math::vec2{(bs*0.5f)+0.5f, (bc*0.5f)+0.5f};
        pVert->norm = math::vec3{0.f, 0.f, 1.f};
    }
    
    LOG_MSG("\tSuccessfully loaded a ", numPoints, "-sided polygon.\n");
    resultDrawMode = draw_mode::LS_TRIANGLE_FAN;
    return true;
}
