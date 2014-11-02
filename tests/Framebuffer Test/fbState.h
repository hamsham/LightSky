/* 
 * File:   fbState.h
 * Author: miles
 *
 * Created on July 30, 2014, 9:50 PM
 */

#ifndef FRAMEBUFFER_STATE_H
#define	FRAMEBUFFER_STATE_H

#include <future>
#include <vector>

#include "main.h"

/**
 * Default resolutions for the framebuffer object test.
 */
enum fb_test_res_t : int {
    TEST_FRAMEBUFFER_WIDTH = 320,
    TEST_FRAMEBUFFER_HEIGHT = 240
};

/**
 * Function to generate a perlin noise texture on another thread.
 * 
 * @param w
 * The width of the texture that should be generated.
 * 
 * @param h
 * The height of the texture that should be generated.
 * 
 * @return A greyscale texture containing perlin noise
 */
std::vector<float> generateNoiseTexture(int w, int h);

/**
 * Framebuffer testing state
 */
class fbState final : virtual public ls::game::gameState {
    /*
     * Event Management
     */
    private:
        float                   secondTimer     = 0.f;
        int                     mouseX          = 0;
        int                     mouseY          = 0;
        ls::draw::shaderProgram meshProg        = {};
        ls::draw::framebuffer   testFb          = {};
        ls::draw::matrixStack*  pMatStack       = nullptr;
        ls::draw::sceneManager* pScene          = nullptr;
        bool*                   pKeyStates      = nullptr;
        math::mat4*             pModelMatrices  = nullptr;
        math::vec2i             fbRes           = {TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT};
        math::quat              orientation     = {};
        
        // allows textures to be generated on another thread
        std::future<std::vector<float>> futureNoise;
        
        virtual void    onSystemEvent           (const SDL_Event&) override;
        void            onKeyboardUpEvent       (const SDL_KeyboardEvent&);
        void            onKeyboardDownEvent     (const SDL_KeyboardEvent&);
        void            onWindowEvent           (const SDL_WindowEvent&);
        void            onMouseMoveEvent        (const SDL_MouseMotionEvent&);
        void            onMouseWheelEvent       (const SDL_MouseWheelEvent&);
        
        void            updateKeyStates         (float);
        
        bool            initMemory              ();
        bool            initFileData            ();
        bool            initShaders             ();
        bool            initMatrices            ();
        bool            initDrawModels          ();
        bool            initFramebuffers        ();
        void            setRendererParams       ();
        
        math::mat4      get3dViewport           () const;
        void            resetGlViewport         ();
        
        void            regenerateNoise         ();
        
        void            drawScene               ();
        
    public:
        fbState         ();
        fbState         (const fbState&)        = delete;
        fbState         (fbState&&);
        
        ~fbState        ();
        
        fbState&        operator=               (const fbState&) = delete;
        fbState&        operator=               (fbState&&);
        
        bool            onStart                 () override;
        void            onRun                   (float) override;
        void            onPause                 (float) override;
        void            onStop                  () override;
};

#endif	/* FRAMEBUFFER_STATE_H */

