/* 
 * File:   draw/geometry.h
 * Author: Miles Lacey
 *
 * Created on April 6, 2014, 12:36 AM
 */

#ifndef __LS_DRAW_MESH_H__
#define	__LS_DRAW_MESH_H__

#include "lightsky/draw/drawCommand.h"
#include "lightsky/draw/setup.h"
#include "lightsky/draw/BufferObject.h"
#include "lightsky/draw/VertexUtils.h"

namespace ls {
namespace draw {

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
        BufferObject vbo;
        
        /**
         * @brief Index Buffer Object to be used with this geometry
         */
        BufferObject ibo;
        
        /**
         * @brief OpenGL parameters for drawing vertices.
         */
        drawCommand drawParams;
        
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
         * @brief Initialize a geometry object using a preexisting VBO.
         * 
         * @param v
         * A constant reference to a BufferObject containing vertex data.
         * 
         * @param d
         * A constant reference to a drawCommand object, containing the render
         * parameters required to render *this geometry.
         */
        void init(const BufferObject& v, const drawCommand& d);
        
        /**
         * @brief Initialize a geometry object using a preexisting VBO.
         * 
         * @param v
         * An r-value reference to a BufferObject containing vertex data.
         * 
         * @param numVertices
         * The total number of vertices contained within the input VBO
         * 
         * @param d
         * An r-value reference to a drawCommand object, containing the render
         * parameters required to render *this geometry.
         */
        void init(BufferObject&& v, drawCommand&& d);
        
        /**
         * @brief Initialize a geometry object using a preexisting VBO.
         * 
         * @param v
         * A constant reference to a BufferObject containing vertex data.
         * 
         * @param i
         * A constant reference to a BufferObject containing index data.
         * 
         * @param d
         * A constant reference to a drawCommand object, containing the render
         * parameters required to render *this geometry.
         */
        void init(
            const BufferObject& v,
            const BufferObject& i,
            const drawCommand& d
        );
        
        /**
         * @brief Initialize a geometry object using a preexisting VBO.
         * 
         * @param v
         * An r-value reference to a BufferObject containing vertex data.
         * 
         * @param i
         * An r-value reference to a BufferObject containing index data.
         * 
         * @param d
         * An r-value reference to a drawCommand object, containing the render
         * parameters required to render *this geometry.
         */
        void init(
            BufferObject&& v,
            BufferObject&& i,
            drawCommand&& d
        );
        
        /**
         * Unload all GPU-based resource that are used by *this.
         */
        void terminate();
        
        /**
         * Get the internal vertex buffer used by *this.
         * 
         * @return A constant reference to a vertex buffer object.
         */
        const BufferObject& getVertexBuffer() const;
        
        /**
         * Get the internal index buffer used by *this.
         * 
         * @return A constant reference to an index buffer object.
         */
        const BufferObject& getIndexBuffer() const;
        
        /**
         * Get the current Draw command for *this geometry.
         * 
         * @return an "drawCommand" structure, containing the proper parameters
         * that should be used to render the vertices within *this.
         */
        const drawCommand& getDrawCommand() const;
        
        /**
         * @brief draw the geometry contained within *this.
         */
        void draw() const;
};

/*-------------------------------------
    Determine if *this is renderable.
-------------------------------------*/
inline bool geometry::isValid() const {
    return vbo.gpuId != 0;
}

/*-------------------------------------
    Get an general identification to be used for this object
-------------------------------------*/
inline unsigned geometry::getId() const {
    return vbo.gpuId;
}

/*-------------------------------------
 * Get the internal vertex buffer used by *this.
-------------------------------------*/
inline const BufferObject& geometry::getVertexBuffer() const {
    return vbo;
}

/*-------------------------------------
 * Get the internal index buffer used by *this.
-------------------------------------*/
inline const BufferObject& geometry::getIndexBuffer() const {
    return ibo;
}

/*-------------------------------------
    Get the current Draw parameters for this geometry.
-------------------------------------*/
inline const drawCommand& geometry::getDrawCommand() const {
    return drawParams;
}

/*-------------------------------------
 * Draw the geometry contained within *this.
-------------------------------------*/
inline void geometry::draw() const {
    ibo.gpuId ? drawParams.draw(vbo, ibo) : drawParams.draw(vbo);
}

} // end draw namespace
} // end ls namespace

#endif	/* __LS_DRAW_MESH_H__ */
