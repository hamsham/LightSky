/* 
 * File:   game/system.cpp
 * Author: Miles Lacey
 * 
 * Created on November 15, 2013, 9:53 PM
 */

#include <new> // std::nothrow
#include <utility> // std::move
#include <chrono> // std::chrono::steady_clock, std::chrono::milliseconds

#include "lightsky/utils/assert.h"

#include "lightsky/game/setup.h"

#include "lightsky/game/gameState.h"
#include "lightsky/game/system.h"

namespace ls {
namespace game {

/*-------------------------------------
    SubSystem Constructor
-------------------------------------*/
system::system() :
    gameState{},
    prevTime{0},
    gameList{}
{}

/*-------------------------------------
    SubSystem Move Construction
-------------------------------------*/
system::system(system&& ss) :
    gameState{std::move(ss)},
    prevTime{ss.prevTime},
    gameList{std::move(ss.gameList)}
{}

/*-------------------------------------
    SubSystem Move Operator
-------------------------------------*/
system& system::operator=(system&& ss) {
    gameState::operator=(std::move(ss));
    
    prevTime = ss.prevTime;
    ss.prevTime = 0;
    
    gameList = std::move(ss.gameList);
    
    return *this;
}

/*-------------------------------------
    SubSystem Destructor
-------------------------------------*/
system::~system() {
}

/*-------------------------------------
    Initialize the subsystem using LightSky's own display system
-------------------------------------*/
bool system::start() {
    setState(game_state_t::STARTING);
    
    if (!onStart()) {
        setState(game_state_t::STOPPED);
        return false;
    }
    
    setState(game_state_t::RUNNING);
    return true;
}

/*-------------------------------------
    SubSystem Running
-------------------------------------*/
void system::run() {
    updateTickTime();
    onRun();
    updateGameStates();
}

/*-------------------------------------
    SubSystem Running
-------------------------------------*/
void system::pause() {
    updateTickTime();
    onPause();
}

/*-------------------------------------
    SubSystem Termination
-------------------------------------*/
void system::stop() {
    clearStateList();
    
    onStop();
    
    pSystem = nullptr;
    
    setState(game_state_t::STOPPED);
    setTickTime(0);
    prevTime = 0;
}

/*-------------------------------------
    SubSystem Tick Time
-------------------------------------*/
void system::updateTickTime() {
    // Frame Time Management
    const uint64_t currTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
    setTickTime(currTime-prevTime);
    prevTime = currTime;
}

/*-------------------------------------
    Update all internal game states.
-------------------------------------*/
void system::updateGameStates() {
    if (!gameList.size()) {
        LS_LOG_GAME_ERR("No game states are available!");
    }
    
    for(unsigned i = 0; i < gameList.size(); ++i) {
        gameState* const pState = gameList[i];
        pState->setTickTime(this->getTickTime());
        
        switch(pState->getState()) {
            case game_state_t::RUNNING:
                pState->run();
                break;
            case game_state_t::PAUSED:
                pState->pause();
                break;
            case game_state_t::STOPPED:
                popGameState(i);
                i -= 1;
                break;
            case game_state_t::STARTING:
                // if a state starts successfully, run it on the next iteration
                if (pState->start() == true) {
                    pState->setState(game_state_t::RUNNING);
                }
                else {
                    // stop a state and delete it on the next iteration.
                    LS_LOG_GAME_ERR("ERROR: A new gameState was unable to start.");
                    pState->setState(game_state_t::STOPPED);
                }
                break;
            default:
                break;
        }
        
    }
}

/*-------------------------------------
    SubSystem State Addition
-------------------------------------*/
bool system::pushGameState(gameState* const pState) {
    if (pState == nullptr) {
        LS_LOG_GAME_ERR("ERROR: A null pointer was pushed onto the game stack.\n");
        return false;
    }
    
    // states will be started in the "updateGameStates()" method.
    pState->setParentSystem(*this);
    pState->setState(game_state_t::STARTING);
    gameList.push_back(pState);
    
    return true;
}

/*-------------------------------------
    SubSystem State Addition
-------------------------------------*/
void system::popGameState() {
    LS_DEBUG_ASSERT(gameList.size());
    popGameState(gameList.size()-1);
}

/*-------------------------------------
    SubSystem State Removal
-------------------------------------*/
void system::popGameState(gameState* const pState) {
    for (unsigned i = 0; i < gameList.size(); ++i) {
        if (gameList[i] == pState) {
            popGameState(i);
            break;
        }
    }
}

/*-------------------------------------
    SubSystem State Removal
-------------------------------------*/
void system::popGameState(unsigned index) {
    LS_DEBUG_ASSERT(index < gameList.size());
    
    // onStop() was moved to here in order to terminate states in a consistent manner.
    gameList[index]->stop();
    delete gameList[index]; // no guarantee that onStop() is in a state's destructor.
    gameList.erase(gameList.begin() + index);
}

/*-------------------------------------
    Clear SubSystem States
-------------------------------------*/
void system::clearStateList() {
    while (gameList.size()) {
        popGameState();
    }
}

/*-------------------------------------
    SubSystem State Retrieval
-------------------------------------*/
gameState const* system::getGameState(unsigned index) const {
    LS_DEBUG_ASSERT(index < gameList.size());
    return gameList[index];
}

/*-------------------------------------
    SubSystem State Retrieval
-------------------------------------*/
gameState* system::getGameState(unsigned index) {
    LS_DEBUG_ASSERT(index < gameList.size());
    return gameList[index];
}

/*-------------------------------------
    SubSystem State Indexing
-------------------------------------*/
unsigned system::getGameStateIndex(gameState* const pState) {
    for (unsigned i = 0; i < gameList.size(); ++i) {
        if (gameList[i] == pState) {
            return i;
        }
    }
    
    return UINT_MAX;
}

} // end game namespace
} // end ls namespace
