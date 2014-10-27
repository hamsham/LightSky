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
class subsystem;

enum state_type : unsigned {
    GAME_INVALID = (unsigned)-1,
    
    GAME_PAUSED = 0,
    GAME_RUNNING = 1,
    GAME_STOPPED = 2,
};

class gameState {
    friend class subsystem;
    
    /*
     * Event Management
     */
    private:
        state_type currentState = state_type::GAME_STOPPED;
        
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
        gameState() {}
        gameState(const gameState&) = delete;
        gameState(gameState&&) = delete;
        
        virtual ~gameState() = 0;
        
        gameState& operator=(const gameState&) = delete;
        gameState& operator=(gameState&&) = delete;
        
        state_type getState() const { return currentState; }
        void setState(state_type s) { currentState = s; }
};

#endif	/* __LS_GAME_STATE_H__ */

