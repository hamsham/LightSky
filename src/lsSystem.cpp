/* 
 * File:   lsSystem.cpp
 * Author: hammy
 * 
 * Created on November 15, 2013, 9:53 PM
 */

#include <new> // std::nothrow
#include <utility> // std::move

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "lsGameState.h"
#include "lsSystem.h"

/*
 * SubSystem Constructor
 */
lsSystem::lsSystem() {
}

/*
 * SubSystem Move Construction
 */
lsSystem::lsSystem(lsSystem&& ss) :
    prevTime{ss.prevTime},
    gameList{std::move(ss.gameList)},
    pDisplay{std::move(ss.pDisplay)},
    context{std::move(ss.context)},
    prng{ss.prng}
{
    ss.pDisplay = nullptr;
    ss.prng = nullptr;
}

/*
 * SubSystem Move Operator
 */
lsSystem& lsSystem::operator=(lsSystem&& ss) {
    prevTime = ss.prevTime;
    ss.prevTime = 0.f;
    
    gameList = std::move(ss.gameList);
    
    pDisplay = pDisplay;
    ss.pDisplay = nullptr;
    
    context = std::move(ss.context);
    
    prng = ss.prng;
    ss.prng = nullptr;
    
    return *this;
}

/*
 * SubSystem Destructor
 */
lsSystem::~lsSystem() {
    terminate();
}

/*
 * Initialize the subsystem using LightSky's own display system
 */
bool lsSystem::init(lsDisplay& disp, bool useVsync) {
    terminate();
    
    LS_LOG_MSG(
        "----------------------------------------\n",
        "Initializing a LightSky Sub-System at ", this, "\n",
        "----------------------------------------"
    );
    
    // make sure there's a display object running
    if (!disp.isRunning()) {
        const math::vec2i res = {LS_DEFAULT_DISPLAY_WIDTH, LS_DEFAULT_DISPLAY_HEIGHT};
        if (!disp.init(res, false)) {
            LS_LOG_ERR("Failed to initialize the display for ", this, ".\n");
            terminate();
            return false;
        }
        LS_LOG_ERR("Successfully initialized the display for ", this, ".\n");
    }
    
    pDisplay = &disp;
    
    if (!context.init(disp, useVsync)) {
        LS_LOG_ERR("\tUnable to create an OpenGL context for the current display.\n");
        terminate();
        return false;
    }
    LS_LOG_MSG("Successfully initialized OpenGL context for ", this, ".\n");
    
    prng = new(std::nothrow) lsRandom(SDL_GetPerformanceCounter());
    if (prng == nullptr) {
        LS_LOG_ERR("Failed to initialize the random number generator for ", this, ".\n");
        terminate();
        return false;
    }
    LS_LOG_MSG("Successfully initialized the random number generator for ", this, ".\n");
    
    LS_LOG_MSG(
        "----------------------------------------\n",
        "Successfully initialized the Sub-System ", this, "\n",
        "----------------------------------------\n"
    );
    
    context.makeCurrent(*pDisplay);
    
    return true;
}

/*
 * SubSystem Termination
 */
void lsSystem::terminate() {
    prevTime = 0.f;
    
    for (lsGameState* state : gameList) {
        state->onStop();
    }
    
    gameList.clear();
    context.terminate();
    pDisplay = nullptr;
    
    delete prng;
    prng = nullptr;
}

/*
 * SubSystem Running
 */
