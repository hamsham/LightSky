
namespace ls {
namespace game {

/*-------------------------------------
    Get the current state of *this object.
-------------------------------------*/
inline game_state_t gameState::getStateStatus() const {
    return currentState;
}
        
/*-------------------------------------
    Set the operational state of *this.
-------------------------------------*/
inline void gameState::setStateStatus(game_state_t s) {
    currentState = s;
}

/*-------------------------------------
    Get the parent subsystem that manages *this (const).
-------------------------------------*/
inline const gameSystem& gameState::getParentSystem() const {
    return *pSystem;
}

/*-------------------------------------
    Get the parent subsystem that manages *this.
-------------------------------------*/
inline gameSystem& gameState::getParentSystem() {
    return *pSystem;
}

/*-------------------------------------
    Check if the current state is running.
-------------------------------------*/
inline bool gameState::isRunning() const {
    return currentState == game_state_t::RUNNING;
}

/*-------------------------------------
    Check if the current state is paused.
-------------------------------------*/
inline bool gameState::isPaused() const {
    return currentState == game_state_t::PAUSED;
}

/*-------------------------------------
    Check if the current state is initializing.
-------------------------------------*/
inline bool gameState::isStarting() const {
    return currentState == game_state_t::STARTING;
}

/*-------------------------------------
    Check if the current state is stopped.
-------------------------------------*/
inline bool gameState::isStopped() const {
    return currentState == game_state_t::STOPPED;
}

} // end game namespace
} // end ls namespace
