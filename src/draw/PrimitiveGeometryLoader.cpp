/* 
 * File:   draw/sceneResource.cpp
 * Author: Miles Lacey
 * 
 * Created on April 2, 2014, 9:04 PM
 */

#include <functional>
#include <utility>

#include "lightsky/draw/BufferObject.h"
#include "lightsky/draw/geometry_utils.h"
#include "lightsky/draw/VertexUtils.h"

namespace ls {

/*-------------------------------------
 * Initialize the arrays that will be used to contain the mesh data.
-------------------------------------*/
bool draw::init_geometry_vbo(
    const common_vertex_t vertTypes,
    BufferObject& vbo,
    const unsigned vertCount,
    const buffer_access_t usage
) {
    BufferObject tempVbo;
    unsigned numVertBytes = get_vertex_byte_size(vertTypes) * vertCount;

    LS_LOG_MSG(
        "Attempting to allocate GPU memory for geometry vertex data.",
        "\n\tVertices:    ", vertCount,
        "\n\t# VBO Bytes: ", numVertexBytes
    );
    
    if (!init_buffer(tempVbo)
    || !setup_vertex_buffer_attribs(tempVbo, vertTypes)
    ) {
        LS_LOG_ERR("Unable to initialize a vertex buffer object on the CPU.");
        return false;
    }
    
    bind_buffer(tempVbo);
    
    if (set_buffer_data(tempVbo, numVertBytes, nullptr, usage)) {
        LS_LOG_ERR("Unable to allocate a vertex buffer on the GPU.");
        terminate_buffer(tempVbo);
        return false;
    }

    LS_LOG_MSG("Successfully allocated GPU memory for geometry vertex data.\n");
    
    vbo = std::move(tempVbo);
    
    return true;
}

/*-------------------------------------
 * Initialize the arrays that will be used to contain the mesh data.
-------------------------------------*/
bool draw::init_geometry_ibo(
    BufferObject& ibo,
    const unsigned vertCount,
    const unsigned indexCount,
    const buffer_access_t usage,
    index_element_t* const pOutIndexType
) {
    BufferObject tempIbo;
    index_element_t dataType = get_required_index_type(vertCount);
    
    unsigned numIndexBytes = indexCount * (dataType == index_element_t::INDEX_TYPE_UINT
        ? sizeof(unsigned)
        : sizeof(unsigned short));

    LS_LOG_MSG(
        "Attempting to allocate GPU memory for geometry index data.",
        "\n\tIndices:     ", indexCount,
        "\n\t# IBO Bytes: ", numIndexBytes
    );
    
    if (!init_buffer(tempIbo)
    || !setup_index_buffer_attribs(tempIbo, pOutIndexType ? pOutIndexType : get_required_index_type(vertCount))
    ) {
        LS_LOG_ERR("Unable to initialize an index buffer object on the CPU.");
        return false;
    }
    
    bind_buffer(tempIbo);
    
    if (set_buffer_data(tempIbo, numIndexBytes, nullptr, usage)) {
        LS_LOG_ERR("Unable to allocate an index buffer on the GPU.");
        terminate_buffer(tempIbo);
        return false;
    }

    LS_LOG_MSG("Successfully allocated GPU memory for geometry index data.\n");
    
    ibo = std::move(tempIbo);
    
    if (pOutIndexType) {
        *pOutIndexType = dataType;
    }
    
    return true;
}

/*-------------------------------------
    Load a square
-------------------------------------*/
bool draw::load_quad_geometry() {
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
    
    totalBounds.set_top_rear_right(math::vec3{1.f, 1.f, LS_EPSILON});
    totalBounds.set_bot_front_left(math::vec3{-1.f, -1.f, -LS_EPSILON});
    
    LS_LOG_MSG("\tSuccessfully loaded a quad mesh.\n");
    resultDrawMode = draw_mode_t::TRI_FAN;
    nodeList.emplace_back(createPrimitiveNode("Quad"));
    return true;
}

/*-------------------------------------
    Load a primitive
-------------------------------------*/
bool draw::loadPolygon(unsigned numPoints) {
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
        
        totalBounds.compare_and_update(pVert->pos);
    }
    
