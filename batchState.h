/* 
 * File:   batchState.h
 * Author: miles
 *
 * Created on June 14, 2014, 3:19 AM
 */

#ifndef BATCH_STATE_H
#define	BATCH_STATE_H

#include "main.h"

class batchState final : virtual public lsGameState {
    /*
     * Event Management
     */
    private:
        int             mouseX                  = 0;
        int             mouseY                  = 0;
        lsShaderProgram shaderProg              = {};
        lsMatrixStack*  pMatStack               = nullptr;
        lsSceneManager* pScene                  = nullptr;
        math::vec3*     pPositions              = nullptr; // array of 3 vec3's
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
        
        void            updateKeyStates         ();
        
        bool initMemory();
        bool generateDrawModels();
        void drawScene();
        void terminate();
        
    public:
        batchState();
        batchState(const batchState&) = delete;
        batchState(batchState&&) = delete;
        
        ~batchState() {
            terminate();
        }
        
        batchState& operator=(const batchState&) = delete;
        batchState& operator=(batchState&&) = delete;
        
        bool onStart() override;
        void onRun(float) override;
        void onPause(float) override;
        void onStop() override;
};

#endif	/* BATCH_STATE_H */

