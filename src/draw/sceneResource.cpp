/* 
 * File:   draw/sceneResource.cpp
 * Author: Miles Lacey
 * 
 * Created on April 2, 2014, 9:04 PM
 */

#include <functional>
#include <utility>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

#include "lightsky/draw/transform.h"
#include "lightsky/draw/geometry.h"
#include "lightsky/draw/geometry_utils.h"
#include "lightsky/draw/sceneResource.h"

namespace {
/*-----------------------------------------------------------------------------
 * Assimp Import Flags & Enumerations
 *
 * These meshes were hand-selected through much trial & error. Do not touch
 * unless you want a swarm of bees hidden in your breakfast cereal box.
-----------------------------------------------------------------------------*/
enum : unsigned int {
    DEFAULT_IMPORT_FLAGS = 0
        | aiProcess_GenUVCoords
        | aiProcess_TransformUVCoords
        | aiProcess_Triangulate
        | aiProcess_GenSmoothNormals
        | aiProcess_OptimizeMeshes
        //| aiProcess_OptimizeGraph // This flag may collapse too many subnodes to be useful.
        | aiProcess_FindInstances
        | aiProcess_SortByPType
        | aiProcess_RemoveComponent
        | aiProcess_JoinIdenticalVertices
        | aiProcess_FindDegenerates
        | aiProcess_FindInvalidData
        | aiProcess_ValidateDataStructure
        | aiProcess_ImproveCacheLocality
        | 0
};

enum mesh_invalid_prim_t : int {
    INVALID_PRIM_IMPORT_FLAGS = 0
        | aiPrimitiveType_LINE
        | aiPrimitiveType_POINT
        | aiPrimitiveType_POLYGON
};

template <typename num_t>
ls::math::vec2_t<num_t> convertAssimpVector(const aiVector2t<num_t>& inVec) {
    return ls::math::vec2_t<num_t>{inVec.x, inVec.y};
}

template <typename num_t>
ls::math::vec3_t<num_t> convertAssimpVector(const aiVector3t<num_t>& inVec) {
    return ls::math::vec3_t<num_t>{inVec.x, inVec.z, -inVec.y};
}

template <typename num_t>
ls::math::quat_t<num_t> convertAssimpVector(const aiQuaterniont<num_t>& inQuat) {
    return ls::math::quat_t<num_t>{inQuat.x, inQuat.y, inQuat.z, inQuat.w};
}

template <typename num_t>
ls::math::mat3_t<num_t> convertAssimpMatrix(const aiMatrix3x3t<num_t>& inMat) {
    return ls::math::mat3_t<num_t>{
        inMat.a1, inMat.b1, inMat.c1,
        inMat.a2, inMat.b2, inMat.c2,
        inMat.a3, inMat.b3, inMat.c3, 
    };
}

template <typename num_t>
ls::math::mat4_t<num_t> convertAssimpMatrix(const aiMatrix4x4t<num_t>& inMat) {
    return ls::math::mat4_t<num_t>{
        inMat.a1, inMat.b1, inMat.c1, inMat.d1,
        inMat.a2, inMat.b2, inMat.c2, inMat.d2,
        inMat.a3, inMat.b3, inMat.c3, inMat.d3,
        inMat.a4, inMat.b4, inMat.c4, inMat.d4
    };
}
}

