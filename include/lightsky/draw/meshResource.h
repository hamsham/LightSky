/* 
 * File:   draw/meshResource.h
 * Author: Miles Lacey
 *
 * Created on April 2, 2014, 9:04 PM
 */

#ifndef __LS_DRAW_MESH_RESOURCE_H__
#define	__LS_DRAW_MESH_RESOURCE_H__

#include <string>
#include <unordered_map>

#include "lightsky/utils/resource.h"

#include "lightsky/draw/atlas.h"
#include "lightsky/draw/boundingBox.h"
#include "lightsky/draw/drawCommand.h"
#include "lightsky/draw/sceneNode.h"
#include "lightsky/draw/setup.h"
#include "lightsky/draw/vertex.h"

struct aiScene;
struct aiMesh;
struct aiNode;

namespace ls {
namespace draw {

/**
 * The mesh resource can be used to load a mesh or meshes from a file. It can
 * also be used to generate basic primitives such as a sphere, cube, cone, etc.
 */
class meshResource final : public utils::resource {
    public:
        /**
         * @brief meshVertexMap_t
         *
         * Maps an ASSIMP mesh to its starting index/ending index pair within an
         * internal array of vertex indices. These index mappings will be used to
         * import a scene heirarchy.
         */
        typedef std::unordered_map<const aiMesh*, sceneNode*> meshMap_t;
        
    private:
        /**
         * Contains the number of vertices used per mesh.
         * This is implemented as a single array of unsigned integers.
         */
        unsigned numVertices = 0;
        
        /**
         * Contains the vertex data used by each mesh.
         * This is implemented as an array of vertex structures.
         */
        vertex* pVertices = nullptr;
        
        /**
         * Contains the number of indices used per mesh.
         * This is implemented as a single array of unsigned short integers.
         */
        unsigned numIndices = 0;
        
        /**
         * Contains the index data used to specify the location of each vertex
         * of each mesh. This is implemented as an array of unsigned short
         * integers.
         */
        draw_index_t* pIndices = nullptr;
        
        /**
         * Contains the resulting draw mode for each mesh after loading.
         */
        draw_mode_t resultDrawMode = draw_mode_t::DEFAULT;
        
        /**
         * Allow the ability to generate the bounding area for a mesh
         */
        boundingBox meshBounds = {};
        
        /**
         * @brief Initialize
         * 
         * This method initializes an internal buffer of vertices for loaded
         * and generated meshes.
         * 
         * @param vertCount
         * This parameter sets the number of vertices which should be allocated
         * into the internal vertex buffer. All data  is contained on CPU-side
         * memory and is not sent to the GPU.
         * 
         * @return TRUE if the internal vertex buffer was successfully
         * allocated, or FALSE if not.
         */
        bool initVertices(unsigned vertCount, unsigned elementCount = 0);

        /**
         * @brief Create a scene node for a generated primitive in order to
         * create a default scene.
         *
         * This should be used at the very end of a mesh generation function in
         * order to properly set the number of vertices.
         *
         * @param name
         * A constant pointer to a constant null-terminated character string.
         * This name will be used to instantiate a generated mesh.
         *
         * @return A scene node containing enough information to create a
         * simple scene with a simple mesh primitive.
         */
        sceneNode createPrimitiveNode(const char* const name);

        /**
         * @brief Scan an ASSIMP scene and attempt to reserve all memory needed
         * to import it.
         *
         * @param pScene
         * A constant pointer to a constant ASSIMP scene.
         *
         * @param meshIndices
         * A mapping of assimp meshes to their indices within an internal scene
         * graph.
         *
         * @return TRUE if all memory required to import the scene was
         * successfully allocated, FALSE if not.
         */
        bool preprocessMeshData(const aiScene* const pScene, draw_index_list_t& meshIndices);

        /**
         * @brief importMeshData
         * Private method to retrieve data from a 3D mesh file using ASSIMP.
         * Make sure all internal data has been preallocated before calling
         * this method. All data attempted to be loaded using this function
         * will be unloaded if this function fails.
         *
         * @param pScene
         * A constant pointer to a constant aiScene structure.
         *
         * @param meshIndices
         * A mapping of assimp meshes to their indices within an internal scene
         * graph.
         *
         * @return TRUE if the mesh was successfully loaded from ASSIMP, FALSE
         * if not.
         */
        bool importMeshData(const aiScene* const pScene, draw_index_list_t& meshIndices);

        /**
         * @brief importMeshFaces
         *
         * Iterate through all faces of a given mesh and add the points on each
         * face to the internal array of vertex indices.
         *
         * @param pMesh
         * A constant pointer to a constant ASSIMP mesh.
         *
         * @param baseVertex
         * The mesh object's first vertex in the internal array of vertices.
         *
         * @param baseIndex
         * The mesh object's first index in the internal array of indices.
         *
         * @param meshIndices
         * A reference to the pair of indices, indicating the number of indices
         * that a single mesh uses, as well as the offset to it's position in
         * the internal array.
         */
        void importMeshFaces(
            const aiMesh* const pMesh,
            unsigned& baseVertex,
            unsigned& baseIndex,
            draw_index_pair_t& meshIndices
        );

        /**
         * @brief readNodeHeirarchy
         * Recursively reads and imports scene graph data from Assimp.
         *
         * @param pNode
         * A pointer to a node in an Assimp scene graph.
         *
         * @param meshMap
         * A map of meshes in a scene to their index values within the internal
         * geometry array.
         *
         * @param parentId
         * An index value of the parent sceneNode contained within an internal
         * array of nodes.
         *
         * @return The index of the the last child node recursively placed into
         * the scene node list.
         */
        unsigned readNodeHeirarchy(
            const aiNode* const pNode,
            const draw_index_list_t& meshMap,
            const unsigned parentId,
            const math::mat4& parentTransform = math::mat4{1.f}
        );
        
