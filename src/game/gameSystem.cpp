/* 
 * File:   game/ganeSystem.cpp
 * Author: Miles Lacey
 * 
 * Created on November 15, 2013, 9:53 PM
 */

#include <new> // std::nothrow
#include <utility> // std::move
#include <chrono> // std::chrono::steady_clock, std::chrono::milliseconds

#include "lightsky/utils/assertions.h"

#include "lightsky/game/setup.h"

#include "lightsky/game/gameState.h"
#include "lightsky/game/gameSystem.h"

namespace ls {
namespace game {

/*-------------------------------------
    SubSystem Constructor
-------------------------------------*/
gameSystem::gameSystem() :
    tickTime{0},
    prevTime{0},
    gameList{}
{}

/*-------------------------------------
    SubSystem Move Construction
-------------------------------------*/
gameSystem::gameSystem(gameSystem&& ss) :
    tickTime{ss.tickTime},
    prevTime{ss.prevTime},
    gameList{std::move(ss.gameList)}
{}

/*-------------------------------------
    SubSystem Move Operator
-------------------------------------*/
gameSystem& gameSystem::operator=(gameSystem&& ss) {
    tickTime = ss.tickTime;
    ss.tickTime = 0;
    
    prevTime = ss.prevTime;
    ss.prevTime = 0;
    
    gameList = std::move(ss.gameList);
    
    return *this;
}

/*-------------------------------------
    SubSystem Destructor
-------------------------------------*/
gameSystem::~gameSystem() {
    stop();
}

/*-------------------------------------
    SubSystem Tick Time
-------------------------------------*/
void gameSystem::updateTickTime() {
    // Frame Time Management
    const uint64_t currTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
    
    tickTime = currTime-prevTime;
    prevTime = currTime;
}

/*-------------------------------------
    Update all internal game states.
-------------------------------------*/
void gameSystem::updateGameStates() {
    if (!gameList.size()) {
        LS_LOG_ERR("No game states are available!");
    }
    
    for(unsigned i = 0; i < gameList.size(); ++i) {
        gameState* const pState = gameList[i];
        
        switch(pState->getStateStatus()) {
            case game_state_t::RUNNING:
                pState->onRun();
                break;
            case game_state_t::PAUSED:
                pState->onPause();
                break;
            case game_state_t::STOPPED:
                popGameState(i);
                i -= 1;
                break;
            case game_state_t::STARTING:
                // if a state starts successfully, run it on the next iteration
                if (pState->onStart() == true) {
                    pState->setStateStatus(game_state_t::RUNNING);
                }
                else {
                    // stop a state and delete it on the next iteration.
                    LS_LOG_ERR("ERROR: A new gameState was unable to start.");
                    pState->setStateStatus(game_state_t::STOPPED);
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
bool gameSystem::pushGameState(gameState* const pState) {
    if (pState == nullptr) {
        LS_LOG_ERR("ERROR: A null pointer was pushed onto the game stack.\n");
        return false;
    }
    
    // states will be started in the "updateGameStates()" method.
    pState->setParentSystem(*this);
    pState->setStateStatus(game_state_t::STARTING);
    gameList.push_back(pState);
    
    return true;
}

/*-------------------------------------
    SubSystem State Addition
-------------------------------------*/
void gameSystem::popGameState() {
    LS_DEBUG_ASSERT(gameList.size());
    popGameState(gameList.size()-1);
}

/*-------------------------------------
    SubSystem State Removal
-------------------------------------*/
void gameSystem::popGameState(gameState* const pState) {
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
void gameSystem::popGameState(unsigned index) {
    LS_DEBUG_ASSERT(index < gameList.size());
    
    // onStop() was moved to here in order to terminate states in a consistent manner.
    gameList[index]->onStop();
    delete gameList[index]; // no guarantee that onStop() is in a state's destructor.
    gameList.erase(gameList.begin() + index);
}

/*-------------------------------------
    Clear SubSystem States
-------------------------------------*/
void gameSystem::clearGameStates() {
    if (isRunnable() == true) {
        for (unsigned i = 0; i < this->gameList.size(); ++i) {
            gameList[i]->setStateStatus(game_state_t::STOPPED);
        }
    }
    else {    
        while (gameList.size()) {
            popGameState();
        }
    }
}

/*-------------------------------------
    SubSystem State Retrieval
-------------------------------------*/
gameState const* gameSystem::getGameState(unsigned index) const {
    LS_DEBUG_ASSERT(index < gameList.size());
    return gameList[index];
}

/*-------------------------------------
    SubSystem State Retrieval
-------------------------------------*/
gameState* gameSystem::getGameState(unsigned index) {
    LS_DEBUG_ASSERT(index < gameList.size());
    return gameList[index];
}

/*-------------------------------------
    SubSystem State Indexing
-------------------------------------*/
unsigned gameSystem::getGameStateIndex(gameState* const pState) const {
    for (unsigned i = 0; i < gameList.size(); ++i) {
        if (gameList[i] == pState) {
            return i;
        }
    }
    
    return UINT_MAX;
}

} // end game namespace
} // end ls namespace
