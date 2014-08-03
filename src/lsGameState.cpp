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
void lsGameState::setParentSystem(lsSubsystem& pSys) {
    pSystem = &pSys;
}

/*
 * Event which allows a game state to input events when a keyboard key
 * is disengaged.
 */
void lsGameState::onKeyboardUpEvent(const SDL_KeyboardEvent&) {}

/*
 * Event which allows a game state to input events when a keyboard key
 * is pressed.
 */
void lsGameState::onKeyboardDownEvent(const SDL_KeyboardEvent&) {}

/*
 * Event which allows a game state to input events when a keyboard key
 * is used for text entry.
 */
void lsGameState::onKeyboardTextEvent(const SDL_TextInputEvent&) {}

/*
 * Event which allows a game state to input events when the current
 * SDL display has been modified.
 */
void lsGameState::onWindowEvent(const SDL_WindowEvent&) {}

/*
 * Event which allows a game state to input events when the mouse has
 * moved.
 */
void lsGameState::onMouseMoveEvent(const SDL_MouseMotionEvent&) {}

/*
 * Event which allows a game state to input events when a button on the
 * user's mouse has been depressed.
 */
void lsGameState::onMouseButtonUpEvent(const SDL_MouseButtonEvent&) {}

/*
 * Event which allows a game state to input events when a button on the
 * user's mouse has been engaged.
 */
void lsGameState::onMouseButtonDownEvent(const SDL_MouseButtonEvent&) {}

/*
 * Event which allows a game state to input events when the scroll wheel
 * on the user's mouse has moved.
 */
void lsGameState::onMouseWheelEvent(const SDL_MouseWheelEvent&) {}

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
