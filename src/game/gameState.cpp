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
    stop();
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
    tickTime{gs.tickTime},
    currentState{gs.currentState},
    pSystem{gs.pSystem}
{
    gs.currentState = game_state_t::STOPPED;
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
gameState& gameState::operator=(gameState&& gs) {
    
    tickTime = gs.tickTime;
    gs.tickTime = 0;
    
    currentState = gs.currentState;
    gs.currentState = game_state_t::STOPPED;
    
    pSystem = gs.pSystem;
    
    return *this;
}

/*-------------------------------------
    Parent Sub-System Assignment.
-------------------------------------*/
void gameState::setParentSystem(system& pSys) {
    pSystem = &pSys;
}

/*-------------------------------------
    The onStart method is called by the parent subsystem when *this
    object has been notified to start. Place all memory allocations here.
-------------------------------------*/
bool gameState::start() {
    setTickTime(0);
    return onStart();
}

/*-------------------------------------
    This method is used to tell the current game state that it should
    update its child components/variables/state.
-------------------------------------*/
void gameState::run() {
    onRun();
}

/*-------------------------------------
    This method is used by the parent subsystem to tell *this game state
    that it's paused.
-------------------------------------*/
void gameState::pause() {
    onPause();
}

/*-------------------------------------
    The onStop method is used by the parent subsystem to indicate that
    *this game state should terminate. Place all memory cleanup here.
-------------------------------------*/
void gameState::stop() {
    onStop();
    setTickTime(0);
}

bool gameState::onStart() {return true;}
void gameState::onRun() {}
void gameState::onPause() {}
void gameState::onStop() {}

} // end game namespace
} // end ls namespace
