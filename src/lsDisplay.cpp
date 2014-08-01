/* 
 * File:   display.cpp
 * Author: hammy
 * 
 * Created on November 15, 2013, 8:50 PM
 */

#include <utility>

#include "lsDisplay.h"
#include "lsColor.h"

/*
 * Display move constructor
 */
lsDisplay::lsDisplay(lsDisplay&& d) :
    pWindow{d.pWindow},
    renderContext{std::move(d.renderContext)}
{
    d.pWindow = nullptr;
}

/*
 * Display move operator
 */
lsDisplay& lsDisplay::operator=(lsDisplay&& d) {
    pWindow = d.pWindow;
    d.pWindow = nullptr;
    
    renderContext = std::move(d.renderContext);
    
    return *this;
}

/******************************************************************************
 * Display Initialization
******************************************************************************/
bool lsDisplay::init(const math::vec2i inResolution, bool isFullScreen, bool vsync) {
    LS_LOG_MSG("Attempting to create an OpenGL 3.3-compatible display through SDL.");
    
    Uint32 windowFlags =
        SDL_WINDOW_OPENGL       |
        SDL_WINDOW_SHOWN        |
        SDL_WINDOW_INPUT_FOCUS  |
        SDL_WINDOW_MOUSE_FOCUS  |
        SDL_WINDOW_RESIZABLE    |
        0;
    
    if (isFullScreen) {
        windowFlags |= SDL_WINDOW_FULLSCREEN;
        LS_LOG_MSG("\tFullscreen: TRUE.");
    }
    else {
        LS_LOG_MSG("\tFullscreen: FALSE.");
    }
    
    /*
     * Create the window
     */
    pWindow = SDL_CreateWindow(
        LS_APP_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        inResolution[0], inResolution[1], windowFlags
    );
    
    if (!pWindow) {
        LS_LOG_ERR("\tUnable to create a display for the renderer.");
        LS_LOG_ERR('\t', SDL_GetError(), '\n');
        terminate();
        return false;
    }
    LS_LOG_MSG("\tSuccessfully created a window through SDL.");
    
    if (!renderContext.init(*this)) {
        LS_LOG_ERR("\tUnable to create an OpenGL context for the current display.\n");
        terminate();
        return false;
    }
    
    setVsync(vsync);
    
    if (getVsync()) {
        LS_LOG_MSG("\tV-Sync: TRUE.");
    }
    else {
        LS_LOG_MSG("\tV-Sync: FALSE.");
    }
    
    LS_LOG_MSG("\tSuccessfully created an OpenGL 3.3-compatible display window.\n");
    
    return true;
}

/******************************************************************************
 * Display Termination
******************************************************************************/
void lsDisplay::terminate() {
    renderContext.terminate();
    
    if (pWindow != nullptr) {
        SDL_DestroyWindow(pWindow);
        pWindow = nullptr;
    }
}

/******************************************************************************
 * Display Resolution Handling
******************************************************************************/
const math::vec2i lsDisplay::getResolution() const {
    int x, y;
    SDL_GetWindowSize(pWindow, &x, &y);
    return math::vec2i{x, y};
}

void lsDisplay::setResolution(const math::vec2i inResolution) {
    SDL_SetWindowSize(pWindow, inResolution[0], inResolution[1]);
}

/******************************************************************************
 * Fullscreen management
******************************************************************************/
void lsDisplay::setFullscreen(bool fs) {
    if (fs == true) {
        SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN);
        SDL_DisableScreenSaver();
    }
    else {
        SDL_SetWindowFullscreen(pWindow, 0);
        SDL_EnableScreenSaver();
    }
}
