/* 
 * File:   uiState.h
 * Author: miles
 *
 * Created on August 5, 2014, 9:18 PM
 */

#ifndef UISTATE_H
#define	UISTATE_H

#include "lightsky/game/gameState.h"

#include "main.h"

/**
 * Text/UI testing state
 */
class uiState final : virtual public ls::game::gameState {
    /*
     * Event Management
     */
    private:
        uint64_t                secondTimer = 0.f;
        ls::draw::atlas         fontAtlas   = {};
        ls::draw::sceneGraph*   pScene      = nullptr;
        ls::draw::textRenderStage* pRenderer = nullptr;
        
        std::string     getTimingStr        () const;
        void            reset2dViewport     () const;
        void            drawScene           ();
        
    public:
        virtual ~uiState();
        
        uiState         ();
        uiState         (const uiState&)    = delete;
        uiState         (uiState&&);
        
        uiState&        operator=           (const uiState&) = delete;
        uiState&        operator=           (uiState&&);
        
        bool            onStart             () override;
        void            onRun               () override;
        void            onPause             () override;
        void            onStop              () override;
};

#endif	/* UISTATE_H */

