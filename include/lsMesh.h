/* 
 * File:   lsMesh.h
 * Author: miles
 *
 * Created on April 6, 2014, 12:36 AM
 */

#ifndef __LS_MESH_H__
#define	__LS_MESH_H__

#include "lsAtlas.h"
#include "lsBoundingBox.h"
#include "lsBufferObject.h"
#include "lsRenderer.h"
#include "lsSetup.h"
#include "lsVertex.h"

//-----------------------------------------------------------------------------
//      Forward declarations
//-----------------------------------------------------------------------------
class lsMeshResource;
class lsDrawModel;

//-----------------------------------------------------------------------------
//      Enumerations
//-----------------------------------------------------------------------------
/**
 * Text/String mesh properties
 */
enum : int {
    LS_VERTICES_PER_GLYPH = 6,
    LS_TEXT_SPACES_PER_TAB = 4
};

//-----------------------------------------------------------------------------
//      Classes
//-----------------------------------------------------------------------------
/**
 * A mesh object contains information about the layout of vertex data located on
 * the GPU.
 * 
 * These classes are rather large. It is reccomended to instanciate them with
 * dynamic allocation.
 * 
 * Designed to be used directly with OpenGL.
 */
class lsMesh {
    /**
     * Allow the mesh resource class to load vertices directly into a mesh.
     */
    friend class lsMeshResource;
    
    /**
     * Allow the draw model to access data held within this object's VBO.
     */
    friend class lsDrawModel;
    
    private:
        /**
         * Vertex Buffer Object to be used with this mesh
         */
        lsVertexBuffer vbo = {};
        
        /**
         * Member to help determine the number of vertices contained within a
         * mesh object.
         */
        unsigned numVertices = 0;
        
        /**
         * Draw mode for each mesh
         */
        ls_draw_t drawMode = ls_draw_t::LS_DEFAULT_DRAW_MODE;
        
        /**
         * Allow the mesh class to contain some sort of bounding area.
         */
        lsBoundingBox bounds = {};
        
        /**
         * Helper function to ensure that the vao/vbo combos are loaded.
         * This function will cause the VBO member to be bound to the active
         * OpenGL rendering context.
         */
        bool initVertices(unsigned numVerts);
        
        /**
         * Private helper function to upload a set of text vertices (or one
         * glyph) to the GPU.
         * When using a font atlas, a total number of VERTICES_PER_GLYPH will be
         * sent to the array pointed at by the parameter pVerts.
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
        void uploadTextGlyph(float xOffset, float yOffset, const lsAtlasEntry& rGlyph, lsVertex* pVerts);
        
    public:
        /**
         * Constructor
         */
        lsMesh();
        
        /**
         * Copy Constructor -- DELETED
         */
        lsMesh(const lsMesh&) = delete;
        
        /**
         * Move Constructor.
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        lsMesh(lsMesh&&);
        
        /**
         * Destructor
         * Unloads all resources used by *this.
         */
        ~lsMesh();
        
        /**
         * Copy Operator -- DELETED
         */
        lsMesh& operator=(const lsMesh&) = delete;
        
        /**
         * Move Operator
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        lsMesh& operator=(lsMesh&&);
        
        /**
         * Get an general identification to be used for this object
         */
        inline unsigned getId() const;
        
        /**
         * Send a loaded mesh to the GPU
         * 
         * @param ml
         * A mesh loader that contains raw vertex data in memory.
         * 
         * @return
         * TRUE if the data was successfully sent to the GPU, or FALSE if an
         * error occurred.
         */
        bool init(const lsMeshResource&);
        
        /**
         * Sent text/string data to the GPU
         * 
         * @param textureAtlas
         * A texture Atlas containing pre-loaded font glyphs and their offsets.
         * 
         * @param std::string
         * A character string that contains data which is to be loaded onto the GPU.
         * 
         * @return
         * TRUE if the data was successfully sent to the GPU, or FALSE if an
         * error occurred.
         */
        bool init(const lsAtlas&, const std::string&);
        
        /**
         * Unload all GPU-based resource that are used by *this;
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
         * @return draw_mode
         */
        ls_draw_t getDrawMode() const;
        
        /**
         * Set the method of drawing that should be used for this mesh.
         * 
         * @param dm
         */
        void setDrawMode(ls_draw_t dm);
        
        /**
         * Get the maximum vertex bounds for this mesh object.
         * 
         * @return a constant reference to a lsBoundingBox objext.
         */
        const lsBoundingBox& getBounds() const;
};

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/*
 * Get an general identification to be used for this object
 */
inline unsigned lsMesh::getId() const {
    return vbo.getId();
}
        
/*
 * Unload all GPU-based resource that are used by *this;
 */
inline void lsMesh::terminate() {
    vbo.terminate();
    numVertices = 0;
}

/*
 * Get the number of vertices contained within this mesh object's VBO.
 */
inline unsigned lsMesh::getNumVertices() const {
    return numVertices;
}

/*
 * Get the current Draw Mode for this mesh.
 */
inline ls_draw_t lsMesh::getDrawMode() const {
    return drawMode;
}

/*
 * Set the method of drawing that should be used for this mesh.
 */
inline void lsMesh::setDrawMode(ls_draw_t dm) {
    drawMode = dm;
}

/*
 * Get the maximum vertex bounds for this mesh.
 */
inline const lsBoundingBox& lsMesh::getBounds() const {
    return bounds;
}

#endif	/* __LS_MESH_H__ */
