/* 
 * File:   draw/geometry.h
 * Author: Miles Lacey
 *
 * Created on April 6, 2014, 12:36 AM
 */

#ifndef __LS_DRAW_MESH_H__
#define	__LS_DRAW_MESH_H__

#include <vector>

#include "lightsky/draw/boundingBox.h"
#include "lightsky/draw/drawCommand.h"
#include "lightsky/draw/setup.h"
#include "lightsky/draw/vertex.h"
#include "lightsky/draw/vertexBuffer.h"

namespace ls {
namespace draw {

/*-----------------------------------------------------------------------------
    Forward declarations
-----------------------------------------------------------------------------*/
class atlas;
struct atlasEntry;
class sceneResource;
struct sceneNode;

/**----------------------------------------------------------------------------
 * @brief Mesh Properties
 * 
 * These enumerations contains properties for different types of geometry
 * objects. These constants used within contain vital information that's used
 * within the geometry object's implementation.
-----------------------------------------------------------------------------*/
enum geometry_property_t: int {
    /*
     * Text/String geometry properties
     */
    MESH_VERTS_PER_GLYPH = 4,
    MESH_INDICES_PER_GLYPH = 6,
    MESH_SPACES_PER_TAB = 4
};

/**----------------------------------------------------------------------------
 * @brief Mesh Object
 * 
 * A geometry object contains information about the layout of vertex data
 * located on the GPU. It's designed to be used directly with OpenGL.
 * These classes are rather large. It is recommended to instantiate them using
 * dynamic allocation.
-----------------------------------------------------------------------------*/
class geometry {
    private:
        /**
         * @brief Vertex Buffer Object to be used with this geometry
         */
        vertexBuffer vbo;
        
        /**
         * @brief Index Buffer Object to be used with this geometry
         */
        indexBuffer ibo;
        
        /**
         * @brief OpenGL parameters for drawing vertices.
         */
        drawCommand drawParams;
        
        /**
         * @brief All sub-meshes contained in *this can be referenced through
         * the "submeshes" member.
         */
        draw_index_list_t submeshes;
        
        /**
         * @brief "bounds" determines bounding area for this set of geometry.
         */
        boundingBox bounds;
        
        /**
         * @brief Vertex Buffer Initialization
         * 
         * Helper function to ensure that the vao/vbo combos are loaded.
         * This function will cause the VBO member to be bound to the active
         * OpenGL rendering context.
         * 
         * @param vbo
         * A Vertex Buffer Object of the type vbo_use_t. This can be used to
         * indicate to OpenGL that the buffer will be a Vertex Buffer, Index
         * Buffer, or any other acceptable usage type.
         * 
         * @param numVerts
         * The number of vertices that will be allocated on the GPU.
         * 
         * @param elementSize
         * The size, in bytes, of a single element in the buffer.
         * 
         * @param usage
         * The draw usage of the internal buffer contained within *this. This
         * parameter can indicate the the mesh is meant to contain static,
         * streamed, or dynamic vertices.
         * 
         * @return TRUE if the internal vertex buffer was successfully
         * initialized, false if not.
         */
        template <vbo_use_t vbo_type>
        static bool initBufferObject(
            vertexBuffer_t<vbo_type>& vbo,
            unsigned numItems,
            unsigned elementSize,
            vbo_rw_t usage = vbo_rw_t::VBO_STATIC_DRAW
        );
        
        /**
         * @brief Map a VBO or IBO in preparation for sending data to the GPU.
         * @param bo
         * A reference to a buffer object of type vbo_t.
         * 
         * @param elementCount
         * The number of elements which are to be sent to the GPU.
         * 
         * @param byteCount
         * The size, in bytes, of the total amount of data to be sent to the
         * GPU.
         * 
         * @param bufferStr
         * A null-terminated character string which can be used to logging.
         * 
         * @return A pointer to a buffer of type data_t which can be used to
         * send data to OpenGL, or NULL if something went wrong.
         */
        template <typename data_t, vbo_use_t vboType>
        data_t* mapBufferData(
            vertexBuffer_t<vboType>& bo,
            const unsigned elementCount,
            const unsigned byteCount,
            const char* const bufferStr
        );
        
        /**
         * @brief Generate the offsets for a string's character according to
         * it's atlas entries, them place the offsets into a vertex and index
         * buffer mapping.
         * 
         * @param a
         * A constant reference to a character atlas.
         * 
         * @param str
         * A constant reference to a string object which will be used to
         * generate a polygonal representation on the GPU.
         * 
         * @param pMappedVerts
         * A pointer to the GPU-mapped vertex buffer object which will contain
         * the generated atlas/string vertices.
         * 
         * @param pMappedIndx
         * A pointer to the GPU-mapped index buffer object which will contain
         * index values for the above vertex buffer.
         */
        void genTextOffsets(const atlas& a, const std::string& str, vertex* pMappedVerts, draw_index_t* pMappedIndx);
        
