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
    currentState{gs.currentState},
    pSystem{gs.pSystem}
{
    gs.currentState = game_state_t::STOPPED;
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
gameState& gameState::operator=(gameState&& gs) {
    
    currentState = gs.currentState;
    gs.currentState = game_state_t::STOPPED;
    
    pSystem = gs.pSystem;
    
    return *this;
}

/*-------------------------------------
    Parent Sub-System Assignment.
-------------------------------------*/
void gameState::setParentSystem(gameSystem& pSys) {
    pSystem = &pSys;
}

/*-------------------------------------
    Start the current system's running state.
-------------------------------------*/
bool gameState::onStart() {
    return true;
}

/*-------------------------------------
    Engage the current system's running state.
-------------------------------------*/
void gameState::onRun() {
}

/*-------------------------------------
    Pause the current system's running state.
-------------------------------------*/
void gameState::onPause() {
}

/*-------------------------------------
    Stop the current system's running state.
-------------------------------------*/
void gameState::onStop() {
}

} // end game namespace
} // end ls namespace
