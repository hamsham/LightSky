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

#include "lsSetup.h"
#include "lsDisplay.h"
#include "lsRandom.h"

/*
 * Forward declarations
 */
union SDL_Event;
class lsGameState;

/**
 * subsystem
 * 
 * The subSystem object commands all hardware events and passes them to the
 * gameState objects that it manages. Game state objects are freed from memory
 * when this object gets destroyed, therefore, all gameState objects managed by
 * a subSystem must be created using the "new" operator.
 */
class lsSubsystem {
    private:
        bool gameIsRunning = false;
        float tickTime = 0.f;
        std::vector<lsGameState*> gameStack;
        lsDisplay display = {};
        lsRandom* prng = nullptr;
        
        void passHardwareEvents(const SDL_Event*, lsGameState*);
        void updateGameStates(float tickTime);
    
    public:
        /**
         * Constructor
         */
        lsSubsystem();
        
        /**
         * Copy Constructor
         * Deleted as this would require a copy of all game states held by this
         * object.
         */
        lsSubsystem(const lsSubsystem&) = delete;
        
        /**
         * Move constructor
         * 
         * @param A subsystem object to be moved.
         */
        lsSubsystem(lsSubsystem&&);
        
        /**
         * Destructor
         * The subsystem destructor will call "terminate()," releasing the memory
         * of all gameState objects held within the gameStack.
         */
        ~lsSubsystem() { terminate(); }
        
        /**
         * Copy operator
         * This method has been deleted in order to avoid a copy of all
         * gameStates managed by this container.
         */
        lsSubsystem& operator=(const lsSubsystem&) = delete;
        
        /**
         * Move operator
         * 
         * @param A subSystem to be moved.
         * 
         * @return A reference to *this.
         */
        lsSubsystem& operator=(lsSubsystem&&);
        
        /**
         * SubSystem initialization
         * 
         * @see lsDisplay::init for the parameters used.
         * 
         * @param inResolution
         * The desired window resolution, in pixels.
         * 
         * @param isFullScreen
         * Determine if the window should be made full-screen.
         * 
         * @param useVsync
         * Determine if the display should have VSync enabled.
         * 
         * @return True if this object was successfully initialized. False if
         * something went wrong.
         */
        bool init(
            const math::vec2i inResolution = math::vec2i{
                LS_DEFAULT_DISPLAY_WIDTH, LS_DEFAULT_DISPLAY_HEIGHT
            },
            bool isFullScreen = false,
            bool useVsync = true
        );
        
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
        void stop() { gameIsRunning = false; tickTime = 0.f; }
        
        /**
         * Push a game state onto the state stack. All prior states will be
         * paused, allowing the topmost state to receive hardware events.
         * 
         * @param A pointer to a gameState object allocated with "new."
         */
        bool pushGameState(lsGameState*);
        
        /**
         * Pop the topmost game state from the stack.
         * This will cause the next state in the stack to begin running again.
         * If there are no states left in the stack, the system will stop.
         */
        void popGameState();
        
        /**
         * Search for a game state in the stack and remove it if it exists.
         * 
         * @param A pointer to the desired game state.
         */
        void popGameState(lsGameState*);
        
        /**
         * Search for a game state in the stack and remove it if it exists.
         * 
         * @param An index of the desired game state.
         */
        void popGameState(unsigned index);
        
        /**
         * Get a game state using an index.
         * 
         * @param index
         * 
         * @return a pointer to the desired game state. Null if the index was
         * out of bounds.
         */
        lsGameState const* getGameState(unsigned index) const;
        
        /**
         * Get the index of a game state.
         * 
         * @param A pointer to the desired game state.
         * 
         * @return The index of the game state held within the game stack.
         * GAME_INVALID if the state was not found.
         */
        unsigned getGameStateIndex(lsGameState*);
        
        /**
         * @return The number of states managed by this system.
         */
        unsigned getGameStackSize() const { return gameStack.size(); }
        
        /**
         * Get a reference to the current display object.
         * 
         * @return const lsDisplay&
         */
        const lsDisplay& getDisplay() const;
        
        /**
         * Get a reference to the current display object.
         * 
         * @return lsDisplay&
         */
        lsDisplay& getDisplay();
        
        /**
         * Get a reference to the system prng (pseudo-random number generator).
         * 
         * @return const lsRandom&
         */
        const lsRandom& getPrng() const;
        
        /**
         * Get a reference to the system prng (pseudo-random number generator).
         * 
         * @return lsRandom&
         */
        lsRandom& getPrng();
        
        /**
         * Get the current number of ticks per frame (in milliseconds).
         * 
         * @return A floating point integer that represents the number of
         * milliseconds which have passed since the last complete update.
         */
        float getTickTime() const;
};

/*
 * Get a reference to the current display object.
 */
inline const lsDisplay& lsSubsystem::getDisplay() const {
    return display;
}

/*
 * Get a reference to the current display object.
 */
inline lsDisplay& lsSubsystem::getDisplay() {
    return display;
}

/*
 * Get a reference to the system prng (pseudo-random number generator).
 */
inline const lsRandom& lsSubsystem::getPrng() const {
    return *prng;
}

/*
 * Get a reference to the system prng (pseudo-random number generator).
 */
inline lsRandom& lsSubsystem::getPrng() {
    return *prng;
}

/*
 * Get the current number of ticks per frame (in milliseconds).
 */
inline float lsSubsystem::getTickTime() const {
    return tickTime;
}

#endif	/* __LS_SYSTEM_H__ */

