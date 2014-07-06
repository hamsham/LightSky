/* 
 * File:   game.cpp
 * Author: hammy
 * 
 * Created on November 15, 2013, 8:45 PM
 */

#include "lsGameState.h"

lsGameState::~lsGameState() {
}

void lsGameState::setParentSystem(lsSubsystem& pSys) {
    pSystem = &pSys;
}
