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
system::system() {
}

/*-------------------------------------
    SubSystem Move Construction
-------------------------------------*/
system::system(system&& ss) :
    prevTime{ss.prevTime},
    gameList{std::move(ss.gameList)}
{}

/*-------------------------------------
    SubSystem Move Operator
-------------------------------------*/
system& system::operator=(system&& ss) {
    prevTime = ss.prevTime;
    ss.prevTime = 0;
    
    tickTime = ss.tickTime;
    ss.tickTime = 0;
    
    gameList = std::move(ss.gameList);
    
    return *this;
}

/*-------------------------------------
    SubSystem Destructor
-------------------------------------*/
system::~system() {
    terminate();
}

/*-------------------------------------
    Initialize the subsystem using LightSky's own display system
-------------------------------------*/
bool system::init() {
    terminate();
    
    LS_LOG_GAME_MSG(
        "----------------------------------------\n",
        "Initializing a LightSky Sub-System at ", this, "\n",
        "----------------------------------------"
    );
    LS_LOG_GAME_MSG(
        "----------------------------------------\n",
        "Successfully initialized the Sub-System ", this, "\n",
        "----------------------------------------\n"
    );
    
    return true;
}

/*-------------------------------------
    SubSystem Termination
-------------------------------------*/
void system::terminate() {
    prevTime = 0;
    
    for (gameState* state : gameList) {
        state->onStop();
    }
    
    gameList.clear();
}

/*-------------------------------------
    SubSystem Running
-------------------------------------*/
void system::run() {
    if (!gameList.size()) {
        LS_LOG_GAME_ERR("No game states are available!");
        this->stop();
        return;
    }
    
    /*
    while (this->hasEvents()) {
     event* const pEvent = this->getNextEvent();
        for (unsigned i = 0; i < gameList.size(); ++i) {
            gameState* const pState = gameList[i];
            pState->onSystemEvent(pEvent);
        }
    }
    */
    
    // Frame Time Management
    const uint64_t currTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
        ).count();
    tickTime = currTime-prevTime;
    prevTime = currTime;

    // Game state management
    for(unsigned i = 0; i < gameList.size(); ++i) {
        switch(gameList[i]->getState()) {
            case game_state_t::RUNNING:
                gameList[i]->onRun(tickTime);
                break;
            case game_state_t::PAUSED:
                gameList[i]->onPause(tickTime);
                break;
            case game_state_t::STOPPED:
                popGameState(i);
                i -= 1;
                break;
            case game_state_t::INIT:
                if (gameList[i]->onStart() == true) {
                    gameList[i]->setState(game_state_t::RUNNING);
                }
                else {
                    LS_LOG_GAME_ERR("ERROR: A new gameState was unable to start.");
                    gameList[i]->setState(game_state_t::STOPPED);
                }
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
    
    pState->setParentSystem(*this);
    pState->setState(game_state_t::INIT);
    gameList.push_back(pState);
    
    return true;
}

/*-------------------------------------
    SubSystem State Addition
-------------------------------------*/
void system::popGameState() {
    if (gameList.size() > 0) {
        popGameState(gameList.size()-1);
    }
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
    gameList[index]->onStop();
    delete gameList[index]; // no guarantee that onStop() is in a state's destructor.
    gameList.erase(gameList.begin() + index);
}

/*-------------------------------------
    SubSystem State Retrieval
-------------------------------------*/
gameState const* system::getGameState(unsigned index) const {
#ifdef LS_DEBUG
    if (index >= gameList.size()) {
        return nullptr;
    }
#endif
    
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

/*-------------------------------------
    This method will stop all game states from running, thereby clearing them
    all off of the stack.
-------------------------------------*/
void system::stop() {
    tickTime = 0;
    
    for (gameState* state : gameList) {
        state->setState(game_state_t::STOPPED);
    }
}

} // end game namespace
} // end ls namespace
