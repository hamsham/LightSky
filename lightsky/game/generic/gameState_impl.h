
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

} // end game namespace
} // end ls namespace
