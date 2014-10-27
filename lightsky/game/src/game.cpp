/* 
 * File:   game/game.cpp
 * Author: Miles Lacey
 *
 * Created on August 2, 2014, 10:27 PM
 */

#include <SDL2/SDL.h>

#include "lightsky/game/game.h"

namespace ls {
namespace game {

/*-------------------------------------
    LightSky initialization.
-------------------------------------*/
bool global::init() {
    if (SDL_WasInit(0) == SDL_INIT_EVERYTHING) {
        return true;
    }
    else {
        global::terminate();
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
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        LS_LOG_GAME_ERR(
            "Unable to initialize SDL due to error ", (int)SDL_GetError(), '\n',
            "Complain to your local programmer.\n"
        );
        return false;
    }
    LS_LOG_GAME_MSG(
        "Successfully initialized SDL.\n",
        SDL_GetError(), '\n'
    );
    SDL_ClearError();
    
    return true;
}


/*-------------------------------------
    LightSky termination
-------------------------------------*/
void global::terminate() {
    if (SDL_WasInit(0)) {
        SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
        SDL_Quit();
    }
}

} // end game namespace
} // end ls namespace
