/* 
 * File:   controlState.cpp
 * Author: miles
 * 
 * Created on August 5, 2014, 9:50 PM
 */

#include <new> // std::nothrow
#include <utility> // std::move

#include <SDL2/SDL.h>

#include "controlState.h"
#include "lsGameState.h"

/******************************************************************************
 * Construction, Assignment, and Destruction
******************************************************************************/
controlState::controlState() :
    lsGameState{}
{}

controlState::controlState(controlState&& state) :
lsGameState{}
{
    *this = (std::move(state));
}

controlState::~controlState() {
}

controlState& controlState::operator=(controlState&& state) {
    lsGameState::operator=(std::move(state));
    
    pKeyStates = state.pKeyStates;
    state.pKeyStates = nullptr;
    
    return *this;
}

/******************************************************************************
 * Key Up Event
******************************************************************************/
void controlState::onKeyboardUpEvent(const SDL_KeyboardEvent& e) {
    const SDL_Keycode key = e.keysym.scancode;
    
    if (key == SDL_SCANCODE_ESCAPE) {
        getParentSystem().stop();
    }
    else if (key == SDL_SCANCODE_F11) {
        bool fullscreen = getParentSystem().getDisplay().getFullScreenState();
        getParentSystem().getDisplay().setFullScreenState(!fullscreen);
    }
    else {
        pKeyStates[key] = false;
    }
}

/******************************************************************************
 * Key Down Event
******************************************************************************/
void controlState::onKeyboardDownEvent(const SDL_KeyboardEvent& e) {
    const SDL_Keycode key = e.keysym.scancode;
    
    pKeyStates[key] = true;
}

/******************************************************************************
 * Text Events
******************************************************************************/
void controlState::onKeyboardTextEvent(const SDL_TextInputEvent&) {
}

/******************************************************************************
 * Window Event
******************************************************************************/
void controlState::onWindowEvent(const SDL_WindowEvent& e) {
    if (e.event == SDL_WINDOWEVENT_CLOSE) {
        getParentSystem().stop();
    }
}

/******************************************************************************
 * Mouse Move Event
******************************************************************************/
void controlState::onMouseMoveEvent(const SDL_MouseMotionEvent&) {
}

/******************************************************************************
 * Mouse Button Up Event
******************************************************************************/
void controlState::onMouseButtonUpEvent(const SDL_MouseButtonEvent&) {
}

/******************************************************************************
 * Mouse Button Down Event
******************************************************************************/
void controlState::onMouseButtonDownEvent(const SDL_MouseButtonEvent& e) {
    // Allow the mouse to enter/exit the window when the user pleases.
    if (e.button == SDL_BUTTON_LEFT) {
        // testing mouse capture for framebuffer/window resizing
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
    else if (e.button == SDL_BUTTON_RIGHT) {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

/******************************************************************************
 * Mouse Wheel Event
******************************************************************************/
void controlState::onMouseWheelEvent(const SDL_MouseWheelEvent&) {
}

/******************************************************************************
 * Starting state
******************************************************************************/
bool controlState::onStart() {
    pKeyStates = new(std::nothrow) bool[TEST_MAX_KEYBORD_STATES];
    
    return pKeyStates != nullptr;
}

/******************************************************************************
 * Stopping state
******************************************************************************/
void controlState::onStop() {
    delete [] pKeyStates;
    pKeyStates = nullptr;
}

/******************************************************************************
 * Running state
******************************************************************************/
void controlState::onRun(float) {
}

/******************************************************************************
 * Pausing state
******************************************************************************/
void controlState::onPause(float) {
}