void lsSystem::run() {
    if (!gameList.size()) {
        LS_LOG_ERR("No game states are available!\n", SDL_GetError(), '\n');
        this->stop();
        return;
    }
    
    // Ensure the display is still open
#ifdef LS_DEBUG
    if (!pDisplay || !pDisplay->isRunning()) {
        this->stop();
        return;
    }
#endif
    
    SDL_Event pEvent;
    while (SDL_PollEvent(&pEvent)) {
        // Hardware events passed through SDL
        for (unsigned i = 0; i < gameList.size(); ++i) {
            passHardwareEvents(pEvent, gameList[i]);
        }
    }

    // Frame Time Management
    const float currTime = (float)SDL_GetTicks(); // SDL uses millisecond timing.
    tickTime = currTime-prevTime;
    prevTime = currTime;

    // Game state management
    updateGameStates(tickTime);

    // Render to the screen after all events have been processed
    lsDisplay& display = *pDisplay;
    context.makeCurrent(display);
    context.flip(display);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*
 * Update Game States
 */
void lsSystem::passHardwareEvents(const SDL_Event& event, lsGameState* const pState) {
    switch (event.type) {
        case SDL_QUIT:              stop();                                         break;
        case SDL_WINDOWEVENT:       pState->onWindowEvent(event.window);            break;
        case SDL_KEYUP:             pState->onKeyboardUpEvent(event.key);           break;
        case SDL_KEYDOWN:           pState->onKeyboardDownEvent(event.key);         break;
        case SDL_TEXTINPUT:         pState->onKeyboardTextEvent(event.text);        break;
        case SDL_MOUSEMOTION:       pState->onMouseMoveEvent(event.motion);         break;
        case SDL_MOUSEBUTTONUP:     pState->onMouseButtonUpEvent(event.button);     break;
        case SDL_MOUSEBUTTONDOWN:   pState->onMouseButtonDownEvent(event.button);   break;
        case SDL_MOUSEWHEEL:        pState->onMouseWheelEvent(event.wheel);         break;
    }
}

/*
 * Update the states in the game stack
 */
void lsSystem::updateGameStates(float tickTime) {
    for(unsigned i = 0; i < gameList.size(); ++i) {
        switch(gameList[i]->getState()) {
            
            case LS_GAME_RUNNING:
                gameList[i]->onRun(tickTime);
                break;
            
            case LS_GAME_PAUSED:
                gameList[i]->onPause(tickTime);
                break;
            
            case LS_GAME_STOPPED:
                popGameState(i);
                i -= 1;
                break;
            
            case LS_GAME_INIT:
                if (gameList[i]->onStart() == true) {
                    gameList[i]->setState(LS_GAME_RUNNING);
                }
                else {
                    LS_LOG_ERR("ERROR: A new gameState was unable to start.");
                    gameList[i]->setState(LS_GAME_STOPPED);
                }
            
            default:
                break;
        }
    }
}

/*
 * SubSystem State Addition
 */
bool lsSystem::pushGameState(lsGameState* pState) {
    if (pState == nullptr) {
        LS_LOG_ERR("ERROR: A null pointer was pushed onto the game stack.\n");
        return false;
    }
    
    pState->setParentSystem(*this);
    pState->setState(LS_GAME_INIT);
    gameList.push_back(pState);
    
    return true;
}

/*
 * SubSystem State Addition
 */
void lsSystem::popGameState() {
    if (gameList.size() > 0) {
        popGameState(gameList.size()-1);
    }
}

/*
 * SubSystem State Removal
 */
void lsSystem::popGameState(lsGameState* pState) {
    for (unsigned i = 0; i < gameList.size(); ++i) {
        if (gameList[i] == pState) {
            popGameState(i);
            break;
        }
    }
}

/*
 * SubSystem State Removal
 */
void lsSystem::popGameState(unsigned index) {
    HL_DEBUG_ASSERT(index < gameList.size());
    
    // onStop() was moved to here in order to terminate states in a consistent manner.
    gameList[index]->onStop();
    delete gameList[index]; // no guarantee that onStop() is in a state's destructor.
    gameList.erase(gameList.begin() + index);
}

/*
 * SubSystem State Retrieval
 */
lsGameState const* lsSystem::getGameState(unsigned index) const {
#ifdef LS_DEBUG
    if (index >= gameList.size()) {
        return nullptr;
    }
#endif
    
    return gameList[index];
}

/*
 * SubSystem State Indexing
 */
unsigned lsSystem::getGameStateIndex(lsGameState* pState) {
    for (unsigned i = 0; i < gameList.size(); ++i) {
        if (gameList[i] == pState) {
            return i;
        }
    }
    
    return LS_GAME_INVALID;
}

/*
 * This method will stop all game states from running, thereby clearing them
 * all off of the stack.
 */
void lsSystem::stop() {
    tickTime = 0.f;
    
    for (lsGameState* state : gameList) {
        state->setState(LS_GAME_STOPPED);
    }
}
