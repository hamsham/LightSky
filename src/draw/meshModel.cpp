/* 
 * File:   draw/meshModel.cpp
 * Author: Miles Lacey
 * 
 * Created on June 10, 2014, 10:07 PM
 */

#include <utility>

#include "lightsky/utils/assertions.h"

#include "lightsky/draw/color.h"
#include "lightsky/draw/sceneNode.h"
#include "lightsky/draw/vertex.h"

namespace ls {
namespace draw {

/*-------------------------------------
    Constructor
-------------------------------------*/
sceneNode::sceneNode() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
sceneNode::sceneNode(sceneNode&& s) :
    pMesh{s.pMesh},
    matrixVbo{std::move(s.matrixVbo)},
    vao{std::move(s.vao)},
    drawParams{std::move(s.drawParams)},
    textureList{std::move(s.textureList)}
{
    s.pMesh = nullptr;
    s.drawParams = {};
}

/*-------------------------------------
    Destructor
-------------------------------------*/
sceneNode::~sceneNode() {
    terminate();
}

sceneNode& sceneNode::operator=(sceneNode&& s) {
    pMesh = s.pMesh;
    s.pMesh = nullptr;
    
    matrixVbo = std::move(s.matrixVbo);
    
    vao = std::move(s.vao);
    
    drawParams = std::move(s.drawParams);
    
    textureList = std::move(s.textureList);
    
    return *this;
}

/*-------------------------------------
    Helper function to ensure all vertex attributes are setup properly.
-------------------------------------*/
void sceneNode::setVertexAttribs() {
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
    matrixVbo.bind();
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
    
    matrixVbo.unbind();
    
    LOG_GL_ERR();
}

/*-------------------------------------
 Release all resouces.
-------------------------------------*/
void sceneNode::terminate() {
    pMesh = nullptr;
    vao.terminate();
    matrixVbo.terminate();
    textureList.clear();
}

/*-------------------------------------
    Set the mesh to be used by this object during a draw operation.
-------------------------------------*/
bool sceneNode::init(const geometry& m) {
    // there's no telling what data might be pushed into the VAO. Get rid of it.
    vao.terminate();
    if (!vao.init()) {
        LS_LOG_ERR("Unable to create a drawModel for geometry ", m.getId(), '.');
        terminate();
        return false;
    }
    
    // vbos are resized when any new data is pushed into them
    if (matrixVbo.isValid() == false) {
        if (!matrixVbo.init()) {
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
    
    return true;
}

/*-------------------------------------
    All meshes support instanced draws by default. This will set the
    number of instances that will appear when drawing a mesh.
-------------------------------------*/
void sceneNode::setNumInstances(int instanceCount, const math::mat4* const modelMatrices) {
    LS_DEBUG_ASSERT(instanceCount > 0);
    matrixVbo.bind();
    matrixVbo.setData(sizeof(math::mat4)*instanceCount, modelMatrices, VBO_DYNAMIC_DRAW);
    matrixVbo.unbind();
    LOG_GL_ERR();
}

/*-------------------------------------
    Change the model matrix for a single instance
-------------------------------------*/
void sceneNode::modifyInstance(int index, const math::mat4& modelMatrix) {
    LS_DEBUG_ASSERT(index >= 0);
    matrixVbo.bind();
    matrixVbo.setSubData(sizeof(math::mat4)*index, sizeof(math::mat4), &modelMatrix);
    matrixVbo.unbind();
    LOG_GL_ERR();
}

/*-------------------------------------
    Render all instances of the currently bound mesh to OpenGL.
-------------------------------------*/
void sceneNode::draw() const {
    for (const texture* const pTex : textureList) {
        pTex->bind();
    }
    
    drawParams.draw(vao);
    
    for (const texture* const pTex : textureList) {
        pTex->unbind();
    }
}

} // end draw namespace
} // end ls namespace
