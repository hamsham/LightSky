/* 
 * File:   draw/sceneResource.h
 * Author: Miles Lacey
 *
 * Created on April 2, 2014, 9:04 PM
 */

#ifndef __LS_DRAW_SCENE_RESOURCE_H__
#define	__LS_DRAW_SCENE_RESOURCE_H__

#include <string>
#include <vector>
#include <deque>
#include <map>

#include "lightsky/utils/resource.h"

#include "lightsky/draw/atlas.h"
#include "lightsky/draw/boundingBox.h"
#include "lightsky/draw/drawCommand.h"
#include "lightsky/draw/sceneNode.h"
#include "lightsky/draw/setup.h"
#include "lightsky/draw/texture.h"
#include "lightsky/draw/vertex.h"

struct aiScene;
struct aiMesh;
struct aiNode;
struct aiMaterial;

namespace ls {
namespace draw {

/**
 * The scene resource can be used to load a 3D scene from a file. It can also
 * be used to generate basic primitives such as a sphere, cube, cone, etc.
 */
class sceneResource final : public utils::resource {
    public:
        enum : unsigned {
            INVALID_SCENE_RESOURCE = (unsigned)-1
        };
        
        /**
         * @brief the resourceNode object contains all of the data necessary
         * to instantiate all of the sceneNode objects within a sceneGraph.
         */
        struct resourceNode {
            std::string nodeName = {};
            std::vector<unsigned> nodeMeshes = {}; // indices for referencing values in "meshList"
            std::vector<unsigned> nodeChildren = {}; // indices for referencing nodes in "nodeList"
            math::mat4 nodeTransform = {}; // use to build a ls::draw::transform. this is non-accumulated.
            unsigned nodeParentId = 0; // index in "nodeList" where the parent is.
        };
        
        struct resourceMesh {
            draw_index_pair_t indices = {};
            unsigned textureIndex = INVALID_SCENE_RESOURCE;
        };
        
        /**
         * @brief resourceTexture structure contains basic information for a
         * scene graph object to load textures into the current OpenGL context
         * and using the correct texture slot.
         */
        struct resourceTexture {
            std::string texPath = "";
            tex_slot_t texSlot = tex_slot_t::TEXTURE_SLOT_DEFAULT;
        };
        
    private:
        /**
         * Contains the resulting draw mode for each scene after loading.
         */
        draw_mode_t resultDrawMode = draw_mode_t::DEFAULT;
        
        /**
         * @brief Contains the interleaved vertex data used by each scene.
         */
        std::vector<vertex> vertexList;
        
        /**
         * @brief Contains the index data used to specify the location of each
         * mesh object's range of vertices.
         */
        std::vector<draw_index_t> indexList;
        
        /**
         * nodeList is a list of resource nodes that can be loaded by a
         * sceneGraph object during instantiation.
         */
        std::deque<resourceNode> nodeList;
        
        /**
         * @brief submeshes lists all of the indices which can be used to
         * refer to subsets of vertex data in "vertexList". Also contains each
         * mesh object's texture index.
         */
        std::vector<resourceMesh> meshList;
        
        /**
         * @brief textureList is a set of texture resource objects, containing
         * the paths to various texture objects that can be loaded by a scene.
         * The reason textures are not loaded directly into memory is to allow
         * a client program to stream textures in on another thread.
         */
        std::map<tex_slot_t, std::vector<resourceTexture>> textureSet;
        
        /**
         * Allow the ability to generate the bounding area for a scene
         */
        boundingBox totalBounds = {};
        
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
         * @return A resource node containing enough information to create a
         * simple scene with a simple mesh primitive.
         */
        resourceNode createPrimitiveNode(const char* const name);

        /**
         * @brief Scan an ASSIMP scene and attempt to reserve all memory needed
         * to import it.
         *
         * @param pScene
         * A constant pointer to a constant ASSIMP scene.
         *
         * @return TRUE if all memory required to import the scene was
         * successfully allocated, FALSE if not.
         */
        bool preprocessMeshData(const aiScene* const pScene);

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
         * @return TRUE if the mesh was successfully loaded from ASSIMP, FALSE
         * if not.
         */
        bool importMeshData(const aiScene* const pScene);

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
         * @brief Scan an assimp scene and load all paths and slots for the
         * textures referenced by a mesh.
         * 
         * @param pScene
         * A constant pointer to a constant ASSIMP scene.
         * 
         * @return TRUE if all texture paths were successfully imported, FALSE
         * if not.
         */
        bool importTexturePaths(const aiScene* const pScene);
        
