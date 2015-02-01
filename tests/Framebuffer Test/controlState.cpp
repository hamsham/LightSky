/* 
 * File:   controlState.cpp
 * Author: miles
 * 
 * Created on August 5, 2014, 9:50 PM
 */

#include <new> // std::nothrow
#include <utility> // std::move

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include "lightsky/game/gameSystem.h"

#include "display.h"
#include "controlState.h"
#include "fbState.h"

namespace {
enum {
    TEST_MAX_KEYBORD_STATES = 282, // according to https://wiki.libsdl.org/SDLScancodeLookup
};
} // end anonymous namespace

/*-------------------------------------
 * Construction, Assignment, and Destruction
-------------------------------------*/
controlState::~controlState() {
}

controlState::controlState() :
    gameState{}
{
    SDL_StopTextInput();
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

controlState::controlState(controlState&& state) :
    gameState{std::move(state)},
    mouseX{state.mouseX},
    mouseY{state.mouseY},
    pKeyStates{state.pKeyStates}
{
    state.mouseX = 0;
    state.mouseY = 0;
    state.pKeyStates = nullptr;
    
    SDL_StopTextInput();
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

controlState& controlState::operator=(controlState&& state) {
    gameState::operator=(std::move(state));
    
    mouseX = state.mouseX;
    state.mouseX = 0;
    
    mouseY = state.mouseY;
    state.mouseY = 0;
    
    pKeyStates = state.pKeyStates;
    state.pKeyStates = nullptr;
    
    return *this;
}

/*-------------------------------------
 * Parent framebuffer state management
-------------------------------------*/
void controlState::setFramebufferState(fbState* const pFramebufferState) {
    pFbState = pFramebufferState;
}

/*-------------------------------------
 * Starting state
-------------------------------------*/
bool controlState::onStart() {
    pKeyStates = new(std::nothrow) bool[TEST_MAX_KEYBORD_STATES];
    
    if (pKeyStates == nullptr) {
        return false;
    }
    
    // initialize the keybord
    for (unsigned i = 0;  i < TEST_MAX_KEYBORD_STATES; ++i) {
        pKeyStates[i] = false;
    }
    
    return true;
}

/*-------------------------------------
 * Running state
-------------------------------------*/
void controlState::onRun() {
    const math::vec2i&& displayRes = global::pDisplay->getResolution();
    glViewport(0, 0, displayRes[0], displayRes[1]);
    
    SDL_Event e;
    
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_WINDOWEVENT:       this->onWindowEvent(e.window);          break;
            case SDL_KEYUP:             this->onKeyboardUpEvent(e.key);         break;
            case SDL_KEYDOWN:           this->onKeyboardDownEvent(e.key);       break;
            case SDL_MOUSEMOTION:       this->onMouseMoveEvent(e.motion);       break;
            case SDL_MOUSEBUTTONDOWN:   this->onMouseButtonDownEvent(e.button); break;
            default: break;
        }
    }
    
    // update the camera position
    math::vec3 pos = {0.f};
    const float moveSpeed = 0.05f * (float)getParentSystem().getTickTime();
    
    if (pKeyStates[SDL_SCANCODE_W]) {
        pos[2] += moveSpeed;
    }
    if (pKeyStates[SDL_SCANCODE_S]) {
        pos[2] -= moveSpeed;
    }
    if (pKeyStates[SDL_SCANCODE_A]) {
        pos[0] += moveSpeed;
    }
    if (pKeyStates[SDL_SCANCODE_D]) {
        pos[0] -= moveSpeed;
    }
    
    pFbState->moveCamera(pos);
}

/*-------------------------------------
 * Stopping state
-------------------------------------*/
void controlState::onStop() {
    mouseX = 0;
    mouseY = 0;
    
    delete [] pKeyStates;
    pKeyStates = nullptr;
}

/*-------------------------------------
 * Key Up Event
-------------------------------------*/
void controlState::onKeyboardUpEvent(const SDL_KeyboardEvent& e) {
    const SDL_Keycode key = e.keysym.scancode;
    
    if (key == SDL_SCANCODE_ESCAPE) {
        ls::game::gameSystem& parentSys = getParentSystem();
        for (unsigned i = 0; i < parentSys.getNumGameStates(); ++i) {
            ls::game::gameState* const pState = parentSys.getGameState(i);
            pState->setStateStatus(ls::game::game_state_t::STOPPED);
        }
    }
    else if (key == SDL_SCANCODE_F11) {
        bool fullscreen = global::pDisplay->getFullScreenState();
        global::pDisplay->setFullScreenState(!fullscreen);
    }
    
    pKeyStates[key] = false;
}

/*-------------------------------------
 * Key Down Event
-------------------------------------*/
void controlState::onKeyboardDownEvent(const SDL_KeyboardEvent& e) {
    const SDL_Keycode key = e.keysym.scancode;
    
    pKeyStates[key] = true;
}

/*-------------------------------------
 * Window Event
-------------------------------------*/
void controlState::onWindowEvent(const SDL_WindowEvent& e) {
    if (e.event == SDL_WINDOWEVENT_CLOSE) {
        getParentSystem().stop();
    }
}

/*-------------------------------------
 * Mouse Button Down Event
-------------------------------------*/
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

/*-------------------------------------
 * Mouse Button Down Event
-------------------------------------*/
void controlState::onMouseMoveEvent(const SDL_MouseMotionEvent& e) {
    // Prevent the orientation from drifting by keeping track of the relative mouse offset
    if (this->getStateStatus() == ls::game::game_state_t::PAUSED
    || SDL_GetRelativeMouseMode() == SDL_FALSE
    || (mouseX == e.xrel && mouseY == e.yrel)
    ) {
        // I would rather quit the function than have unnecessary LERPs and
        // quaternion multiplications.
        return;
    }
    
    mouseX = e.xrel;
    mouseY = e.yrel;
    
    // Get the current mouse position and LERP from the previous mouse position.
    // The mouse position is divided by the window's resolution in order to normalize
    // the mouse delta between 0 and 1. This allows for the camera's orientation to
    // be LERPed without the need for multiplying it by the last time delta.
    // As a result, the camera's movement becomes as smooth and natural as possible.
    const math::vec2&& fRes = (math::vec2)global::pDisplay->getResolution();
    const math::vec3&& mouseDelta = math::vec3{
        (float)mouseX/fRes[0], (float)mouseY/fRes[1], 0.f
    };
    
    pFbState->rotateCamera(mouseDelta);
}
