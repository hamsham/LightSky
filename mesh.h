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
    /**
     * Allow the mesh resource class to load vertices directly into a mesh.
     */
    friend class meshResource;
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
         * Vertex Buffer that will be used specifically for model matrices.
         */
        vertexBuffer modelVbo;
        
        /**
         * Member to help determine the number of vertices contained within a
         * mesh object.
         */
        unsigned numVertices = 0;
        
        /**
         * Counter of the number of instances that are currently reserved for
         * drawing in the vao & vbo. This is also a cound of the number of model
         * matrices that are held within the vbo.
         */
        unsigned numInstances = 1;
        
        /**
         * Helper function to ensure that the vao/vbo combos are loaded.
         */
        bool initVertices(unsigned numVerts);
        
        /**
         * Helper function to ensure all vertex attributes are setup properly.
         */
        void setVertexAttribs();
        
    public:
        /**
         * Constructor
         */
        constexpr mesh() :
            vao{},
            vbo{},
            numVertices{},
            numInstances{}
        {}
        
        /**
         * Copy Constructor -- DELETED
         */
        mesh(const mesh&) = delete;
        
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
        mesh& operator=(const mesh&) = delete;
        
        /**
         * Move Operator
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        mesh& operator=(mesh&&);
        
        /**
         * Get an general identification to be used for this object
         */
        inline unsigned getId() const {
            return vbo.getId();
        }
        
        /**
         * Send a loaded mesh to the GPU
         * @param ml
         * A mesh loader that contains raw vertex data in memory.
         */
        bool init(const meshResource& mr);
        
        /**
         * Unload all GPU-based resource that are used by *this;
         */
        void terminate() {
            vao.terminate();
            vbo.terminate();
            modelVbo.terminate();
            numVertices = 0;
            numInstances = 1;
        }
        
        /**
         * All meshes support instanced draws by default. This will set the
         * number of instances that will appear when drawing a mesh.
         * 
         * @param instanceCount
         * The number of instances (and modelMatrices) that will be drawn by
         * this mesh.
         * 
         * @param modelMatrices
         * A pointer to an array of model matrices that will be applied to each
         * mesh instance.
         */
        void setNumInstances(int instanceCount, const math::mat4* const modelMatrices);
        
        /**
         * Change the model matrix for a single instance
         * 
         * @param index
         * @param modelMatrix
         */
        void modifyInstance(int index, const math::mat4& modelMatrix);
        
        /**
         * Get the number of instances that will be rendered when a call to
         * "draw()" is made.
         * 
         * @return the number of meshes/model matrices rendered by/with this
         * mesh.
         */
        unsigned getNumInstances() const {
            return numInstances;
        }
        
        /**
         * Draw a mesh
         * 
         * This method renders a mesh to the currently bound framebuffer.
         */
        void draw() const;
        
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
         */
        void drawSubMesh(int startPos, int endPos) const;
};

inline void mesh::draw() const {
    vao.bind();
    glDrawArraysInstanced(LS_TRIANGLES, 0, numVertices, numInstances);
    vao.unbind();
}

inline void mesh::drawSubMesh(int startPos, int endPos) const {
    vao.bind();
    glDrawArraysInstanced(LS_TRIANGLES, startPos, endPos, numInstances);
    vao.unbind();
}

#endif	/* __LS_MESH_H__ */

