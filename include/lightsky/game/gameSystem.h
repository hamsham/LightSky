/* 
 * File:   game/system.h
 * Author: Miles Lacey
 *
 * Created on November 15, 2013, 9:53 PM
 */

#ifndef __LS_GAME_GAME_SYSTEM_H__
#define	__LS_GAME_GAME_SYSTEM_H__

#include <vector>
#include <cstdint> // uint64_t

namespace ls {
namespace game {

class gameState;

/**----------------------------------------------------------------------------
 * The system object commands all hardware events and passes them to any
 * gameState objects that it manages. Game state objects are freed from memory
 * when this object gets destroyed, therefore, all gameState objects managed by
 * a subSystem must be created using the "new" operator.
-----------------------------------------------------------------------------*/
class gameSystem {
    private:
        /**
         * Stores the previous hardware time since the last update.
         */
        uint64_t tickTime;
        
        /**
         * Stores the previous hardware time since the last update.
         */
        uint64_t prevTime;
        
        /**
         * A vector of game states. The game will stop running when there are
         * no more states left in the list.
         * Push a state into *this, then call "run()" in a loop in order to keep
         * a game running.
         */
        std::vector<gameState*> gameList;
        
    protected:
        /**
         * @brief Update the amount of milliseconds which have passed since the
         * last update.
         */
        void updateTickTime();
        
        /**
         * @brief Update all internal game states.
         * 
         * @param tickTime
         * The time, in milliseconds, which have passed since the last call to
         * "onUpdate()".
         */
        void updateGameStates();
    
    public:
        /**
         * @brief Constructor
         * 
         * Initializes all members in *this to their default values.
         */
        gameSystem();
        
        /**
         * @brief Copy Constructor -- DELETED
         * 
         * Deleted as this would require a copy of all game states held by this
         * object.
         */
        gameSystem(const gameSystem&) = delete;
        
        /**
         * @brief Move constructor
         * 
         * @param sys
         * An r-value reference to another state object who's members will be
         * moved into *this.
         */
        gameSystem(gameSystem&& sys);
        
        /**
         * @brief Destructor
         * 
         * The subsystem destructor will call "terminate()," releasing the
         * memory of all gameState objects held within the gameStack.
         */
        virtual ~gameSystem();
        
        /**
         * @brief Copy operator -- DELETED
         * 
         * This method has been deleted in order to avoid a copy of all
         * gameStates managed by this container.
         */
        gameSystem& operator=(const gameSystem&) = delete;
        
        /**
         * @brief Move operator
         * 
         * @param sys
         * An r-value reference to another state object who's members will be
         * moved into *this.
         * 
         * @return A reference to *this.
         */
        gameSystem& operator=(gameSystem&& sys);
        
        /**
         * @brief SubSystem initialization
         * 
         * @param disp
         * A display object. If the display is not already running, this method
         * will cause if to be created. The display will remain attached to
         * *this object until "terminate()" is called.
         * 
         * @param useVsync
         * Determine if the display should have VSync enabled.
         * 
         * @return TRUE if this object was successfully initialized. FALSE if
         * something went wrong.
         */
        virtual bool start();
        
        /**
         * @brief Begin a game loop
         * 
         * This method will call "onRun()", iterate through all sub states, and
         * call their methods to start, stop, pause, or update. This method
         * must be called in a program's main loop.
         */
        virtual void run();
        
        /**
         * @brief Run an idle game loop
         * 
         * Updates the internal timer but does not update internal game states.
         */
        virtual void pause();
        
        /**
         * @brief Stop *this and all sub-states.
         * 
         * This method will iterate through each managed game state and stop
         * them, thereby destroying each owned state. All memory and resources
         * used by *this will be freed.
         */
        virtual void stop();
        
        /**
         * Push a game state onto the state list. All prior states will be
         * paused, allowing the topmost state to receive hardware events.
         * 
         * @param pState
         * A pointer to a gameState object allocated with "new."
         */
        bool pushGameState(gameState* const pState);
        
        /**
         * Pop the last game state from the list. If there are no states left
         * in the list, the system will stop.
         */
        void popGameState();
        
        /**
         * Search for a game state in the list and remove it if it exists.
         * 
         * @param pState
         * A pointer to the desired game state.
         */
        void popGameState(gameState* const pState);
        
        /**
         * Search for a game state in the list and remove it if it exists.
         * 
         * @param index
         * An index of the desired game state.
         */
        void popGameState(unsigned index);
        
        /**
         * @brief Remove all game states within *this.
         */
        void clearGameStates();
        
        /**
         * Get a game state using an index.
         * 
         * @param index
         * The index of the desired gamestate contained in *this.
         * 
         * @return a pointer to the desired game state. Null if the index was
         * out of bounds.
         */
        gameState const* getGameState(unsigned index) const;
        
        /**
         * Get a game state using an index.
         * 
         * @param index
         * The index of the desired gamestate contained in *this.
         * 
         * @return a pointer to the desired game state. Null if the index was
         * out of bounds.
         */
        gameState* getGameState(unsigned index);
        
        /**
         * @brief Get the index of a game state.
         * 
         * @param pState
         * A pointer to the desired game state contained in *this.
         * 
         * @return The index of the game state held within the game list.
         * UINT_MAX if the state was not found.
         */
        unsigned getGameStateIndex(gameState* const pState) const;
        
        /**
         * Get the number of game states contained within *this.
         * 
         * @return The number of states managed by this system.
         */
        unsigned getNumGameStates() const;
        
        /**
         * @brief Get the time, in milliseconds, which have passed since the
         * last call to either "run()" or "pause()"
         * 
         * @return A 64-bit unsigned integral type which represents the time in
         * milliseconds which have passed since the last system update.
         */
        uint64_t getTickTime() const;
        
        /**
         * @brief Get the time, in milliseconds, of the last call to either
         * "run()" or "pause()"
         * 
         * @return A 64-bit unsigned integral type which represents the time in
         * milliseconds of the last update.
         */
        uint64_t getUpdateTime() const;
        
        /**
         * @brief Determine if *this system still has states to run.
         * 
         * This function has the same effect as querying
         * this->getGameStackSize() > 0
         * 
         * @return TRUE if the game list has something pushed onto it, FALSE
         * if otherwise.
         */
        virtual bool isRunnable() const;
};

} // end game namespace
} // end ls namespace

#include "lightsky/game/generic/gameSystem_impl.h"

#endif	/* __LS_GAME_GAME_SYSTEM_H__ */

