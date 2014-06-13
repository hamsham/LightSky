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


/*
 * MeshLoader Move Constructor
 */
meshResource::meshResource(meshResource&& ml) :
    resource{},
    numVertices{ml.numVertices},
    pVertices{ml.pVertices},
    resultDrawMode{ml.resultDrawMode},
    meshBounds{std::move(ml.meshBounds)}
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
    
    meshBounds = std::move(ml.meshBounds);
    
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
    
    resultDrawMode = draw_mode::DEFAULT_DRAW_MODE;
    
    meshBounds.resetSize();
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
    
    meshBounds.setTopRearRight(math::vec3{1.f, 1.f, HL_EPSILON});
    meshBounds.setBotFrontLeft(math::vec3{-1.f, -1.f, -HL_EPSILON});
    
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
        
        meshBounds.compareAndUpdate(pVert->pos);
    }
    
    LOG_MSG("\tSuccessfully loaded a ", numPoints, "-sided polygon.\n");
    resultDrawMode = draw_mode::LS_TRIANGLE_FAN;
    return true;
}

/*
 * Load a cube
 */
bool meshResource::loadCube() {
    LOG_MSG("Attempting to load a cube mesh.");
    
    if (!initVertices(26)) {
        LOG_ERR("\tAn error occurred while initializing a cube mesh.\n");
        return false;
    }

    /*
     * POSITIONS
     */
    // front face
    pVertices[0].pos = math::vec3{-1.f, -1.f, 1.f};
    pVertices[1].pos = math::vec3{1.f, -1.f, 1.f};
    pVertices[2].pos = math::vec3{-1.f, 1.f, 1.f};
    pVertices[3].pos = math::vec3{1.f, 1.f, 1.f};

    // right
    pVertices[4].pos = math::vec3{1.f, 1.f, 1.f};
    pVertices[5].pos = math::vec3{1.f, -1.f, 1.f};
    pVertices[6].pos = math::vec3{1.f, 1.f, -1.f};
    pVertices[7].pos = math::vec3{1.f, -1.f, -1.f};

    // back face
    pVertices[8].pos = math::vec3{1.f, -1.f, -1.f};
    pVertices[9].pos = math::vec3{-1.f, -1.f, -1.f};
    pVertices[10].pos = math::vec3{1.f, 1.f, -1.f};
    pVertices[11].pos = math::vec3{-1.f, 1.f, -1.f};

    // left
    pVertices[12].pos = math::vec3{-1.f, 1.f, -1.f};
    pVertices[13].pos = math::vec3{-1.f, -1.f, -1.f};
    pVertices[14].pos = math::vec3{-1.f, 1.f, 1.f};
    pVertices[15].pos = math::vec3{-1.f, -1.f, 1.f};

    // bottom
    pVertices[16].pos = math::vec3{-1.f, -1.f, 1.f};
    pVertices[17].pos = math::vec3{-1.f, -1.f, -1.f};
    pVertices[18].pos = math::vec3{1.f, -1.f, 1.f};
    pVertices[19].pos = math::vec3{1.f, -1.f, -1.f};

    // top
    pVertices[20].pos = math::vec3{1.f, -1.f, -1.f};
    pVertices[21].pos = math::vec3{-1.f, 1.f, 1.f};
    pVertices[22].pos = math::vec3{-1.f, 1.f, 1.f};
    pVertices[23].pos = math::vec3{1.f, 1.f, 1.f};
    pVertices[24].pos = math::vec3{-1.f, 1.f, -1.f};
    pVertices[25].pos = math::vec3{1.f, 1.f, -1.f};

    /*
     *  UV
     */
    pVertices[0].uv = math::vec2{0.f, 0.f};
    pVertices[1].uv = math::vec2{1.f, 0.f};
    pVertices[2].uv = math::vec2{0.f, 1.f};
    pVertices[3].uv = math::vec2{1.f, 1.f};

    pVertices[4].uv = math::vec2{0.f, 1.f};
    pVertices[5].uv = math::vec2{0.f, 0.f};
    pVertices[6].uv = math::vec2{1.f, 1.f};
    pVertices[7].uv = math::vec2{1.f, 0.f};

    pVertices[8].uv = math::vec2{0.f, 0.f};
    pVertices[9].uv = math::vec2{1.f, 0.f};
    pVertices[10].uv = math::vec2{0.f, 1.f};
    pVertices[11].uv = math::vec2{1.f, 1.f};

    pVertices[12].uv = math::vec2{0.f, 1.f};
    pVertices[13].uv = math::vec2{0.f, 0.f};
    pVertices[14].uv = math::vec2{1.f, 1.f};
    pVertices[15].uv = math::vec2{1.f, 0.f};

    pVertices[16].uv = math::vec2{0.f, 1.f};
    pVertices[17].uv = math::vec2{0.f, 0.f};
    pVertices[18].uv = math::vec2{1.f, 1.f};
    pVertices[19].uv = math::vec2{1.f, 0.f};

    pVertices[20].uv = math::vec2{1.f, 0.f};
    pVertices[21].uv = math::vec2{0.f, 0.f};
    pVertices[22].uv = math::vec2{0.f, 0.f};
    pVertices[23].uv = math::vec2{1.f, 0.f};
    pVertices[24].uv = math::vec2{0.f, 1.f};
    pVertices[25].uv = math::vec2{1.f, 1.f};

    /*
     * NORMALS
     */
    pVertices[0].norm =
        pVertices[1].norm =
            pVertices[2].norm =
                pVertices[3].norm = math::vec3{0.f, 0.f, 1.f};

    pVertices[4].norm =
        pVertices[5].norm =
            pVertices[6].norm =
                pVertices[7].norm = math::vec3{1.f, 0.f, 0.f};

    pVertices[8].norm =
        pVertices[9].norm =
            pVertices[10].norm =
                pVertices[11].norm = math::vec3{0.f, 0.f, -1.f};

    pVertices[12].norm =
        pVertices[13].norm =
            pVertices[14].norm =
                pVertices[15].norm = math::vec3{-1.f, 0.f, 0.f};

    pVertices[16].norm =
        pVertices[17].norm =
            pVertices[18].norm =
                pVertices[19].norm = math::vec3{0.f, -1.f, 0.f};

    pVertices[20].norm =
        pVertices[21].norm = math::vec3{-1.f, 0.f, 0.f};
    
    pVertices[22].norm =
        pVertices[23].norm =
            pVertices[24].norm =
                pVertices[25].norm = math::vec3{0.f, 1.f, 0.f};
    
    meshBounds.setTopRearRight(math::vec3{1.f, 1.f, 1.f});
    meshBounds.setBotFrontLeft(math::vec3{-1.f, -1.f, -1.f});
    
    LOG_MSG("\tSuccessfully loaded a cube mesh.\n");
    resultDrawMode = draw_mode::LS_TRIANGLE_STRIP;
    return true;
}

