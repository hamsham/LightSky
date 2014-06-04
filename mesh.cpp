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
    modelVbo{std::move(m.modelVbo)},
    numVertices{m.numVertices},
    drawMode{m.drawMode}
{
    m.numVertices = 0;
    m.numInstances = 0;
    m.drawMode = draw_mode::DEFAULT_DRAW_MODE;
}

/*
 * Move Operator
 */
mesh& mesh::operator=(mesh&& m) {
    vao = std::move(m.vao);
    vbo = std::move(m.vbo);
    modelVbo = std::move(m.modelVbo);
    
    numVertices = m.numVertices;
    m.numVertices = 0;
    
    numInstances = m.numInstances;
    m.numInstances = 0;
    
    drawMode = m.drawMode;
    m.drawMode = draw_mode::DEFAULT_DRAW_MODE;
    
    return *this;
}

/*
 * Helper function to initialize all vertex buffers & arrays
 */
bool mesh::initVertices(unsigned numVerts) {
    if (numVerts == 0) {
        LOG_ERR("\tInvalid vertex count in the mesh loader. Aborting GPU load.");
        terminate();
        return false;
    }
    
    vao.terminate();
    if (!vao.init()) {
        LOG_ERR("\tUnable to initialize a mesh VAO.");
        return false;
    }
    
    if (vbo.isValid() == false) {
        if (!vbo.init()) {
            LOG_ERR("\tUnable to initialize a mesh VBO.");
            terminate();
            return false;
        }
    }
    
    if (modelVbo.isValid() == false) {
        if (!modelVbo.init()) {
            LOG_ERR("\tUnable to initialize a model matrix buffer.");
            terminate();
            return false;
        }
    }
    
    // ensure at lease one model matrix is available on initialization.
    const math::mat4 identityMat = {1.f};
    setNumInstances(1, &identityMat);
    
    LOG_MSG("\tVertex Count: ", numVerts);
    return true;
}

/*
 * Helper function to ensure all vertex attributes are setup properly.
 */
void mesh::setVertexAttribs() {
    vao.bind();
    vbo.bind();
    
    // Vertex positions
    vao.enableAttrib(LS_VERTEX_POSITION_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_POSITION_ATTRIB, LS_ARRAY_SIZE(vertex::pos.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, pos.v)
    );
    
    // Vertex UVs
    vao.enableAttrib(LS_VERTEX_TEXTURE_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_TEXTURE_ATTRIB, LS_ARRAY_SIZE(vertex::uv.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, uv.v)
    );
    
    // Vertex normals
    vao.enableAttrib(LS_VERTEX_NORMAL_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_NORMAL_ATTRIB, LS_ARRAY_SIZE(vertex::norm.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, norm.v)
    );
    
    LOG_GL_ERR();
    
    // setup the VBO/VAO for instancing
    modelVbo.bind();
    for (unsigned i = 0; i < 4; ++i) {
        vao.enableAttrib(LS_MODEL_MATRIX_ATTRIB+i);
        vao.setAttribOffset(
            LS_MODEL_MATRIX_ATTRIB+i, 4, GL_FLOAT, GL_FALSE,
            sizeof(math::mat4), (const GLvoid*)(sizeof(float)*i*4)
        );
        vao.setAttribInstanceRate(LS_MODEL_MATRIX_ATTRIB+i, 1);
    }
    
    LOG_GL_ERR();
    
    vao.unbind();
    vbo.unbind();
    modelVbo.unbind();
    
    LOG_GL_ERR();
}

/*
 * Load the data contained within a mesh loader onto the GPU
 */
bool mesh::init(const meshResource& ml) {
    LOG_MSG("Attempting to send mesh vertex data to the GPU.");
    
    if (!initVertices(ml.getNumVertices())) {
        return false;
    }
    
    vbo.bind();
    vbo.setData(ml.getByteSize(), ml.getVertices(), buffer_usage_t::STATIC_DRAW);
    LOG_GL_ERR();
    
    setVertexAttribs();
    
    numVertices = ml.getNumVertices();
    drawMode = ml.getDrawMode();
    
    LOG_MSG("\tSuccessfully sent a mesh of ", numVertices, " vertices to the GPU.\n");
    
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
