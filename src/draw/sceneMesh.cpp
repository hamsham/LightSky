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
 Destructor
-------------------------------------*/
sceneMesh::~sceneMesh() {
    terminate();
}

/*-------------------------------------
    Constructor
-------------------------------------*/
sceneMesh::sceneMesh() {
}

/*-------------------------------------
    Copy Constructor
-------------------------------------*/
/*
sceneMesh::sceneMesh(const sceneMesh& m) {
    this->operator=(m);
}
*/

/*-------------------------------------
    Move Constructor
-------------------------------------*/
sceneMesh::sceneMesh(sceneMesh&& m) :
    pGeometry{m.pGeometry},
    vao{std::move(m.vao)},
    submeshIndices{m.submeshIndices.first, m.submeshIndices.count},
    textureList{std::move(m.textureList)}
{
    m.pGeometry = nullptr;
    m.submeshIndices = {0, 0};
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
sceneMesh& sceneMesh::operator=(sceneMesh&& m) {
    pGeometry = m.pGeometry;
    m.pGeometry = nullptr;
    
    vao = std::move(m.vao);
    
    submeshIndices = std::move(m.submeshIndices);
    m.submeshIndices = {0, 0};
    
    textureList = std::move(m.textureList);
    
    return *this;
}

/*-------------------------------------
 * Copy Operator
-------------------------------------*/
/*
sceneMesh& sceneMesh::operator=(const sceneMesh& m) {
    terminate();
    
    if (&m == this || !m.getId() || !m.getGeometry()) {
        return *this;
    }
    
    if (!init(*m.pGeometry)) {
        return *this;
    }
    
    submeshIndices = m.submeshIndices;
    textureList = m.textureList;
    
    return *this;
}
*/

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
    
    vao.unbind();
    
    pGeometry->getVertexBuffer().unbind();
    pGeometry->getIndexBuffer().unbind();
    
    LOG_GL_ERR();
}

/*-------------------------------------
 Release all resouces.
-------------------------------------*/
void sceneMesh::terminate() {
    pGeometry = nullptr;
    vao.terminate();
    submeshIndices = {0, 0};
    textureList.clear();
}

/*-------------------------------------
    Set the mesh to be used by this object during a draw operation.
-------------------------------------*/
bool sceneMesh::init(const geometry& g) {
    // there's no telling what data might be pushed into the VAO. Get rid of it.
    terminate();
    
    if (!vao.init()) {
        LS_LOG_ERR("Unable to create a drawModel for geometry ", g.getId(), '.');
        terminate();
        return false;
    }
    
    pGeometry = &g;
    submeshIndices = g.getDrawCommand().indices;
    
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
    LS_DEBUG_ASSERT(texIndex < textureList.size());
    textureList.erase(textureList.begin() + texIndex);
}

/*-------------------------------------
    Render all textured geometry of the currently bound mesh to OpenGL.
-------------------------------------*/
void sceneMesh::draw() const {
    LS_DEBUG_ASSERT(this->isValid());
    
    LOG_GL_ERR();
    
    if (textureList.size()) {
        for (const texture* const pTex : textureList) {
            pTex->bind();
        }

        drawCommand tempCommand = pGeometry->getDrawCommand();
        tempCommand.indices = submeshIndices;
        tempCommand.draw(vao);

        for (const texture* const pTex : textureList) {
            pTex->unbind();
        }
    }
    else {
        drawCommand tempCommand = pGeometry->getDrawCommand();
        tempCommand.indices = submeshIndices;
        tempCommand.draw(vao);
    }
}

} // end draw namespace
} // end ls namespace