/*
 * Load a cylinder
 */
bool meshResource::loadCylinder(unsigned numSides) {
    // make sure there are enough points for a minimal cylinder
    if (numSides < 2) {
        numSides = 2;
    }
    
    LOG_MSG("Attempting to load a ", numSides, "-sided cylinder.");
    
    if (!initVertices(numSides*12)) {
        LOG_ERR("\tAn error occurred while initializing a ", numSides, "-sided cylinder.\n");
        return false;
    }
    
    int iNumSides = (int)numSides;
    vertex* pCapVert = pVertices;
    vertex* pSideVert = pVertices+(numSides*6);
        
    // Make the cylinder caps using the "makePolygon()" algorithm
    for (int i = -iNumSides; i < iNumSides; ++i) {
        const float topBot  = (i < 0) ? 1.f : -1.f;
        
        const float theta1  = HL_TWO_PI * ((float)i / (float)iNumSides) * topBot;
        const float bc1     = std::cos(theta1);
        const float bs1     = std::sin(theta1);

        const float theta2  = HL_TWO_PI * ((float)(i-1) / (float)iNumSides) * topBot;
        const float bc2     = std::cos(theta2);
        const float bs2     = std::sin(theta2);
        
        // center
        pCapVert->pos       = math::vec3{0.f, topBot, 0.f};
        pCapVert->uv        = math::vec2{0.5f, 0.5f};
        pCapVert->norm      = math::vec3{0.f, topBot, 0.f};
        meshBounds.compareAndUpdate(pCapVert->pos);
        ++pCapVert;

        // cap, first triangle leg
        pCapVert->pos       = math::vec3{bc1, topBot, bs1};
        pCapVert->uv        = math::vec2{(bs1*0.5f)+0.5f, (bc1*0.5f)+0.5f};
        pCapVert->norm      = math::vec3{0.f, topBot, 0.f};
        meshBounds.compareAndUpdate(pCapVert->pos);
        ++pCapVert;

        // cap, second triangle leg
        pCapVert->pos       = math::vec3{bc2, topBot, bs2};
        pCapVert->uv        = math::vec2{(bs2*0.5f)+0.5f, (bc2*0.5f)+0.5f};
        pCapVert->norm      = math::vec3{0.f, topBot, 0.f};
        meshBounds.compareAndUpdate(pCapVert->pos);
        ++pCapVert;
        
        // Cylinder Side, apex
        pSideVert->pos      = math::vec3{bc1, -topBot, bs1};
        pSideVert->uv       = math::vec2{(bs1*0.5f)+0.5f, (bc1*0.5f)+0.5f};
        pSideVert->norm     = math::vec3{bc1, 0.f, bs1};
        meshBounds.compareAndUpdate(pSideVert->pos);
        ++pSideVert;
        
        // Cylinder Side, leg 1
        pSideVert->pos      = math::vec3{bc2, topBot, bs2};
        pSideVert->uv       = math::vec2{(bs2*0.5f)+0.5f, (bc2*0.5f)+0.5f};
        pSideVert->norm     = math::vec3{bc2, 0.f, bs2};
        meshBounds.compareAndUpdate(pSideVert->pos);
        ++pSideVert;
        
        // Cylinder Side, leg 2
        pSideVert->pos      = math::vec3{bc1, topBot, bs1};
        pSideVert->uv       = math::vec2{(bs1*0.5f)+0.5f, (bc1*0.5f)+0.5f};
        pSideVert->norm     = math::vec3{bc1, 0.f, bs1};
        meshBounds.compareAndUpdate(pSideVert->pos);
        ++pSideVert;
    }
    
    
    LOG_MSG("\tSuccessfully loaded a ", numSides, "-sided cylinder.\n");
    resultDrawMode = draw_mode::LS_TRIANGLES;
    return true;
}