    public:
        /**
         * @brief Constructor
         * 
         * Initializes all members contained within *this.
         */
        meshResource();
        
        /**
         * @brief Copy Constructor -- DELETED
         */
        meshResource(const meshResource&) = delete;
        
        /**
         * @brief Move Constructor
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed during the operation.
         * 
         * @param r
         * An r-value reference to a temporary mesh resource object.
         */
        meshResource(meshResource&& r);
        
        /**
         * @brief Destructor
         * 
         * Unloads all data contain within *this.
         */
        virtual ~meshResource() override;
        
        /**
         * @brief Copy Constructor -- DELETED
         */
        meshResource& operator=(const meshResource&) = delete;
        
        /**
         * @brief Move Operator
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed during the operation.
         * 
         * @param r
         * An r-value reference to a temporary mesh resource object.
         * 
         * @return a reference to *this.
         */
        meshResource& operator=(meshResource&& r);

        /**
         *  Get the size, in bytes, of the stored vertex elements.
         *  
         *  @return a long integral type, used to determine how many bytes
         *  are used by the vertex buffer.
         */
        long getVertexByteSize() const;

        /**
         *  Get the size, in bytes, of the stored index elements.
         *  
         *  @return a long integral type, used to determine how many bytes
         *  are used by the index buffer.
         */
        long getIndexByteSize() const;
        
        /**
         * Get the number of loaded vertex variables in a mesh.
         * 
         * @return An unsigned integral type, representing the number of
         * vertices contained within the mesh loaded by *this.
         */
        unsigned getNumVertices() const;
        
        /**
         * Get the array of standard vertex types of a loaded mesh.
         * 
         * @return A pointer to the internal array which contains the vertices
         * loaded by *this.
         */
        const vertex* getVertices() const;
        
        /**
         * Get the number of loaded indices in a mesh.
         * 
         * @return An unsigned integral type, representing the number of
         * indices contained within the mesh loaded by *this.
         */
        unsigned getNumIndices() const;
        
        /**
         * Get the array of vertex element indices types of a loaded mesh.
         * 
         * @return A pointer to the internal array which contains the indices
         * loaded by *this.
         */
        const draw_index_t* getIndices() const;
        
        /**
         * @brief Unload
         * 
         * Free all memory used by *this.
         */
        virtual void unload() override;
        
        /**
         * Get the draw mode that was generated while loading a mesh.
         * 
         * @return The target draw mode for the currently loaded mesh.
         */
        draw_mode_t getDrawMode() const;
        
        /**
         * Get the maximum bounds of a loaded mesh.
         * 
         * @return A constant reference to an boundingBox object.
         */
        const boundingBox& getBoundingBox() const;
        
        /**
         * N-Sided polygon primitive loading method
         * 
         * @param numPoints
         * The number of points that the polygon should contain. This number
         * must be greater than 1.
         * 
         * @return
         * TRUE if the function loaded the mesh correctly, or
         * FALSE if an error occurred during the load.
         */
        bool loadPolygon(unsigned numPoints = 3);
        
        /**
         * Triangle primitive loading method
         * 
         * @return
         * TRUE if the function loaded the mesh correctly, or
         * FALSE if an error occurred during the load.
         * 
         * Triangle texture coordinates are as follows:
         * 
         * |----1---|
         * |   /\   |
         * |  /  \  |
         * | /    \ |
         * 0/______\2
         */
        bool loadTriangle();
        
        /** 
         * Load a set of vertices representing a square/quad.
         * 
         * @return
         * TRUE if the function loaded the mesh correctly, or
         * FALSE if an error occurred during the load.
         */
        bool loadQuad();
        
        /**
         * Load a set of vertices representing a circle.
         * 
         * @return
         * TRUE if the function loaded the mesh correctly, or
         * FALSE if an error occurred during the load.
         */
        bool loadCircle(unsigned numPoints = 5);
        
        /**
         * Load a set of vertices representing a cube.
         * 
         * @return
         * TRUE if the function loaded the mesh correctly, or
         * FALSE if an error occurred during the load.
         */
        bool loadCube();
        
        /**
         * Load a set of vertices representing a cylinder.
         * 
         * @return
         * TRUE if the function loaded the mesh correctly, or
         * FALSE if an error occurred during the load.
         */
        bool loadCylinder(unsigned numSides = 2);
        
        /**
         * Load a set of vertices representing a cone.
         * 
         * @return
         * TRUE if the function loaded the mesh correctly, or
         * FALSE if an error occurred during the load.
         */
        bool loadCone(unsigned numSides = 2);
        
        /**
         * Load a set of vertices representing a sphere.
         * 
         * @return
         * TRUE if the function loaded the mesh correctly, or
         * FALSE if an error occurred during the load.
         */
        bool loadSphere(unsigned resolution);

        /**
         * @brief Load a 3D mesh file -- NOT YET IMPLEMENTED.
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be loadable into memory.
         * 
         * @return true if the file was successfully loaded. False if not.
         */
        bool loadFile(const std::string& filename) override;

        /**
         * @brief Save a mesh to a file -- NOT YET IMPLEMENTED
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const std::string&) const override;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/meshResource_impl.h"

#endif	/* __LS_DRAW_MESH_RESOURCE_H__ */

