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
#include "text.h"

/*
 * MeshLoader Move Constructor
 */
meshResource::meshResource(meshResource&& ml) :
    resource{},
    
    numMeshes{ml.numMeshes},
    
    numVertices{ml.numVertices},
    vertices{ml.vertices}
{
    resource::pData = ml.pData;
    ml.pData = nullptr;
    
    resource::dataSize = ml.dataSize;
    ml.dataSize = 0;
    
    ml.numMeshes = 0;
    
    ml.numVertices = nullptr;
    ml.vertices = nullptr;
}

/*
 * Mesh Loader move operator
 */
meshResource& meshResource::operator=(meshResource&& ml) {
    resource::pData = ml.pData;
    ml.pData = nullptr;
    
    resource::dataSize = ml.dataSize;
    ml.dataSize = 0;
    
    numMeshes = ml.numMeshes;
    ml.numMeshes = 0;
    
    numVertices = ml.numVertices;
    ml.numVertices = nullptr;
    
    vertices = ml.vertices;
    ml.vertices = nullptr;
    
    return *this;
}

/*
 * MeshLoader Destructor
 */
void meshResource::unload() {
    resource::pData = nullptr;
    resource::dataSize = 0;
    
    for (unsigned i = 0; i < numMeshes; ++i) {
        for (unsigned vertIter = 0; vertIter < numVertices[i]; ++vertIter) {
            delete [] vertices[vertIter];
        }
    }
    
    numMeshes = 0;
    
    delete [] numVertices;
    numVertices = nullptr;
    
    delete [] vertices;
    vertices = nullptr;
}

/*
 * Initialize the arrays that will be used to contain the mesh data.
 */
bool meshResource::initArrays(unsigned meshCount) {
    unload();
    
    numMeshes   = meshCount;
    numVertices = new(std::nothrow) unsigned[numMeshes];
    vertices    = new(std::nothrow) vertex* [numMeshes];
    
    if (numVertices == nullptr || vertices == nullptr) {
        LOG_ERR("Unable to allocate memory for ", numMeshes, " meshes.");
        unload();
        return false;
    }
    
    for (unsigned i = 0; i < meshCount; ++i) {
        numVertices[i] = 0;
        vertices[i] = nullptr;
    }
    
    return true;
}

/*
 * Initialize a mesh at a position
 */
bool meshResource::initMeshAt(unsigned meshIndex, unsigned vertCount) {
    if (meshIndex >= numMeshes) {
        return false;
    }
    
    if (vertices != nullptr && vertices[meshIndex] != nullptr) {
        resource::dataSize -= sizeof(vertex) * numVertices[meshIndex];
    }
    
    // clear all preexisting memory first
    auto clearVerts = [&]()->void {
        vertices[meshIndex] = 0;
        delete [] vertices[meshIndex];
        vertices[meshIndex] = nullptr;
    };
    
    clearVerts();
    
    vertices[meshIndex] = new(std::nothrow) vertex[vertCount];

    if (vertices[meshIndex] == nullptr) {
        LOG_ERR("Unable to allocate memory for the vertices used by mesh ", meshIndex, ".\n");
        clearVerts();
        return false;
    }
    else {
        numVertices[meshIndex] = vertCount;
        resource::pData = reinterpret_cast<char*>(vertices[meshIndex]);
        resource::dataSize += sizeof(vertex) * (vertCount);
    }
    
    return true;
}

/**
 * Load a set of meshes from a file
 * TODO
 */
bool meshResource::loadFile(const char* filename) {
    (void)filename;
    return false;
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
    
    if (!initArrays(1)) {
        LOG_ERR("An error occurred while initializing an array of meshes.\n");
        return false;
    }
    
    if (!initMeshAt(0, numPoints)) {
        LOG_ERR("An error occurred while initializing a mesh.\n");
        return false;
    }
    
    for (unsigned i = 0; i < numPoints; ++i) {
        const float theta = HL_TWO_PI * ((float)i / (float)numPoints);
        const float bc = std::cos(theta);
        const float bs = std::sin(theta);
        
        LOG_MSG("Loaded pont ", bc, ' ', bs, '.');
            
        vertices[0][i].pos = math::vec3{bs, bc, 0.f};
        vertices[0][i].uv = math::vec2{(bs+1.f)*0.5f, (bc+1.f)*0.5f};
        vertices[0][i].norm = math::vec3{0.f, 0.f, 1.f};
    }
    
    LOG_MSG("Successfully loaded a ", numPoints, "-sided polygon.\n");
    return true;
}

/*
 * load a convex polygon
 */
