
namespace ls {
namespace game {

/*-------------------------------------
    Initialize the subsystem using LightSky's own display system
-------------------------------------*/
inline bool gameSystem::start() {
    return gameList.size() != 0;
}

/*-------------------------------------
    SubSystem Running
-------------------------------------*/
inline void gameSystem::run() {
    updateTickTime();
    updateGameStates();
}

/*-------------------------------------
    SubSystem Running
-------------------------------------*/
inline void gameSystem::pause() {
    updateTickTime();
}

/*-------------------------------------
    SubSystem Termination
-------------------------------------*/
inline void gameSystem::stop() {
    clearGameStates();
    prevTime = tickTime = 0;
}

/*-------------------------------------
    Return The number of states managed by this system.
-------------------------------------*/
inline unsigned gameSystem::getGameStackSize() const {
    return gameList.size();
}

/*-------------------------------------
    Return The number of milliseconds since the last update.
-------------------------------------*/
inline uint64_t gameSystem::getTickTime() const {
    return tickTime;
}

/*-------------------------------------
    Return the time of the last update.
-------------------------------------*/
inline uint64_t gameSystem::getUpdateTime() const {
    return prevTime;
}

/*-------------------------------------
    Determine if *this is still running
-------------------------------------*/
inline bool gameSystem::isRunnable() const {
    return gameList.size() > 0;
}

} // end game namespace
} // end ls namespace
