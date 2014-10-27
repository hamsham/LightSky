/* 
 * File:   game/gameState.cpp
 * Author: Miles Lacey
 * 
 * Created on November 15, 2013, 8:45 PM
 */

#include "lightsky/game/gameState.h"

namespace ls {
namespace game {

/*-------------------------------------
    Destructor
-------------------------------------*/
gameState::~gameState() {
}

/*-------------------------------------
    Constructor
-------------------------------------*/
gameState::gameState() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
gameState::gameState(gameState&& gs) :
    pSystem{gs.pSystem},
    currentState{gs.currentState}
{
    gs.currentState = LS_GAME_STOPPED;
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
gameState& gameState::operator=(gameState&& gs) {
    pSystem = gs.pSystem;
    
    currentState = gs.currentState;
    gs.currentState = LS_GAME_STOPPED;
    
    return *this;
}

/*-------------------------------------
    Parent Sub-System Assignment.
-------------------------------------*/
void gameState::setParentSystem(system& pSys) {
    pSystem = &pSys;
}

/*-----------------------------------------------------------------------------
    Keyboard Events
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Event which allows a game state to input events when a keyboard key
    is disengaged.
-------------------------------------*/
void gameState::onKeyboardUpEvent(const SDL_KeyboardEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a keyboard key
    is pressed.
-------------------------------------*/
void gameState::onKeyboardDownEvent(const SDL_KeyboardEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a keyboard key
    is used for text entry.
-------------------------------------*/
void gameState::onKeyboardTextEvent(const SDL_TextInputEvent&) {
}

/*-----------------------------------------------------------------------------
    Window Events
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Event which allows a game state to input events when the current
    SDL display has been modified.
-------------------------------------*/
void gameState::onWindowEvent(const SDL_WindowEvent&) {
}

/*-----------------------------------------------------------------------------
    Mouse Events
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Event which allows a game state to input events when the mouse has
    moved.
-------------------------------------*/
void gameState::onMouseMoveEvent(const SDL_MouseMotionEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a button on the
    user's mouse has been depressed.
-------------------------------------*/
void gameState::onMouseButtonUpEvent(const SDL_MouseButtonEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a button on the
    user's mouse has been engaged.
-------------------------------------*/
void gameState::onMouseButtonDownEvent(const SDL_MouseButtonEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when the scroll wheel
    on the user's mouse has moved.
-------------------------------------*/
void gameState::onMouseWheelEvent(const SDL_MouseWheelEvent&) {
}

/*-----------------------------------------------------------------------------
    Controller Events
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Event which allows a game state to input events when a controller
    has been plugged in.
-------------------------------------*/
void gameState::onControllerAddedEvent(const SDL_ControllerDeviceEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a controller
    has disconnected.
-------------------------------------*/
void gameState::onControllerRemovedEvent(const SDL_ControllerDeviceEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a controller
    has been remapped.
-------------------------------------*/
void gameState::onControllerRemappedEvent(const SDL_ControllerDeviceEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a controller
    has modified its axes.
-------------------------------------*/
void gameState::onControllerAxisEvent(const SDL_ControllerAxisEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a controller
    has had a button released.
-------------------------------------*/
void gameState::onControllerButtonUpEvent(const SDL_ControllerButtonEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a controller
    has had a button pressed.
-------------------------------------*/
void gameState::onControllerButtonDownEvent(const SDL_ControllerButtonEvent&) {
}

/*-----------------------------------------------------------------------------
    Joystick Events
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Event which allows a game state to input events when a joystick
    has been plugged in.
-------------------------------------*/
void gameState::onJoyAddEvent(const SDL_JoyDeviceEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a joystick
    has been disconnected.
-------------------------------------*/
void gameState::onJoyRemoveEvent(const SDL_JoyDeviceEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a joystick
    has modified its axes.
-------------------------------------*/
void gameState::onJoyAxisEvent(const SDL_JoyAxisEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a joystick
    has changed it's trackball position.
-------------------------------------*/
void gameState::onJoyBallEvent(const SDL_JoyBallEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a joystick
    had a button pressed.
-------------------------------------*/
void gameState::onJoyButtonDownEvent(const SDL_JoyButtonEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a joystick
    had a button released.
-------------------------------------*/
void gameState::onJoyButtonUpEvent(const SDL_JoyButtonEvent&) {
}

/*-------------------------------------
    Event which allows a game state to input events when a joystick
    hat button event has occurred.
-------------------------------------*/
void gameState::onJoyHatEvent(const SDL_JoyHatEvent&) {
}

/*-----------------------------------------------------------------------------
    System Events
-----------------------------------------------------------------------------*/
/*-------------------------------------
    The onStart method is called by the parent subsystem when *this
    object has been notified to start. Place all memory allocations here.
-------------------------------------*/
bool gameState::onStart() {
    return true;
}

/*-------------------------------------
    The onStop method is used by the parent subsystem to indicate that
    *this game state should terminate. Place all memory cleanup here.
-------------------------------------*/
void gameState::onStop() {
}

/*-------------------------------------
    This method is used to tell the current game state that it should
    update its child components/variables/state.
-------------------------------------*/
void gameState::onRun(float) {
}

/*-------------------------------------
    This method is used by the parent subsystem to tell *this game state
    that it's paused.
-------------------------------------*/
void gameState::onPause(float) {
}

} // end game namespace
} // end ls namespace
