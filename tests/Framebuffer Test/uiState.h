/* 
 * File:   uiState.h
 * Author: miles
 *
 * Created on August 5, 2014, 9:18 PM
 */

#ifndef UISTATE_H
#define	UISTATE_H

#include "main.h"

/**
 * Text/UI testing state
 */
class uiState final : virtual public ls::game::gameState {
    /*
     * Event Management
     */
    private:
        float                   secondTimer = 0.f;
        ls::draw::shaderProgram fontProg    = {};
        ls::draw::sceneManager* pScene      = nullptr;
        ls::draw::blendObject*  pBlender    = {};
        
        bool            initMemory          ();
        bool            initFileData        ();
        bool            initShaders         ();
        bool            initDrawModels      ();
        void            setRendererParams   ();
        
        std::string     getTimingStr        () const;
        
        math::mat4      get2dViewport       () const;
        void            resetGlViewport     ();
        
        void            drawScene           ();
        
    public:
        uiState         ();
        uiState         (const uiState&)      = delete;
        uiState         (uiState&&);
        
        ~uiState        ();
        
        uiState&        operator=             (const uiState&) = delete;
        uiState&        operator=             (uiState&&);
        
        bool            onStart             () override;
        void            onRun               (float) override;
        void            onPause             (float) override;
        void            onStop              () override;
};

#endif	/* UISTATE_H */