namespace ls {
namespace draw {

/*-------------------------------------
    Destructor
-------------------------------------*/
sceneResource::~sceneResource() {
}

/*-------------------------------------
    Constructor
-------------------------------------*/
sceneResource::sceneResource() {
}

/*-------------------------------------
    SceneResource Copy Constructor
-------------------------------------*/
sceneResource::sceneResource(const sceneResource& r) :
    resource{},
    resultDrawMode{r.resultDrawMode},
    vertexList{r.vertexList},
    indexList{r.indexList},
    nodeList{r.nodeList},
    meshList{r.meshList},
    cameraList{r.cameraList},
    textureSet{r.textureSet},
    totalBounds{r.totalBounds}
{
    this->pData = reinterpret_cast<char*>(vertexList.data());
    this->dataSize = r.dataSize;
}

/*-------------------------------------
    SceneResource Move Constructor
-------------------------------------*/
sceneResource::sceneResource(sceneResource&& r) :
    resource{},
    resultDrawMode{r.resultDrawMode},
    vertexList{std::move(r.vertexList)},
    indexList{std::move(r.indexList)},
    nodeList{std::move(r.nodeList)},
    meshList{std::move(r.meshList)},
    cameraList{std::move(r.cameraList)},
    textureSet{std::move(r.textureSet)},
    totalBounds{std::move(r.totalBounds)}
{
    this->pData = r.pData;
    r.pData = nullptr;
    
    this->dataSize = r.dataSize;
    r.dataSize = 0;
    
    r.resultDrawMode = draw_mode_t::DEFAULT;
}

/*-------------------------------------
    Mesh Loader copy operator
-------------------------------------*/
sceneResource& sceneResource::operator=(const sceneResource& r) {
    unload();
    
    resultDrawMode = r.resultDrawMode;
    
    vertexList = r.vertexList;
    indexList = r.indexList;
    nodeList = r.nodeList;
    meshList = r.meshList;
    cameraList = r.cameraList;
    textureSet = r.textureSet;
    totalBounds = r.totalBounds;
    
    this->pData = reinterpret_cast<char*>(vertexList.data());
    this->dataSize = r.dataSize;
    
    return *this;
}

/*-------------------------------------
    Mesh Loader move operator
-------------------------------------*/
sceneResource& sceneResource::operator=(sceneResource&& r) {
    unload();
    
    this->pData = r.pData;
    r.pData = nullptr;
    
    this->dataSize = r.dataSize;
    r.dataSize = 0;
    
    resultDrawMode = r.resultDrawMode;
    r.resultDrawMode = draw_mode_t::DEFAULT;
    
    vertexList = std::move(r.vertexList);
    
    indexList = std::move(r.indexList);
    
    nodeList = std::move(r.nodeList);
    
    meshList = std::move(r.meshList);
    
    cameraList = std::move(r.cameraList);
    
    textureSet = std::move(r.textureSet);
    
    totalBounds = std::move(r.totalBounds);
    
    return *this;
}

/*-------------------------------------
    SceneResource Destructor
-------------------------------------*/
void sceneResource::unload() {
    this->pData = nullptr;
    
    this->dataSize = 0;
    
    resultDrawMode = draw_mode_t::DEFAULT;
    
    vertexList.clear();
    
    indexList.clear();
    
    nodeList.clear();
    
    meshList.clear();
    
    cameraList.clear();
    
    textureSet.clear();
    
    totalBounds.resetSize();
}

/*-------------------------------------
    Initialize the arrays that will be used to contain the mesh data.
-------------------------------------*/
bool sceneResource::initVertices(unsigned vertCount, unsigned indexCount) {
    unload();
    
    // create the vertex buffer
    vertexList.resize(vertCount);
    vertexList.shrink_to_fit();
    
    // create the index buffer
    if (indexCount > 0) {
        indexList.resize(indexCount);
        indexList.shrink_to_fit();
    }
    
    this->dataSize
        = (sizeof(vertex) * vertCount)
        + (sizeof(draw_index_t) * indexCount);
    
    this->pData = reinterpret_cast<char*>(vertexList.data());

    LS_LOG_MSG(
        "\tSuccessfully allocated ", this->dataSize, " bytes for mesh data.",
        "\n\t\tVertices: ", vertCount,
        "\n\t\tIndices:  ", indexCount
    );
    
    return true;
}

/*-------------------------------------
    Create a node for generated primitives
-------------------------------------*/
sceneResource::resourceNode sceneResource::createPrimitiveNode(const char * const name) {
    resourceNode primNode;

    primNode.nodeParentId = 0;
    primNode.nodeMeshes.push_back(0);
    primNode.nodeName = name;
    primNode.nodeChildren.clear();
    primNode.nodeTransform = math::mat4{1.f};
    
    resourceMesh m;
    m.indices.first = 0;
    m.indices.count = vertexList.size();
    m.textureIndex = INVALID_SCENE_RESOURCE;
    meshList.push_back(m);

    return primNode;
}

/*-------------------------------------
    Load a square
-------------------------------------*/
bool sceneResource::loadQuad() {
    LS_LOG_MSG("Attempting to load a quad mesh.");
    
    if (!initVertices(4)) {
        LS_LOG_ERR("\tAn error occurred while initializing a quad mesh.\n");
        return false;
    }
    
    vertexList[0].pos = math::vec3{1.f, 1.f, 0.f};
    vertexList[0].uv = math::vec2{1.f, 1.f};
    vertexList[0].norm = math::vec3{0.f, 0.f, 1.f};
    
    vertexList[1].pos = math::vec3{-1.f, 1.f, 0.f};
    vertexList[1].uv = math::vec2{0.f, 1.f};
    vertexList[1].norm = math::vec3{0.f, 0.f, 1.f};
    
    vertexList[2].pos = math::vec3{-1.f, -1.f, 0.f};
    vertexList[2].uv = math::vec2{0.f, 0.f};
    vertexList[2].norm = math::vec3{0.f, 0.f, 1.f};
    
    vertexList[3].pos = math::vec3{1.f, -1.f, 0.f};
    vertexList[3].uv = math::vec2{1.f, 0.f};
    vertexList[3].norm = math::vec3{0.f, 0.f, 1.f};
    
    totalBounds.setTopRearRight(math::vec3{1.f, 1.f, LS_EPSILON});
    totalBounds.setBotFrontLeft(math::vec3{-1.f, -1.f, -LS_EPSILON});
    
    LS_LOG_MSG("\tSuccessfully loaded a quad mesh.\n");
    resultDrawMode = draw_mode_t::TRI_FAN;
    nodeList.emplace_back(createPrimitiveNode("Quad"));
    return true;
}

/*-------------------------------------
    Load a primitive
-------------------------------------*/
bool sceneResource::loadPolygon(unsigned numPoints) {
    // make sure there are enough points for a minimal pyramid
    if (numPoints < 3) {
        numPoints = 3;
    }
    
    LS_LOG_MSG("Attempting to load a ", numPoints, "-sided polygon.");
    
    if (!initVertices(numPoints)) {
        LS_LOG_ERR("\tAn error occurred while initializing a ", numPoints, "-sided polygon.\n");
        return false;
    }
    
    for (unsigned i = 0; i < numPoints; ++i) {
        const float theta = -LS_TWO_PI * ((float)i / (float)numPoints);
        const float bc = std::cos(theta);
        const float bs = std::sin(theta);
        vertex* const pVert = vertexList.data()+i;
        pVert->pos = math::vec3{bs, bc, 0.f};
        pVert->uv = math::vec2{(bs*0.5f)+0.5f, (bc*0.5f)+0.5f};
        pVert->norm = math::vec3{0.f, 0.f, 1.f};
        
        totalBounds.compareAndUpdate(pVert->pos);
    }
    
    LS_LOG_MSG("\tSuccessfully loaded a ", numPoints, "-sided polygon.\n");
    resultDrawMode = draw_mode_t::TRI_FAN;
    nodeList.emplace_back(createPrimitiveNode("Polygon"));
    return true;
}

/*-------------------------------------
    Load a cube
-------------------------------------*/
bool sceneResource::loadCube() {
    LS_LOG_MSG("Attempting to load a cube mesh.");
    
    if (!initVertices(26)) {
        LS_LOG_ERR("\tAn error occurred while initializing a cube mesh.\n");
        return false;
    }

    /*
     * POSITIONS
     */
    // front face
    vertexList[0].pos = math::vec3{-1.f, -1.f, 1.f};
    vertexList[1].pos = math::vec3{1.f, -1.f, 1.f};
    vertexList[2].pos = math::vec3{-1.f, 1.f, 1.f};
    vertexList[3].pos = math::vec3{1.f, 1.f, 1.f};

    // right
    vertexList[4].pos = math::vec3{1.f, 1.f, 1.f};
    vertexList[5].pos = math::vec3{1.f, -1.f, 1.f};
    vertexList[6].pos = math::vec3{1.f, 1.f, -1.f};
    vertexList[7].pos = math::vec3{1.f, -1.f, -1.f};

    // back face
    vertexList[8].pos = math::vec3{1.f, -1.f, -1.f};
    vertexList[9].pos = math::vec3{-1.f, -1.f, -1.f};
    vertexList[10].pos = math::vec3{1.f, 1.f, -1.f};
    vertexList[11].pos = math::vec3{-1.f, 1.f, -1.f};

    // left
    vertexList[12].pos = math::vec3{-1.f, 1.f, -1.f};
    vertexList[13].pos = math::vec3{-1.f, -1.f, -1.f};
    vertexList[14].pos = math::vec3{-1.f, 1.f, 1.f};
    vertexList[15].pos = math::vec3{-1.f, -1.f, 1.f};

    // bottom
    vertexList[16].pos = math::vec3{-1.f, -1.f, 1.f};
    vertexList[17].pos = math::vec3{-1.f, -1.f, -1.f};
    vertexList[18].pos = math::vec3{1.f, -1.f, 1.f};
    vertexList[19].pos = math::vec3{1.f, -1.f, -1.f};

    // top
    vertexList[20].pos = math::vec3{1.f, -1.f, -1.f};
    vertexList[21].pos = math::vec3{-1.f, 1.f, 1.f};
    vertexList[22].pos = math::vec3{-1.f, 1.f, 1.f};
    vertexList[23].pos = math::vec3{1.f, 1.f, 1.f};
    vertexList[24].pos = math::vec3{-1.f, 1.f, -1.f};
    vertexList[25].pos = math::vec3{1.f, 1.f, -1.f};

    /*
     *  UV
     */
    vertexList[0].uv = math::vec2{0.f, 0.f};
    vertexList[1].uv = math::vec2{1.f, 0.f};
    vertexList[2].uv = math::vec2{0.f, 1.f};
    vertexList[3].uv = math::vec2{1.f, 1.f};

    vertexList[4].uv = math::vec2{0.f, 1.f};
    vertexList[5].uv = math::vec2{0.f, 0.f};
    vertexList[6].uv = math::vec2{1.f, 1.f};
    vertexList[7].uv = math::vec2{1.f, 0.f};

    vertexList[8].uv = math::vec2{0.f, 0.f};
    vertexList[9].uv = math::vec2{1.f, 0.f};
    vertexList[10].uv = math::vec2{0.f, 1.f};
    vertexList[11].uv = math::vec2{1.f, 1.f};

    vertexList[12].uv = math::vec2{0.f, 1.f};
    vertexList[13].uv = math::vec2{0.f, 0.f};
    vertexList[14].uv = math::vec2{1.f, 1.f};
    vertexList[15].uv = math::vec2{1.f, 0.f};

    vertexList[16].uv = math::vec2{0.f, 1.f};
    vertexList[17].uv = math::vec2{0.f, 0.f};
    vertexList[18].uv = math::vec2{1.f, 1.f};
    vertexList[19].uv = math::vec2{1.f, 0.f};

    vertexList[20].uv = math::vec2{1.f, 0.f};
    vertexList[21].uv = math::vec2{0.f, 0.f};
    vertexList[22].uv = math::vec2{0.f, 0.f};
    vertexList[23].uv = math::vec2{1.f, 0.f};
    vertexList[24].uv = math::vec2{0.f, 1.f};
    vertexList[25].uv = math::vec2{1.f, 1.f};

    /*
     * NORMALS
     */
    vertexList[0].norm =
        vertexList[1].norm =
            vertexList[2].norm =
                vertexList[3].norm = math::vec3{0.f, 0.f, 1.f};

    vertexList[4].norm =
        vertexList[5].norm =
            vertexList[6].norm =
                vertexList[7].norm = math::vec3{1.f, 0.f, 0.f};

    vertexList[8].norm =
        vertexList[9].norm =
            vertexList[10].norm =
                vertexList[11].norm = math::vec3{0.f, 0.f, -1.f};

    vertexList[12].norm =
        vertexList[13].norm =
            vertexList[14].norm =
                vertexList[15].norm = math::vec3{-1.f, 0.f, 0.f};

    vertexList[16].norm =
        vertexList[17].norm =
            vertexList[18].norm =
                vertexList[19].norm = math::vec3{0.f, -1.f, 0.f};

    vertexList[20].norm =
        vertexList[21].norm = math::vec3{-1.f, 0.f, 0.f};
    
    vertexList[22].norm =
        vertexList[23].norm =
            vertexList[24].norm =
                vertexList[25].norm = math::vec3{0.f, 1.f, 0.f};
    
    totalBounds.setTopRearRight(math::vec3{1.f, 1.f, 1.f});
    totalBounds.setBotFrontLeft(math::vec3{-1.f, -1.f, -1.f});
    
    LS_LOG_MSG("\tSuccessfully loaded a cube mesh.\n");
    resultDrawMode = draw_mode_t::TRI_STRIP;
    nodeList.emplace_back(createPrimitiveNode("Cube"));
    return true;
}

/*-------------------------------------
    Load a cylinder
-------------------------------------*/
bool sceneResource::loadCylinder(unsigned numSides) {
    // make sure there are enough points for a minimal cylinder
    if (numSides < 2) {
        numSides = 2;
    }
    
    LS_LOG_MSG("Attempting to load a ", numSides, "-sided cylinder.");
    
    if (!initVertices(numSides*12)) {
        LS_LOG_ERR("\tAn error occurred while initializing a ", numSides, "-sided cylinder.\n");
        return false;
    }
    
    int iNumSides = (int)numSides;
    vertex* pCapVert = vertexList.data();
    vertex* pSideVert = vertexList.data()+(numSides*6);
        
    // Make the cylinder caps using the "makePolygon()" algorithm
    for (int i = -iNumSides; i < iNumSides; ++i) {
        const float topBot  = (i < 0) ? 1.f : -1.f;
        
        const float theta1  = LS_TWO_PI * ((float)i / (float)iNumSides) * topBot;
        const float bc1     = std::cos(theta1);
        const float bs1     = std::sin(theta1);

        const float theta2  = LS_TWO_PI * ((float)(i-1) / (float)iNumSides) * topBot;
        const float bc2     = std::cos(theta2);
        const float bs2     = std::sin(theta2);
        
        // center
        pCapVert->pos       = math::vec3{0.f, topBot, 0.f};
        pCapVert->uv        = math::vec2{0.5f, 0.5f};
        pCapVert->norm      = math::vec3{0.f, topBot, 0.f};
        totalBounds.compareAndUpdate(pCapVert->pos);
        ++pCapVert;

        // cap, first triangle leg
        pCapVert->pos       = math::vec3{bc1, topBot, bs1};
        pCapVert->uv        = math::vec2{(bs1*0.5f)+0.5f, (bc1*0.5f)+0.5f};
        pCapVert->norm      = math::vec3{0.f, topBot, 0.f};
        totalBounds.compareAndUpdate(pCapVert->pos);
        ++pCapVert;

        // cap, second triangle leg
        pCapVert->pos       = math::vec3{bc2, topBot, bs2};
        pCapVert->uv        = math::vec2{(bs2*0.5f)+0.5f, (bc2*0.5f)+0.5f};
        pCapVert->norm      = math::vec3{0.f, topBot, 0.f};
        totalBounds.compareAndUpdate(pCapVert->pos);
        ++pCapVert;
        
        // Cylinder Side, apex
        pSideVert->pos      = math::vec3{bc1, -topBot, bs1};
        pSideVert->uv       = math::vec2{(bs1*0.5f)+0.5f, (bc1*0.5f)+0.5f};
        pSideVert->norm     = math::vec3{bc1, 0.f, bs1};
        totalBounds.compareAndUpdate(pSideVert->pos);
        ++pSideVert;
        
        // Cylinder Side, leg 1
        pSideVert->pos      = math::vec3{bc2, topBot, bs2};
        pSideVert->uv       = math::vec2{(bs2*0.5f)+0.5f, (bc2*0.5f)+0.5f};
        pSideVert->norm     = math::vec3{bc2, 0.f, bs2};
        totalBounds.compareAndUpdate(pSideVert->pos);
        ++pSideVert;
        
        // Cylinder Side, leg 2
        pSideVert->pos      = math::vec3{bc1, topBot, bs1};
        pSideVert->uv       = math::vec2{(bs1*0.5f)+0.5f, (bc1*0.5f)+0.5f};
        pSideVert->norm     = math::vec3{bc1, 0.f, bs1};
        totalBounds.compareAndUpdate(pSideVert->pos);
        ++pSideVert;
    }
    
    
    LS_LOG_MSG("\tSuccessfully loaded a ", numSides, "-sided cylinder.\n");
    resultDrawMode = draw_mode_t::TRIS;
    nodeList.emplace_back(createPrimitiveNode("Cylinder"));
    return true;
}

/*-------------------------------------
    Load a Cone
-------------------------------------*/
bool sceneResource::loadCone(unsigned numSides) {
    // make sure there are enough points for a minimal pyramid
    if (numSides < 2) {
        numSides = 2;
    }
    
    LS_LOG_MSG("Attempting to load a ", numSides, "-sided cone.");
    
    if (!initVertices(numSides*6)) {
        LS_LOG_ERR("\tAn error occurred while initializing a ", numSides, "-sided cone.\n");
        return false;
    }
    
    int iNumSides = (int)numSides;
    vertex* pCapVert = vertexList.data();
        
    // Make the cylinder caps using the "makePolygon()" algorithm
    for (int i = -iNumSides; i < iNumSides; ++i) {
        const float topBot  = (i < 0) ? 1.f : -1.f;
        
        // center
        {
            pCapVert->pos       = math::vec3{0.f, topBot, 0.f};
            pCapVert->uv        = math::vec2{0.5f, 0.5f};
            pCapVert->norm      = math::vec3{0.f, topBot, 0.f};
            totalBounds.compareAndUpdate(pCapVert->pos);
            ++pCapVert;
        }

        // cap, first triangle leg
        {
            const float theta1  = LS_TWO_PI * ((float)i / (float)iNumSides) * topBot;
            const float bc1     = std::cos(theta1);
            const float bs1     = std::sin(theta1);
            pCapVert->pos       = math::vec3{bc1, -1.f, bs1};
            pCapVert->uv        = math::vec2{(bs1*0.5f)+0.5f, (bc1*0.5f)+0.5f};
            pCapVert->norm      = i < 0
                                ? math::normalize(math::vec3{bc1, 1.f, bs1})
                                : math::vec3{0.f, topBot, 0.f};
            totalBounds.compareAndUpdate(pCapVert->pos);
            ++pCapVert;
        }

        // cap, second triangle leg
        {
            const float theta2  = LS_TWO_PI * ((float)(i-1) / (float)iNumSides) * topBot;
            const float bc2     = std::cos(theta2);
            const float bs2     = std::sin(theta2);
            pCapVert->pos       = math::vec3{bc2, -1.f, bs2};
            pCapVert->uv        = math::vec2{(bs2*0.5f)+0.5f, (bc2*0.5f)+0.5f};
            pCapVert->norm      = i < 0
                                ? math::normalize(math::vec3{bc2, 1.f, bs2})
                                : math::vec3{0.f, topBot, 0.f};
            totalBounds.compareAndUpdate(pCapVert->pos);
            ++pCapVert;
        }
    }
    
    LS_LOG_MSG("\tSuccessfully loaded a ", numSides, "-sided cone.\n");
    resultDrawMode = draw_mode_t::TRIS;
    nodeList.emplace_back(createPrimitiveNode("Cone"));
    return true;
}

/*-------------------------------------
    Load a Sphere
    
    I found this method on the website by Kevin Harris:
    http://www.codesampler.com/oglsrc/oglsrc_8.htm#ogl_textured_sphere
    
    This loading method was originally found here:
    http://astronomy.swin.edu.au/~pbourke/opengl/sphere/
-------------------------------------*/
bool sceneResource::loadSphere(unsigned res) {
    // Only load an even number of vertices
    if (res % 2 == 1) {
        ++res;
    }
    
    // calculate the exact number of vertices to load
    unsigned totalVertCount = res*(res+1); // more trial and error
    
    LS_LOG_MSG("Attempting to load a ", totalVertCount, "-point sphere (", res, "x).");
    
    if (!initVertices(totalVertCount)) {
        LS_LOG_ERR("\tAn error occurred while initializing a ", totalVertCount, "-point sphere.\n");
        return false;
    }
    
    const int iNumSides = (int)res;
    const float fNumSides = (float)res;
    vertex* pVert = vertexList.data();

    for(int i = 0; i < iNumSides/2; ++i) {
        float theta1 = i * LS_TWO_PI / fNumSides - LS_PI_OVER_2;
        float theta2 = (i + 1) * LS_TWO_PI / fNumSides - LS_PI_OVER_2;
        
        for(int j = 0; j <= iNumSides; ++j) {
            const float theta3 = j * LS_TWO_PI / fNumSides;
            
            {
                const float ex  = LS_COS(theta1) * LS_SIN(theta3);
                const float ey  = LS_SIN(theta1);
                const float ez  = LS_COS(theta1) * LS_COS(theta3);
                pVert->pos      = math::normalize(math::vec3{ex, ey, -ez});
                pVert->uv       = math::vec2{-j/fNumSides, 2.f*i/fNumSides};
                pVert->norm     = pVert->pos;
                
                totalBounds.compareAndUpdate(pVert->pos);
                ++pVert;
            }
            {
                const float ex  = LS_COS(theta2) * LS_SIN(theta3);
                const float ey  = LS_SIN(theta2);
                const float ez  = LS_COS(theta2) * LS_COS(theta3);
                pVert->pos      = math::normalize(math::vec3{ex, ey, -ez});
                pVert->uv       = math::vec2{-j/fNumSides , 2.f*(i+1)/fNumSides};
                pVert->norm     = pVert->pos;
                
                totalBounds.compareAndUpdate(pVert->pos);
                ++pVert;
            }
        }
    }
    
    LS_LOG_MSG("\tSuccessfully loaded a ", totalVertCount, "-point sphere.\n");
    resultDrawMode = draw_mode_t::TRI_STRIP;
    nodeList.emplace_back(createPrimitiveNode("Sphere"));
    return true;
}

/*-------------------------------------
    Load a set of meshes from a file
-------------------------------------*/
bool sceneResource::loadFile(const std::string& filename) {
    unload();
    LS_LOG_MSG("Attempting to load 3D mesh file ", filename, '.');

    Assimp::Importer fileImporter;

    // prevent bad primitives
    fileImporter.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, INVALID_PRIM_IMPORT_FLAGS);
    fileImporter.SetPropertyInteger(AI_CONFIG_PP_FD_REMOVE, 1);
    fileImporter.SetExtraVerbose(true);

