/* 
 * File:   game/gameState.h
 * Author: Miles Lacey
 *
 * Created on November 15, 2013, 8:45 PM
 */

#ifndef __LS_GAME_GAME_STATE_H__
#define	__LS_GAME_GAME_STATE_H__

#include <cstdint>

namespace ls {
namespace game {

class gameSystem;

/**----------------------------------------------------------------------------
    A game_state_t is a type used in order to help manage interactions between
    ls::game::system objects and different game state objects.
-----------------------------------------------------------------------------*/
enum class game_state_t : int {
    PAUSED      = 0,
    RUNNING     = 1,
    STOPPED     = 2,
    STARTING    = 3
};

/**----------------------------------------------------------------------------
    @brief Game State Base Class
    
    An Abstract base class that can be overridden to organize games onto stacks
    within an lsSubsystem. gameState objects are pushed onto a "stack" managed
    by the lsSubsystem. Game states are passed hardware events by subsystems
    when they are running.
-----------------------------------------------------------------------------*/
class gameState {
    friend class gameSystem;
    
    private:
        /**
         * The current state that is used by *this. This variable is also
         * assigned by the parent subsystem and should not be modified.
         */
        game_state_t currentState = game_state_t::STOPPED;
        
        /**
         * A "const" pointer to the parent lsSubsystem which manages *this.
         * this pointer is assigned automatically when a system is pushed onto
         * the subsystem's stack. Do not try to modify this.
         */
        mutable gameSystem* pSystem; // set by an lsSubsystem upon initialization
        
        /**
         * Used by the parent subsystem to help with gameState management.
         * 
         * @param sys
         * A reference to the parent subsystem.
         */
        void setParentSystem(gameSystem& sys);
        
    protected:
        /*---------------------------------------------------------------------
            System Events
        ---------------------------------------------------------------------*/
        /**
         * The onStart method is called by the parent subsystem when *this
         * object has been notified to start. Place all memory allocations here.
         * 
         * @return bool
         * TRUE to indicate that *this has successfully initialized, FALSE if
         * otherwise.
         */
        virtual bool onStart();
        
        /**
         * The onStop method is used by the parent subsystem to indicate that
         * *this game state should terminate. Place all memory cleanup here.
         */
        virtual void onStop();
        
        /**
         * This method is used to tell the current game state that it should
         * update its child components/variables/state.
         */
        virtual void onRun();
        
        /**
         * This method is used by the parent subsystem to tell *this game state
         * that it's paused.
         */
        virtual void onPause();
        
    public:
        /**
         * @brief Default Constructor
         */
        gameState();
        
        /**
         * Copy Constructor -- DELETED
         * 
         * LightSky makes no attempts to copy game state objects.
         */
        gameState(const gameState&) = delete;
        
        /**
         * @brief Move Constructor
         * 
         * Moves all memory allocations from the input parameter into *this.
         * This method may be called at some point by the parent subsystem.
         * 
         * @param gs
         * An r-value reference to a game state who's members are to be moved
         * into *this.
         */
        gameState(gameState&& gs);
        
        /**
         * @brief Destructor
         * 
         * It is recommended to perform all object cleanup using the "onStop()"
         * method. This should be used as a last-resort.
         */
        virtual ~gameState() = 0;
        
        /**
         * @brief Copy Operator -- DELETED
         * 
         * LightSky makes no attempts to copy game state objects.
         */
        gameState& operator=(const gameState&) = delete;
        
        /**
         * @brief Move Operator
         * 
         * Moves all memory allocations from the input parameter into *this.
         * This method may be called at some point by the parent subsystem.
         * 
         * @param gs
         * An r-value reference to a game state that's about to go out
         * of scope and be terminated.
         * 
         * @return A reference to *this.
         */
        gameState& operator=(gameState&& gs);
        
        /**
         * Get the current state of *this object.
         * This object's state is used by the parent subsystem to determine when
         * it should go out of scope and terminate.
         * 
         * @return game_state_t
         */
        game_state_t getStateStatus() const;
        
        /**
         * Set the operational state of *this.
         * 
         * @param s
         * A game_state_t which will be used to set the current runtime state
         * of *this.
         */
        void setStateStatus(game_state_t s);
        
        /*
         * Get the parent subsystem that manages *this.
         * 
         * @return A reference to *this object's managing lsSubsystem.
         */
        gameSystem& getParentSystem() const;
        
        /**
         * @brief Check if the current state is running.
         * 
         * @return True if this object's current state is set to
         * game_state_t::RUNNING, return false if not.
         */
        virtual bool isRunning() const;
        
        /**
         * @brief Check if the current state is paused.
         * 
         * @return True if this object's current state is set to
         * game_state_t::PAUSED, return false if not.
         */
        virtual bool isPaused() const;
        
        /**
         * @brief Check if the current state is initializing.
         * 
         * @return True if this object's current state is set to
         * game_state_t::STARTING, return false if not.
         */
        virtual bool isStarting() const;
        
        /**
         * @brief Check if the current state is stopped.
         * 
         * @return True if this object's current state is set to
         * game_state_t::STOPPED, return false if not.
         */
        virtual bool isStopped() const;
};

} // end game namespace
} // end ls namespace

#include "lightsky/game/generic/gameState_impl.h"

#endif	/* __LS_GAME_GAME_STATE_H__ */
