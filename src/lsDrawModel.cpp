/* 
 * File:   lsDrawModel.cpp
 * Author: miles
 * 
 * Created on June 10, 2014, 10:07 PM
 */

#include <utility>

#include "utils/assert.h"

#include "lsColor.h"
#include "lsDrawModel.h"

//-----------------------------------------------------------------------------
//      Class Implementations
//-----------------------------------------------------------------------------
/*
 * Constructor
 */
lsDrawModel::lsDrawModel() {
}

/*
 * Move Constructor
 */
lsDrawModel::lsDrawModel(lsDrawModel&& dm) :
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

/*
 * Destructor
 */
lsDrawModel::~lsDrawModel() {
    terminate();
}

lsDrawModel& lsDrawModel::operator=(lsDrawModel&& dm) {
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
void lsDrawModel::setVertexAttribs() {
    const lsVertexBuffer& vbo = pMesh->vbo;
    
    vao.bind();
    vbo.bind();
    
    // Vertex positions
    vao.enableAttrib(LS_VERTEX_POSITION_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_POSITION_ATTRIB, LS_ARRAY_SIZE(lsVertex::pos.v),
        GL_FLOAT, GL_FALSE, sizeof(lsVertex), (GLvoid*)offsetof(lsVertex, pos.v)
    );
    
    // Vertex UVs
    vao.enableAttrib(LS_VERTEX_TEXTURE_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_TEXTURE_ATTRIB, LS_ARRAY_SIZE(lsVertex::uv.v),
        GL_FLOAT, GL_FALSE, sizeof(lsVertex), (GLvoid*)offsetof(lsVertex, uv.v)
    );
    
    // Vertex normals
    vao.enableAttrib(LS_VERTEX_NORMAL_ATTRIB);
    vao.setAttribOffset(
        LS_VERTEX_NORMAL_ATTRIB, LS_ARRAY_SIZE(lsVertex::norm.v),
        GL_FLOAT, GL_FALSE, sizeof(lsVertex), (GLvoid*)offsetof(lsVertex, norm.v)
    );
    
    LOG_GL_ERR();
    
    // setup the VBO/VAO for instancing
    modelVbo.bind();
    for (unsigned i = 0; i < 4; ++i) {
        vao.enableAttrib(LS_MODEL_MATRIX_ATTRIB0+i);
        vao.setAttribOffset(
            LS_MODEL_MATRIX_ATTRIB0+i, 4, GL_FLOAT, GL_FALSE,
            sizeof(math::mat4), (const GLvoid*)(sizeof(float)*i*4)
        );
        vao.setAttribInstanceRate(LS_MODEL_MATRIX_ATTRIB0+i, 1);
    }
    
    LOG_GL_ERR();
    
    vao.unbind();
    vbo.unbind();
    modelVbo.unbind();
    
    LOG_GL_ERR();
}

void lsDrawModel::terminate() {
    pMesh = nullptr;
    pTexture = nullptr;
    numInstances = 1;
    vao.terminate();
    modelVbo.terminate();
}

/*
 * Set the mesh to be used by this object during a draw operation.
 */
bool lsDrawModel::init(const lsMesh& m, const lsTexture& t) {
    // there's no telling what data might be pushed into the VAO. Get rid of it.
    vao.terminate();
    if (!vao.init()) {
        LS_LOG_ERR("Unable to create a drawModel for mesh ", m.getId(), '.');
        terminate();
        return false;
    }
    
    // vbos are resized when any new data is pushed into them
    if (modelVbo.isValid() == false) {
        if (!modelVbo.init()) {
            LS_LOG_ERR("\tUnable to initialize a model matrix buffer.");
            terminate();
            return false;
        }
        else {
            // ensure at lease one model matrix is available on initialization.
            const math::mat4 identityMat = {1.f};
            setNumInstances(1, &identityMat);
        }
    }
    
    pMesh = &m;
    
    setVertexAttribs();
    setTexture(t);
    
    return true;
}

/*
 * All meshes support instanced draws by default. This will set the
 * number of instances that will appear when drawing a mesh.
 */
void lsDrawModel::setNumInstances(int instanceCount, const math::mat4* const modelMatrices) {
    HL_ASSERT(instanceCount > 0);
    modelVbo.bind();
    modelVbo.setData(sizeof(math::mat4)*instanceCount, modelMatrices, LS_DYNAMIC_DRAW);
    modelVbo.unbind();
    LOG_GL_ERR();
    
    numInstances = instanceCount;
}

/*
 * Change the model matrix for a single instance
 */
void lsDrawModel::modifyInstance(int index, const math::mat4& modelMatrix) {
    HL_ASSERT(index >= 0 && index < numInstances);
    modelVbo.bind();
    modelVbo.setSubData(sizeof(math::mat4)*index, sizeof(math::mat4), &modelMatrix);
    modelVbo.unbind();
    LOG_GL_ERR();
}