    // load
    const aiScene* const pScene = fileImporter.ReadFile(filename.c_str(), DEFAULT_IMPORT_FLAGS);

    if (!pScene) {
        LS_LOG_ERR(
            "\tError: Unable to load the mesh file ", filename,
            " due to an import error:\n\t", fileImporter.GetErrorString(), '\n'
        );
        unload();
        return false;
    }

    if (!preprocessMeshData(pScene)) {
        LS_LOG_ERR(
            "\tError: Failed to allocate data for the 3D mesh file ",
            filename, ".\n"
        );
        unload();
        return false;
    }

    if (!importMeshData(pScene)) {
        LS_LOG_ERR("\tError: Failed to load the 3D mesh ", filename, "!\n");
        unload();
        return false;
    }
    else {
        // lights, camera, action
        importCameras(pScene);
        
        // load the scene graph
        const aiNode* const pRootNode = pScene->mRootNode;
        readNodeHeirarchy(pRootNode, 0);
    }
    
    if (!importTexturePaths(pScene)) {
        LS_LOG_ERR("\tA recoverable error occurred while importing texture data.");
    }
    
    resultDrawMode = draw_mode_t::TRIS;

    LS_LOG_MSG(
        "\tSuccessfully loaded the 3D mesh file  \"", filename, "\"!\n",
        "\tTotal Vertices:  ", getNumVertices(), '\n',
        "\tTotal Indices:   ", getNumIndices(), '\n',
        "\tTotal Meshes:    ", getNumMeshes(), '\n',
        "\tTotal Cameras:   ", getNumCameras(), '\n',
        "\tTotal Nodes:     ", getNumNodes(), '\n',
        "\tTotal Textures:  ", getNumTextureTypes(), '\n'
    );

