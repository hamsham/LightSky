
#ifndef __LS_DRAW_PICKING_BUFFER_H__
#define __LS_DRAW_PICKING_BUFFER_H__

#include <cstdint>

#include "lightsky/draw/color.h"
#include "lightsky/draw/framebuffer.h"
#include "lightsky/draw/renderbuffer.h"
#include "lightsky/draw/texture.h"

namespace ls {
namespace draw {

/**----------------------------------------------------------------------------
 * @brief picking_id_t
 *
 * Identifies a 32-bit data type which is used to receive colors from a
 * picking buffer instead of an array of 8-bit types.
-----------------------------------------------------------------------------*/
typedef uint32_t picking_id_t;

/**----------------------------------------------------------------------------
 * @brief The pickingBuffer class is a combination of a framebuffer, a render
 * buffer (for depth) and a texture (for using IDs as colors). This type of
 * framebuffer allows for scene nodes to be rendered, then selected using
 * their node IDs.
-----------------------------------------------------------------------------*/
class pickingBuffer {
    public:
        /**
         * @brief Convert an array of 4 unsigned bytes to a single 32-bit
         * identification tag. This tag can be used to select object through
         * a framebuffer.
         *
         * @param pixelColor
         * A color type of 4 unsigned bytes (8-bit).
         *
         * @return A 32-bit unsigned integral type which can be used as an ID
         * for objects rendered to a picking buffer.
         */
        static picking_id_t convertPixelColorToId(const color::colorub_t pixelColor);

        /**
         * @brief Convert a 32-bit integer into a color that can be used for
         * rendering.
         *
         * @param id
         * A 32-bit unsigned integer which will be converted into a unique
         * color for rendering onto a framebuffer.
         *
         * @return A color type containign 4 floating-point values which can
         * be sent to a framebuffer for rendering.
         */
        static color::colorf_t convertIdToPixelColor(picking_id_t id);

    private:
        /**
         * @brief Contains the framebuffer object that will be used for all
         * drawing operations after calling "bind()".
         */
        framebuffer fbo;

        /**
         * @brief The color buffer contains the user-provided IDs of each piece
         * of geometry rendered to the framebuffer object.
         *
         * When geometry is rendered to *this, the color buffer will convert
         * all IDs to color values, which can then be read back after the
         * rendering is completed.
         */
        texture colorBuffer;

        /**
         * @brief A depth buffer is required by all framebuffers for
         * completedness. An FBO cannot be created without one.
         */
        renderbuffer depthBuffer;

    public:
        /**
         * @brief Destructor
         *
         * Releases all data from *this back to the GPU.
         */
        ~pickingBuffer();

        /**
         * @brief Constructor
         *
         * Initializes all members in *this.
         */
        pickingBuffer();

        /**
         * @brief Copy Constructor
         *
         * Deleted as *this object contains no data storage members. If a copy
         * is required, simply make another picking buffer object with the
         * same dimensions as *this.
         */
        pickingBuffer(const pickingBuffer&) = delete;

        /**
         * @brief Move Constructor
         *
         * Moves all texture, renderbuffer, and framebuffer handles from the
         * input parameter into *this without performing any copies.
         *
         * @param sb
         * An r-value reference to a temporary picking buffer.
         */
        pickingBuffer(pickingBuffer&& sb);

        /**
         * @brief Copy Constructor
         *
         * Deleted as *this object contains no data storage members. If a copy
         * is required, simply make another picking buffer object with the
         * same dimensions as *this.
         */
        pickingBuffer& operator=(const pickingBuffer&) = delete;

        /**
         * @brief Move Operator
         *
         * Moves all texture, renderbuffer, and framebuffer handles from the
         * input parameter into *this without performing any copies.
         *
         * @param sb
         * An r-value reference to a temporary picking buffer.
         *
         * @return A reference to *this.
         */
        pickingBuffer& operator=(pickingBuffer&& sb);

        /**
         * @brief Initialize the members of a picking buffer.
         *
         * This method creates handles to the framebuffer, texture, and depth
         * buffer used by *this. No storage is allocated.
         *
         * This method does nothing if the internal members were already
         * initialized.
         *
         * @return TRUE if all members were successfully initialized, FALSE if
         * not.
         */
        bool init();

        /**
         * @brief Initialize the members of a picking buffer and allocate (or
         * reallocate) storage for data on the GPU.
         *
         * This method creates handles to the framebuffer, texture, and depth
         * buffer used by *this. No storage is allocated. Make sure that this
         * command is only called when necessary as it may slow down any
         * remaining OpenGL commands enqueued by video driver.
         *
         * @param w
         * The desired width, in pixels, of the internal framebuffer+render
         * targets.
         *
         * @param h
         * The desired height, in pixels, of the internal framebuffer+render
         * targets.
         *
         * @return TRUE if all members were successfully initialized, FALSE if
         * not.
         */
        bool init(int w, int h);

        /**
         * @brief Initialize the members of a picking buffer and allocate (or
         * reallocate) storage for data on the GPU.
         *
         * This method creates handles to the framebuffer, texture, and depth
         * buffer used by *this. No storage is allocated. Make sure that this
         * command is only called when necessary as it may slow down any
         * remaining OpenGL commands enqueued by video driver.
         *
         * @param size
         * The desired width and height, in pixels, of the internal framebuffer
         * and render targets.
         *
         * @return TRUE if all members were successfully initialized, FALSE if
         * not.
         */
        bool init(const math::vec2i& size);

        /**
         * @brief Bind the internal framebuffer in order to perform read/write
         * or other operations.
         */
        void bind() const;

        /**
         * @brief Unind the internal framebuffer and return operation to the
         * default OpenGL framebuffer.
         */
        void unbind() const;

        /**
         * @brief Release all CPU and GPU resources used by *this.
         */
        void terminate();

        /**
         * @brief Get the color of a pixel at a point within the internal
         * framebuffer, converted from a normalized array of four 8-byte values
         * into a single 32-bit unsigned integer.
         *
         * This method will halt the OpenGL command buffer used by the driver
         * and immediately send any pending draw operations to the GPU. It is
         * recommened that this function is called only when absolutely
         * necessary as it can severely impact performance.
         *
         * @param x
         * The horizontal position, in pixels, of the value to be retrieved
         * from the internal framebuffer. Keep in mind that OpenGL references
         * horizontal pixels with "0" for the pixel closest to the left of the
         * screen.
         *
         * @param y
         * The vertical position, in pixels, of the value to be retrieved. Keep
         * in mind that OpenGL references vertical pixels with "0" for the
         * pixel closest to the bottom of the screen.
         *
         * @return A 32-bit unsigned integral type, containing a bitmask of the
         * RGBA values placed within a specific point of the internal
         * framebuffer.
         */
        picking_id_t getIdAtLocation(int x, int y);
};

/*-------------------------------------
 * Initialization Delegation
-------------------------------------*/
inline bool pickingBuffer::init(const math::vec2i& size) {
    return init(size[0], size[1]);
}

/*-------------------------------------
 * FBO Binding
-------------------------------------*/
inline void pickingBuffer::bind() const {
    fbo.bind();
}

/*-------------------------------------
 * FBO Releasing
-------------------------------------*/
inline void pickingBuffer::unbind() const {
    fbo.unbind();
}

} // end draw namespace
} // end ls namespace

#endif // __LS_DRAW_PICKING_BUFFER_H__

