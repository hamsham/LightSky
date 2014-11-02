/* 
 * File:   game/gameState.cpp
 * Author: Miles Lacey
 * 
 * Created on November 15, 2013, 8:45 PM
 */

#include "lightsky/game/gameState.h"

namespace ls {
namespace game {

/*-------------------------------------
    Destructor
-------------------------------------*/
gameState::~gameState() {
}

/*-------------------------------------
    Constructor
-------------------------------------*/
gameState::gameState() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
gameState::gameState(gameState&& gs) :
    pSystem{gs.pSystem},
    currentState{gs.currentState}
{
    gs.currentState = GAME_STOPPED;
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
gameState& gameState::operator=(gameState&& gs) {
    pSystem = gs.pSystem;
    
    currentState = gs.currentState;
    gs.currentState = GAME_STOPPED;
    
    return *this;
}

/*-------------------------------------
    Parent Sub-System Assignment.
-------------------------------------*/
void gameState::setParentSystem(system& pSys) {
    pSystem = &pSys;
}

/*-------------------------------------
 Run a custom function if SDL generated an event.
-------------------------------------*/
void gameState::onSystemEvent(const SDL_Event&) {
}

/*-------------------------------------
    The onStart method is called by the parent subsystem when *this
    object has been notified to start. Place all memory allocations here.
-------------------------------------*/
bool gameState::onStart() {
    return true;
}

/*-------------------------------------
    The onStop method is used by the parent subsystem to indicate that
    *this game state should terminate. Place all memory cleanup here.
-------------------------------------*/
void gameState::onStop() {
}

/*-------------------------------------
    This method is used to tell the current game state that it should
    update its child components/variables/state.
-------------------------------------*/
void gameState::onRun(float) {
}

/*-------------------------------------
    This method is used by the parent subsystem to tell *this game state
    that it's paused.
-------------------------------------*/
void gameState::onPause(float) {
}

} // end game namespace
} // end ls namespace
