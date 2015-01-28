/* 
 * File:   fbState.h
 * Author: miles
 *
 * Created on July 30, 2014, 9:50 PM
 */

#ifndef FRAMEBUFFER_STATE_H
#define	FRAMEBUFFER_STATE_H

#include <vector>

#include "lightsky/game/gameState.h"

#include "main.h"

/**----------------------------------------------------------------------------
 * Default resolutions for the framebuffer object test.
-----------------------------------------------------------------------------*/
enum fb_test_res_t : int {
    TEST_FRAMEBUFFER_WIDTH = 320,
    TEST_FRAMEBUFFER_HEIGHT = 240
};

/*-----------------------------------------------------------------------------
 * Forward declarations
-----------------------------------------------------------------------------*/
class controlState;

/**----------------------------------------------------------------------------
 * Framebuffer testing state
-----------------------------------------------------------------------------*/
class fbState final : virtual public ls::game::gameState {
    
    friend class controlState;
    
    /*
     * Event Management
     */
    private:
        controlState*           pControlState   = nullptr;
        ls::draw::sceneGraph*   pScene          = nullptr;
        ls::draw::defaultRenderStage* pRenderer = nullptr;
        
        bool            initMemory              ();
        
    public:
        virtual ~fbState();
        
        fbState         ();
        fbState         (const fbState&)        = delete;
        fbState         (fbState&&);
        
        fbState&        operator=               (const fbState&) = delete;
        fbState&        operator=               (fbState&&);
        
        bool            onStart                 () override;
        void            onRun                   () override;
        void            onPause                 () override;
        void            onStop                  () override;
        
        void            moveCamera              (const math::vec3& deltaPos);
        void            rotateCamera            (const math::vec3& deltaAngle);
};

#endif	/* FRAMEBUFFER_STATE_H */

