/* 
 * File:   mainSystem.cpp
 * Author: miles
 * 
 * Created on November 21, 2014, 10:43 PM
 */

#include "mainSystem.h"
#include "eventState.h"
#include "controlState.h"
#include "fbState.h"
#include "uiState.h"

mainSystem::~mainSystem() {
}

mainSystem::mainSystem() {
}

mainSystem::mainSystem(mainSystem&& ms) :
    system{std::move(ms)}
{}

mainSystem& mainSystem::operator=(mainSystem&& ms) {
    system::operator=(std::move(ms));
    
    return *this;
}

bool mainSystem::onStart() {
    
    // push some states and run the game
    if (!this->pushGameState(new controlState{})
    ||  !this->pushGameState(new fbState{})
    ||  !this->pushGameState(new uiState{})
    ) {
        onStop();
        return false;
    }
    return true;
}

void mainSystem::onRun() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        for (unsigned i = 0; i < getGameStackSize(); ++i) {
            ls::game::gameState* const pState = getGameState(i);
            dynamic_cast<eventState* const>(pState)->onEvent(event);
        }
    }
}

void mainSystem::onPause() {
}

void mainSystem::onStop() {
}


