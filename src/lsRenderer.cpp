/* 
 * File:   renderer.cpp
 * Author: miles
 * 
 * Created on May 17, 2014, 5:34 PM
 */

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <GL/glew.h>

#include "lsRenderer.h"
#include "lsDisplay.h"

/*
 * Renderer constructor
 */
lsRenderer::lsRenderer() :
    pContext{nullptr}
{}

/*
 * Renderer move constructor
 */
lsRenderer::lsRenderer(lsRenderer&& r) :
    pContext{r.pContext}
{
    r.pContext = nullptr;
}

/*
 * Renderer move operator
 */
lsRenderer& lsRenderer::operator=(lsRenderer&& r) {
    pContext = r.pContext;
    r.pContext = nullptr;
    
    return *this;
}

/*
 * Renderer destructor
 */
lsRenderer::~lsRenderer() {
    terminate();
}

/*
 * Renderer initialization
 */
bool lsRenderer::init(const lsDisplay& display, bool useVsync) {
    if (pContext) {
        terminate();
    }
    
    if (display.isRunning() == false) {
        LS_LOG_ERR("\tAttempted to initialize a renderer with no display.\n");
        return false;
    }
    
    /*
     * Attach the OpenGL context to our window handle
     */
    if (SDL_GL_GetCurrentContext() == nullptr) {
        LS_LOG_MSG("Initializing an OpenGL rendering context.");
        pContext = SDL_GL_CreateContext(display.getWindow());
    }
    else {
        LS_LOG_MSG("Taking ownership of an OpenGL rendering context.");
        pContext = SDL_GL_GetCurrentContext();
    }
    if (!pContext) {
        LS_LOG_ERR("\tUnable to create a render context through SDL.");
        LS_LOG_ERR('\t', SDL_GetError(), '\n');
        terminate();
        return false;
    }
    LS_LOG_MSG("\tSuccessfully created a basic render context.");
    
    /*
     * Setup GLEW so we can actually use OpenGL 3+
     */
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        LS_LOG_ERR("\tUnable to initialize GLEW.\n");
        terminate();
        return false;
    }
    LS_LOG_MSG("\tSuccessfully initialized GLEW.");
    
    /*
     * Check if OpenGL 3.3 is up and running
     */
    if (!GLEW_VERSION_3_3) {
        LS_LOG_ERR("\tOpenGL 3.3 is not supported by the current hardware\n.");
        terminate();
        return false;
    }
    
    this->makeCurrent(display);
    this->setViewport(math::vec2i{0, 0}, display.getResolution());
    
    // Set the default back buffer color
    const lsColor& mgcPnk = lsMagicPink;
    glClearColor(mgcPnk[0], mgcPnk[1], mgcPnk[2], mgcPnk[3]);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    setVsync(useVsync);
    
    LS_LOG_MSG(
        "\tSuccessfully initialized a OpenGL 3.3-compatible renderer:"
        "\n\tFace Culling:      ", getFaceCulling(),
        "\n\tDepth Testing:     ", getDepthTesting(),
        "\n\tBlending State:    ", getBlending(),
        "\n\tV-Sync:            ", getVsync()
    );
    
    LS_LOG_MSG("\tSuccessfully initialized the OpenGL 3.3 renderer.\n");
    
    return true;
}

///////////////////////////////////////////////////////////////////////////////
//      Renderer Management
///////////////////////////////////////////////////////////////////////////////
/*
 * Renderer resource termination
 */
void lsRenderer::terminate() {
    SDL_GL_DeleteContext(pContext);
    pContext = nullptr;
}

/*
 * Enable/Disable VSync
 */
void lsRenderer::setVsync(bool vsync) {
    SDL_GL_SetSwapInterval((int)vsync);
}

/*
 * Determine if VSync is enabled or disabled within the current window.
 */
bool lsRenderer::getVsync() const {
    return SDL_GL_GetSwapInterval() != 0;
}

/*
 * Swap the current display's front and back buffers.
 */
void lsRenderer::flip(const lsDisplay& display) const {
    SDL_GL_SwapWindow(display.getWindow());
}
