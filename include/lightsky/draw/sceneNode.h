/* 
 * File:   draw/sceneNode.h
 * Author: Miles Lacey
 *
 * Created on June 10, 2014, 10:07 PM
 */

#ifndef __LS_DRAW_SCENE_NODE_H__
#define	__LS_DRAW_SCENE_NODE_H__

#include <vector>

#include "lightsky/draw/vertexBuffer.h"
#include "lightsky/draw/geometry.h"
#include "lightsky/draw/texture.h"
#include "lightsky/draw/vertexArray.h"

namespace ls {
namespace draw {

/**
 * A sceneNode represents a single renderable mesh that can be drawn multiple
 * times by attaching both an mesh and a set of model matrices. The more model
 * matrices that are bound to a mesh model, the more instances will be rendered
 * by OpenGL.
 */
class sceneNode final {
    private:
        /**
         * @brief pMesh points to the mesh that should be drawn using *this.
         */
        const geometry* pMesh = nullptr;
        
        /**
         * Vertex Buffer that will be used specifically for model matrices.
         */
        vertexBuffer matrixVbo = {};
        
        /**
         * Vertex array to be used with this mesh object
         */
        vertexArray vao = {};
        
        /**
         * @brief Parameters used to draw instanced version of the mesh used by
         * *this.
         */
        drawCommand drawParams = {};
        
        /**
         * @brief textureList contains pointers to the textures which should be
         * applied when rendering this model's mesh.
         */
        std::vector<const texture*> textureList;
        
        /**
         * @brief Helper function to ensure all vertex attributes are setup
         * properly.
         */
        void setVertexAttribs();
        
    public:
        /**
         * @brief Default Constructor
         */
        sceneNode();
        
        /**
         * @brief Copy Constructor -- DELETED
         */
        sceneNode(const sceneNode& mm) = delete;
        
        /**
         * @brief Move Constructor
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         * 
         * @param s
         * An R-Value reference to an meshModel that is about to go
         * out of scope.
         */
        sceneNode(sceneNode&& s);
        
        /**
         * @brief Destructor
         * 
         * Frees All memory and resources used by *this.
         */
        ~sceneNode();
        
        /**
         * @brief Copy Operator -- DELETED
         */
        sceneNode& operator=(const sceneNode& s) = delete;
        
        /**
         * @brief Move Operator
         * 
         * Moves all data from the input parameter into *this.
         * 
         * @param s
         * An R-Value reference to an meshModel that is about to go
         * out of scope.
         * 
         * @return A reference to *this.
         */
        sceneNode& operator=(sceneNode&& s);
        
        /**
         * @brief Get the GPU-Assigned ID associated with this mesh model.
         * 
         * This ID is directly correlated to the VAO which holds all model
         * matrices and vertex data for the mesh bound to *this.
         * 
         * @return An unsigned integral type representing a unique ID for this
         * mesh model.
         */
        unsigned getId() const;
        
        /**
         * @brief Determine if *this is renderable to the currently bound
         * framebuffer.
         * 
         * @return TRUE if *this contains a valid vertex buffer and renderable
         * geometry, FALSE if not.
         */
        bool isValid() const;
        
        /**
         * @brief Set the mesh and texture to be used by this object during a
         * draw operation.
         * 
         * @param g
         * A const reference to valid OpenGL-managed vertices.
         * 
         * @return TRUE if the mesh was successfully loaded with a VBO assigned
         * to handle model matrices, FALSE if otherwise.
         */
        bool init(const geometry& g);
        
        /**
         * @brief Clear all draw parameters to their default, null values and
         * free any allocated resources used by *this.
         * 
         * This method will also terminate any internal VAO and VBO objects
         * that are used internally.
         */
        void terminate();
        
        /**
         * @brief Determine if *this sceneNode contains a reference to any
         * geometry.
         * 
         * @return TRUE if *this has a valid pointer to some geometry, FALSE
         * if not.
         */
        bool hasGeometry() const;
        
        /**
         * @brief Get the mesh that is currently used by this model
         * 
         * @return a const reference to the mesh used by *this.
         */
        const geometry* getGeometry() const;
        
        
        /**
         * @brief Get the number of textures used by *this.
         * 
         * @return An unsigned integral type containin the amount of textures
         * used by *this.
         */
        unsigned getNumTextures() const;
        
        
        /**
         * @brief Get the textures that are currently used by this model
         * 
         * @return A const reference to the list of textures used by *this.
         */
        const std::vector<const texture*>& getTextures() const;
        
        /**
         * @brief Add a texture to be used by *this during a draw operation.
         * 
         * @param texRef
         * A const reference to a texture
         */
        void addTexture(const texture& texRef);
        
        /**
         * @brief Remove a texture from the list used by *this during a draw
         * operation.
         * 
         * @param texIndex
         * An index value to the texture in *this to be removed.
         */
        void removeTexture(const texture& texRef);
        
        /**
         * @brief All meshes support instanced draws by default. This will set
         * the number of instances that will appear when drawing a mesh.
         * 
         * @param instanceCount
         * The number of instances (and modelMatrices) that will be drawn by
         * this mesh.
         * 
         * @param modelMatrices
         * A pointer to an array of model matrices that will be applied to each
         * mesh instance.
         */
        void setNumInstances(int instanceCount, const math::mat4* const modelMatrices = nullptr);
        
        /**
         * @brief Change the model matrix for a single instance
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
         * @brief Determine if this current model is able to be rendered.
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

#include "lightsky/draw/generic/sceneNode_impl.h"

#endif	/* __LS_DRAW_SCENE_NODE_H__ */
