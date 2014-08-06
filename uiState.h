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
class uiState final : virtual public lsGameState {
    /*
     * Event Management
     */
    private:
        lsShaderProgram fontProg            = {};
        lsSceneManager* pScene              = nullptr;
        lsBlendObject*  pBlender            = {};
        
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
        uiState       ();
        uiState       (const uiState&)      = delete;
        uiState       (uiState&&);
        
        ~uiState      ();
        
        uiState&      operator=             (const uiState&) = delete;
        uiState&      operator=             (uiState&&);
        
        bool            onStart             () override;
        void            onRun               (float) override;
        void            onPause             (float) override;
        void            onStop              () override;
};

#endif	/* UISTATE_H */