    LS_LOG_MSG("\tSuccessfully loaded a ", numPoints, "-sided polygon.\n");
    resultDrawMode = draw_mode_t::TRI_FAN;
    nodeList.emplace_back(createPrimitiveNode("Polygon"));
    return true;
}

/*-------------------------------------
    Load a cube
-------------------------------------*/
bool draw::loadCube() {
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
    
    totalBounds.set_top_rear_right(math::vec3{1.f, 1.f, 1.f});
    totalBounds.set_bot_front_left(math::vec3{-1.f, -1.f, -1.f});
    
    LS_LOG_MSG("\tSuccessfully loaded a cube mesh.\n");
    resultDrawMode = draw_mode_t::TRI_STRIP;
    nodeList.emplace_back(createPrimitiveNode("Cube"));
    return true;
}

/*-------------------------------------
    Load a cylinder
-------------------------------------*/
bool draw::loadCylinder(unsigned numSides) {
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
        totalBounds.compare_and_update(pCapVert->pos);
        ++pCapVert;

        // cap, first triangle leg
        pCapVert->pos       = math::vec3{bc1, topBot, bs1};
        pCapVert->uv        = math::vec2{(bs1*0.5f)+0.5f, (bc1*0.5f)+0.5f};
        pCapVert->norm      = math::vec3{0.f, topBot, 0.f};
        totalBounds.compare_and_update(pCapVert->pos);
        ++pCapVert;

        // cap, second triangle leg
        pCapVert->pos       = math::vec3{bc2, topBot, bs2};
        pCapVert->uv        = math::vec2{(bs2*0.5f)+0.5f, (bc2*0.5f)+0.5f};
        pCapVert->norm      = math::vec3{0.f, topBot, 0.f};
        totalBounds.compare_and_update(pCapVert->pos);
        ++pCapVert;
        
        // Cylinder Side, apex
        pSideVert->pos      = math::vec3{bc1, -topBot, bs1};
        pSideVert->uv       = math::vec2{(bs1*0.5f)+0.5f, (bc1*0.5f)+0.5f};
        pSideVert->norm     = math::vec3{bc1, 0.f, bs1};
        totalBounds.compare_and_update(pSideVert->pos);
        ++pSideVert;
        
        // Cylinder Side, leg 1
        pSideVert->pos      = math::vec3{bc2, topBot, bs2};
        pSideVert->uv       = math::vec2{(bs2*0.5f)+0.5f, (bc2*0.5f)+0.5f};
        pSideVert->norm     = math::vec3{bc2, 0.f, bs2};
        totalBounds.compare_and_update(pSideVert->pos);
        ++pSideVert;
        
        // Cylinder Side, leg 2
        pSideVert->pos      = math::vec3{bc1, topBot, bs1};
        pSideVert->uv       = math::vec2{(bs1*0.5f)+0.5f, (bc1*0.5f)+0.5f};
        pSideVert->norm     = math::vec3{bc1, 0.f, bs1};
        totalBounds.compare_and_update(pSideVert->pos);
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
bool draw::loadCone(unsigned numSides) {
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
            totalBounds.compare_and_update(pCapVert->pos);
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
            totalBounds.compare_and_update(pCapVert->pos);
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
            totalBounds.compare_and_update(pCapVert->pos);
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
bool draw::loadSphere(unsigned res) {
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
                
                totalBounds.compare_and_update(pVert->pos);
                ++pVert;
            }
            {
                const float ex  = LS_COS(theta2) * LS_SIN(theta3);
                const float ey  = LS_SIN(theta2);
                const float ez  = LS_COS(theta2) * LS_COS(theta3);
                pVert->pos      = math::normalize(math::vec3{ex, ey, -ez});
                pVert->uv       = math::vec2{-j/fNumSides , 2.f*(i+1)/fNumSides};
                pVert->norm     = pVert->pos;
                
                totalBounds.compare_and_update(pVert->pos);
                ++pVert;
            }
        }
    }
    
    LS_LOG_MSG("\tSuccessfully loaded a ", totalVertCount, "-point sphere.\n");
    resultDrawMode = draw_mode_t::TRI_STRIP;
    nodeList.emplace_back(createPrimitiveNode("Sphere"));
    return true;
}


} // end ls namespace
