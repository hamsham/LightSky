/* 
 * File:   draw/meshResource.h
 * Author: Miles Lacey
 *
 * Created on April 2, 2014, 9:04 PM
 */

#ifndef __LS_DRAW_MESH_RESOURCE_H__
#define	__LS_DRAW_MESH_RESOURCE_H__

#include <string>

#include "lightsky/draw/setup.h"
#include "lightsky/utils/resource.h"
#include "lightsky/draw/vertex.h"
#include "lightsky/draw/atlas.h"
#include "lightsky/draw/boundingBox.h"

namespace ls {
namespace draw {

/**
 * The mesh resource can be used to load a mesh or meshes from a file. It can
 * also be used to generate basic primitives such as a sphere, cube, cone, etc.
 */
class meshResource final : public ls::utils::resource {
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
        vertex* pVertices = nullptr;
        
        /**
         * Contains the resulting draw mode for each mesh after loading.
         */
        draw_mode_t resultDrawMode = draw_mode_t::DRAW_MODE_DEFAULT;
        
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
        bool initVertices(unsigned vertCount);
        
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
         * @param mr
         * An r-value reference to a temporary mesh resource object.
         */
        meshResource(meshResource&& mr);
        
        
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
         * @param mr
         * An r-value reference to a temporary mesh resource object.
         * 
         * @return a reference to *this.
         */
        meshResource& operator=(meshResource&& mr);
        
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
        vertex* getVertices() const;
        
        /**
         * @brief Unload
         * 
         * Free all memory used by *this.
         */
        virtual void unload() override;

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
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/meshResource_impl.h"

#endif	/* __LS_DRAW_MESH_RESOURCE_H__ */

