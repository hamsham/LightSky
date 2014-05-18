/* 
 * File:   testState.h
 * Author: hammy
 *
 * Created on January 19, 2014, 4:19 PM
 */

#ifndef __STATE_TESTSTATE_H__
#define	__STATE_TESTSTATE_H__

#include "main.h"
#include <GL/glew.h>
#include "shaderProgram.h"
#include "gameState.h"
#include "matrixStack.h"
#include "texture.h"
#include "vertexArray.h"
#include "bufferObject.h"
#include "textureAtlas.h"
#include "mesh.h"
#include "meshResource.h"

class testState final : virtual public gameState {
    /*
     * Event Management
     */
    private:
        int             mouseX = 0;
        int             mouseY = 0;
        shaderProgram   program = {};
        texture2d       tex = {};
        mesh            testMesh = {};
        mesh            textMesh = {};
        matrixStack*    matStack = nullptr;
        math::quat      orientation = {};
        textureAtlas    atlas = {};
        
        virtual void    onKeyboardUpEvent       (const SDL_KeyboardEvent*) override;
        virtual void    onKeyboardDownEvent     (const SDL_KeyboardEvent*) override;
        void            updateKeyStates         ();
        virtual void    onKeyboardTextEvent     (const SDL_TextInputEvent*) override;
        virtual void    onWindowEvent           (const SDL_WindowEvent*) override;
        
        virtual void    onMouseMoveEvent        (const SDL_MouseMotionEvent*) override;
        virtual void    onMouseButtonUpEvent    (const SDL_MouseButtonEvent*) override;
        virtual void    onMouseButtonDownEvent  (const SDL_MouseButtonEvent*) override;
        virtual void    onMouseWheelEvent       (const SDL_MouseWheelEvent*) override;
        
        void drawScene();
        
    public:
        testState();
        testState(const testState&) = delete;
        testState(testState&&) = delete;
        
        ~testState();
        
        testState& operator=(const testState&) = delete;
        testState& operator=(testState&&) = delete;
        
        bool onStart() override;
        void onRun(float) override;
        void onPause(float) override;
        void onStop() override;
};

#endif	/* __STATE_TESTSTATE_H__ */

