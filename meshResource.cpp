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
int getDrawableCharCount(const char* const str) {
    int charCount = 0;
    
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
    pVertices{ml.pVertices}
{
    resource::pData = ml.pData;
    ml.pData = nullptr;
    
    resource::dataSize = ml.dataSize;
    ml.dataSize = 0;
    ml.numVertices = 0;
    ml.pVertices = nullptr;
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
        
        LOG_MSG("\tLoaded pont {", bc, ',', bs, "}.");
    }
    
    LOG_MSG("\tSuccessfully loaded a ", numPoints, "-sided polygon.\n");
    return true;
}

/*
 * Load the polygons required to create a renderable string of characters.
 */
bool meshResource::loadText(const textureAtlas& ta, const std::string& str) {
    LOG_MSG("Attempting to load a text mesh.");
    
    // deternime the number of non-whitespace characters
    const int numChars = getDrawableCharCount(str.c_str());
    
    if (!initVertices(numChars*text_properties::VERTICES_PER_GLYPH)) {
        LOG_ERR("\tAn error occurred while initializing a text mesh.\n");
        return false;
    }
    
    // Attempt to get a pointer to an unsynchronized memory buffer
    vertex* pVerts = pVertices;
    
    // Get pointers to the buffer data that will be filled with quads
    const atlasEntry* const pGlyphs = ta.getEntries();
    // The y-origin was found using a lot of testing. This was for resolution independence
    float yPos = -((pGlyphs['\n'].bearing[1]*2.f)+pGlyphs['\n'].bearing[1]-pGlyphs['\n'].size[1]);
    float xPos = 0.f;
    
    for (unsigned i = 0; i < str.size(); ++i) {
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
            pVerts->pos = {xOffset, yOffset+rGlyph.size[1], 0.f};
            pVerts->uv = {rGlyph.uv[0][0], rGlyph.uv[0][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
            
            pVerts->pos = {xOffset, yOffset, 0.f};
            pVerts->uv = {rGlyph.uv[0][0], rGlyph.uv[1][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
            
            pVerts->pos = {xOffset+rGlyph.size[0], yOffset+rGlyph.size[1], 0.f};
            pVerts->uv = {rGlyph.uv[1][0], rGlyph.uv[0][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
            
            // 2nd triangle
            pVerts->pos = {xOffset+rGlyph.size[0], yOffset+rGlyph.size[1], 0.f};
            pVerts->uv = {rGlyph.uv[1][0], rGlyph.uv[0][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
            
            pVerts->pos = {xOffset, yOffset, 0.f};
            pVerts->uv = {rGlyph.uv[0][0], rGlyph.uv[1][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
            
            pVerts->pos = {xOffset+rGlyph.size[0],yOffset, 0.f};
            pVerts->uv = {rGlyph.uv[1][0], rGlyph.uv[1][1]};
            pVerts->norm = {0.f, 0.f, 1.f};
            ++pVerts;
        }
    }
    
    LOG_MSG("\tSuccessfully loaded a text mesh.\n");
    
    return true;
}
