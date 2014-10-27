/* 
 * File:   draw/context.cpp
 * Author: Miles Lacey
 * 
 * Created on August 2, 2014, 8:44 PM
 */

#include <SDL2/SDL_video.h>
#include <GL/glew.h>

#include "lightsky/draw/setup.h"
#include "lightsky/draw/color.h"
#include "lightsky/draw/context.h"
#include "lightsky/draw/display.h"
#include "lightsky/draw/renderer.h"

namespace ls {
namespace draw {

/*-------------------------------------
    Render Context constructor
-------------------------------------*/
context::context() :
    pContext{nullptr}
{}

/*-------------------------------------
    Render Context move constructor
-------------------------------------*/
context::context(context&& r) :
    pContext{r.pContext}
{
    r.pContext = nullptr;
}

/*-------------------------------------
    Render Context move operator
-------------------------------------*/
context& context::operator=(context&& r) {
    pContext = r.pContext;
    r.pContext = nullptr;
    
    return *this;
}

/*-------------------------------------
    Render Context destructor
-------------------------------------*/
context::~context() {
    terminate();
}

/*-------------------------------------
    Render Context initialization
-------------------------------------*/
bool context::init(const display& disp, bool useVsync) {
    terminate();
    
    if (disp.isRunning() == false) {
        LS_LOG_ERR("\tAttempted to initialize a render context with no display.\n");
        return false;
    }
    
    // Attach the OpenGL context to our window handle
    LS_LOG_MSG("Initializing an OpenGL rendering context.");
    pContext = SDL_GL_CreateContext(disp.getWindow());
    
    if (!pContext) {
        LS_LOG_ERR("\tUnable to create a render context through SDL.");
        LS_LOG_ERR('\t', SDL_GetError(), '\n');
        terminate();
        return false;
    }
    LS_LOG_MSG("\tSuccessfully created a basic render context.");
    
    // Setup GLEW so we can actually use OpenGL 3+
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        LS_LOG_ERR("\tUnable to initialize GLEW.\n");
        terminate();
        return false;
    }
    LS_LOG_MSG("\tSuccessfully initialized GLEW.");
    
    // Check if OpenGL 3.3 is up and running
    if (!GLEW_VERSION_3_3) {
        LS_LOG_ERR("\tOpenGL 3.3 is not supported by the current hardware\n.");
        terminate();
        return false;
    }
    
    // Quick setup in order to normalize OpenGL to the display coordinates.
    this->makeCurrent(disp);
    renderer tempRenderer;
    tempRenderer.setViewport(math::vec2i{0, 0}, disp.getResolution());
    
    // Set the default back buffer color
    const color& mgcPnk = lsMagenta;
    glClearColor(mgcPnk[0], mgcPnk[1], mgcPnk[2], mgcPnk[3]);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    setVsync(useVsync);
    
    LS_LOG_MSG(
        "\tSuccessfully initialized a OpenGL 3.3-compatible render context:"
        "\n\tV-Sync: ", getVsync()
    );
    
    LS_LOG_MSG("\tSuccessfully initialized the OpenGL 3.3 render context.\n");
    
    return true;
}

/*-------------------------------------
    Renderer resource termination
-------------------------------------*/
void context::terminate() {
    if (pContext) {
        SDL_GL_DeleteContext(pContext);
    }
    pContext = nullptr;
}

/*-------------------------------------
    Activate the render context used in this window.
-------------------------------------*/
void context::makeCurrent(const display& disp) const {
    SDL_GL_MakeCurrent(disp.getWindow(), pContext);
}

/*-------------------------------------
    Enable/Disable VSync
-------------------------------------*/
void context::setVsync(bool vsync) {
    SDL_GL_SetSwapInterval((int)vsync);
}

/*-------------------------------------
    Determine if VSync is enabled or disabled within the current window.
-------------------------------------*/
bool context::getVsync() const {
    return SDL_GL_GetSwapInterval() != 0;
}

/*-------------------------------------
    Swap the current display's front and back buffers.
-------------------------------------*/
void context::flip(const display& disp) const {
    SDL_GL_SwapWindow(disp.getWindow());
}

} // end draw namespace
} // end ls namespace
