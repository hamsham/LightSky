/* 
 * File:   system.cpp
 * Author: hammy
 * 
 * Created on November 15, 2013, 9:53 PM
 */

#include <new> // std::nothrow
#include <utility> // std::move

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "lsGameState.h"
#include "lsSetup.h"
#include "lsSystem.h"
#include "lsDisplay.h"

/******************************************************************************
 * SubSystem Constructor
******************************************************************************/
lsSubsystem::lsSubsystem() {
}

/******************************************************************************
 * SubSystem Move Construction
******************************************************************************/
lsSubsystem::lsSubsystem(lsSubsystem&& ss) :
    gameIsRunning{ss.gameIsRunning},
    gameStack{std::move(ss.gameStack)},
    display{std::move(ss.display)},
    prng{ss.prng}
{
    ss.prng = nullptr;
}

/******************************************************************************
 * SubSystem Move Operator
******************************************************************************/
lsSubsystem& lsSubsystem::operator=(lsSubsystem&& ss) {
    gameIsRunning = ss.gameIsRunning;
    ss.gameIsRunning = false;
    
    gameStack = std::move(ss.gameStack);
    
    display = std::move(ss.display);
    
    prng = ss.prng;
    ss.prng = nullptr;
    
    return *this;
}

/******************************************************************************
 * SubSystem Initialization
******************************************************************************/
bool lsSubsystem::init(
    const math::vec2i inResolution,
    bool isFullScreen,
    bool useVsync
) {
    terminate();
    
    LS_LOG_MSG(
        "----------------------------------------\n",
        "Initializing a LightSky Sub-System at ", this, "\n",
        "----------------------------------------"
    );
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
        "Successfully initialized the game hardware interface through SDL.\n",
        SDL_GetError(), '\n'
    );
    
    if (!display.init(inResolution, isFullScreen, useVsync)) {
        LS_LOG_ERR("Failed to initialize the display for ", this, ".\n");
        terminate();
        return false;
    }
    LS_LOG_ERR("Successfully initialized the display for ", this, ".\n");
    
    prng = new(std::nothrow) lsRandom(SDL_GetPerformanceCounter());
    if (prng == nullptr) {
        LS_LOG_ERR("Failed to initialize the random number generator for ", this, ".\n");
        terminate();
        return false;
    }
    LS_LOG_ERR("Successfully initialized the random number generator for ", this, ".\n");
    
    LS_LOG_MSG(
        "----------------------------------------\n",
        "Successfully initialized the Sub-System ", this, "\n",
        "----------------------------------------\n"
    );
    
    return true;
}

/******************************************************************************
 * SubSystem Termination
******************************************************************************/
void lsSubsystem::terminate() {
    if (SDL_WasInit(0)) {
        SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
        SDL_Quit();
    }
    
    gameIsRunning = false;
    
    if (gameStack.size() == 0) {
        return;
    }
    
    unsigned i = gameStack.size();
    while (--i) {
        gameStack[i]->setState(LS_GAME_STOPPED);
    }
    
    gameStack.clear();
    display.terminate();
    
    delete prng;
    prng = nullptr;
}

