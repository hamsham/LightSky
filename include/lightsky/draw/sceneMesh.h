/* 
 * File:   sceneMesh.h
 * Author: Miles
 *
 * Created on January 14, 2015, 9:02 PM
 */

#ifndef __LS_DRAW_SCENE_MESH_H__
#define	__LS_DRAW_SCENE_MESH_H__

#include <vector>

#include "lightsky/draw/geometry.h"
#include "lightsky/draw/texture.h"
#include "lightsky/draw/vertexArray.h"

namespace ls {
namespace draw {

/**
 */
class sceneMesh {
    private:
        /**
         * @brief pMesh points to the mesh that should be drawn using *this.
         */
        const geometry* pGeometry = nullptr;
        
        /**
         * Vertex array to be used with this mesh object
         */
        vertexArray vao = {};
        
        /**
         * @brief submeshIndices sets the specific indices of "pGeometry" that
         * will be rendered.
         */
        draw_index_pair_t submeshIndices = {};
        
        /**
         * @brief pTextures contains pointers to the textures which should be
         * applied when rendering *this.
         */
        std::vector<const texture*> textureList;
        
        /**
         * @brief Helper function to ensure all VAO attributes are setup
         * properly.
         */
        void setVertexAttribs();
    
    public:
        /**
         * @brief Destructor
         * 
         * Releases all memory contained within *this.
         */
        ~sceneMesh();
        
        /**
         * @brief Constructor
         */
        sceneMesh();
        
        /**
         * @brief Copy Constructor
         * 
         * This copies the reference to the geometry contained within the input
         * parameter and duplicates its matrix buffer.
         * 
         * @param m
         * A constant reference to another sceneMesh object.
         */
        sceneMesh(const sceneMesh& m);
        
        /**
         * @brief Move Constructor
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         * 
         * @param m
         * An R-Value reference to an mesh that is about to go out of scope.
         */
        sceneMesh(sceneMesh&& m);
        
        /**
         * @brief Copy Operator
         * 
         * This copies the reference to the geometry contained within the input
         * parameter and duplicates its matrix buffer.
         * 
         * @param m
         * A constant reference to another sceneMesh object.
         * 
         * @return A reference to *this.
         */
        sceneMesh& operator=(const sceneMesh& m);
        
        /**
         * @brief Move Operator
         * 
         * Moves all data from the input parameter into *this.
         * 
         * @param m
         * An R-Value reference to a mesh that is about to go out of scope.
         * 
         * @return A reference to *this.
         */
        sceneMesh& operator=(sceneMesh&& m);
        
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
         * @brief Set the geometry to be used by *this object during a draw
         * operation.
         * 
         * @param g
         * A constant reference to valid OpenGL-managed vertices.
         * 
         * @return TRUE if the mesh was successfully loaded with a VAO, FALSE
         * if something went wrong during initialization..
         */
        bool init(const geometry& g);
        
        /**
         * @brief Set the specific vertices to be rendered from "pGeometry."
         * 
         * @param indices
         * A draw_index_pair_t, determining the subset of vertices in
         * "pGeometry" which will be used by *this during each call to "draw()."
         */
        void setIndices(const draw_index_pair_t& indices);
        
        /**
         * @brief Set the specific vertices to be rendered from "pGeometry."
         * 
         * @return A draw_index_pair_t, determining the subset of vertices in
         * "pGeometry" which are used by *this during each call to "draw()."
         */
        const draw_index_pair_t& getIndices() const;
        
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
        void removeTexture(unsigned texIndex);
        
        /**
         * @brief Determine if this current model is able to be rendered.
         * 
         * @return TRUE if both the current mesh and current texture point to
         * non-null, objects.
         */
        bool canDraw() const;
        
        /**
         * @brief Draw a mesh using the geometry referenced by *this.
         * 
         * This method renders a mesh to the currently bound framebuffer.
         */
        void draw() const;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/sceneMesh_impl.h"

#endif	/* __LS_DRAW_SCENE_MESH_H__ */

