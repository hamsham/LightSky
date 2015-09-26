/* 
 * File:   draw/sceneResource.cpp
 * Author: Miles Lacey
 * 
 * Created on April 2, 2014, 9:04 PM
 */

#include <functional>
#include <utility>
#include <new> // std::nothrow

#include "lightsky/draw/BufferObject.h"
#include "lightsky/draw/geometry_utils.h"
#include "lightsky/draw/VertexUtils.h"
#include "lightsky/draw/PrimitiveGeometryLoader.h"

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
    || !setup_index_buffer_attribs(tempIbo, pOutIndexType ? *pOutIndexType : get_required_index_type(vertCount))
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
    Load a primitive
-------------------------------------*/
bool draw::load_polygon_geometry(
    const common_vertex_t vertTypes,
    BufferObject& vbo,
    const buffer_access_t usage,
    draw_mode_t& outDrawMode,
    unsigned numPoints
) {
    // make sure there are enough points for a minimal pyramid
    if (numPoints < 3) {
        numPoints = 3;
    }
    
    LS_LOG_MSG("Attempting to load a ", numPoints, "-sided polygon.");
    
    if (!init_geometry_vbo(vertTypes, vbo, numPoints, usage)) {
        LS_LOG_ERR("\tAn error occurred while initializing a quad mesh.\n");
        return false;
    }
    
    const unsigned bytesPerVert = get_vertex_byte_size(vertTypes);
    const unsigned totalBytes = bytesPerVert * numPoints;
    utils::pointer<char[]> pVertexList = {new(std::nothrow) char[totalBytes]};
    void* offset = nullptr;
    
    for (unsigned i = 0; i < numPoints; ++i) {
        const float theta = -LS_TWO_PI * ((float)i / (float)numPoints);
        const float bc = std::cos(theta);
        const float bs = std::sin(theta);
        void* const pVert = pVertexList;
        
        if (vertTypes & common_vertex_t::POSITION_VERTEX) {
            *reinterpret_cast<math::vec3*>(pVert+offset) = math::vec3{bs, bc, 0.f};
            offset += sizeof(math::vec3);
        }
        
        if (vertTypes & common_vertex_t::TEXTURE_VERTEX) {
            *reinterpret_cast<math::vec2*>(pVert+offset) = math::vec2{(bs*0.5f)+0.5f, (bc*0.5f)+0.5f};
            offset += sizeof(math::vec2);
        }
        
        if (vertTypes & common_vertex_t::NORMAL_VERTEX) {
            *reinterpret_cast<math::vec3*>(pVert+offset) = math::vec3{0.f, 0.f, 1.f};
            offset += sizeof(math::vec3);
        }
        
        if (vertTypes & common_vertex_t::POSITION_VERTEX) {
            *reinterpret_cast<math::vec3*>(pVert+offset) = math::vec3{1.f, 0.f, 0.f};
            offset += sizeof(math::vec3);
        }
        
        if (vertTypes & common_vertex_t::POSITION_VERTEX) {
            *reinterpret_cast<math::vec3*>(pVert+offset) = math::vec3{0.f, 1.f, 0.f};
            offset += sizeof(math::vec3);
        }
    }
    
    outDrawMode = draw_mode_t::TRI_FAN;
    set_buffer_sub_data(vbo, 0, totalBytes, pVertexList);
    
    LS_LOG_MSG("\tSuccessfully loaded a ", numPoints, "-sided polygon.\n");
    
    return true;
}

} // end ls namespace