/*
 * Load a Cone
 */
bool meshResource::loadCone(unsigned numSides) {
    // make sure there are enough points for a minimal pyramid
    if (numSides < 2) {
        numSides = 2;
    }
    
    LOG_MSG("Attempting to load a ", numSides, "-sided cone.");
    
    if (!initVertices(numSides*6)) {
        LOG_ERR("\tAn error occurred while initializing a ", numSides, "-sided cone.\n");
        return false;
    }
    
    int iNumSides = (int)numSides;
    vertex* pCapVert = pVertices;
        
    // Make the cylinder caps using the "makePolygon()" algorithm
    for (int i = -iNumSides; i < iNumSides; ++i) {
        const float topBot  = (i < 0) ? 1.f : -1.f;
        
        // center
        {
            pCapVert->pos       = math::vec3{0.f, topBot, 0.f};
            pCapVert->uv        = math::vec2{0.5f, 0.5f};
            pCapVert->norm      = math::vec3{0.f, topBot, 0.f};
            meshBounds.compareAndUpdate(pCapVert->pos);
            ++pCapVert;
        }

        // cap, first triangle leg
        {
            const float theta1  = HL_TWO_PI * ((float)i / (float)iNumSides) * topBot;
            const float bc1     = std::cos(theta1);
            const float bs1     = std::sin(theta1);
            pCapVert->pos       = math::vec3{bc1, -1.f, bs1};
            pCapVert->uv        = math::vec2{(bs1*0.5f)+0.5f, (bc1*0.5f)+0.5f};
            pCapVert->norm      = i < 0
                                ? math::normalize(math::vec3{bc1, 1.f, bs1})
                                : math::vec3{0.f, topBot, 0.f};
            meshBounds.compareAndUpdate(pCapVert->pos);
            ++pCapVert;
        }

        // cap, second triangle leg
        {
            const float theta2  = HL_TWO_PI * ((float)(i-1) / (float)iNumSides) * topBot;
            const float bc2     = std::cos(theta2);
            const float bs2     = std::sin(theta2);
            pCapVert->pos       = math::vec3{bc2, -1.f, bs2};
            pCapVert->uv        = math::vec2{(bs2*0.5f)+0.5f, (bc2*0.5f)+0.5f};
            pCapVert->norm      = i < 0
                                ? math::normalize(math::vec3{bc2, 1.f, bs2})
                                : math::vec3{0.f, topBot, 0.f};
            meshBounds.compareAndUpdate(pCapVert->pos);
            ++pCapVert;
        }
    }
    
    LOG_MSG("\tSuccessfully loaded a ", numSides, "-sided cone.\n");
    resultDrawMode = draw_mode::LS_TRIANGLES;
    return true;
}

