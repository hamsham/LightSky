/* 
 * File:   display.cpp
 * Author: hammy
 * 
 * Created on November 15, 2013, 8:50 PM
 */

#include <cstdio>
#include <utility>

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

#include "lsColor.h"
#include "lsDisplay.h"
#include "lsUtil.h"

void printWindowFlags(uint32_t flags) {
    LS_LOG_MSG(
        "\tWindow Flags:\n",
        "\t\tSDL_WINDOW_FULLSCREEN:         ",  0 < (flags & SDL_WINDOW_FULLSCREEN), '\n',
        "\t\tSDL_WINDOW_FULLSCREEN_DESKTOP: ",  0 < (flags & SDL_WINDOW_FULLSCREEN_DESKTOP), '\n',
        "\t\tSDL_WINDOW_OPENGL:             ",  0 < (flags & SDL_WINDOW_OPENGL), '\n',
        "\t\tSDL_WINDOW_SHOWN:              ",  0 < (flags & SDL_WINDOW_SHOWN), '\n',
        "\t\tSDL_WINDOW_HIDDEN:             ",  0 < (flags & SDL_WINDOW_HIDDEN), '\n',
        "\t\tSDL_WINDOW_BORDERLESS:         ",  0 < (flags & SDL_WINDOW_BORDERLESS), '\n',
        "\t\tSDL_WINDOW_RESIZABLE:          ",  0 < (flags & SDL_WINDOW_RESIZABLE), '\n',
        "\t\tSDL_WINDOW_MINIMIZED:          ",  0 < (flags & SDL_WINDOW_MINIMIZED), '\n',
        "\t\tSDL_WINDOW_MAXIMIZED:          ",  0 < (flags & SDL_WINDOW_MAXIMIZED), '\n',
        "\t\tSDL_WINDOW_INPUT_GRABBED:      ",  0 < (flags & SDL_WINDOW_INPUT_GRABBED), '\n',
        "\t\tSDL_WINDOW_INPUT_FOCUS:        ",  0 < (flags & SDL_WINDOW_INPUT_FOCUS), '\n',
        "\t\tSDL_WINDOW_MOUSE_FOCUS:        ",  0 < (flags & SDL_WINDOW_MOUSE_FOCUS), '\n',
        "\t\tSDL_WINDOW_FOREIGN:            ",  0 < (flags & SDL_WINDOW_FOREIGN), '\n',
        "\t\tSDL_WINDOW_ALLOW_HIGHDPI:      ",  0 < (flags & SDL_WINDOW_ALLOW_HIGHDPI), '\n',
        "\t\tSDL_WINDOW_MOUSE_CAPTURE:      ",  0 < (flags & SDL_WINDOW_MOUSE_CAPTURE), '\n'
    );
}

/*
 * Display constructor
 */
lsDisplay::lsDisplay() {
}

/*
 * Display move constructor
 */
lsDisplay::lsDisplay(lsDisplay&& d) :
    pWindow{d.pWindow},
    windowIsNative{d.windowIsNative}
{
    d.pWindow = nullptr;
    d.windowIsNative = false;
}

/*
 * Display move operator
 */
lsDisplay& lsDisplay::operator=(lsDisplay&& d) {
    pWindow = d.pWindow;
    d.pWindow = nullptr;
    
    windowIsNative = d.windowIsNative;
    d.windowIsNative = false;
    
    return *this;
}

/*
 * Display destructor
 */
lsDisplay::~lsDisplay() {
    terminate();
}

/*
 * Display Initialization using a native window handle
 */
bool lsDisplay::init(void* const hwnd) {
    LS_LOG_MSG("Attempting to link with a preexisting display.");
    
    if (hwnd == nullptr) {
        LS_LOG_ERR("\tNo display information provided.\n");
        return false;
    }
    
    LS_LOG_MSG("\tLoading internal flags for a native window.");
    
    
    lsDisplay tempDisp{};
    
    if (!tempDisp.init(math::vec2i{0})) {
        LS_LOG_ERR("\tUnable to create a shared context for a native window.\n");
        return false;
    }
    else {
        printWindowFlags(SDL_GetWindowFlags(tempDisp.getWindow()));
        
        // SDL requires a string, containing the SDL_Window* pointer, to be
        // formatted with "%p". using std::to_string() does not work.
        char nativeHandleStr[sizeof(void*)*2]; // <--- only big enough to stringify a pointer
        sprintf(nativeHandleStr, "%p", (void*)tempDisp.getWindow());

        LS_LOG_MSG("\tCopying window flags from ", nativeHandleStr, " to ", hwnd, '.');
        
        const int wasFlagCopied = SDL_SetHintWithPriority(
            SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT,
            nativeHandleStr, SDL_HINT_OVERRIDE
        );
        
        if (wasFlagCopied != SDL_TRUE) {
            LS_LOG_ERR("\tUnable to toggle internal OpenGL 3.3 compatibility.\n");
            return false;
        }
    }
    
    // Create the window
    pWindow = SDL_CreateWindowFrom(hwnd);
    
    if (!pWindow) {
        LS_LOG_ERR("\tUnable to link with a preexisting display.");
        LS_LOG_ERR('\t', SDL_GetError(), '\n');
        terminate();
        return false;
    }
    else {
        LS_LOG_MSG("\tSuccessfully linked with a preexisting display.\n");
        windowIsNative = true;
        printWindowFlags(SDL_GetWindowFlags(pWindow));
        SDL_GL_LoadLibrary(nullptr); // must be called in order to avoid crashing
    }
    
    return true;
}

/*
 * Display Initialization With no default window handle
 */
bool lsDisplay::init(const math::vec2i inResolution, bool isFullScreen) {
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
        LS_LOG_ERR("\tUnable to create a display object.");
        LS_LOG_ERR('\t', SDL_GetError(), '\n');
        terminate();
        return false;
    }
    else {
        windowIsNative = false;
        LS_LOG_MSG("\tSuccessfully created a window through SDL.");
    }
    
    return true;
}

/*
 * Display Termination
 */
void lsDisplay::terminate() {
    if (pWindow != nullptr && windowIsNative == false) {
        SDL_DestroyWindow(pWindow);
        pWindow = nullptr;
    }
    
    windowIsNative = false;
}

/*
 * Display Resolution Handling
 */
const math::vec2i lsDisplay::getResolution() const {
    int x, y;
    SDL_GetWindowSize(pWindow, &x, &y);
    return math::vec2i{x, y};
}

void lsDisplay::setResolution(const math::vec2i inResolution) {
    SDL_SetWindowSize(pWindow, inResolution[0], inResolution[1]);
}

/*
 * Fullscreen management
 */
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

/*
 * Get a handle to the SDL_Window responsible for the window that this
 * object references.
 */
SDL_Window* lsDisplay::getWindow() const {
    return pWindow;
}
