
#include <utility>

#include "lightsky/draw/setup.h"
#include "lightsky/draw/color.h"
#include "lightsky/draw/pickingBuffer.h"

namespace ls {
namespace draw {

/*-------------------------------------
 * Color Conversion to ID
-------------------------------------*/
picking_id_t pickingBuffer::convertPixelColorToId(const color::colorub_t col) {
    return 0
        | (col[0] << 0)
        | (col[1] << 8)
        | (col[2] << 16);
}

/*-------------------------------------
 * ID Conversion to Color
-------------------------------------*/
color::colorf_t pickingBuffer::convertIdToPixelColor(picking_id_t id) {
    constexpr float idNormFactor = 1.f/255.f;
    return color::colorf_t{
        (float)((id & 0x000000FF) >> 0) * idNormFactor,
        (float)((id & 0x0000FF00) >> 8) * idNormFactor,
        (float)((id & 0x00FF0000) >> 16) * idNormFactor,
        1.f
    };
}

/*-------------------------------------
 * Destructor
-------------------------------------*/
pickingBuffer::~pickingBuffer() {
    terminate();
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
pickingBuffer::pickingBuffer() :
    fbo{},
    colorBuffer{},
    depthBuffer{}
{}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
pickingBuffer::pickingBuffer(pickingBuffer&& sb) :
    fbo{std::move(sb.fbo)},
    colorBuffer{std::move(sb.colorBuffer)},
    depthBuffer{std::move(sb.depthBuffer)}
{}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
pickingBuffer& pickingBuffer::operator =(pickingBuffer&& sb) {
    fbo = std::move(sb.fbo);
    colorBuffer = std::move(sb.colorBuffer);
    depthBuffer = std::move(sb.depthBuffer);

    return *this;
}

/*-------------------------------------
 * FBO, Depth Buffer, and Color Buffer Initialization
-------------------------------------*/
bool pickingBuffer::init() {
    if (fbo.getId()) {
        return true;
    }

    if (!fbo.init()) {
        LS_LOG_ERR("Unable to generate the framebuffer for a picking buffer.");
        terminate();
        return false;
    }
    LOG_GL_ERR();

    return true;
}

/*-------------------------------------
 * Storage Allocation/Reallocation
-------------------------------------*/
bool pickingBuffer::init(int width, int height) {
    if (!init()) {
        return false;
    }

    if (!colorBuffer.init(COLOR_FMT_RGB_8, math::vec2i{width, height})) {
        LS_LOG_ERR("Unable to generate the color attachment for a picking buffer.");
        terminate();
        return false;
    }
    LOG_GL_ERR();

    if (!depthBuffer.init(RBO_FMT_DEPTH_16, math::vec2i{width, height})) {
        LS_LOG_ERR("Unable to generate the depth attachment for a picking buffer.");
        terminate();
        return false;
    }
    LOG_GL_ERR();

    fbo.bind();
    fbo.attachRenderTarget(FBO_ATTACHMENT_0, colorBuffer);
    fbo.attachRenderTarget(FBO_ATTACHMENT_DEPTH, depthBuffer);
    framebuffer::printStatus(fbo);
    fbo.unbind();
    LOG_GL_ERR();

    return true;
}

/*-------------------------------------
 * Resource Termination
-------------------------------------*/
void pickingBuffer::terminate() {
    fbo.terminate();
    colorBuffer.terminate();
    depthBuffer.terminate();
}

/*-------------------------------------
 * Pixel Selection
-------------------------------------*/
picking_id_t pickingBuffer::getIdAtLocation(int x, int y) {
    // flush all pending draw commands in order to "pick" an object on screen
    // this method is SLOW but very simple and precise.
    glFlush();
    glFinish();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // reset OpenGL's pixel alignment

    // colors are sent to the default framebuffer as 4 floats, then read as 4 unsigned bytes
    color::colorub_t backbufferColor;

    glReadPixels(x, y, 1, 1, COLOR_FMT_RGB_8, COLOR_TYPE_BYTE, &backbufferColor);

    // pack the read pixels into a single integer
    const picking_id_t id = convertPixelColorToId(backbufferColor);

    LOG_GL_ERR();
    //LS_LOG_MSG("Selected pixel {", x, ", ", y, "} with id: ", id, '.');

    return id;
}

} // end draw namespace
} // end ls namespace

