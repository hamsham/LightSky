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
 * Renderer move constructor
 */
lsRenderer::lsRenderer(lsRenderer&& r) :
    pDisplay{r.pDisplay},
    pContext{r.pContext}
{
    r.pDisplay = nullptr;
    r.pContext = nullptr;
}

/*
 * Renderer move operator
 */
lsRenderer& lsRenderer::operator=(lsRenderer&& r) {
    pDisplay = r.pDisplay;
    r.pDisplay = nullptr;
    
    pContext = r.pContext;
    r.pContext = nullptr;
    
    return *this;
}

/*
 * Renderer initialization
 */
bool lsRenderer::init(const lsDisplay& display) {
    LS_LOG_MSG("Initializing an OpenGL rendering context.");
    
    if (display.isRunning() == false) {
        LS_LOG_ERR("\tAttempted to initialize a renderer with no display.\n");
        return false;
    }
    
    if (pContext != nullptr) {
        LS_LOG_ERR("\tAttempted to initialize a renderer without deleting a previous context.\n");
        return false;
    }
    
    /*
     * Attach the OpenGL context to our window handle
     */
    pDisplay = &display;
    pContext = SDL_GL_CreateContext(pDisplay->getWindow());
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
    
    pDisplay->makeContextCurrent();
    setViewport(math::vec2i{0, 0}, pDisplay->getResolution());
    
    // Set the default back buffer color
    const lsColor& mgcPnk = lsMagicPink;
    glClearColor(mgcPnk[0], mgcPnk[1], mgcPnk[2], mgcPnk[3]);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    LS_LOG_MSG(
        "\tSuccessfully initialized a OpenGL 3.3-compatible renderer:"
        "\n\tFace Culling:      ", getFaceCulling(),
        "\n\tDepth Testing:     ", getDepthTesting(),
        "\n\tBlending State:    ", getBlending()
    );
    
    LS_LOG_MSG("\tSuccessfully initialized the OpenGL renderer.\n");
    
    return true;
}

/*
 * Renderer resource termination
 */
void lsRenderer::terminate() {
    SDL_GL_DeleteContext(pContext);
    pContext = nullptr;
}
