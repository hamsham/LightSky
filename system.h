/* 
 * File:   system.h
 * Author: hammy
 *
 * Created on November 15, 2013, 9:53 PM
 */

#ifndef __LS_SYSTEM_H__
#define	__LS_SYSTEM_H__

#include <vector>
#include <SDL2/SDL_timer.h>
#include "main.h"
#include "display.h"
#include "gameState.h"

union SDL_Event;

/**
 * subsystem
 * 
 * The subSystem object commands all hardware events and passes them to the
 * gameState objects that it manages. Game state objects are freed from memory
 * when this object gets destroyed, therefore, all gameState objects managed by
 * a subSystem must be created using the "new" operator.
 */
class subsystem {
    private:
        bool gameIsRunning = false;
        std::vector<gameState*> gameStack;
        
        void passHardwareEvents(const SDL_Event*, gameState*);
        void updateGameStates(float tickTime);
    
    public:
        /**
         * Constructor
         */
        subsystem();
        
        /**
         * Copy Constructor
         * Deleted as this would require a copy of all game states held by this
         * object.
         */
        subsystem(const subsystem&) = delete;
        
        /**
         * Move constructor
         * @param A subsystem object to be moved.
         */
        subsystem(subsystem&&);
        
        /**
         * Destructor
         * The subsystem destructor will call "terminate()," releasing the memory
         * of all gameState objects held within the gameStack.
         */
        ~subsystem() { terminate(); }
        
        /**
         * Copy operator
         * This method has been deleted in order to avoid a copy of all
         * gameStates managed by this container.
         */
        subsystem& operator=(const subsystem&) = delete;
        
        /**
         * Move operator
         * @param A subSystem to be moved.
         * @return A reference to *this.
         */
        subsystem& operator=(subsystem&&);
        
        /**
         * SubSystem initialization
         * @return True if this object was successfully initialized. False if
         * something went wrong.
         */
        bool init();
        
        /**
         * Terminate.
         * This method will free the memory of all game states managed by this
         * container.
         */
        void terminate();
        
        /**
         * Begin a game loop.
         * This method will loop until all gameStates have either been stopped
         * (and therefore removed from this object) or until the program's main
         * display has been terminated.
         */
        void run();
        
        /**
         * Stop
         * This method will prevent the game loop from running, thereby
         * returning control back to this object's caller.
         */
        void stop() { gameIsRunning = false; }
        
        /**
         * Push a game state onto the state stack. All prior states will be
         * paused, allowing the topmost state to receive hardware events.
         * @param A pointer to a gameState object allocated with "new."
         */
        bool pushGameState(gameState*);
        
        /**
         * Pop the topmost game state from the stack.
         * This will cause the next state in the stack to begin running again.
         * If there are no states left in the stack, the system will stop.
         */
        void popGameState();
        
        /**
         * Search for a game state in the stack and remove it if it exists.
         * @param A pointer to the desired game state.
         */
        void popGameState(gameState*);
        
        /**
         * Search for a game state in the stack and remove it if it exists.
         * @param An index of the desired game state.
         */
        void popGameState(unsigned index);
        
        /**
         * Get a game state using an index.
         * @param index
         * @return a pointer to the desired game state. Null if the index was
         * out of bounds.
         */
        gameState const* getGameState(unsigned index) const;
        
        /**
         * Get the index of a game state.
         * @param A pointer to the desired game state.
         * @return The index of the game state held within the game stack.
         * GAME_INVALID if the state was not found.
         */
        unsigned getGameStateIndex(gameState*);
        
        /**
         * @return The number of states managed by this system.
         */
        unsigned getGameStackSize() const { return gameStack.size(); }
};

#endif	/* __LS_SYSTEM_H__ */

