/* 
 * File:   draw/mesh.h
 * Author: Miles Lacey
 *
 * Created on April 6, 2014, 12:36 AM
 */

#ifndef __LS_DRAW_MESH_H__
#define	__LS_DRAW_MESH_H__

#include "lightsky/draw/atlas.h"
#include "lightsky/draw/boundingBox.h"
#include "lightsky/draw/bufferObject.h"
#include "lightsky/draw/renderer.h"
#include "lightsky/draw/setup.h"
#include "lightsky/draw/vertex.h"

namespace ls {
namespace draw {

/*-----------------------------------------------------------------------------
    Forward declarations
-----------------------------------------------------------------------------*/
class meshResource;
class meshModel;

/**----------------------------------------------------------------------------
 * @brief Mesh Properties
 * 
 * These enumerations contains properties for different types of mesh objects.
 * These constants used within contain vital information that's used within the
 * mesh object's implementation.
-----------------------------------------------------------------------------*/
enum mesh_property_t: int {
    /*
     * Text/String mesh properties
     */
    MESH_VERTS_PER_GLYPH = 6,
    MESH_SPACES_PER_TAB = 4
};

/**----------------------------------------------------------------------------
 * @brief Mesh Object
 * 
 * A mesh object contains information about the layout of vertex data located on
 * the GPU. It's designed to be used directly with OpenGL.
 * These classes are rather large. It is recommended to instantiate them using
 * dynamic allocation.
-----------------------------------------------------------------------------*/
class mesh {
    /**
     * Allow the mesh resource class to load vertices directly into a mesh.
     */
    friend class meshResource;
    
    /**
     * Allow the draw model to access data held within this object's VBO.
     */
    friend class meshModel;
    
    private:
        /**
         * Vertex Buffer Object to be used with this mesh
         */
        vertexBuffer vbo = {};
        
        /**
         * Member to help determine the number of vertices contained within a
         * mesh object.
         */
        unsigned numVertices = 0;
        
        /**
         * Draw mode for each mesh
         */
        draw_mode_t drawMode = draw_mode_t::DRAW_MODE_DEFAULT;
        
        /**
         * Allow the mesh class to contain some sort of bounding area.
         */
        boundingBox bounds = {};
        
        /**
         * @brief Vertex Buffer Initialization
         * 
         * Helper function to ensure that the vao/vbo combos are loaded.
         * This function will cause the VBO member to be bound to the active
         * OpenGL rendering context.
         * 
         * @param numVerts
         * The number of vertices that will be allocated on the GPU.
         * 
         * @return TRUE if the internal vertex buffer was successfully
         * initialized, false if not.
         */
        bool initVertices(unsigned numVerts);
        
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
        mesh();
        
        /**
         * @brief Copy Constructor -- DELETED
         */
        mesh(const mesh&) = delete;
        
        /**
         * @brief Move Constructor.
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         * 
         * @param m
         * An r-value reference to a temporary mesh object.
         */
        mesh(mesh&& m);
        
        /**
         * @brief Destructor
         * 
         * Unloads all resources used by *this.
         */
        ~mesh();
        
        /**
         * @brief Copy Operator -- DELETED
         */
        mesh& operator=(const mesh&) = delete;
        
        /**
         * @brief Move Operator
         * 
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         * 
         * @param m
         * An r-value reference to a temporary mesh object.
         * 
         * @return a reference to *this.
         */
        mesh& operator=(mesh&& m);
        
        /**
         * Get an general identification to be used for this object
         * 
         * @return an unsigned integral variable representing the GPU-side
         * handle to the vertex buffer object used by *this.
         */
        inline unsigned getId() const;
        
        /**
         * @brief Initialize
         * 
         * This method send a set of vertices from a mesh resource object to
         * the GPU using OpenGL.
         * 
         * @param mr
         * A mesh loader that contains raw vertex data in memory.
         * 
         * @return TRUE if the data was successfully sent to the GPU, or FALSE
         * if an error occurred.
         */
        bool init(const meshResource& mr);
        
        /**
         * @brief Initialize
         * 
         * Similar to its overload, this method sends text/string data to the
         * GPU using a texture atlas and a corresponding string object. This
         * method will generate a mesh on the fly, attempting to match the
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
         * Get the number of vertices contained within this mesh object's VBO.
         * 
         * @return The number of vertices used to draw this mesh.
         */
        unsigned getNumVertices() const;
        
        /**
         * Get the current Draw Mode for this mesh.
         * 
         * @return an enumeration representing the proper draw mode that should
         * be used to render the vertices within *this.
         */
        draw_mode_t getDrawMode() const;
        
        /**
         * Set the method of drawing that should be used for this mesh. Its
         * recommended not to use this method as it is set during
         * initialization. If the current draw mode is changed, it should be
         * cached in the event that the mode should be restored.
         * 
         * @param dm
         * An enumeration that will be used to determine how to render the
         * vertices contained within *this.
         */
        void setDrawMode(draw_mode_t dm);
        
        /**
         * Get the maximum vertex bounds for this mesh object.
         * 
         * @return a constant reference to a boundingBox objext.
         */
        const boundingBox& getBounds() const;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/mesh_impl.h"

#endif	/* __LS_DRAW_MESH_H__ */
