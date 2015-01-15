/* 
 * File:   mesh.cpp
 * Author: hammy
 * 
 * Created on January 14, 2015, 9:02 PM
 */

#include <utility> // std::move

#include "lightsky/draw/sceneMesh.h"

namespace ls {
namespace draw {

/*-------------------------------------
    Constructor
-------------------------------------*/
sceneMesh::sceneMesh() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
sceneMesh::sceneMesh(sceneMesh&& m) :
    numInstances{m.numInstances},
    pGeometry{m.pGeometry},
    matrixVbo{std::move(m.matrixVbo)},
    vao{std::move(m.vao)},
    submeshIndices{std::move(m.submeshIndices)},
    textureList{std::move(m.textureList)}
{
    m.numInstances = 0;
    m.pGeometry = nullptr;
    m.submeshIndices = {};
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
sceneMesh& sceneMesh::operator=(sceneMesh&& m) {
    numInstances = m.numInstances;
    m.numInstances = 0;
    
    pGeometry = m.pGeometry;
    m.pGeometry = nullptr;
    
    matrixVbo = std::move(m.matrixVbo);
    
    vao = std::move(m.vao);
    
    submeshIndices = std::move(m.submeshIndices);
    m.submeshIndices = {};
    
    textureList = std::move(m.textureList);
    
    return *this;
}

/*-------------------------------------
    Helper function to ensure all vertex attributes are setup properly.
-------------------------------------*/
void sceneMesh::setVertexAttribs() {
    vao.bind();
    
    pGeometry->getVertexBuffer().bind();
    pGeometry->getIndexBuffer().bind();
    
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
    
    pGeometry->getVertexBuffer().unbind();
    pGeometry->getIndexBuffer().unbind();
    
    matrixVbo.unbind();
    
    LOG_GL_ERR();
}

/*-------------------------------------
 Release all resouces.
-------------------------------------*/
void sceneMesh::terminate() {
    numInstances = 0;
    pGeometry = nullptr;
    vao.terminate();
    matrixVbo.terminate();
    textureList.clear();
}

/*-------------------------------------
    Set the mesh to be used by this object during a draw operation.
-------------------------------------*/
bool sceneMesh::init(const geometry& g) {
    // there's no telling what data might be pushed into the VAO. Get rid of it.
    vao.terminate();
    if (!vao.init()) {
        LS_LOG_ERR("Unable to create a drawModel for geometry ", g.getId(), '.');
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
    
    pGeometry = &g;
    submeshIndices.first = g.getDrawCommand().first;
    submeshIndices.count = g.getDrawCommand().count;
    
    const math::mat4 identity{1.f};
    setNumInstances(1, &identity);
    
    setVertexAttribs();
    
    return true;
}

/*-------------------------------------
    Get the texture that is currently used by this model
-------------------------------------*/
unsigned sceneMesh::getNumTextures() const {
    return textureList.size();
}

/*-------------------------------------
    Get the texture that is currently used by this model
-------------------------------------*/
const std::vector<const texture*>& sceneMesh::getTextures() const {
    return textureList;
}

/*-------------------------------------
    Set the texture ID to be used by this object during a draw operation.
-------------------------------------*/
void sceneMesh::addTexture(const texture& texRef) {
    if (!texRef.isValid()) {
        return;
    }
    
    for (const texture* const pTex : textureList) {
        if (pTex == &texRef) {
            return;
        }
    }
    textureList.push_back(&texRef);
}

/*-------------------------------------
    Remove a texture from *this.
-------------------------------------*/
void sceneMesh::removeTexture(unsigned texIndex) {
    LS_DEBUG_ASSERT(texIndex < textureList.size);
    textureList.erase(textureList.begin() + texIndex);
}

/*-------------------------------------
    All meshes support instanced draws by default. This will set the
    number of instances that will appear when drawing a mesh.
-------------------------------------*/
void sceneMesh::setNumInstances(int instanceCount, const math::mat4* const modelMatrices) {
    LS_DEBUG_ASSERT(instanceCount > 0);
    matrixVbo.bind();
    matrixVbo.setData(sizeof(math::mat4)*instanceCount, modelMatrices, VBO_DYNAMIC_DRAW);
    matrixVbo.unbind();
    LOG_GL_ERR();
    
    numInstances = instanceCount;
}

/*-------------------------------------
    Change the model matrix for a single instance
-------------------------------------*/
void sceneMesh::modifyInstance(int index, const math::mat4& modelMatrix) {
    LS_DEBUG_ASSERT(index >= 0);
    LS_DEBUG_ASSERT(index < instanceCount);
    
    matrixVbo.bind();
    matrixVbo.setSubData(sizeof(math::mat4)*index, sizeof(math::mat4), &modelMatrix);
    matrixVbo.unbind();
    LOG_GL_ERR();
}

/*-------------------------------------
    Render all instances of the currently bound mesh to OpenGL.
-------------------------------------*/
void sceneMesh::draw() const {
    LS_DEBUG_ASSERT(this->isValid);
    
    for (const texture* const pTex : textureList) {
        pTex->bind();
    }
    
    drawCommand tempCommand = pGeometry->getDrawCommand();
    tempCommand.first = submeshIndices.first;
    tempCommand.count = submeshIndices.count;
    tempCommand.draw(vao, numInstances);
    
    for (const texture* const pTex : textureList) {
        pTex->unbind();
    }
}

} // end draw namespace
} // end ls namespace