        /**
         * Private helper function to upload a number of text vertices to the
         * GPU. When using a font atlas, a total number of VERTICES_PER_GLYPH
         * will be sent to the array pointed at by the parameter pVerts.
         * 
         * @param xOffset
         * The current x-offset of all the vertices to be uploaded.
         * 
         * @param yOffset
         * The current y-offset of all the vertices to be uploaded.
         * 
         * @param rGlyph
         * The particular atlas glyph to be sent to the GPU at the x/y offsets.
         * 
         * @param pVerts
         * A pointer to the DMA-mapped buffer of vertices where the current
         * glyph is to be sent.
         */
        void uploadTextGlyph(float xOffset, float yOffset, const atlasEntry& rGlyph, vertex* pVerts);
        
    public:
        /**
         * @brief Constructor
         * 
         * Initializes all members in *this to their default values.
         */
        geometry();
        
        /**
         * @brief Copy Constructor -- DELETED
         */
        geometry(const geometry&) = delete;
        
        /**
         * @brief Move Constructor.
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         * 
         * @param m
         * An r-value reference to a temporary geometry object.
         */
        geometry(geometry&& m);
        
        /**
         * @brief Destructor
         * 
         * Unloads all resources used by *this.
         */
        ~geometry();
        
        /**
         * @brief Copy Operator -- DELETED
         */
        geometry& operator=(const geometry&) = delete;
        
        /**
         * @brief Move Operator
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         * 
         * @param m
         * An r-value reference to a temporary geometry object.
         * 
         * @return a reference to *this.
         */
        geometry& operator=(geometry&& m);
        
        /**
         * @brief Determine if *this is renderable to the currently bound
         * framebuffer.
         * 
         * @return TRUE if *this contains a valid vertex buffer and renderable
         * geometry, FALSE if not.
         */
        bool isValid() const;
        
        /**
         * Get an general identification to be used for this object
         * 
         * @return an unsigned integral variable representing the GPU-side
         * handle to the vertex buffer object used by *this.
         */
        unsigned getId() const;
        
        /**
         * @brief Initialize
         * 
         * This method send a set of vertices from a geometry resource object
         * to the GPU using OpenGL.
         * 
         * @param mr
         * A mesh loader that contains raw vertex data in memory.
         * 
         * @return TRUE if the data was successfully sent to the GPU, or FALSE
         * if an error occurred.
         */
        bool init(const sceneResource& mr);
        
        /**
         * @brief Initialize
         * 
         * Similar to its overload, this method sends text/string data to the
         * GPU using a texture atlas and a corresponding string object. This
         * method will generate a geometry on the fly, attempting to match the
         * characters in the input string, and send the vertices to the GPU.
         * 
         * @param glyphAtlas
         * A texture Atlas containing pre-loaded font glyphs and their offsets.
         * 
         * @param str
         * A constant reference to a character string, containing data which
         * is to be loaded onto the GPU.
         * 
         * @return
         * TRUE if the data was successfully sent to the GPU, or FALSE if an
         * error occurred.
         */
        bool init(const atlas& glyphAtlas, const std::string& str);
        
        /**
         * Unload all GPU-based resource that are used by *this.
         */
        void terminate();
        
        /**
         * Get the internal vertex buffer used by *this.
         * 
         * @return A constant reference to a vertex buffer object.
         */
        const vertexBuffer& getVertexBuffer() const;
        
        /**
         * Get the internal index buffer used by *this.
         * 
         * @return A constant reference to an index buffer object.
         */
        const indexBuffer& getIndexBuffer() const;
        
        /**
         * Get the current Draw command for *this geometry.
         * 
         * @return an "drawCommand" structure, containing the proper parameters
         * that should be used to render the vertices within *this.
         */
        const drawCommand& getDrawCommand() const;
        
        /**
         * @brief Get the list of indices which represent sub-geometry, or
         * "meshes". These indices can be used to draw subsets of a geometry
         * object, initialize a mesh object, or be used to add a mesh to a
         * sceneNode object.
         * 
         * @return A constant reference to the list of indices used to render
         * *this.
         */
        const draw_index_list_t& getSubGeometry() const;
        
        /**
         * Get the maximum vertex bounds for this geometry object.
         * 
         * @return a constant reference to a boundingBox objext.
         */
        const boundingBox& getBounds() const;
        
        /**
         * @brief draw the geometry contained within *this.
         */
        void draw() const;

        /**
         * @brief Draw a piece of geometry.
         *
         * This method renders geometry to the currently bound framebuffer.
         *
         * @param indexPair
         * Contains the starting offset (or element for indexed geometry) to
         * the first vertex to be drawn and end offset (or element count for
         * indexed geometry) to the last vertex to be drawn.
         */
        void draw(const draw_index_pair_t& indexPair) const;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/geometry_impl.h"

#endif	/* __LS_DRAW_MESH_H__ */
