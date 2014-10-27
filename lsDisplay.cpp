/* 
 * File:   display.cpp
 * Author: hammy
 * 
 * Created on November 15, 2013, 8:50 PM
 */

#include <GL/glew.h>
#include "display.h"
#include "color.h"

/******************************************************************************
 * Display Initialization
******************************************************************************/
bool display::init(
    const math::vec2i inResolution,
    bool isFullScreen,
    bool useVsync
) {
    Uint32 windowFlags =
        SDL_WINDOW_OPENGL       |
        SDL_WINDOW_SHOWN        |
        SDL_WINDOW_INPUT_FOCUS  |
        SDL_WINDOW_MOUSE_FOCUS  |
        0;
    
    if (isFullScreen) {
        windowFlags |= SDL_WINDOW_FULLSCREEN;
    }
    
    /*
     * Create the window
     */
    pWindow = SDL_CreateWindow(
        LS_APP_NAME,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        inResolution[0], inResolution[1], windowFlags
    );
    if (!pWindow) {
        std::cerr << SDL_GetError() << std::endl;
        terminate();
        return false;
    }
    
    /*
     * Attach the OpenGL context to our window handle
     */
    pContext = SDL_GL_CreateContext(pWindow);
    if (!pContext) {
        std::cerr << SDL_GetError() << std::endl;
        terminate();
        return false;
    }
    
    /*
     * Setup GLEW so we can actually use OpenGL 3+
     */
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        LOG_ERR("ERROR: Unable to initialize GLEW.\n");
        terminate();
        return false;
    }
    
    /*
     * Misc
     */
    SDL_GL_MakeCurrent(pWindow, pContext);
    SDL_GL_SetSwapInterval(useVsync ? 1 : 0);
    const color::color& mgcPnk = color::magicPink;
    glClearColor(mgcPnk[0], mgcPnk[1], mgcPnk[2], mgcPnk[3]);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    if (!renderContext.init()) {
        terminate();
        return false;
    }
    
    return true;
}

/******************************************************************************
 * Display Termination
******************************************************************************/
void display::terminate() {
    if (!pWindow) {
        return;
    }
    
    renderContext.terminate();
    
    SDL_GL_DeleteContext(pContext);
    pContext = nullptr;
    
    SDL_DestroyWindow(pWindow);
    pWindow = nullptr;
}

/******************************************************************************
 * Display Resolution Handling
******************************************************************************/
const math::vec2i display::getResolution() const {
    int x, y;
    SDL_GetWindowSize(pWindow, &x, &y);
    return math::vec2i{x, y};
}

void display::setResolution(const math::vec2i inResolution) {
    SDL_SetWindowSize(pWindow, inResolution[0], inResolution[1]);
}

/******************************************************************************
 * Fullscreen management
******************************************************************************/
void display::setFullscreen(bool fs) {
    if (fs == true) {
        SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN);
        SDL_DisableScreenSaver();
    }
    else {
        SDL_SetWindowFullscreen(pWindow, 0);
        SDL_EnableScreenSaver();
    }
}
