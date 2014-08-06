/* 
 * File:   fbState.h
 * Author: miles
 *
 * Created on July 30, 2014, 9:50 PM
 */

#ifndef FRAMEBUFFER_STATE_H
#define	FRAMEBUFFER_STATE_H

#include "lightSky.h"

/**
 * Default resolutions for the framebuffer object test.
 */
enum fb_test_res_t : int {
    TEST_FRAMEBUFFER_WIDTH = 320,
    TEST_FRAMEBUFFER_HEIGHT = 240
};

/**
 * Framebuffer testing state
 */
class fbState final : virtual public lsGameState {
    /*
     * Event Management
     */
    private:
        int             mouseX                  = 0;
        int             mouseY                  = 0;
        lsShaderProgram meshProg                = {};
        lsShaderProgram fontProg                = {};
        lsFramebuffer   testFb                  = {};
        lsMatrixStack*  pMatStack               = nullptr;
        lsSceneManager* pScene                  = nullptr;
        bool*           pKeyStates              = nullptr;
        math::mat4*     pModelMatrices          = nullptr;
        math::vec2i     fbRes                   = {TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT};
        math::quat      orientation             = {};
        lsBlendObject*  pBlender                = {};
        
        virtual void    onKeyboardUpEvent       (const SDL_KeyboardEvent&) override;
        virtual void    onKeyboardDownEvent     (const SDL_KeyboardEvent&) override;
        virtual void    onKeyboardTextEvent     (const SDL_TextInputEvent&) override;
        virtual void    onWindowEvent           (const SDL_WindowEvent&) override;
        
        virtual void    onMouseMoveEvent        (const SDL_MouseMotionEvent&) override;
        virtual void    onMouseButtonUpEvent    (const SDL_MouseButtonEvent&) override;
        virtual void    onMouseButtonDownEvent  (const SDL_MouseButtonEvent&) override;
        virtual void    onMouseWheelEvent       (const SDL_MouseWheelEvent&) override;
        
        void            updateKeyStates         (float);
        
        bool            initMemory              ();
        bool            initFileData            ();
        bool            initShaders             ();
        bool            initMatrices            ();
        bool            initDrawModels          ();
        bool            initFramebuffers        ();
        void            setRendererParams       ();
        
        void            terminate               ();
        
        std::string     getTimingStr            () const;
        math::mat4      get3dViewport           () const;
        math::mat4      get2dViewport           () const;
        
        void            resetGlViewport          ();
        
        void            drawScene               ();
        void            drawMeshes              ();
        void            drawStrings             ();
        
    public:
        fbState         ();
        fbState         (const fbState&)        = delete;
        fbState         (fbState&&)             = delete;
        
        ~fbState        ();
        
        fbState&        operator=               (const fbState&) = delete;
        fbState&        operator=               (fbState&&) = delete;
        
        bool            onStart                 () override;
        void            onRun                   (float) override;
        void            onPause                 (float) override;
        void            onStop                  () override;
};

#endif	/* FRAMEBUFFER_STATE_H */

