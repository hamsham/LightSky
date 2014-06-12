/* 
 * File:   drawModel.cpp
 * Author: miles
 * 
 * Created on June 10, 2014, 10:07 PM
 */

#include <utility>

#include "assert.h"
#include "drawModel.h"

drawModel::drawModel(const drawModel&) {
    HL_ASSERT(false, "Draw-Model copy constructor is not yet implemented.");
}

drawModel::drawModel(drawModel&& dm) :
    pMesh{dm.pMesh},
    pTexture{dm.pTexture},
    numInstances{dm.numInstances},
    modelVbo{std::move(dm.modelVbo)},
    vao{std::move(dm.vao)}
{
    dm.pMesh = nullptr;
    dm.pTexture = nullptr;
    dm.numInstances = 1;
}

drawModel& drawModel::operator=(const drawModel&) {
    HL_ASSERT(false, "Draw-Model copy operator is not yet implemented.");
    return *this;
}

drawModel& drawModel::operator=(drawModel&& dm) {
    pMesh = dm.pMesh;
    dm.pMesh = nullptr;
    
    pTexture = dm.pTexture;
    dm.pTexture = nullptr;
    
    numInstances = dm.numInstances;
    dm.numInstances = 1;
    
    modelVbo = std::move(dm.modelVbo);
    vao = std::move(dm.vao);
    
    return *this;
}

/*
 * Helper function to ensure all vertex attributes are setup properly.
 */
void drawModel::setVertexAttribs(const mesh& m) {
    vertexBuffer& vbo = m.vbo;
    
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

void drawModel::reset() {
    pMesh = nullptr;
    pTexture = nullptr;
    numInstances = 1;
    vao.terminate();
    modelVbo.terminate();
}

bool drawModel::setMesh(const mesh* const m) {
    if (m == nullptr) {
        reset();
        return false;
    }
    
    vao.terminate();
    if (!vao.init()) {
        LOG_ERR("Unable to create a drawModel for mesh ", m->getId(), '.');
        reset();
        return false;
    }
    
    if (modelVbo.isValid() == false) {
        if (!modelVbo.init()) {
            LOG_ERR("\tUnable to initialize a model matrix buffer.");
            reset();
            return false;
        }
        else {
            // ensure at lease one model matrix is available on initialization.
            const math::mat4 identityMat = {1.f};
            setNumInstances(1, &identityMat);
        }
    }
    
    setVertexAttribs(*m);
    
    return true;
}

void drawModel::setNumInstances(int instanceCount, const math::mat4* const modelMatrices) {
    HL_ASSERT(instanceCount > 0);
    HL_ASSERT(modelMatrices != nullptr);
    modelVbo.bind();
    modelVbo.setData(sizeof(math::mat4)*instanceCount, modelMatrices, buffer_usage_t::DYNAMIC_DRAW);
    modelVbo.unbind();
    LOG_GL_ERR();
    
    numInstances = instanceCount;
}

void drawModel::modifyInstance(int index, const math::mat4& modelMatrix) {
    HL_ASSERT(instanceCount >= 0 && instanceCount < numInstances);
    modelVbo.bind();
    modelVbo.setSubData(sizeof(math::mat4)*index, sizeof(math::mat4), &modelMatrix);
    modelVbo.unbind();
    LOG_GL_ERR();
}
