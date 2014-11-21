
namespace ls {
namespace game {

/*-------------------------------------
    Return The number of states managed by this system.
-------------------------------------*/
inline unsigned system::getGameStackSize() const {
    return gameList.size();
}

/*-------------------------------------
    Get the current number of ticks per frame (in milliseconds).
-------------------------------------*/
inline uint64_t system::getTickTime() const {
    return tickTime;
}

/*-------------------------------------
    Determine if *this is still running
-------------------------------------*/
inline bool system::isRunning() const {
    return gameList.size() > 0;
}

} // end game namespace
} // end ls namespace
