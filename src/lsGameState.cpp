/* 
 * File:   lsGameState.cpp
 * Author: hammy
 * 
 * Created on November 15, 2013, 8:45 PM
 */

#include "lsGameState.h"

/*
 * Destructor
 */
lsGameState::~lsGameState() {
}

/*
 * Constructor
 */
lsGameState::lsGameState() {
}

/*
 * Move Constructor
 */
lsGameState::lsGameState(lsGameState&& gs) :
    pSystem{gs.pSystem},
    currentState{gs.currentState}
{
    gs.currentState = LS_GAME_STOPPED;
}

/*
 * Move Operator
 */
lsGameState& lsGameState::operator=(lsGameState&& gs) {
    pSystem = gs.pSystem;
    
    currentState = gs.currentState;
    gs.currentState = LS_GAME_STOPPED;
    
    return *this;
}

/*
 * Parent Sub-System Assignment.
 */
void lsGameState::setParentSystem(lsSystem& pSys) {
    pSystem = &pSys;
}

//-----------------------------------------------------------------------------
//          Keyboard Events
//-----------------------------------------------------------------------------
/*
 * Event which allows a game state to input events when a keyboard key
 * is disengaged.
 */
void lsGameState::onKeyboardUpEvent(const SDL_KeyboardEvent&) {
}

/*
 * Event which allows a game state to input events when a keyboard key
 * is pressed.
 */
void lsGameState::onKeyboardDownEvent(const SDL_KeyboardEvent&) {
}

/*
 * Event which allows a game state to input events when a keyboard key
 * is used for text entry.
 */
void lsGameState::onKeyboardTextEvent(const SDL_TextInputEvent&) {
}

//-----------------------------------------------------------------------------
//          Window Events
//-----------------------------------------------------------------------------
/*
 * Event which allows a game state to input events when the current
 * SDL display has been modified.
 */
void lsGameState::onWindowEvent(const SDL_WindowEvent&) {
}

//-----------------------------------------------------------------------------
//          Mouse Events
//-----------------------------------------------------------------------------
/*
 * Event which allows a game state to input events when the mouse has
 * moved.
 */
void lsGameState::onMouseMoveEvent(const SDL_MouseMotionEvent&) {
}

/*
 * Event which allows a game state to input events when a button on the
 * user's mouse has been depressed.
 */
void lsGameState::onMouseButtonUpEvent(const SDL_MouseButtonEvent&) {
}

/*
 * Event which allows a game state to input events when a button on the
 * user's mouse has been engaged.
 */
void lsGameState::onMouseButtonDownEvent(const SDL_MouseButtonEvent&) {
}

/*
 * Event which allows a game state to input events when the scroll wheel
 * on the user's mouse has moved.
 */
void lsGameState::onMouseWheelEvent(const SDL_MouseWheelEvent&) {
}

//-----------------------------------------------------------------------------
//          Controller Events
//-----------------------------------------------------------------------------
/*
 * Event which allows a game state to input events when a controller
 * has been plugged in.
 */
void lsGameState::onControllerAddedEvent(const SDL_ControllerDeviceEvent&) {
}

/*
 * Event which allows a game state to input events when a controller
 * has disconnected.
 */
void lsGameState::onControllerRemovedEvent(const SDL_ControllerDeviceEvent&) {
}

/*
 * Event which allows a game state to input events when a controller
 * has been remapped.
 */
void lsGameState::onControllerRemappedEvent(const SDL_ControllerDeviceEvent&) {
}

/*
 * Event which allows a game state to input events when a controller
 * has modified its axes.
 */
void lsGameState::onControllerAxisEvent(const SDL_ControllerAxisEvent&) {
}

/*
 * Event which allows a game state to input events when a controller
 * has had a button released.
 */
void lsGameState::onControllerButtonUpEvent(const SDL_ControllerButtonEvent&) {
}

/*
 * Event which allows a game state to input events when a controller
 * has had a button pressed.
 */
void lsGameState::onControllerButtonDownEvent(const SDL_ControllerButtonEvent&) {
}
        
//-----------------------------------------------------------------------------
//          Joystick Events
//-----------------------------------------------------------------------------
/*
 * Event which allows a game state to input events when a joystick
 * has been plugged in.
 */
void lsGameState::onJoyAddEvent(const SDL_JoyDeviceEvent&) {
}

/*
 * Event which allows a game state to input events when a joystick
 * has been disconnected.
 */
void lsGameState::onJoyRemoveEvent(const SDL_JoyDeviceEvent&) {
}

/*
 * Event which allows a game state to input events when a joystick
 * has modified its axes.
 */
void lsGameState::onJoyAxisEvent(const SDL_JoyAxisEvent&) {
}

/*
 * Event which allows a game state to input events when a joystick
 * has changed it's trackball position.
 */
void lsGameState::onJoyBallEvent(const SDL_JoyBallEvent&) {
}

/*
 * Event which allows a game state to input events when a joystick
 * had a button pressed.
 */
void lsGameState::onJoyButtonDownEvent(const SDL_JoyButtonEvent&) {
}

/*
 * Event which allows a game state to input events when a joystick
 * had a button released.
 */
void lsGameState::onJoyButtonUpEvent(const SDL_JoyButtonEvent&) {
}

/*
 * Event which allows a game state to input events when a joystick
 * hat button event has occurred.
 */
void lsGameState::onJoyHatEvent(const SDL_JoyHatEvent&) {
}

//-----------------------------------------------------------------------------
//          System Events
//-----------------------------------------------------------------------------
/*
 * The onStart method is called by the parent subsystem when *this
 * object has been notified to start. Place all memory allocations here.
 */
bool lsGameState::onStart() {
    return true;
}

/*
 * The onStop method is used by the parent subsystem to indicate that
 * *this game state should terminate. Place all memory cleanup here.
 */
void lsGameState::onStop() {
}

/*
 * This method is used to tell the current game state that it should
 * update its child components/variables/state.
 */
void lsGameState::onRun(float) {
}

/*
 * This method is used by the parent subsystem to tell *this game state
 * that it's paused.
 */
void lsGameState::onPause(float) {
}
