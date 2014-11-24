
namespace ls {
namespace game {

/*-------------------------------------
    Get the current state of *this object.
-------------------------------------*/
inline game_state_t gameState::getState() const {
    return currentState;
}
        
/*-------------------------------------
    Set the operational state of *this.
-------------------------------------*/
inline void gameState::setState(game_state_t s) {
    currentState = s;
}

/*-------------------------------------
    Get the parent subsystem that manages *this.
-------------------------------------*/
inline system& gameState::getParentSystem() const {
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

/*-------------------------------------
    Set the number of elapsed milliseconds.
-------------------------------------*/
inline void gameState::setTickTime(uint64_t millisElapsed) {
    tickTime = millisElapsed;
}

/*-------------------------------------
    Set the number of elapsed milliseconds.
-------------------------------------*/
inline uint64_t gameState::getTickTime() const {
    return tickTime;
}

} // end game namespace
} // end ls namespace
