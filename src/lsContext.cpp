/* 
 * File:   lsContext.cpp
 * Author: miles
 * 
 * Created on August 2, 2014, 8:44 PM
 */

#include <SDL2/SDL_video.h>
#include <GL/glew.h>

#include "lsColor.h"
#include "lsContext.h"
#include "lsDisplay.h"
#include "lsSetup.h"
#include "lsRenderer.h"

/*
 * Render Context constructor
 */
lsContext::lsContext() :
    pContext{nullptr}
{}

/*
 * Render Context move constructor
 */
lsContext::lsContext(lsContext&& r) :
    pContext{r.pContext}
{
    r.pContext = nullptr;
}

/*
 * Render Context move operator
 */
lsContext& lsContext::operator=(lsContext&& r) {
    pContext = r.pContext;
    r.pContext = nullptr;
    
    return *this;
}

/*
 * Render Context destructor
 */
lsContext::~lsContext() {
    terminate();
}

/*
 * Render Context initialization
 */
bool lsContext::init(const lsDisplay& display, bool useVsync) {
    terminate();
    
    if (display.isRunning() == false) {
        LS_LOG_ERR("\tAttempted to initialize a render context with no display.\n");
        return false;
    }
    
    // Attach the OpenGL context to our window handle
    LS_LOG_MSG("Initializing an OpenGL rendering context.");
    pContext = SDL_GL_CreateContext(display.getWindow());
    
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
    this->makeCurrent(display);
    lsRenderer tempRenderer;
    tempRenderer.setViewport(math::vec2i{0, 0}, display.getResolution());
    
    // Set the default back buffer color
    const lsColor& mgcPnk = lsMagenta;
    glClearColor(mgcPnk[0], mgcPnk[1], mgcPnk[2], mgcPnk[3]);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    setVsync(useVsync);
    
    LS_LOG_MSG(
        "\tSuccessfully initialized a OpenGL 3.3-compatible rendere context:"
        "\n\tV-Sync: ", getVsync()
    );
    
    LS_LOG_MSG("\tSuccessfully initialized the OpenGL 3.3 render context.\n");
    
    return true;
}

///////////////////////////////////////////////////////////////////////////////
//      Render Context Management
///////////////////////////////////////////////////////////////////////////////
/*
 * Renderer resource termination
 */
void lsContext::terminate() {
    if (pContext) {
        SDL_GL_DeleteContext(pContext);
    }
    pContext = nullptr;
}

/*
 * Enable/Disable VSync
 */
void lsContext::setVsync(bool vsync) {
    SDL_GL_SetSwapInterval((int)vsync);
}

/*
 * Determine if VSync is enabled or disabled within the current window.
 */
bool lsContext::getVsync() const {
    return SDL_GL_GetSwapInterval() != 0;
}

/*
 * Swap the current display's front and back buffers.
 */
void lsContext::flip(const lsDisplay& display) const {
    SDL_GL_SwapWindow(display.getWindow());
}
