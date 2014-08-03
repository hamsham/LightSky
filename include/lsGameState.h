/* 
 * File:   lsGameState.h
 * Author: hammy
 *
 * Created on November 15, 2013, 8:45 PM
 */

#ifndef __LS_GAME_STATE_H__
#define	__LS_GAME_STATE_H__

#include "lsSystem.h"

//-----------------------------------------------------------------------------
//      Forward declarations
//-----------------------------------------------------------------------------
struct SDL_WindowEvent;
struct SDL_KeyboardEvent;
struct SDL_TextInputEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;

//-----------------------------------------------------------------------------
//      Enumerations
//-----------------------------------------------------------------------------
/**
 * Enumeration to help manage interactions between the lsSubsystem and different
 * game state objects.
 */
enum ls_state_t : unsigned {
    LS_GAME_INVALID = (unsigned)-1,
    
    LS_GAME_PAUSED = 0,
    LS_GAME_RUNNING = 1,
    LS_GAME_STOPPED = 2,
};

//-----------------------------------------------------------------------------
//      Classes
//-----------------------------------------------------------------------------
/**
 * lsGameState
 * 
 * An Abstract base class that can be overridden to organize games onto stacks
 * within an lsSubsystem. lsGameState objects are pushed onto a "stack" managed
 * by the lsSubsystem. Game states are passed hardware events by subsystems when
 * they are running.
 */
class lsGameState {
    friend class lsSubsystem;
    
    /*
     * Event Management
     */
    private:
        /**
         * A "const" pointer to the parent lsSubsystem which manages *this.
         * this pointer is assigned automatically when a system is pushed onto
         * the subsystem's stack. Do not try to modify this.
         */
        mutable lsSubsystem* pSystem; // set by an lsSubsystem upon initialization
        
        /**
         * The current state that is used by *this. This variable is also
         * assigned by the parent subsystem and should not be modified.
         */
        ls_state_t currentState = LS_GAME_STOPPED;
        
        /**
         * Used by the parent subsystem to help with lsGameState management.
         * 
         * @param A reference to the parent subsystem.
         */
        void setParentSystem(lsSubsystem&);
        
    protected:
        // All hardware and "on###()" methods are called by their parent
        // subsystem.
        
        /**
         * Event which allows a game state to input events when a keyboard key
         * is disengaged.
         * 
         * @param A reference to an SDL_KeyboardEvent*
         */
        virtual void onKeyboardUpEvent(const SDL_KeyboardEvent&);
        
        /**
         * Event which allows a game state to input events when a keyboard key
         * is pressed.
         * 
         * @param A reference to an SDL_KeyboardEvent*
         */
        virtual void onKeyboardDownEvent(const SDL_KeyboardEvent&);
        
        /**
         * Event which allows a game state to input events when a keyboard key
         * is used for text entry.
         * 
         * @param A reference to an SDL_TextInputEvent*
         */
        virtual void onKeyboardTextEvent(const SDL_TextInputEvent&);
        
        /**
         * Event which allows a game state to input events when the current
         * SDL display has been modified.
         * 
         * @param A reference to an SDL_WindowEvent*
         */
        virtual void onWindowEvent(const SDL_WindowEvent&);
        
        /**
         * Event which allows a game state to input events when the mouse has
         * moved.
         * 
         * @param A reference to an SDL_MouseMotionEvent*
         */
        virtual void onMouseMoveEvent(const SDL_MouseMotionEvent&);
        
        /**
         * Event which allows a game state to input events when a button on the
         * user's mouse has been depressed.
         * 
         * @param A reference to an SDL_MouseButtonEvent*
         */
        virtual void onMouseButtonUpEvent(const SDL_MouseButtonEvent&);
        
        /**
         * Event which allows a game state to input events when a button on the
         * user's mouse has been engaged.
         * 
         * @param A reference to an SDL_MouseButtonEvent*
         */
        virtual void onMouseButtonDownEvent(const SDL_MouseButtonEvent&);
        
        /**
         * Event which allows a game state to input events when the scroll wheel
         * on the user's mouse has moved.
         * 
         * @param A reference to an SDL_MouseWheelEvent*
         */
        virtual void onMouseWheelEvent(const SDL_MouseWheelEvent&);
        
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
         * 
         * @param A floating-point number to indicate how many milliseconds
         * have passed since the last parent system update.
         */
        virtual void onRun(float);
        
        /**
         * This method is used by the parent subsystem to tell *this game state
         * that it's paused.
         * 
         * @param A floating-point number to indicate how many milliseconds
         * have passed since the last parent system update.
         */
        virtual void onPause(float);
        
    public:
        /**
         * Default Constructor.
         */
        lsGameState();
        
        /**
         * Copy Constructor -- DELETED
         * 
         * LightSky makes no attempts to copy game state objects.
         */
        lsGameState(const lsGameState&) = delete;
        
        /**
         * Move Constructor.
         * Moves all memory allocations from the input parameter into *this.
         * This method may be called at some point by the parent subsystem.
         * 
         * @param An r-value reference to a game state that's about to go out
         * of scope and be terminated.
         */
        lsGameState(lsGameState&&);
        
        /**
         * Destructor.
         * It is recommended to perform all object cleanup using the "onStop()"
         * method. This should be used as a last-resort.
         */
        virtual ~lsGameState() = 0;
        
        /**
         * Copy Operator -- DELETED
         * 
         * LightSky makes no attempts to copy game state objects.
         */
        lsGameState& operator=(const lsGameState&) = delete;
        
        /**
         * Move Operator.
         * Moves all memory allocations from the input parameter into *this.
         * This method may be called at some point by the parent subsystem.
         * 
         * @param An r-value reference to a game state that's about to go out
         * of scope and be terminated.
         * 
         * @return A reference to *this.
         */
        lsGameState& operator=(lsGameState&&);
        
        /**
         * Get the current state of *this object.
         * This object's state is used by the parent subsystem to determine when
         * it should go out of scope and terminate.
         * 
         * @return ls_state_t
         */
        ls_state_t getState() const;
        
        /**
         * Set the operational state of *this.
         * 
         * @param ls_state_t
         * The current runtime state of *this.
         */
        void setState(ls_state_t s);
        
        /*
         * Get the parent subsystem that manages *this.
         * 
         * @return A reference to *this object's managing lsSubsystem.
         */
        lsSubsystem& getParentSystem() const;
};

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/*
 * Get the current state of *this object.
 */
inline ls_state_t lsGameState::getState() const {
    return currentState;
}
        
/*
 * Set the operational state of *this.
 */
inline void lsGameState::setState(ls_state_t s) {
    currentState = s;
}

/*
 * Get the parent subsystem that manages *this.
 */
inline lsSubsystem& lsGameState::getParentSystem() const {
    return *pSystem;
}

#endif	/* __LS_GAME_STATE_H__ */