        /**
         * @brief Import a single texture path from Assimp
         * 
         * @param Material
         * A constant pointer to a constant ASSIMP material.
         * 
         * @param slotType
         * An ASSIMP aiTextureType, representing the type of texture to be
         * loaded.
         */
        void importSingleTexturePath(const aiMaterial* const pMaterial, int slotType);

        /**
         * @brief readNodeHeirarchy
         * Recursively reads and imports scene graph data from Assimp.
         *
         * @param pNode
         * A pointer to a node in an Assimp scene graph.
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
            const unsigned parentId,
            const math::mat4 parentTransform = math::mat4{1.f}
        );
        
    public:
        /**
         * @brief Destructor
         * 
         * Unloads all data contain within *this.
         */
        virtual ~sceneResource() override;
        
        /**
         * @brief Constructor
         * 
         * Initializes all members contained within *this.
         */
        sceneResource();
        
        /**
         * @brief Copy Constructor
         * 
         * Copies all CPU-side data from the input parameter into *this.
         * 
         * @param r
         * A constant reference to another sceneResource object.
         */
        sceneResource(const sceneResource& r);
        
        /**
         * @brief Move Constructor
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed during the operation.
         * 
         * @param r
         * An r-value reference to a temporary mesh resource object.
         */
        sceneResource(sceneResource&& r);
        
        /**
         * @brief Copy Operator
         * 
         * Copies all CPU-side data from the input parameter into *this.
         * 
         * @param r
         * A constant reference to another sceneResource object.
         * 
         * @return A reference to *this.
         */
        sceneResource& operator=(const sceneResource& r);
        
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
        sceneResource& operator=(sceneResource&& r);

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
         * @return A constant reference to the internal array which contains
         * the vertices loaded by *this.
         */
        const std::vector<vertex>& getVertices() const;
        
        /**
         * Get the number of loaded indices in a mesh.
         * 
         * @return An unsigned integral type, representing the number of
         * indices contained within the scene loaded by *this.
         */
        unsigned getNumIndices() const;
        
        /**
         * Get the array of vertex element indices types of a loaded mesh.
         * 
         * @return A constant reference to the internal array which contains
         * the indices loaded by *this.
         */
        const std::vector<draw_index_t>& getIndices() const;
        
        /**
         * Get the number of loaded scene nodes.
         * 
         * @return An unsigned integral type, representing the number of
         * nodes contained within the scene loaded by *this.
         */
        unsigned getNumNodes() const;
        
        /**
         * Get the array of resource node types of a loaded scene.
         * 
         * @return A constant reference to the internal array which contains
         * the nodes loaded by *this.
         */
        const std::deque<resourceNode>& getNodes() const;
        
        /**
         * Get the number of sub-meshes indices in a scene.
         * 
         * @return An unsigned integral type, representing the number of
         * geometrical subsets contained within the scene loaded by *this.
         */
        unsigned getNumMeshes() const;
        
        /**
         * Get the array of index pairs of a loaded scene, representing
         * individual meshes.
         * 
         * @return A constant reference to the internal array which contains
         * the index pairs loaded by *this.
         */
        const std::vector<resourceMesh>& getMeshes() const;
        
        /**
         * Get the number of types texture available for importing.
         * 
         * @param slot
         * The specific texture slot type to query for texture counts.
         * 
         * @return An unsigned integral type, containing the number of
         * textures found in a 3D scene file.
         */
        unsigned getNumTextureTypes(tex_slot_t slot = tex_slot_t::TEXTURE_SLOT_DEFAULT) const;
        
        /**
         * Get the array of texture paths, determining where a texture can
         * be loaded from.
         * 
         * @return A constant reference to the map of arrays which contains
         * the resourceTexture objects available to load from disk.
         */
        const std::map<tex_slot_t, std::vector<resourceTexture>>& getTextures() const;
        
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

#include "lightsky/draw/generic/sceneResource_impl.h"

#endif	/* __LS_DRAW_SCENE_RESOURCE_H__ */

