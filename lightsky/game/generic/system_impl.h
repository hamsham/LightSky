
namespace ls {
namespace game {

/*-------------------------------------
    Return The number of states managed by this system.
-------------------------------------*/
inline unsigned system::getGameStackSize() const {
    return gameList.size();
}

/*-------------------------------------
    Get a reference to the current display object.
-------------------------------------*/
inline const ls::draw::display& system::getDisplay() const {
    return *pDisplay;
}

/*-------------------------------------
    Get a reference to the current display object.
-------------------------------------*/
inline ls::draw::display& system::getDisplay() {
    return *pDisplay;
}

/*-------------------------------------
    Get a reference to the current render context.
-------------------------------------*/
inline const ls::draw::context& system::getContext() const {
    return renderContext;
}

/*-------------------------------------
    Get a reference to the current render context.
-------------------------------------*/
inline ls::draw::context& system::getContext() {
    return renderContext;
}

/*-------------------------------------
    Get a reference to the system prng (pseudo-random number generator).
-------------------------------------*/
inline const ls::utils::randomNum& system::getPrng() const {
    return *prng;
}

/*-------------------------------------
    Get a reference to the system prng (pseudo-random number generator).
-------------------------------------*/
inline ls::utils::randomNum& system::getPrng() {
    return *prng;
}

/*-------------------------------------
    Get the current number of ticks per frame (in milliseconds).
-------------------------------------*/
inline float system::getTickTime() const {
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
