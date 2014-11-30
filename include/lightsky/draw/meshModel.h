/* 
 * File:   draw/meshModel.h
 * Author: Miles Lacey
 *
 * Created on June 10, 2014, 10:07 PM
 */

#ifndef __LS_DRAW_MESH_MODEL_H__
#define	__LS_DRAW_MESH_MODEL_H__

#include "lightsky/draw/vertexBuffer.h"
#include "lightsky/draw/geometry.h"
#include "lightsky/draw/texture.h"
#include "lightsky/draw/vertexArray.h"

namespace ls {
namespace draw {

/**
 * A meshModel represents a single renderable mesh that can be drawn multiple
 * times by attaching both an mesh and a set of model matrices. The more model
 * matrices that are bound to a mesh model, the more instances will be rendered
 * by OpenGL.
 */
class meshModel final {
    private:
        /**
         * A pointer to the mesh that should be drawn using this model.
         * The "draw" methods should NOT be called if this is null.
         */
        const geometry* pMesh = nullptr;
        
        /**
         * A pointer to the texture that should be applied when rendering this
         * model's mesh.
         * The "draw" methods should NOT be called if this is null.
         */
        const texture* pTexture = nullptr;
        
        /**
         * Vertex Buffer that will be used specifically for model matrices.
         */
        vertexBuffer modelVbo = {};
        
        /**
         * Vertex array to be used with this mesh object
         */
        vertexArray vao = {};
        
        /**
         * @brief Parameters used to draw instanced version of the mesh used by
         * *this.
         */
        drawCommand drawParams;
        
        /**
         * Helper function to ensure all vertex attributes are setup properly.
         */
        void setVertexAttribs();
        
    public:
        /**
         * @brief Default Constructor
         */
        meshModel();
        
        /**
         * Copy Constructor -- DELETED
         */
        meshModel(const meshModel& mm) = delete;
        
        /**
         * @brief Move Constructor
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         * 
         * @param mm
         * An R-Value reference to an meshModel that is about to go
         * out of scope.
         */
        meshModel(meshModel&& mm);
        
        /**
         * @brief Destructor
         * 
         * Frees All memory and resources used by *this.
         */
        ~meshModel();
        
        /**
         * Copy Operator -- DELETED
         */
        meshModel& operator=(const meshModel& mm) = delete;
        
        /**
         * @brief Move Operator
         * 
         * Moves all data from the input parameter into *this.
         * 
         * @param mm
         * An R-Value reference to an meshModel that is about to go
         * out of scope.
         * 
         * @return A reference to *this.
         */
        meshModel& operator=(meshModel&& mm);
        
        /**
         * Get the GPU-Assigned ID associated with this mesh model. This ID is
         * directly correlated to the VAO which holds all model matrices and
         * vertex data for the mesh bound to *this.
         * 
         * @return An unsigned integral type representing a unique ID for this
         * mesh model.
         */
        unsigned getId() const;
        
        /**
         * Set the mesh and texture to be used by this object during a draw
         * operation.
         * 
         * @param meshRef
         * A const reference to an mesh
         * 
         * @param texRef
         * A const reference to an texture
         * 
         * @return TRUE if the mesh was successfully loaded with a VBO assigned
         * to handle model matrices, FALSE if otherwise.
         */
        bool init(const geometry& meshRef, const texture& texRef);
        
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
        const geometry& getMesh() const;
        
        /**
         * Get the texture that is currently used by this model
         * 
         * @return A const reference to a texture object.
         */
        const texture& getTexture() const;
        
        /**
         * Set the texture ID to be used by this object during a draw operation.
         * 
         * @param texRef
         * A const reference to a texture
         */
        void setTexture(const texture& texRef);
        
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
         * The index to specify which model matrix in *this should be modified.
         * Model matrices are sent directly to an instance/array buffer on the
         * GPU.
         * 
         * @param modelMatrix
         * A constant reference to a model matrix which is to replace the one
         * on the GPU, specified by 'index.'
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
         * @brief Draw a mesh
         * 
         * This method renders a mesh to the currently bound framebuffer.
         */
        void draw() const;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/meshModel_impl.h"

#endif	/* __LS_DRAW_MESH_MODEL_H__ */
