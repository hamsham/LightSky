/* 
 * File:   controlState.h
 * Author: miles
 *
 * Created on August 5, 2014, 9:50 PM
 */

#ifndef CONTROLSTATE_H
#define	CONTROLSTATE_H

#include "main.h"

#include "eventState.h"

/**
 * Global Controller testing state
 */
class controlState final : virtual public ls::game::gameState, public eventState {
    /*
     * Event Management
     */
    private:
        bool*           pKeyStates              = nullptr;
        
        void            onKeyboardUpEvent       (const SDL_KeyboardEvent&);
        void            onKeyboardDownEvent     (const SDL_KeyboardEvent&);
        void            onWindowEvent           (const SDL_WindowEvent&);
        void            onMouseButtonDownEvent  (const SDL_MouseButtonEvent&);
        
    public:
        virtual ~controlState();
        
        controlState    ();
        controlState    (const controlState&)   = delete;
        controlState    (controlState&&);
        
        controlState&   operator=               (const controlState&) = delete;
        controlState&   operator=               (controlState&&);
        
        void            onEvent                 (const SDL_Event&) override;
        
        bool            onStart                 () override;
        void            onRun                   () override;
        void            onPause                 () override;
        void            onStop                  () override;
};

#endif	/* CONTROLSTATE_H */

