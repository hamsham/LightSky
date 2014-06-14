/* 
 * File:   gameState.h
 * Author: hammy
 *
 * Created on November 15, 2013, 8:45 PM
 */

#ifndef __LS_GAME_STATE_H__
#define	__LS_GAME_STATE_H__

// Forward declarations
struct SDL_WindowEvent;
struct SDL_KeyboardEvent;
struct SDL_TextInputEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;
class lsSubsystem;

enum ls_state_t : unsigned {
    LS_GAME_INVALID = (unsigned)-1,
    
    LS_GAME_PAUSED = 0,
    LS_GAME_RUNNING = 1,
    LS_GAME_STOPPED = 2,
};

class lsGameState {
    friend class lsSubsystem;
    
    /*
     * Event Management
     */
    private:
        ls_state_t currentState = LS_GAME_STOPPED;
        
    protected:
        // The hardware and OnFoo methods are called by their associated system,
        virtual void onKeyboardUpEvent(const SDL_KeyboardEvent*) {}
        virtual void onKeyboardDownEvent(const SDL_KeyboardEvent*) {}
        virtual void onKeyboardTextEvent(const SDL_TextInputEvent*) {}
        virtual void onWindowEvent(const SDL_WindowEvent*) {}
        
        virtual void onMouseMoveEvent(const SDL_MouseMotionEvent*) {}
        virtual void onMouseButtonUpEvent(const SDL_MouseButtonEvent*) {}
        virtual void onMouseButtonDownEvent(const SDL_MouseButtonEvent*) {}
        virtual void onMouseWheelEvent(const SDL_MouseWheelEvent*) {}
        
        virtual bool onStart() { return true; }
        virtual void onStop() {}
        virtual void onRun(float) {}
        virtual void onPause(float) {}
        
    public:
        lsGameState() {}
        lsGameState(const lsGameState&) = delete;
        lsGameState(lsGameState&&) = delete;
        
        virtual ~lsGameState() = 0;
        
        lsGameState& operator=(const lsGameState&) = delete;
        lsGameState& operator=(lsGameState&&) = delete;
        
        ls_state_t getState() const {return currentState;}
        void setState(ls_state_t s) {currentState = s;}
};

#endif	/* __LS_GAME_STATE_H__ */

