/* 
 * File:   testState.h
 * Author: miles
 *
 * Created on June 13, 2014, 11:26 PM
 */

#ifndef __TESTSTATE_H__
#define	__TESTSTATE_H__

#include "main.h"

class testState final : virtual public lsGameState {
    /*
     * Event Management
     */
    private:
        int             mouseX = 0;
        int             mouseY = 0;
        lsShaderProgram   meshProgram = {};
        lsShaderProgram   fontProgram = {};
        lsMatrixStack*    matStack = nullptr;
        math::quat      orientation = {};
        lsSceneManager*   pScene = nullptr;
        
        virtual void    onKeyboardUpEvent       (const SDL_KeyboardEvent*) override;
        virtual void    onKeyboardDownEvent     (const SDL_KeyboardEvent*) override;
        void            updateKeyStates         ();
        virtual void    onKeyboardTextEvent     (const SDL_TextInputEvent*) override;
        virtual void    onWindowEvent           (const SDL_WindowEvent*) override;
        
        virtual void    onMouseMoveEvent        (const SDL_MouseMotionEvent*) override;
        virtual void    onMouseButtonUpEvent    (const SDL_MouseButtonEvent*) override;
        virtual void    onMouseButtonDownEvent  (const SDL_MouseButtonEvent*) override;
        virtual void    onMouseWheelEvent       (const SDL_MouseWheelEvent*) override;
        
        bool generateDrawModels();
        void drawScene();
        void terminate();
        
    public:
        testState();
        testState(const testState&) = delete;
        testState(testState&&) = delete;
        
        ~testState() {
            terminate();
        }
        
        testState& operator=(const testState&) = delete;
        testState& operator=(testState&&) = delete;
        
        bool onStart() override;
        void onRun(float) override;
        void onPause(float) override;
        void onStop() override;
};

#endif	/* __TESTSTATE_H__ */

