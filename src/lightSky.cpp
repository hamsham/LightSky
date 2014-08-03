/* 
 * File:   lightSky.cpp
 * Author: miles
 *
 * Created on August 2, 2014, 10:27 PM
 */

#include "lightSky.h"

/*
 * LightSky initialization.
 */
bool lsInit() {
    if (SDL_WasInit(0) == SDL_INIT_EVERYTHING) {
        return true;
    }
    else {
        lsTerminate();
    }
    
    SDL_SetMainReady();
    
    /*
     * Setup the necessary parameters for OpenGL 3.3
     */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
#ifdef LS_DEBUG
        | SDL_GL_CONTEXT_DEBUG_FLAG
#endif
    );
    
    if (!SDL_Init(SDL_INIT_EVERYTHING)) {
        LS_LOG_ERR(
            "Unable to initialize SDL.\n", SDL_GetError(), '\n',
            "Complain to your local programmer.\n"
        );
        return false;
    }
    LS_LOG_MSG(
        "Successfully initialized SDL.\n",
        SDL_GetError(), '\n'
    );
    SDL_ClearError();
    
    return true;
}


/*
 * LightSky termination
 */
void lsTerminate() {
    if (SDL_WasInit(0)) {
        SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
        SDL_Quit();
    }
}