bool meshResource::loadTriangle() {
    LOG_MSG("Attempting to load a triangle.");
    
    if (!initArrays(1)) {
        LOG_ERR("An error occurred while initializing an array of meshes.\n");
        return false;
    }
    
    if (!initMeshAt(0, 3)) {
        LOG_ERR("An error occurred while initializing a triangle.\n");
        return false;
    }
    
    for (unsigned i = 0; i < 3; ++i) {
        const float theta = HL_TWO_PI * ((float)i / 3.f);
        const float bc = std::cos(theta);
        const float bs = std::sin(theta);
        vertex* const pVert = &vertices[0][i];
            
        pVert->pos = math::vec3{bs, bc, 0.f};
        pVert->uv = math::vec2{(bs+1.f)*0.5f, (bc+1.f)*0.5f};
        pVert->norm = math::vec3{0.f, 0.f, 1.f};
        
        LOG_MSG("Loaded pont ", i, '.');
    }
    
    LOG_MSG("Successfully loaded a triangle.\n");
    
    return true;
}

bool meshResource::loadText(const textureAtlas& ta, const std::string& str) {
    LOG_MSG("Attempting to load text.");
    
    if (!initArrays(1)) {
        LOG_ERR("An error occurred while initializing an array of meshes.\n");
        return false;
    }
    
    const int numChars = getDrawableCharCount(str.c_str());
    
    if (!initMeshAt(0, numChars*text_properties::VERTICES_PER_GLYPH)) {
        LOG_ERR("An error occurred while initializing text.\n");
        return false;
    }
    
    // Attempt to get a pointer to an unsynchronized memory buffer
    vertex* pData = &vertices[0][0];
    
    // Get pointers to the buffer data that will be filled with quads
    const atlasEntry* const pGlyphs = ta.getEntries();
    // The y-origin was found using a lot of testing. This was for resolution independence
    float yPos = -((pGlyphs['\n'].bearing[1]*2.f)+pGlyphs['\n'].bearing[1]-pGlyphs['\n'].size[1]);
    float xPos = 0.f;
    
    for (unsigned i = 0; str[i]; ++i) {
        const unsigned currChar = (unsigned)str[i];
        const atlasEntry& rGlyph = pGlyphs[currChar];
        const float vertHang = (rGlyph.bearing[1]-rGlyph.size[1]);
        
        if (currChar == '\n') {
            yPos -= (rGlyph.bearing[1]*2.f)+vertHang; // formula found through trial and error
            xPos = 0.f;
        }
        else if (currChar == '\v') {
            yPos -= ((rGlyph.bearing[1]*2.f)+vertHang)*text_properties::SPACES_PER_TAB;
            xPos = 0.f;
        }
        else if (currChar == '\r') {
            xPos = 0.f;
        }
        else if (currChar == ' ') {
            xPos += rGlyph.advance[0];
        }
        else if (currChar == '\t') {
            xPos += rGlyph.advance[0]*text_properties::SPACES_PER_TAB;
        }
        else {
            // 0--------2,3
            // |     /  |
            // |   /    |
            // | /      |
            // 1,4------5
            const float yOffset = yPos+vertHang;
            const float xOffset = xPos+rGlyph.bearing[0];
            xPos += rGlyph.advance[0];
            
            // 1st triangle
            pData->pos = {xOffset, yOffset+rGlyph.size[1], 0.f};
            pData->uv = {rGlyph.uv[0][0], rGlyph.uv[0][1]};
            pData->norm = {0.f, 0.f, 1.f};
            ++pData;
            
            pData->pos = {xOffset, yOffset, 0.f};
            pData->uv = {rGlyph.uv[0][0], rGlyph.uv[1][1]};
            pData->norm = {0.f, 0.f, 1.f};
            ++pData;
            
            pData->pos = {xOffset+rGlyph.size[0], yOffset+rGlyph.size[1], 0.f};
            pData->uv = {rGlyph.uv[1][0], rGlyph.uv[0][1]};
            pData->norm = {0.f, 0.f, 1.f};
            ++pData;
            
            // 2nd triangle
            pData->pos = {xOffset+rGlyph.size[0], yOffset+rGlyph.size[1], 0.f};
            pData->uv = {rGlyph.uv[1][0], rGlyph.uv[0][1]};
            pData->norm = {0.f, 0.f, 1.f};
            ++pData;
            
            pData->pos = {xOffset+rGlyph.size[0],yOffset, 0.f};
            pData->uv = {rGlyph.uv[1][0], rGlyph.uv[1][1]};
            pData->norm = {0.f, 0.f, 1.f};
            ++pData;
            
            pData->pos = {xOffset, yOffset, 0.f};
            pData->uv = {rGlyph.uv[0][0], rGlyph.uv[1][1]};
            pData->norm = {0.f, 0.f, 1.f};
            ++pData;
        }
    }
    
    numVertices[0] = numChars*VERTICES_PER_GLYPH;
    
    return true;
}