/*
 * Load a Sphere
 * 
 * I found this method on the website by Kevin Harris:
 * http://www.codesampler.com/oglsrc/oglsrc_8.htm#ogl_textured_sphere
 * 
 * This loading method was originally found here:
 * http://astronomy.swin.edu.au/~pbourke/opengl/sphere/
 */
bool meshResource::loadSphere(unsigned res) {
    // Only load an even number of vertices
    if (res % 2 == 1) {
        ++res;
    }
    
    // calculate the exact number of vertices to load
    unsigned totalVertCount = res*(res+1); // more trial and error
    
    LOG_MSG("Attempting to load a ", totalVertCount, "-point sphere (", res, "x).");
    
    if (!initVertices(totalVertCount)) {
        LOG_ERR("\tAn error occurred while initializing a ", totalVertCount, "-point sphere.\n");
        return false;
    }
    
    const int iNumSides = (int)res;
    const float fNumSides = (float)res;
    vertex* pVert = pVertices;

    for(int i = 0; i < iNumSides/2; ++i) {
        float theta1 = i * HL_TWO_PI / fNumSides - HL_PI_OVER_2;
        float theta2 = (i + 1) * HL_TWO_PI / fNumSides - HL_PI_OVER_2;
        
        for(int j = 0; j <= iNumSides; ++j) {
            const float theta3 = j * HL_TWO_PI / fNumSides;
            
            {
                const float ex  = HL_COS(theta2) * HL_SIN(theta3);
                const float ey  = HL_SIN(theta2);
                const float ez  = HL_COS(theta2) * HL_COS(theta3);
                pVert->pos      = math::vec3{ex, ey, ez};
                pVert->uv       = math::vec2{-(j/fNumSides) , 2.f*(i+1)/fNumSides};
                pVert->norm     = math::vec3{ex, ey, ez};
                ++pVert;
            }
            {
                const float ex  = HL_COS(theta1) * HL_SIN(theta3);
                const float ey  = HL_SIN(theta1);
                const float ez  = HL_COS(theta1) * HL_COS(theta3);
                pVert->pos      = math::vec3{ex, ey, ez};
                pVert->uv       = math::vec2{-(j/fNumSides), 2.f*i/fNumSides};
                pVert->norm     = math::vec3{ex, ey, ez};
                ++pVert;
            }
        }
    }
    
    LOG_MSG("\tSuccessfully loaded a ", totalVertCount, "-point sphere.\n");
    resultDrawMode = draw_mode::LS_TRIANGLE_STRIP;
    return true;
}
