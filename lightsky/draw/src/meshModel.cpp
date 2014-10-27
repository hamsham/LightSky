/* 
 * File:   draw/meshModel.cpp
 * Author: Miles Lacey
 * 
 * Created on June 10, 2014, 10:07 PM
 */

#include <utility>

#include "lightsky/utils/assert.h"

#include "lightsky/draw/color.h"
#include "lightsky/draw/meshModel.h"
#include "lightsky/draw/vertex.h"

namespace ls {
namespace draw {

/*-------------------------------------
    Constructor
-------------------------------------*/
meshModel::meshModel() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
meshModel::meshModel(meshModel&& dm) :
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

/*-------------------------------------
    Destructor
-------------------------------------*/
meshModel::~meshModel() {
    terminate();
}

meshModel& meshModel::operator=(meshModel&& dm) {
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

/*-------------------------------------
    Helper function to ensure all vertex attributes are setup properly.
-------------------------------------*/
void meshModel::setVertexAttribs() {
    const vertexBuffer& vbo = pMesh->vbo;
    
    vao.bind();
    vbo.bind();
    
    // Vertex positions
    vao.enableAttrib(VERTEX_ATTRIB_POS);
    vao.setAttribOffset(
        VERTEX_ATTRIB_POS, LS_ARRAY_SIZE(vertex::pos.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, pos.v)
    );
    
    // Vertex UVs
    vao.enableAttrib(VERTEX_ATTRIB_TEX);
    vao.setAttribOffset(
        VERTEX_ATTRIB_TEX, LS_ARRAY_SIZE(vertex::uv.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, uv.v)
    );
    
    // Vertex normals
    vao.enableAttrib(VERTEX_ATTRIB_NORM);
    vao.setAttribOffset(
        VERTEX_ATTRIB_NORM, LS_ARRAY_SIZE(vertex::norm.v),
        GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, norm.v)
    );
    
    LOG_GL_ERR();
    
    // setup the VBO/VAO for instancing
    modelVbo.bind();
    for (unsigned i = 0; i < 4; ++i) {
        vao.enableAttrib(VERTEX_ATTRIB_MAT_ROW0+i);
        vao.setAttribOffset(
            VERTEX_ATTRIB_MAT_ROW0+i, 4, GL_FLOAT, GL_FALSE,
            sizeof(math::mat4), (const GLvoid*)(sizeof(float)*i*4)
        );
        vao.setAttribInstanceRate(VERTEX_ATTRIB_MAT_ROW0+i, 1);
    }
    
    LOG_GL_ERR();
    
    vao.unbind();
    vbo.unbind();
    modelVbo.unbind();
    
    LOG_GL_ERR();
}

void meshModel::terminate() {
    pMesh = nullptr;
    pTexture = nullptr;
    numInstances = 1;
    vao.terminate();
    modelVbo.terminate();
}

/*-------------------------------------
    Set the mesh to be used by this object during a draw operation.
-------------------------------------*/
bool meshModel::init(const mesh& m, const texture& t) {
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

/*-------------------------------------
    All meshes support instanced draws by default. This will set the
    number of instances that will appear when drawing a mesh.
-------------------------------------*/
void meshModel::setNumInstances(int instanceCount, const math::mat4* const modelMatrices) {
    LS_DEBUG_ASSERT(instanceCount > 0);
    modelVbo.bind();
    modelVbo.setData(sizeof(math::mat4)*instanceCount, modelMatrices, LS_DYNAMIC_DRAW);
    modelVbo.unbind();
    LOG_GL_ERR();
    
    numInstances = instanceCount;
}

/*-------------------------------------
    Change the model matrix for a single instance
-------------------------------------*/
void meshModel::modifyInstance(int index, const math::mat4& modelMatrix) {
    LS_DEBUG_ASSERT(index >= 0 && index < numInstances);
    modelVbo.bind();
    modelVbo.setSubData(sizeof(math::mat4)*index, sizeof(math::mat4), &modelMatrix);
    modelVbo.unbind();
    LOG_GL_ERR();
}

} // end draw namespace
} // end ls namespace
