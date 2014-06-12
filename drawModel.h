/* 
 * File:   DrawModel.h
 * Author: miles
 *
 * Created on June 10, 2014, 10:07 PM
 */

#ifndef __LS_DRAWMODEL_H__
#define	__LS_DRAWMODEL_H__

#include "bufferObject.h"
#include "mesh.h"
#include "texture.h"
#include "vertexArray.h"

class drawModel final {
    private:
        mesh* pMesh;
        texture* pTexture;
        
        /**
         * Counter of the number of instances that are currently reserved for
         * drawing in the vao & vbo. This is also a cound of the number of model
         * matrices that are held within the vbo.
         */
        int numInstances = 1;
        
        /**
         * Vertex Buffer that will be used specifically for model matrices.
         */
        vertexBuffer modelVbo = {};
        
        /**
         * Vertex array to be used with this mesh object
         */
        vertexArray vao = {};
        
        /**
         * Helper function to ensure all vertex attributes are setup properly.
         */
        void setVertexAttribs(const mesh* const);
        
    public:
        constexpr drawModel() {}
        drawModel(const drawModel&);
        drawModel(drawModel&&);
        
        ~drawModel() {
            reset();
        }
        
        drawModel& operator=(const drawModel&);
        drawModel& operator=(drawModel&&);
        
        /**
         * Get an general identification to be used for this object
         */
        inline unsigned getId() const {
            return vao.getId();
        }
        
        /**
         * Reset all draw parameters to their default, null, values
         */
        void reset();
        
        /**
         * Get the mesh that is currently used by this model
         * 
         * @return a pointer to the mesh used by *this.
         * The return value can be NULL.
         */
        inline mesh* getMesh() const {
            return pMesh;
        }
        
        /**
         * Set the mesh to be used by this object during a draw operation.
         * 
         * @param a const pointer to a const mesh
         */
        inline bool setMesh(const mesh* const);
        
        /**
         * Get the texture that is currently used by this model
         * 
         * @return a pointer to the texture used by *this.
         * The return value can be NULL.
         */
        inline texture* getTexture() const {
            return pMesh;
        }
        
        /**
         * Set the texture to be used by this object during a draw operation.
         * 
         * @param a const pointer to a const texture
         */
        inline void setTexture(const texture* const);
        
        /**
         * Get the number of instances that will be rendered when a call to
         * "draw()" is made.
         * 
         * @return the number of meshes/model matrices rendered by/with this
         * mesh.
         */
        int getNumInstances() const {
            return numInstances;
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

inline void drawModel::draw() const {
    const draw_mode dm = pMesh->getDrawMode();
    const unsigned numVerts = pMesh->getNumVertices();
    
    vao.bind();
    glDrawArraysInstanced(dm, 0, numVerts, numInstances);
    vao.unbind();
}

inline void drawModel::drawSubMesh(int startPos, int endPos) const {
    vao.bind();
    glDrawArraysInstanced(pMesh->getDrawMode(), startPos, endPos, numInstances);
    vao.unbind();
}

#endif	/* __LS_DRAWMODEL_H__ */

