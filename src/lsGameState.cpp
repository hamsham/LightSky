/* 
 * File:   lsGameState.cpp
 * Author: hammy
 * 
 * Created on November 15, 2013, 8:45 PM
 */

#include "lsGameState.h"

/*
 * Destructor
 */
lsGameState::~lsGameState() {
}

/*
 * Move Constructor
 */
lsGameState::lsGameState(lsGameState&& gs) :
    pSystem{gs.pSystem},
    currentState{gs.currentState}
{
    gs.currentState = LS_GAME_STOPPED;
}

/*
 * Move Operator
 */
lsGameState& lsGameState::operator=(lsGameState&& gs) {
    pSystem = gs.pSystem;
    
    currentState = gs.currentState;
    gs.currentState = LS_GAME_STOPPED;
    
    return *this;
}

/*
 * Parent Sub-System Assignment.
 */
void lsGameState::setParentSystem(lsSubsystem& pSys) {
    pSystem = &pSys;
}
