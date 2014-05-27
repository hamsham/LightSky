/* 
 * File:   mesh.cpp
 * Author: miles
 * 
 * Created on April 6, 2014, 12:36 AM
 */

#include <utility>
#include "assert.h"
#include "mesh.h"
#include "resource.h"
#include "meshResource.h"

/*
 * Move Constructor
 */
mesh::mesh(mesh&& m) :
    vao{std::move(m.vao)},
    vbo{std::move(m.vbo)},
    numVertices{m.numVertices}
{
    m.numVertices = 0;
}

/*
 * Move Operator
 */
mesh& mesh::operator=(mesh&& m) {
    vao = std::move(m.vao);
    vbo = std::move(m.vbo);
    
    numVertices = m.numVertices;
    m.numVertices = 0;
    
    return *this;
}

/*
 * Load the data contained within a mesh loader onto the GPU
 */
bool mesh::init(const meshResource& ml, unsigned meshIndex) {
    LOG_MSG("Loading a mesh.");
    terminate();
    
    if (meshIndex >= ml.getNumMeshes()) {
        LOG_ERR("Attempted to load an out-of range mesh.");
        return false;
    }
    
    if (!vao.init()) {
        LOG_ERR("Unable to initialize a mesh VAO.");
        return false;
    }
    
    if (!vbo.init()) {
        LOG_ERR("Unable to initialize a mesh VBO.");
        vao.terminate();
        return false;
    }
    
    if (!modelVbo.init()) {
        LOG_ERR("Unable to initialize a model matrix buffer.");
        vbo.terminate();
        vao.terminate();
        return false;
    }
    
    if (ml.getNumVertices(meshIndex) == 0) {
        LOG_ERR("\tInvalid vertex count ", meshIndex, ". Aborting GPU load.");
        return false;
    }
    else {
        LOG_MSG("\tVertex Count: ", ml.getNumVertices(meshIndex));
    }
    
    vao.bind();
    vbo.bind();
    vbo.setData(ml.getByteSize(), ml.getVertices(meshIndex), buffer_usage_t::STATIC_DRAW);
    
    // Vertex positions
    vao.enableAttrib(LS_VERTEX_POSITION_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_POSITION_ATTRIB, LS_ARRAY_SIZE(vertex::pos.v),
        GL_FLOAT, GL_FALSE,
        sizeof(vertex), (GLvoid*)offsetof(vertex, pos.v)
    );
    
    // Vertex UVs
    vao.enableAttrib(LS_VERTEX_TEXTURE_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_TEXTURE_ATTRIB, LS_ARRAY_SIZE(vertex::uv.v),
        GL_FLOAT, GL_FALSE,
        sizeof(vertex), (GLvoid*)offsetof(vertex, uv.v)
    );
    
    // Vertex normals
    vao.enableAttrib(LS_VERTEX_NORMAL_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_NORMAL_ATTRIB, LS_ARRAY_SIZE(vertex::norm.v),
        GL_FLOAT, GL_FALSE,
        sizeof(vertex), (GLvoid*)offsetof(vertex, norm.v)
    );
    
    LOG_GL_ERR();
    
    // setup the VBO/VAO for instancing
    const math::mat4 identityMat = {1.f};
    modelVbo.bind();
    modelVbo.setData(sizeof(math::mat4), &identityMat, buffer_usage_t::DYNAMIC_DRAW);
    for (unsigned i = 0; i < 4; ++i) {
        vao.enableAttrib(LS_MODEL_MATRIX_ATTRIB+i);
        vao.setAttribOffset(
            LS_MODEL_MATRIX_ATTRIB + i, 4, GL_FLOAT, GL_FALSE,
            sizeof(math::mat4), (const GLvoid*)(sizeof(float)*i*4)
        );
        vao.setAttribInstanceRate(LS_MODEL_MATRIX_ATTRIB+i, 1);
    }
    
    LOG_GL_ERR();
    
    vao.unbind();
    vbo.unbind();
    modelVbo.unbind();
    
    LOG_GL_ERR();
    
    numVertices = ml.getNumVertices(meshIndex);
    
    LOG_MSG("Mesh object successfully loaded.\n");
    
    return true;
}

void mesh::setNumInstances(int instanceCount, const math::mat4* const modelMatrices) {
    modelVbo.bind();
    modelVbo.setData(sizeof(math::mat4)*instanceCount, modelMatrices, buffer_usage_t::DYNAMIC_DRAW);
    modelVbo.unbind();
    
    numInstances = instanceCount;
}

void mesh::modifyInstance(int index, const math::mat4& modelMatrix) {
    modelVbo.bind();
    modelVbo.setSubData(sizeof(math::mat4)*index, sizeof(math::mat4), &modelMatrix);
    modelVbo.unbind();
}
