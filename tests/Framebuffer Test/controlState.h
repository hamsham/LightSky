/* 
 * File:   controlState.h
 * Author: miles
 *
 * Created on August 5, 2014, 9:50 PM
 */

#ifndef CONTROLSTATE_H
#define	CONTROLSTATE_H

#include "main.h"

#include "lightsky/game/gameState.h"

class fbState;

/**----------------------------------------------------------------------------
 * Global Controller testing state
-----------------------------------------------------------------------------*/
class controlState final : virtual public ls::game::gameState {
    
    friend class fbState;
    
    /*
     * Event Management
     */
    private:
        int             mouseX                  = 0;
        int             mouseY                  = 0;
        bool*           pKeyStates              = nullptr;
        fbState*        pFbState                = nullptr;
        // ^set by the state that instantiated *this
        
        void            setFramebufferState     (fbState* const);
        
        void            onKeyboardUpEvent       (const SDL_KeyboardEvent&);
        void            onKeyboardDownEvent     (const SDL_KeyboardEvent&);
        void            onWindowEvent           (const SDL_WindowEvent&);
        void            onMouseMoveEvent        (const SDL_MouseMotionEvent&);
        void            onMouseButtonDownEvent  (const SDL_MouseButtonEvent&);
        
    public:
        virtual ~controlState();
        
        controlState    ();
        controlState    (const controlState&)   = delete;
        controlState    (controlState&&);
        
        controlState&   operator=               (const controlState&) = delete;
        controlState&   operator=               (controlState&&);
        
        bool            onStart                 () override;
        void            onRun                   () override;
        void            onStop                  () override;
};

#endif	/* CONTROLSTATE_H */

