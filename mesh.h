/* 
 * File:   mesh.h
 * Author: miles
 *
 * Created on April 6, 2014, 12:36 AM
 */

#ifndef __LS_MESH_H__
#define	__LS_MESH_H__

#include <cstdint>

#include "main.h"
#include "bufferObject.h"
#include "renderer.h"
#include "vertexArray.h"
#include "vertex.h"

class meshResource;

/**
 * A mesh object contains information about the layout of vertex data located on
 * the GPU.
 * 
 * Designed to be used directly with OpenGL.
 */
class mesh {
    private:
        /**
         * Vertex array to be used with this mesh object
         */
        vertexArray vao;
        
        /**
         * Vertex Buffer Object to be used with this mesh
         */
        vertexBuffer vbo;
        
        /**
         * Member to help determine the number of vertices contained within a
         * mesh object.
         */
        unsigned numVertices = 0;
        
    public:
        /**
         * Constructor
         */
        constexpr mesh() :
            vao{},
            vbo{}
        {}
        
        /**
         * Copy Constructor -- DELETED
         */
        mesh(const mesh&);
        
        /**
         * Move Constructor.
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        mesh(mesh&&);
        
        /**
         * Destructor
         * Unloads all resources used by *this.
         */
        ~mesh() {
            terminate();
        }
        
        /**
         * Copy Operator -- DELETED
         */
        mesh& operator=(const mesh&);
        
        /**
         * Move Operator
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        mesh& operator=(mesh&&);
        
        /**
         * Send a loaded mesh to the GPU
         * @param ml
         * A mesh loader that contains raw vertex data in memory.
         * 
         * @param vertexTypes
         * A bitfield containing the types of vertices that were requested to
         * be loaded.
         */
        bool init(const meshResource& mr, unsigned meshIndex);
        
        /**
         * Unload all GPU-based resource that are used by *this;
         */
        void terminate() {
            vbo.terminate();
            vao.terminate();
            numVertices = 0;
        }
        
        /**
         * Draw a mesh
         * 
         * @param startPos
         * indicates the starting offset to the the mesh contained within *this
         * that should be drawn.
         * 
         * @param endPos
         * indicates the offset to the final sub-mesh contained within *this
         * that should be drawn.
         * 
         * @param instanceCount - determines the number of instances that
         * need to be drawn at runtime.
         */
        void draw(int instanceCount = 1) const;
        
        /**
         * Draw a single part of the total sub-meshes contained within *this.
         * This function already takes the vertex counts into account.
         * 
         * @param startPos
         * indicates the starting offset to the the mesh contained within *this
         * that should be drawn.
         * 
         * @param endPos
         * indicates the offset to the final sub-mesh contained within *this
         * that should be drawn.
         * 
         * @param instanceCount - determines the number of instances that
         * need to be drawn at runtime.
         */
        void drawSubMesh(int startPos, int endPos, int instanceCount = 1) const;
};

inline void mesh::draw(int instanceCount) const {
    vao.bind();
    glDrawArraysInstanced(LS_TRIANGLES, 0, numVertices, instanceCount);
    vao.unbind();
}

inline void mesh::drawSubMesh(int startPos, int endPos, int instanceCount) const {
    vao.bind();
    glDrawArraysInstanced(LS_TRIANGLES, startPos, endPos, instanceCount);
    vao.unbind();
}

#endif	/* __LS_MESH_H__ */

