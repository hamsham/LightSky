/* 
 * File:   lightState.h
 * Author: miles
 *
 * Created on June 14, 2014, 3:19 AM
 */

#ifndef LIGHT_STATE_H
#define	LIGHT_STATE_H

#include "main.h"

class lightState final : virtual public lsGameState {
    /*
     * Event Management
     */
    private:
        int             mouseX                  = 0;
        int             mouseY                  = 0;
        lsTexture       lightVolume             = {LS_TEX_3D};
        lsShaderProgram shaderProg              = {};
        lsMatrixStack*  pMatStack               = nullptr;
        lsSceneManager* pScene                  = nullptr;
        bool*           pKeyStates              = nullptr;
        math::mat4*     pModelMatrices          = nullptr;
        math::quat      orientation             = {};
        
        virtual void    onKeyboardUpEvent       (const SDL_KeyboardEvent*) override;
        virtual void    onKeyboardDownEvent     (const SDL_KeyboardEvent*) override;
        virtual void    onKeyboardTextEvent     (const SDL_TextInputEvent*) override;
        virtual void    onWindowEvent           (const SDL_WindowEvent*) override;
        
        virtual void    onMouseMoveEvent        (const SDL_MouseMotionEvent*) override;
        virtual void    onMouseButtonUpEvent    (const SDL_MouseButtonEvent*) override;
        virtual void    onMouseButtonDownEvent  (const SDL_MouseButtonEvent*) override;
        virtual void    onMouseWheelEvent       (const SDL_MouseWheelEvent*) override;
        
        void            updateKeyStates         (float);
        
        bool            initMemory              ();
        bool            generateDrawModels      ();
        void            drawScene               ();
        void            terminate               ();
        
    public:
        lightState();
        lightState(const lightState&) = delete;
        lightState(lightState&&) = delete;
        
        ~lightState() {
            terminate();
        }
        
        lightState& operator=(const lightState&) = delete;
        lightState& operator=(lightState&&) = delete;
        
        bool onStart() override;
        void onRun(float) override;
        void onPause(float) override;
        void onStop() override;
};

#endif	/* LIGHT_STATE_H */

