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
        
        virtual void    onSystemEvent           (const SDL_Event&) override;
        void            onKeyboardUpEvent       (const SDL_KeyboardEvent&);
        void            onKeyboardDownEvent     (const SDL_KeyboardEvent&);
        void            onWindowEvent           (const SDL_WindowEvent&);
        void            onMouseButtonDownEvent  (const SDL_MouseButtonEvent&);
        
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

