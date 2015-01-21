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

#include "lightsky/game/gameState.h"

#include "main.h"

/**----------------------------------------------------------------------------
 * Default resolutions for the framebuffer object test.
-----------------------------------------------------------------------------*/
enum fb_test_res_t : int {
    TEST_FRAMEBUFFER_WIDTH = 320,
    TEST_FRAMEBUFFER_HEIGHT = 240
};

/**----------------------------------------------------------------------------
 * Function to generate a perlin noise texture on another thread.
 * 
 * @param w
 * The width of the texture that should be generated.
 * 
 * @param h
 * The height of the texture that should be generated.
 * 
 * @return A greyscale texture containing perlin noise
-----------------------------------------------------------------------------*/
std::vector<float> generateNoiseTexture(int w, int h);

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
        float                   secondTimer     = 0.f;
        ls::draw::framebuffer   testFb          = {};
        ls::draw::renderbuffer  testRb          = {};
        ls::draw::sceneGraph*   pScene          = nullptr;
        ls::draw::defaultRenderStage* pRenderer = nullptr;
        math::vec2i             fbRes           = {TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT};
        math::quat              orientation     = {};
        
        // allows textures to be generated on another thread
        std::future<std::vector<float>> futureNoise;
        
        void            updateKeyStates         ();
        
        bool            initMemory              ();
        bool            initFileData            ();
        bool            initRenderer            ();
        bool            initFramebuffers        ();
        void            setRendererParams       ();
        
        math::mat4      get3dViewport           () const;
        
        void            regenerateNoise         ();
        
        void            drawScene               ();
        
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
        void            resizeFramebuffer       (const math::vec2i& res);
        void            scaleFramebuffer        (const int deltaScale);
        void            rotateCamera            (const math::vec3& deltaAngle);
        void            translateCamera         (const math::vec3& deltaPos);
};

#endif	/* FRAMEBUFFER_STATE_H */