/******************************************************************************
 * SubSystem Running
******************************************************************************/
void lsSubsystem::run() {
    float prevTime = 0;
    gameIsRunning = true;
    SDL_Event pEvent = {0};
    
    while (gameIsRunning && gameStack.size()) {
        // Ensure the display is still open
        if (!display.isRunning()) {
            LS_LOG_ERR("The display is no longer running!\n", SDL_GetError(), '\n');
            gameIsRunning = false;
        }
        
        // Hardware events passed through SDL
        lsGameState* const pState = gameStack.back();
        if (SDL_PollEvent(&pEvent)) {
            passHardwareEvents(&pEvent, pState);
            continue;
        }
        
        // Frame Time Management
        const float currTime = (float)SDL_GetTicks(); // SDL uses millisecond timing.
        const float tickTime = currTime-prevTime;
        prevTime = currTime;
        
        // Game state management
        updateGameStates(tickTime);
        
        // Render to the screen after all events have been processed
        display.flip();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

/******************************************************************************
 * Update Game States
 *****************************************************************************/
void lsSubsystem::passHardwareEvents(const SDL_Event* pEvent, lsGameState* pState) {
    switch (pEvent->type) {
        case SDL_QUIT:              gameIsRunning = false;                           break;
        case SDL_WINDOWEVENT:       pState->onWindowEvent(&pEvent->window);          break;
        case SDL_KEYUP:             pState->onKeyboardUpEvent(&pEvent->key);         break;
        case SDL_KEYDOWN:           pState->onKeyboardDownEvent(&pEvent->key);       break;
        case SDL_TEXTINPUT:         pState->onKeyboardTextEvent(&pEvent->text);      break;
        case SDL_MOUSEMOTION:       pState->onMouseMoveEvent(&pEvent->motion);       break;
        case SDL_MOUSEBUTTONUP:     pState->onMouseButtonUpEvent(&pEvent->button);   break;
        case SDL_MOUSEBUTTONDOWN:   pState->onMouseButtonDownEvent(&pEvent->button); break;
        case SDL_MOUSEWHEEL:        pState->onMouseWheelEvent(&pEvent->wheel);       break;
    }
}

/******************************************************************************
 * Update the states in the game stack
 *****************************************************************************/
void lsSubsystem::updateGameStates(float tickTime) {
    for(unsigned i = 0; i < gameStack.size(); ++i) {
        switch(gameStack[i]->getState()) {
            case LS_GAME_RUNNING:
                gameStack[i]->onRun(tickTime);
                break;
            case LS_GAME_STOPPED:
                popGameState(i);
                i -= 1;
                break;
            case LS_GAME_PAUSED:
                gameStack[i]->onPause(tickTime);
            default:
                break;
        }
    }
}

/******************************************************************************
 * SubSystem State Addition
******************************************************************************/
bool lsSubsystem::pushGameState(lsGameState* pState) {
    if (pState == nullptr) {
        LS_LOG_ERR("ERROR: A null pointer was pushed onto the game stack.\n");
        return false;
    }
    
    if (!pState->onStart()) {
        LS_LOG_ERR("ERROR: A new gameState was unable to start.");
        return false;
    }
    
    if (gameStack.size() > 0) {
        gameStack.back()->setState(LS_GAME_PAUSED);
    }
    
    pState->setParentSystem(*this);
    pState->setState(LS_GAME_RUNNING);
    gameStack.push_back(pState);
    
    return true;
}

/******************************************************************************
 * SubSystem State Addition
******************************************************************************/
void lsSubsystem::popGameState() {
    if (gameStack.size() > 0) {
        popGameState(gameStack.size()-1);
    }
}

/******************************************************************************
 * SubSystem State Removal
******************************************************************************/
void lsSubsystem::popGameState(lsGameState* pState) {
    for (unsigned i = 0; i < gameStack.size(); ++i) {
        if (gameStack[i] == pState) {
            popGameState(i);
            break;
        }
    }
}

/******************************************************************************
 * SubSystem State Removal
******************************************************************************/
void lsSubsystem::popGameState(unsigned index) {
#ifdef LS_DEBUG
    if (index >= gameStack.size()) {
        return;
    }
#endif
    
    gameStack[index]->onStop();
    delete gameStack[index];
    gameStack.erase(gameStack.begin() + index);
    
    // Only resume the last state if it was paused. Leave it alone otherwise
    if (    gameStack.size() > 0
    &&      gameStack.back()->getState() == LS_GAME_PAUSED
    ) {
        gameStack.back()->setState(LS_GAME_RUNNING);
    }
}

/******************************************************************************
 * SubSystem State Retrieval
******************************************************************************/
lsGameState const* lsSubsystem::getGameState(unsigned index) const {
#ifdef LS_DEBUG
    if (index >= gameStack.size()) {
        return nullptr;
    }
#endif
    
    return gameStack[index];
}

/******************************************************************************
 * SubSystem State Indexing
******************************************************************************/
unsigned lsSubsystem::getGameStateIndex(lsGameState* pState) {
    for (unsigned i = 0; i < gameStack.size(); ++i) {
        if (gameStack[i] == pState) {
            return i;
        }
    }
    
    return LS_GAME_INVALID;
}
