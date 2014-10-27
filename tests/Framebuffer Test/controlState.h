/* 
 * File:   controlState.h
 * Author: miles
 *
 * Created on August 5, 2014, 9:50 PM
 */

#ifndef CONTROLSTATE_H
#define	CONTROLSTATE_H

#include "main.h"

/**
 * Global Controller testing state
 */
class controlState final : virtual public ls::game::gameState {
    /*
     * Event Management
     */
    private:
        bool*           pKeyStates              = nullptr;
        
        virtual void    onKeyboardUpEvent       (const SDL_KeyboardEvent&) override;
        virtual void    onKeyboardDownEvent     (const SDL_KeyboardEvent&) override;
        virtual void    onKeyboardTextEvent     (const SDL_TextInputEvent&) override;
        virtual void    onWindowEvent           (const SDL_WindowEvent&) override;
        
        virtual void    onMouseMoveEvent        (const SDL_MouseMotionEvent&) override;
        virtual void    onMouseButtonUpEvent    (const SDL_MouseButtonEvent&) override;
        virtual void    onMouseButtonDownEvent  (const SDL_MouseButtonEvent&) override;
        virtual void    onMouseWheelEvent       (const SDL_MouseWheelEvent&) override;
        
    public:
        controlState    ();
        controlState    (const controlState&)   = delete;
        controlState    (controlState&&);
        
        ~controlState   ();
        
        controlState&   operator=               (const controlState&) = delete;
        controlState&   operator=               (controlState&&);
        
        bool            onStart                 () override;
        void            onRun                   (float) override;
        void            onPause                 (float) override;
        void            onStop                  () override;
};

#endif	/* CONTROLSTATE_H */

