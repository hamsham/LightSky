
namespace ls {
namespace game {

/*-------------------------------------
    Return The number of states managed by this system.
-------------------------------------*/
inline unsigned system::getGameStackSize() const {
    return gameList.size();
}

/*-------------------------------------
    Determine if *this is still running
-------------------------------------*/
inline bool system::isRunning() const {
    return gameState::isRunning() && gameList.size() > 0;
}

} // end game namespace
} // end ls namespace
