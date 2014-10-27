/* 
 * File:   mesh.h
 * Author: miles
 *
 * Created on April 6, 2014, 12:36 AM
 */

#ifndef __LS_MESH_H__
#define	__LS_MESH_H__

#include <cstdint>

#include "atlas.h"
#include "boundingBox.h"
#include "bufferObject.h"
#include "main.h"
#include "renderer.h"
#include "vertex.h"

/*
 * Forward declarations
 */
class meshResource;
class drawModel;

/**
 * Text/String mesh properties
 */
enum text_properties : int {
    VERTICES_PER_GLYPH = 6,
    SPACES_PER_TAB = 4
};

/**
 * A mesh object contains information about the layout of vertex data located on
 * the GPU.
 * 
 * These classes are rather large. It is reccomended to instanciate them with
 * dynamic allocation.
 * 
 * Designed to be used directly with OpenGL.
 */
class mesh {
    /**
     * Allow the mesh resource class to load vertices directly into a mesh.
     */
    friend class meshResource;
    
    /**
     * Allow the draw model to access data held within this object's VBO.
     */
    friend class drawModel;
    
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
        draw_mode drawMode = draw_mode::DEFAULT_DRAW_MODE;
        
        /**
         * Allow the mesh class to contain some sort of bounding area.
         */
        boundingBox bounds = {};
        
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
        void uploadTextGlyph(float xOffset, float yOffset, const atlasEntry& rGlyph, vertex* pVerts);
        
    public:
        /**
         * Constructor
         */
        mesh() {}
        
        /**
         * Copy Constructor -- DELETED
         */
        mesh(const mesh&) = delete;
        
        /**
         * Move Constructor.
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        mesh(mesh&&);
        
        /**
         * Destructor
         * Unloads all resources used by *this.
         */
        ~mesh() {
            terminate();
        }
        
        /**
         * Copy Operator -- DELETED
         */
        mesh& operator=(const mesh&) = delete;
        
        /**
         * Move Operator
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        mesh& operator=(mesh&&);
        
        /**
         * Get an general identification to be used for this object
         */
        inline unsigned getId() const {
            return vbo.getId();
        }
        
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
        bool init(const meshResource& mr);
        
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
        bool init(const atlas&, const std::string&);
        
        /**
         * Unload all GPU-based resource that are used by *this;
         */
        void terminate() {
            vbo.terminate();
            numVertices = 0;
        }
        
        /**
         * Get the number of vertices contained within this mesh object's VBO.
         * 
         * @return The number of vertices used to draw this mesh.
         */
        unsigned getNumVertices() const {
            return numVertices;
        }
        
        /**
         * Get the current Draw Mode for this mesh.
         * 
         * @return draw_mode
         */
        draw_mode getDrawMode() const {
            return drawMode;
        }
        
        /**
         * Set the method of drawing that should be used for this mesh.
         * 
         * @param dm
         */
        void setDrawMode(draw_mode dm) {
            drawMode = dm;
        }
        
        const boundingBox& getBounds() const {
            return bounds;
        }
};

#endif	/* __LS_MESH_H__ */