    return true;
}

/*-------------------------------------
    Preprocess ASSIMP scene data.
-------------------------------------*/
bool sceneResource::preprocessMeshData(const aiScene * const pScene) {

    // perform a pre-processing step in order to ensure a one-time allocation
    // of vertex+index data.
    unsigned numVertices = 0;
    unsigned numIndices = 0;

    for (unsigned meshIter = 0; meshIter < pScene->mNumMeshes; ++meshIter) {
        const aiMesh* const pMesh = pScene->mMeshes[meshIter];

        numVertices += pMesh->mNumVertices;

        // make sure the mesh has been triangulated.
        for (unsigned faceIter = 0; faceIter < pMesh->mNumFaces; ++faceIter) {
            const aiFace& face = pMesh->mFaces[faceIter];

            // skip non-triangulated faces
            if (face.mNumIndices != 3) {
                LS_LOG_ERR(
                    "\tWarning: Mesh \"", pMesh->mName.C_Str(),
                    "\", contains a polygon with ", face.mNumIndices, " vertices.\n"
                    "\tThis mesh may not appear correctly when loaded."
                );
                continue;
            }

            numIndices += 3;
        }
    }

    // initVertices implicitly calls "unload()"
    if (!initVertices(numVertices, numIndices)) {
        return false;
    }
    else {
        meshList.resize(pScene->mNumMeshes);
        meshList.shrink_to_fit();
    }
    
    return true;
}

/*-------------------------------------
    Load mesh data using ASSIMP
-------------------------------------*/
bool sceneResource::importMeshData(const aiScene* const pScene) {

    unsigned vertCount = 0;     // current number of loaded vertices
    unsigned baseVertex = 0;    // index of the mesh's first polygon vertex
    unsigned baseIndex = 0;     // index of the mesh's first face index

    // vertex data in ASSIMP is not interleaved. It has to be converted into
    // the internally used vertex format which is recommended for use on mobile
    // devices.
    for (unsigned meshIter = 0; meshIter < pScene->mNumMeshes; ++meshIter) {
        const aiMesh* const pMesh = pScene->mMeshes[meshIter];

        // load all vertices
        for (unsigned vertIter = 0; vertIter < pMesh->mNumVertices; ++vertIter) {
            const aiVector3D& vec = pMesh->mVertices[vertIter];
            vertex& vert = this->vertexList[vertCount++];
            vert.pos[0] = vec.x;
            vert.pos[1] = vec.y;
            vert.pos[2] = vec.z;
            
            totalBounds.compareAndUpdate(vert.pos);

            // Just in case the "aiProcess_GenNormals" step fails.
            if (pMesh->HasNormals()) {
                const aiVector3D& nrm = pMesh->mNormals[vertIter];
                vert.norm[0] = nrm.x;
                vert.norm[1] = nrm.y;
                vert.norm[2] = nrm.z;
            }

            // Always check for texture coords so the loader doesn't crash
            // "aiTextureType_DIFFUSE" is the default UV channel.
            if (pMesh->HasTextureCoords(0)) {
                const aiVector3D& tex = pMesh->mTextureCoords[0][vertIter];
                vert.uv[0] = tex.x;
                vert.uv[1] = tex.y;
            }
        }

        resourceMesh& outMesh = meshList[meshIter];
        
        outMesh.textureIndex = pMesh->mMaterialIndex;
        
        // load all face data
        importMeshFaces(pMesh, baseVertex, baseIndex, outMesh.indices);
        importMeshBones(pMesh, outMesh);
    }

    return true;
}

/*-------------------------------------
    Read all face data (triangles)
-------------------------------------*/
void sceneResource::importMeshFaces(
    const aiMesh* const pMesh,
    unsigned& baseVertex,
    unsigned& baseIndex,
    draw_index_pair_t& meshIndices
) {
    // get the index offset related the the current mesh entry
    unsigned vertIndex = baseIndex;

    // iterate through all faces in the mesh
    for (unsigned faceIter = 0; faceIter < pMesh->mNumFaces; ++faceIter) {
        const aiFace& face = pMesh->mFaces[faceIter];

        // skip non-triangulated faces
        if(face.mNumIndices != 3) {
            continue;
        }

        this->indexList[vertIndex++] = face.mIndices[0] + baseVertex;
        this->indexList[vertIndex++] = face.mIndices[1] + baseVertex;
        this->indexList[vertIndex++] = face.mIndices[2] + baseVertex;
    }

    // store the first/last vertex indices
    meshIndices.first = sizeof(draw_index_t) * baseIndex;
    meshIndices.count = vertIndex-baseIndex;

    // prepare the vertex and index offsets to the next mesh entry
    baseIndex += meshIndices.count;
    baseVertex += pMesh->mNumVertices;
}

/*-------------------------------------
    Read and import all bones
-------------------------------------*/
void sceneResource::importMeshBones(const aiMesh* const pMesh, resourceMesh& outMesh) {
    const unsigned numBones = pMesh->mNumBones;
    
    std::vector<bone>& boneList = outMesh.bones;
    boneList.resize(numBones);
    boneList.shrink_to_fit();
    
    for (unsigned i = 0; i < pMesh->mNumBones; ++i) {
        const aiBone* const pBone = pMesh->mBones[i];
        
        bone& b = boneList[i];
        b.setOffsetMatrix(convertAssimpMatrix(pBone->mOffsetMatrix));
        
        const unsigned numWeights = pBone->mNumWeights;
        std::vector<boneVertex>& weights = b.getVertexWeights();
        weights.resize(numWeights);
        weights.shrink_to_fit();
        
        for (unsigned j = 0; j < numWeights; ++j) {
            const aiVertexWeight& inWeight = pBone->mWeights[j];
            boneVertex& boneVert = weights[j];
            
            boneVert.vertIndex = inWeight.mVertexId;
            boneVert.weight = inWeight.mWeight;
        }
    }
}

/*-------------------------------------
    Read and import all texture paths
-------------------------------------*/
bool sceneResource::importTexturePaths(const aiScene* const pScene) {
    for (unsigned i = 0; i < pScene->mNumMaterials; ++i) {
        const aiMaterial* const pMaterial = pScene->mMaterials[i];
        importSingleTexturePath(pMaterial, aiTextureType_DIFFUSE);
        importSingleTexturePath(pMaterial, aiTextureType_AMBIENT);
        importSingleTexturePath(pMaterial, aiTextureType_NORMALS);
        importSingleTexturePath(pMaterial, aiTextureType_SPECULAR);
    }
    
    return true;
}

/*-------------------------------------
    Read and import a single texture path
-------------------------------------*/
void sceneResource::importSingleTexturePath(const aiMaterial* const pMaterial, int slotType) {
    // make sure there's a convention for converting aiTextureTypes to tex_slot_t types.
    tex_slot_t outSlot = tex_slot_t::TEXTURE_SLOT_DEFAULT;
    const unsigned totalTexCount = pMaterial->GetTextureCount((aiTextureType)slotType);
    
    switch (slotType) {
        case aiTextureType::aiTextureType_DIFFUSE:
            outSlot = tex_slot_t::TEXTURE_SLOT_DIFFUSE;
            LS_LOG_MSG("\tLocated ", totalTexCount, " diffuse textures.");
            break;
        case aiTextureType::aiTextureType_AMBIENT:
            outSlot = tex_slot_t::TEXTURE_SLOT_AMBIENT;
            LS_LOG_MSG("\tLocated ", totalTexCount, " ambient textures.");
            break;
        case aiTextureType::aiTextureType_NORMALS:
            outSlot = tex_slot_t::TEXTURE_SLOT_NORMAL;
            LS_LOG_MSG("\tLocated ", totalTexCount, " normal textures.");
            break;
        case aiTextureType::aiTextureType_SPECULAR:
            outSlot = tex_slot_t::TEXTURE_SLOT_SPECULAR;
            LS_LOG_MSG("\tLocated ", totalTexCount, " specular textures.");
            break;
            
        // TODO: other textures are unsupported at the moment.
        default:
            outSlot = tex_slot_t::TEXTURE_SLOT_DEFAULT;
            LS_LOG_MSG("\tLocated ", totalTexCount, " miscellaneous textures.");
            break;
    }
    
    // get the appropriate texture slot array from *this.
    std::vector<resourceTexture>& outTexList = textureSet[outSlot];
    
    // iterate
    for (unsigned i = 0; i < totalTexCount; ++i) {
        outTexList.emplace_back(resourceTexture{});
        resourceTexture& outTex = outTexList.back();
        outTex.texSlot = outSlot;
        
        // assimp will automatically clear and populate "inPath".
        aiString inPath;
        if (pMaterial->GetTexture((aiTextureType)slotType, i, &inPath, nullptr, nullptr, nullptr, nullptr, nullptr) != AI_SUCCESS) {
            outTex.texPath = "";
        }
        else {
            // add the imported texture to the appropriate array in textureSet.
            outTex.texPath = inPath.C_Str();
        }
        
        LS_LOG_MSG("\tFound texture data at \"", outTex.texPath, "\".");
    }
}

/*-------------------------------------
 * Import all matrices
-------------------------------------*/
void sceneResource::importCameras(const aiScene* const pScene) {
    const aiCamera* const* const pCamList = pScene->mCameras;
    const unsigned numCameras = pScene->mNumCameras;
    
    cameraList.resize(numCameras);
    cameraList.shrink_to_fit();
    
    for (unsigned i = 0; i < numCameras; ++i) {
        const aiCamera* const pInCam = pCamList[i];
        camera& cam = cameraList[i];
        
        cam.setProjectionParams(
            pInCam->mHorizontalFOV,
            pInCam->mAspect, 1.f,
            pInCam->mClipPlaneNear,
            pInCam->mClipPlaneFar
        );
        cam.makePerspective();
        
        const aiNode* const pNode = pScene->mRootNode->FindNode(pInCam->mName);
        
        if (pNode) {
            const aiMatrix4x4& inMat = pNode->mTransformation;
            aiVector3D inVec;
            
            inVec = pInCam->mPosition;
            inVec *= inMat;
            const math::vec3&& finalPos = convertAssimpVector(inVec);

            inVec = pInCam->mLookAt;
            inVec *= inMat;
            const math::vec3&& finalDir = convertAssimpVector(inVec);

            inVec = pInCam->mUp;
            inVec *= inMat;
            const math::vec3&& finalUp = convertAssimpVector(inVec);
            
            cam.lookAt(finalPos, finalDir, finalUp);
        }
        
        cam.update();
        
        LS_LOG_MSG("\tLoaded Scene Camera ", i, '/', numCameras, ':',
            "\n\t\tField of View: ", LS_RAD2DEG(cam.getFov()),
            "\n\t\tAspect Ratio:  ", cam.getAspectRatio(),
            "\n\t\tNear Plane:    ", cam.getNearPlane(),
            "\n\t\tFar Plane:     ", cam.getFarPlane(),
            "\n\t\tPosition:      {", cam.getPosition()[0], ", ", cam.getPosition()[1], ", ", cam.getPosition()[2], '}',
            "\n\t\tLook Target:   {", cam.getTarget()[0], ", ", cam.getTarget()[1], ", ", cam.getTarget()[2], '}',
            "\n\t\tUp Direction:  {", cam.getUpDirection()[0], ", ", cam.getUpDirection()[1], ", ", cam.getUpDirection()[2], '}'
        );
    }
}

/*-------------------------------------
    Read and import all meshes in a scene
-------------------------------------*/
unsigned sceneResource::readNodeHeirarchy(
    const aiNode* const pNode,
    const unsigned parentId,
    const math::mat4 parentTransform
) {
    // add a new scene node to the list
    const unsigned currentIndex = nodeList.size();
    nodeList.emplace_back(resourceNode{});
    resourceNode& currentNode = nodeList.back();

    currentNode.nodeParentId = parentId;
    currentNode.nodeName = pNode->mName.C_Str();

    LS_LOG_MSG("\tLoaded scene node: ", currentNode.nodeName, '.');

    // map the internal indices to the assimp node's mesh list
    std::vector<unsigned>& currentNodeMeshes = currentNode.nodeMeshes;
    currentNodeMeshes.resize(pNode->mNumMeshes);

    for (unsigned meshIter = 0; meshIter < pNode->mNumMeshes; ++meshIter) {
        // get a mesh index value from Assimp
        currentNodeMeshes[meshIter] = pNode->mMeshes[meshIter];
    }

    // import the node's model matrix
    const aiMatrix4x4& nodeMat = pNode->mTransformation;
    currentNode.nodeTransform = convertAssimpMatrix(nodeMat) * parentTransform;

    // allocate memory for the child nodes
    std::vector<unsigned>& childIndices = currentNode.nodeChildren;
    childIndices.resize(pNode->mNumChildren);

    // recursively load node children
    for (unsigned childIter = 0; childIter < pNode->mNumChildren; ++childIter) {
        // return the index of each child node and place it into "childIndices."
        childIndices[childIter] = readNodeHeirarchy(pNode->mChildren[childIter], currentIndex, currentNode.nodeTransform);
    }

    // return the index of *this in "nodeList."
    return currentIndex;
}

/*-------------------------------------
    Save a mesh to a file.
-------------------------------------*/
bool sceneResource::saveFile(const std::string& filename) const {
    LS_LOG_ERR(
        "Error: Cannot save the file ", filename, ". ",
        "Saving mesh data is not yet implemented."
    );
    return false;
}


} // end draw namespace
} // end ls namespace
