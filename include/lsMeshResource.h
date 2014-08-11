/* 
 * File:   lsMeshResource.h
 * Author: miles
 *
 * Created on April 2, 2014, 9:04 PM
 */

#ifndef __LS_MESH_RESOURCE_H__
#define	__LS_MESH_RESOURCE_H__

#include <string>

#include "lsSetup.h"
#include "lsResource.h"
#include "lsVertex.h"
#include "lsAtlas.h"
#include "lsBoundingBox.h"

/**
 * The mesh resource can be used to load a mesh or meshes from a file. It can
 * also be used to generate basic primitives such as a sphere, cube, cone, etc.
 */
class lsMeshResource final : public lsResource {
    private:
        /**
         * Contains the number of vertices used per mesh.
         * This is implemented as a single array of unsigned integers.
         */
        unsigned numVertices = 0;
        
        /**
         * Contains the vertex data used by each mesh.
         * This is implemented as an array of vertex arrays.
         */
        lsVertex* pVertices = nullptr;
        
        /**
         * Contains the resulting draw mode for each mesh after loading.
         */
        ls_draw_t resultDrawMode = ls_draw_t::LS_DEFAULT_DRAW_MODE;
        
        /**
         * Allow the ability to generate the bounding area for a mesh
         */
        lsBoundingBox meshBounds = {};
        
        bool initVertices(unsigned vertCount);
        
    public:
        /**
         * Constructor
         */
        lsMeshResource();
        
        /**
         * Copy Constructor -- DELETED
         */
        lsMeshResource(const lsMeshResource&) = delete;
        
        /**
         * Move Constructor
         * Moves all data from the input parameter into *this. No copies are
         * performed during the operation.
         */
        lsMeshResource(lsMeshResource&&);
        
        
        /**
         * Destructor
         * Unloads all data contain within *this.
         */
        virtual ~lsMeshResource() override;
        
        /**
         * Copy Constructor -- DELETED
         */
        lsMeshResource& operator=(const lsMeshResource&) = delete;
        
        /**
         * Move Operator
         * Moves all data from the input parameter into *this. No copies are
         * performed during the operation.
         */
        lsMeshResource& operator=(lsMeshResource&&);
        
        /**
         * Get the number of loaded vertex variables in a mesh
         */
        unsigned getNumVertices() const;
        
        /**
         * Get the array of standard vertex types of a loaded mesh
         */
        lsVertex* getVertices() const;
        
        /**
         * Unload
         * Free all memory used by *this.
         */
        virtual void unload() override;

        /**
         * Load a 3D mesh file.
         * Not yet implemented
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be loadable into memory.
         * 
         * @return true if the file was successfully loaded. False if not.
         */
        bool loadFile(const std::string& filename) override;

        /**
         * Save a mesh to a file.
         * Not yet implemented.
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const std::string&) const override;
        
        /**
         * Get the draw mode that was generated while loading a mesh.
         * 
         * @return The target draw mode for the currently loaded mesh.
         */
        ls_draw_t getDrawMode() const;
        
        /**
         * Get the maximum bounds of a loaded mesh.
         * 
         * @return A constant reference to an lsBoundingBox object.
         */
        const lsBoundingBox& getBoundingBox() const;
        
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
};

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/*
 * Get the number of loaded vertex variables in a mesh
 */
inline unsigned lsMeshResource::getNumVertices() const {
    return numVertices;
}

/*
 * Get the array of standard vertex types of a loaded mesh
 */
inline lsVertex* lsMeshResource::getVertices() const {
    return pVertices;
}

/*
 * Get the draw mode that was generated while loading a mesh.
 */
inline ls_draw_t lsMeshResource::getDrawMode() const {
    return resultDrawMode;
}

/*
 * Get a mesh object's maximum dimensions
 */
inline const lsBoundingBox& lsMeshResource::getBoundingBox() const {
    return meshBounds;
}
        
/*
 * Triangle primitive loading method
 */
inline bool lsMeshResource::loadTriangle() {
    return loadPolygon(3);
}
        
/*
 * Load a set of vertices representing a circle.
 */
inline bool lsMeshResource::loadCircle(unsigned numPoints) {
    return loadPolygon(numPoints);
}

#endif	/* __LS_MESH_RESOURCE_H__ */

