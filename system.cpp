/* 
 * File:   system.cpp
 * Author: hammy
 * 
 * Created on November 15, 2013, 9:53 PM
 */

#include <utility>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "main.h"
#include "system.h"
#include "display.h"

/******************************************************************************
 * SubSystem Constructor
******************************************************************************/
subsystem::subsystem() {
}

/******************************************************************************
 * SubSystem Move Construction
******************************************************************************/
subsystem::subsystem(subsystem&& ss) :
    gameIsRunning{ss.gameIsRunning},
    gameStack{std::move(ss.gameStack)}
{}

/******************************************************************************
 * SubSystem Move Operator
******************************************************************************/
subsystem& subsystem::operator=(subsystem&& ss) {
    gameIsRunning = ss.gameIsRunning;
    ss.gameIsRunning = false;
    
    gameStack = std::move(ss.gameStack);
    
    return *this;
}

/******************************************************************************
 * SubSystem Initialization
******************************************************************************/
bool subsystem::init() {
    SDL_SetMainReady();
    
    /*
     * Setup the necessary parameters for OpenGL 3.3
     */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
#ifdef LSLS_DEBUG
        | SDL_GL_CONTEXTLS_DEBUG_FLAG
#endif
    );
    
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        LOG_MSG("SDL successfully initialized.\n");
    }
    else {
        LOG_ERR(
            "Unable to initialize SDL.\n", SDL_GetError(), '\n',
            "Complain to your local programmer.\n"
        );
        return false;
    }
    
    LOG_MSG(
        "Successfully initialized the game hardware interface.\n",
        SDL_GetError(), '\n'
    );
    
    return true;
}

/******************************************************************************
 * SubSystem Termination
******************************************************************************/
void subsystem::terminate() {
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
        gameStack[i]->setState(state_type::GAME_STOPPED);
    }
    
    gameStack.clear();
}

/******************************************************************************
 * SubSystem Running
******************************************************************************/
void subsystem::run() {
    float prevTime = 0;
    gameIsRunning = true;
    SDL_Event pEvent = {0};
    
    while (gameIsRunning && gameStack.size()) {
        // Ensure the display is still open
        if (!global::pDisplay->isRunning()) {
            std::cerr << SDL_GetError() << std::endl;
            gameIsRunning = false;
        }
        
        // Hardware events passed through SDL
        gameState* const pState = gameStack.back();
        if (SDL_PollEvent(&pEvent)) {
            passHardwareEvents(&pEvent, pState);
            continue;
        }
        
        // Frame Time Management
        const float currTime = (float)SDL_GetPerformanceCounter();
        const float tickTime = (currTime-prevTime)/(float)SDL_GetPerformanceFrequency();
        prevTime = currTime;
        
        // Game state management
        updateGameStates(tickTime);
        
        // Render to the screen after all events have been processed
        global::pDisplay->flip();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

/******************************************************************************
 * Update Game States
 *****************************************************************************/
void subsystem::passHardwareEvents(const SDL_Event* pEvent, gameState* pState) {
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
void subsystem::updateGameStates(float tickTime) {
    for(unsigned i = 0; i < gameStack.size(); ++i) {
        switch(gameStack[i]->getState()) {
            case state_type::GAME_RUNNING:
                gameStack[i]->onRun(tickTime);
                break;
            case state_type::GAME_STOPPED:
                popGameState(i);
                i -= 1;
                break;
            case state_type::GAME_PAUSED:
                gameStack[i]->onPause(tickTime);
            default:
                break;
        }
    }
}

/******************************************************************************
 * SubSystem State Addition
******************************************************************************/
bool subsystem::pushGameState(gameState* pState) {
    if (pState == nullptr) {
        LOG_ERR("ERROR: A null pointer was pushed onto the game stack.\n");
        return false;
    }
    
    if (!pState->onStart()) {
        LOG_ERR("ERROR: A new gameState was unable to start.");
        return false;
    }
    
    if (gameStack.size() > 0) {
        gameStack.back()->setState(state_type::GAME_PAUSED);
    }
    
    pState->setState(state_type::GAME_RUNNING);
    gameStack.push_back(pState);
    
    return true;
}

/******************************************************************************
 * SubSystem State Addition
******************************************************************************/
void subsystem::popGameState() {
    if (gameStack.size() > 0) {
        popGameState(gameStack.size()-1);
    }
}

/******************************************************************************
 * SubSystem State Removal
******************************************************************************/
void subsystem::popGameState(gameState* pState) {
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
void subsystem::popGameState(unsigned index) {
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
    &&      gameStack.back()->getState() == state_type::GAME_PAUSED
    ) {
        gameStack.back()->setState(state_type::GAME_RUNNING);
    }
}

/******************************************************************************
 * SubSystem State Retrieval
******************************************************************************/
gameState const* subsystem::getGameState(unsigned index) const {
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
unsigned subsystem::getGameStateIndex(gameState* pState) {
    for (unsigned i = 0; i < gameStack.size(); ++i) {
        if (gameStack[i] == pState) {
            return i;
        }
    }
    
    return state_type::GAME_INVALID;
}
