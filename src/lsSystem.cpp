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
#include <SDL2/SDL_timer.h>

#include "lsGameState.h"
#include "lsSystem.h"

/*
 * SubSystem Constructor
 */
lsSubsystem::lsSubsystem() {
}

/*
 * SubSystem Move Construction
 */
lsSubsystem::lsSubsystem(lsSubsystem&& ss) :
    prevTime{ss.prevTime},
    gameStack{std::move(ss.gameStack)},
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
lsSubsystem& lsSubsystem::operator=(lsSubsystem&& ss) {
    prevTime = ss.prevTime;
    ss.prevTime = 0.f;
    
    gameStack = std::move(ss.gameStack);
    
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
lsSubsystem::~lsSubsystem() {
    terminate();
}

/*
 * Initialize the subsystem using LightSky's own display system
 */
bool lsSubsystem::init(lsDisplay& disp, bool useVsync) {
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

/*
 * SubSystem Termination
 */
void lsSubsystem::terminate() {
    prevTime = 0.f;
    
    for (lsGameState* state : gameStack) {
        state->setState(LS_GAME_STOPPED);
        state->onStop();
    }
    
    gameStack.clear();
    context.terminate();
    pDisplay = nullptr;
    
    delete prng;
    prng = nullptr;
}

/*
 * SubSystem Running
 */
void lsSubsystem::run() {
    if (!gameStack.size()) {
        LS_LOG_ERR("No game states are available!\n", SDL_GetError(), '\n');
        return;
    }
    
    // Ensure the display is still open
    if (!pDisplay || !pDisplay->isRunning()) {
        LS_LOG_ERR("The display is no longer running!\n", SDL_GetError(), '\n');
        return;
    }
    
    SDL_Event pEvent = {0};
    while (SDL_PollEvent(&pEvent)) {
    // Hardware events passed through SDL
        lsGameState* const pState = gameStack.back();
        passHardwareEvents(pEvent, pState);
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
void lsSubsystem::passHardwareEvents(const SDL_Event& event, lsGameState* const pState) {
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

/*
 * SubSystem State Addition
 */
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

/*
 * SubSystem State Addition
 */
void lsSubsystem::popGameState() {
    if (gameStack.size() > 0) {
        popGameState(gameStack.size()-1);
    }
}

/*
 * SubSystem State Removal
 */
void lsSubsystem::popGameState(lsGameState* pState) {
    for (unsigned i = 0; i < gameStack.size(); ++i) {
        if (gameStack[i] == pState) {
            popGameState(i);
            break;
        }
    }
}

/*
 * SubSystem State Removal
 */
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
    if (gameStack.size() > 0 && gameStack.back()->getState() == LS_GAME_PAUSED) {
        gameStack.back()->setState(LS_GAME_RUNNING);
    }
}

/*
 * SubSystem State Retrieval
 */
lsGameState const* lsSubsystem::getGameState(unsigned index) const {
#ifdef LS_DEBUG
    if (index >= gameStack.size()) {
        return nullptr;
    }
#endif
    
    return gameStack[index];
}

/*
 * SubSystem State Indexing
 */
unsigned lsSubsystem::getGameStateIndex(lsGameState* pState) {
    for (unsigned i = 0; i < gameStack.size(); ++i) {
        if (gameStack[i] == pState) {
            return i;
        }
    }
    
    return LS_GAME_INVALID;
}

/*
 * This method will stop all game states from running, thereby clearing them
 * all off of the stack.
 */
void lsSubsystem::stop() {
    tickTime = 0.f;
    
    for (lsGameState* state : gameStack) {
        state->setState(LS_GAME_STOPPED);
    }
}
