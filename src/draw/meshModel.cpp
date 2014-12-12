/* 
 * File:   draw/meshModel.cpp
 * Author: Miles Lacey
 * 
 * Created on June 10, 2014, 10:07 PM
 */

#include <utility>

#include "lightsky/utils/assertions.h"

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
    modelVbo{std::move(dm.modelVbo)},
    vao{std::move(dm.vao)}
{
    dm.pMesh = nullptr;
    dm.pTexture = nullptr;
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
    
    modelVbo = std::move(dm.modelVbo);
    vao = std::move(dm.vao);
    
    return *this;
}

/*-------------------------------------
    Helper function to ensure all vertex attributes are setup properly.
-------------------------------------*/
void meshModel::setVertexAttribs() {
    vao.bind();
    
    pMesh->getVertexBuffer().bind();
    pMesh->getIndexBuffer().bind();
    
    // Vertex positions
    vao.enableAttrib(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_POS));
    vao.setAttribOffset(
        LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_POS),
        LS_ARRAY_SIZE(vertex::pos.v), GL_FLOAT, GL_FALSE, sizeof(vertex),
        (GLvoid*)LS_ENUM_VAL(vertex_desc_t::ELEMENT_COUNT_POS)
    );
    
    // Vertex UVs
    vao.enableAttrib(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_TEX));
    vao.setAttribOffset(
        LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_TEX),
        LS_ARRAY_SIZE(vertex::uv.v), GL_FLOAT, GL_FALSE, sizeof(vertex),
        (GLvoid*)LS_ENUM_VAL(vertex_desc_t::ELEMENT_COUNT_TEX)
    );
    
    // Vertex normals
    vao.enableAttrib(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_NORM));
    vao.setAttribOffset(
        LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_NORM),
        LS_ARRAY_SIZE(vertex::norm.v), GL_FLOAT, GL_FALSE, sizeof(vertex),
        (GLvoid*)LS_ENUM_VAL(vertex_desc_t::ELEMENT_COUNT_NORM)
    );
    
    LOG_GL_ERR();
    
    // setup the VBO/VAO for instancing
    modelVbo.bind();
    for (unsigned i = 0; i < 4; ++i) {
        vao.enableAttrib(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_MAT_ROW0)+i);
        vao.setAttribOffset(
            LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_MAT_ROW0)+i, 4, GL_FLOAT,
            GL_FALSE, sizeof(math::mat4), (const GLvoid*)(sizeof(float)*i*4)
        );
        vao.setAttribInstanceRate(LS_ENUM_VAL(vertex_attrib_t::VERTEX_ATTRIB_MAT_ROW0)+i, 1);
    }
    
    LOG_GL_ERR();
    
    vao.unbind();
    
    pMesh->getVertexBuffer().unbind();
    pMesh->getIndexBuffer().unbind();
    
    modelVbo.unbind();
    
    LOG_GL_ERR();
}

void meshModel::terminate() {
    pMesh = nullptr;
    pTexture = nullptr;
    vao.terminate();
    modelVbo.terminate();
}

/*-------------------------------------
    Set the mesh to be used by this object during a draw operation.
-------------------------------------*/
bool meshModel::init(const geometry& m, const texture& t) {
    // there's no telling what data might be pushed into the VAO. Get rid of it.
    vao.terminate();
    if (!vao.init()) {
        LS_LOG_ERR("Unable to create a drawModel for geometry ", m.getId(), '.');
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
    
    drawParams = m.getDrawCommand();
    const math::mat4 identity{1.f};
    setNumInstances(1, &identity);
    
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
    modelVbo.setData(sizeof(math::mat4)*instanceCount, modelMatrices, VBO_DYNAMIC_DRAW);
    modelVbo.unbind();
    LOG_GL_ERR();
    
    switch (drawParams.getDrawCommand()) {
        case draw_command_t::ARRAYS: {
            const drawArrays& da = drawParams.getDrawFunction().da;
            drawParams.paramsArraysInstanced(da.first, da.count, instanceCount);
            break;
        }
        case draw_command_t::ARRAYS_INSTANCED: {
            const drawArraysInstanced& dai = drawParams.getDrawFunction().dai;
            drawParams.paramsArraysInstanced(dai.first, dai.count, instanceCount);
            break;
        }
        case draw_command_t::ELEMENTS: {
            const drawElements& de = drawParams.getDrawFunction().de;
            drawParams.paramsElementsInstanced(de.count, de.type, de.offset, instanceCount);
            break;
        }
        case draw_command_t::ELEMENTS_RANGED: {
            const drawElementsRanged& der = drawParams.getDrawFunction().der;
            drawParams.paramsElementsInstanced(der.count, der.type, der.offset, instanceCount);
            break;
        }
        case draw_command_t::ELEMENTS_INSTANCED: {
            const drawElementsInstanced& dei = drawParams.getDrawFunction().dei;
            drawParams.paramsElementsInstanced(dei.count, dei.type, dei.offset, instanceCount);
            break;
        }
        default:
            LS_DEBUG_ASSERT(false);
            break;
    }
}

/*-------------------------------------
    Change the model matrix for a single instance
-------------------------------------*/
void meshModel::modifyInstance(int index, const math::mat4& modelMatrix) {
    LS_DEBUG_ASSERT(index >= 0);
    modelVbo.bind();
    modelVbo.setSubData(sizeof(math::mat4)*index, sizeof(math::mat4), &modelMatrix);
    modelVbo.unbind();
    LOG_GL_ERR();
}

} // end draw namespace
} // end ls namespace
