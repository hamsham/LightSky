/* 
 * File:   lsDrawModel.h
 * Author: miles
 *
 * Created on June 10, 2014, 10:07 PM
 */

#ifndef __LS_DRAW_MODEL_H__
#define	__LS_DRAW_MODEL_H__

#include "lsBufferObject.h"
#include "lsMesh.h"
#include "lsTexture.h"
#include "lsVertexArray.h"

/**
 * A draw model represents a single renderable mesh that can be drawn multiple
 * times by attaching both an lsMesh and a set of model matrices. The more model
 * matrices that are bound to a draw model, the more instances will be rendered
 * by OpenGL.
 */
class lsDrawModel final {
    private:
        /**
         * The default texture for a mesh. This texture is used upon
         * initializing a mesh so that it can be rendered without error.
         */
        static lsTexture defaultTex;
        
        /**
         * Initialization method for the default texture.
         * 
         * @return TRUE if the default texture was initialized properly, FALSE
         * if not.
         */
        static bool initDefaultTexture();
        
    public:
        /**
         * Get the default texture used by freshly loaded models.
         * 
         * @return A constant reference to the default model texture
         */
        const lsTexture& getDefaultTexture() const;
        
    private:
        /**
         * A pointer to the mesh that should be drawn using this model.
         * The "draw" methods should NOT be called if this is null.
         */
        lsMesh* pMesh = nullptr;
        
        /**
         * A pointer to the texture that should be applied when rendering this
         * model's mesh.
         * The "draw" methods should NOT be called if this is null.
         */
        const lsTexture* pTexture = nullptr;
        
        /**
         * Counter of the number of instances that are currently reserved for
         * drawing in the vao & vbo. This is also a cound of the number of model
         * matrices that are held within the vbo.
         */
        int numInstances = 1;
        
        /**
         * Vertex Buffer that will be used specifically for model matrices.
         */
        lsVertexBuffer modelVbo = {};
        
        /**
         * Vertex array to be used with this mesh object
         */
        lsVertexArray vao = {};
        
        /**
         * Helper function to ensure all vertex attributes are setup properly.
         */
        void setVertexAttribs();
        
    public:
        /**
         * Default Constructor
         */
        lsDrawModel();
        
        /**
         * Copy Constructor -- DELETED
         */
        lsDrawModel(const lsDrawModel&) = delete;
        
        /**
         * Move Constructor
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         * 
         * @param An R-Value reference to an lsDrawModel that is about to go
         * out of scope.
         */
        lsDrawModel(lsDrawModel&&);
        
        /**
         * Destructor
         * 
         * Frees All memory and resources used by *this.
         */
        ~lsDrawModel();
        
        /**
         * Copy Operator -- DELETED
         */
        lsDrawModel& operator=(const lsDrawModel&) = delete;
        
        /**
         * Move Operator
         * 
         * Moves all data from the input parameter into *this.
         * 
         * @param An R-Value reference to an lsDrawModel that is about to go
         * out of scope.
         * 
         * @return A reference to *this.
         */
        lsDrawModel& operator=(lsDrawModel&&);
        
        /**
         * Get the GPU-Assigned ID associated with this draw model. This ID is
         * directly correlated to the VAO which holds all model matrices and
         * vertex data for the mesh bound to *this.
         * 
         * @return An unsigned integral type representing a unique ID for this
         * draw model.
         */
        unsigned getId() const;
        
        /**
         * Set the mesh to be used by this object during a draw operation.
         * 
         * @param a const reference to an lsMesh
         * 
         * @return TRUE if the mesh was successfully loaded with a VBO assigned
         * to handle model matrices, FALSE if otherwise.
         */
        bool init(lsMesh&);
        
        /**
         * Set the mesh and texture to be used by this object during a draw
         * operation.
         * 
         * @param a const reference to an lsMesh
         * 
         * @param A cconst reference to an lsTexture
         * 
         * @return TRUE if the mesh was successfully loaded with a VBO assigned
         * to handle model matrices, FALSE if otherwise.
         */
        bool init(lsMesh&, lsTexture&);
        
        /**
         * Clear all draw parameters to their default, null values and free any
         * allocated resources used by *this.
         * 
         * This method will also terminate any internal VAO and VBO objects
         * that are used internally.
         */
        void terminate();
        
        /**
         * Get the mesh that is currently used by this model
         * 
         * @return a const reference to the mesh used by *this.
         */
        const lsMesh& getMesh() const;
        
        /**
         * Get the texture that is currently used by this model
         * 
         * @return A const reference to a texture object.
         */
        const lsTexture& getTexture() const;
        
        /**
         * Set the texture ID to be used by this object during a draw operation.
         * 
         * @param a const reference to a texture
         */
        void setTexture(const lsTexture&);
        
        /**
         * Get the number of instances that will be rendered when a call to
         * "draw()" is made.
         * 
         * @return the number of meshes/model matrices rendered by/with this
         * mesh.
         */
        int getNumInstances() const;
        
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
         * Determine if this current model is able to be rendered.
         * 
         * @return TRUE if both the current mesh and current texture point to
         * non-null, objects.
         */
        bool canDraw() const;
        
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

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/*
 * Get the default texture used by freshly loaded models.
 */
inline const lsTexture& lsDrawModel::getDefaultTexture() const {
    return defaultTex;
}

/*
 * Get the GPU-Assigned ID associated with this draw model.
 */
inline unsigned lsDrawModel::getId() const {
    return vao.getId();
}

/*
 * Set the mesh and texture to be used by this object during a draw
 * operation.
 */
inline bool lsDrawModel::init(lsMesh& m, lsTexture& t) {
    if (!init(m)) {
        return false;
    }
    pTexture = &t;
    return true;
}

/*
 * Get the mesh that is currently used by this model
 */
inline const lsMesh& lsDrawModel::getMesh() const {
    return *pMesh;
}

/*
 * Get the texture that is currently used by this model
 */
inline const lsTexture& lsDrawModel::getTexture() const {
    return *pTexture;
}

/*
 * Set the texture ID to be used by this object during a draw operation.
 */
inline void lsDrawModel::setTexture(const lsTexture& tex) {
    pTexture = &tex;
}

/*
 * Get the number of instances that will be rendered when a call to
 * "draw()" is made.
 */
inline int lsDrawModel::getNumInstances() const {
    return numInstances;
}

/*
 * Determine if this current model is able to be rendered.
 */
inline bool lsDrawModel::canDraw() const {
    return pMesh != nullptr && pTexture != nullptr;
}

/*
 * Render all instances of the currently bound mesh to OpenGL.
 */
inline void lsDrawModel::draw() const {
    pTexture->bind();
    vao.bind();
    glDrawArraysInstanced(pMesh->getDrawMode(), 0, pMesh->getNumVertices(), numInstances);
    vao.unbind();
    pTexture->unbind();
}

/*
 * Render an instanced set of sub-meshes
 */
inline void lsDrawModel::drawSubMesh(int startPos, int endPos) const {
    pTexture->bind();
    vao.bind();
    glDrawArraysInstanced(pMesh->getDrawMode(), startPos, endPos, numInstances);
    vao.unbind();
    pTexture->unbind();
}

#endif	/* __LS_DRAW_MODEL_H__ */

