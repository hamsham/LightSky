/* 
 * File:   game/system.h
 * Author: Miles Lacey
 *
 * Created on November 15, 2013, 9:53 PM
 */

#ifndef __LS_GAME_SYSTEM_H__
#define	__LS_GAME_SYSTEM_H__

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
class system {
    private:
        /**
         * Stores the previous hardware time since the last update.
         */
        uint64_t prevTime = 0;
        
        /**
         * Duration of the last "tick," or the last time that the "run()"
         * function had been called.
         */
        uint64_t tickTime = 0;
        
        /**
         * A vector of game states. The game will stop running when there are
         * no more states left in the list.
         * Push a state into *this, then call "run()" in a loop in order to keep
         * a game running.
         */
        std::vector<gameState*> gameList;
    
    public:
        /**
         * @brief Constructor
         * 
         * Initializes all members in *this to their default values.
         */
        system();
        
        /**
         * @brief Copy Constructor -- DELETED
         * 
         * Deleted as this would require a copy of all game states held by this
         * object.
         */
        system(const system&) = delete;
        
        /**
         * @brief Move constructor
         * 
         * @param sys
         * An r-value reference to another state object who's members will be
         * moved into *this.
         */
        system(system&& sys);
        
        /**
         * @brief Destructor
         * 
         * The subsystem destructor will call "terminate()," releasing the
         * memory of all gameState objects held within the gameStack.
         */
        virtual ~system();
        
        /**
         * @brief Copy operator -- DELETED
         * 
         * This method has been deleted in order to avoid a copy of all
         * gameStates managed by this container.
         */
        system& operator=(const system&) = delete;
        
        /**
         * @brief Move operator
         * 
         * @param sys
         * An r-value reference to another state object who's members will be
         * moved into *this.
         * 
         * @return A reference to *this.
         */
        system& operator=(system&& sys);
        
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
        virtual bool init();
        
        /**
         * @brief Terminate *this and all sub-states.
         * 
         * This method will free all memory and resources of all game states
         * managed by this container.
         */
        void terminate();
        
        /**
         * @brief Begin a game loop
         * 
         * This method will iterate through all gameStates , pass them hardware
         * events, and call their methods to start, stop, pause, or update.
         * This method must be called in a program's main loop.
         */
        virtual void run();
        
        /**
         * @brief Stop
         * 
         * This method will iterate through each managed game state and stop
         * them, thereby destroying each owned state.
         */
        void stop();
        
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
         * @brief Get the index of a game state.
         * 
         * @param pState
         * A pointer to the desired game state contained in *this.
         * 
         * @return The index of the game state held within the game list.
         * UINT_MAX if the state was not found.
         */
        unsigned getGameStateIndex(gameState* const pState);
        
        /**
         * Get the number of game states contained within *this.
         * 
         * @return The number of states managed by this system.
         */
        unsigned getGameStackSize() const;
        
        /**
         * Get the current number of ticks per frame (in milliseconds).
         * 
         * @return An unsigned integral number which represents the number of
         * milliseconds which have passed since the last complete update.
         */
        uint64_t getTickTime() const;
        
        /**
         * Determine if *this system is still running and operational.
         * This function has the same effect as querying
         * this->getGameStackSize() > 0
         * 
         * @return TRUE if the game list has something pushed onto it, FALSE
         * if otherwise.
         */
        bool isRunning() const;
};

} // end game namespace
} // end ls namespace

#include "lightsky/game/generic/system_impl.h"

#endif	/* __LS_GAME_SYSTEM_H__ */

