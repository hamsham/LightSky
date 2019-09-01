/*
 * File:   ControlState.cpp
 * Author: miles
 *
 * Created on August 5, 2014, 9:50 PM
 */

#include <new> // std::nothrow
#include <utility> // std::move

#include "lightsky/math/Math.h"

#include "lightsky/draw/Setup.h"

#include "lightsky/game/GameSystem.h"

#include "MainState.h"
#include "Display.h"
#include "ControlState.h"

namespace math = ls::math;
namespace draw = ls::draw;
namespace utils = ls::utils;
namespace game = ls::game;



/*-----------------------------------------------------------------------------
 * Provate internal variables
-----------------------------------------------------------------------------*/
namespace {

enum {
    TEST_MAX_KEYBORD_STATES = 282, // according to https://wiki.libsdl.org/SDLScancodeLookup
};

} // end anonymous namespace



/*-----------------------------------------------------------------------------
 * Control Class
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Destructor
-------------------------------------*/
ControlState::~ControlState() {
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
ControlState::ControlState() :
    GameState {},
    mouseX{0.f},
    mouseY{0.f},
    pEvent{nullptr},
    pKeyStates{nullptr},
    camTrans{draw::transform_type_t::TRANSFORM_TYPE_VIEW_ARC_LOCKED_Y},
    camProjection{},
    vpMatrix{}
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
ControlState::ControlState(ControlState&& state) :
    GameState{std::move(state)},
    mouseX{state.mouseX},
    mouseY{state.mouseY},
    pEvent{std::move(state.pEvent)},
    pKeyStates{std::move(state.pKeyStates)},
    camTrans{std::move(state.camTrans)},
    camProjection{std::move(state.camProjection)},
    vpMatrix{std::move(state.vpMatrix)}
{
    state.mouseX = 0.f;
    state.mouseY = 0.f;

    SDL_SetRelativeMouseMode(SDL_TRUE);
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
ControlState& ControlState::operator =(ControlState&& state) {
    GameState::operator =(std::move(state));

    mouseX = state.mouseX;
    state.mouseX = 0.f;

    mouseY = state.mouseY;
    state.mouseY = 0.f;

    pEvent = std::move(state.pEvent);
    pKeyStates = std::move(state.pKeyStates);
    
    camTrans = std::move(state.camTrans);
    
    camProjection = std::move(state.camProjection);
    
    vpMatrix = std::move(state.vpMatrix);

    return *this;
}

/*-------------------------------------
 * Setup the main camera
-------------------------------------*/
void ControlState::setup_camera() {
    camProjection.set_fov(LS_DEG2RAD(60.f));
    camProjection.set_aspect_ratio((math::vec2)global::pDisplay->get_resolution());
    camProjection.set_near_plane(0.1f);
    camProjection.set_far_plane(1000.f);
    camProjection.set_projection_type(draw::projection_type_t::PROJECTION_PERSPECTIVE);

    camTrans.set_type(draw::transform_type_t::TRANSFORM_TYPE_VIEW_FPS_LOCKED_Y);
    //camTrans.set_type(draw::transform_type_t::TRANSFORM_TYPE_VIEW_ARC_LOCKED_Y);
    //camTrans.look_at(math::vec3{5.f}, math::vec3{0.f});
    camTrans.look_at(math::vec3{0.f}, math::vec3{3.f, -5.f, 0.f}, math::vec3{0.f, 1.f, 0.f});
    camTrans.lock_y_axis(true);
}

/*-------------------------------------
 * Starting state
-------------------------------------*/
bool ControlState::on_start() {
    pEvent.reset(new SDL_Event);
    pKeyStates.reset(new bool[TEST_MAX_KEYBORD_STATES]);

    if (pKeyStates == nullptr) {
        return false;
    }

    // initialize the keyboard
    for (unsigned i = 0; i < TEST_MAX_KEYBORD_STATES; ++i) {
        pKeyStates[i] = false;
    }
    
    setup_camera();

    return true;
}

/*-------------------------------------
 * Running state
-------------------------------------*/
void ControlState::on_run() {
    const math::vec2i& displayRes = global::pDisplay->get_resolution();
    camProjection.set_aspect_ratio((math::vec2)displayRes);
    
    glViewport(0, 0, displayRes[0], displayRes[1]);

    while (SDL_PollEvent(pEvent.get())) {
        switch (pEvent->type) {
            case SDL_WINDOWEVENT:
                this->on_window_event(pEvent->window);
                break;
                
            case SDL_KEYUP:
                this->on_key_up_event(pEvent->key);
                break;
                
            case SDL_KEYDOWN:
                this->on_key_down_event(pEvent->key);
                break;
                
            case SDL_MOUSEMOTION:
                this->on_mouse_move_event(pEvent->motion);
                break;
                
            case SDL_FINGERMOTION:
                this->on_track_mouse_event(pEvent->tfinger);
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                this->on_mouse_down_event(pEvent->button);
                break;
                
            case SDL_MOUSEWHEEL:
                this->on_wheel_event(pEvent->wheel);
                break;
                
            default:
                break;
        }
    }

    // update the camera position
    math::vec3 pos = {0.f};
    const float moveSpeed = 0.005f * (float)get_parent_system().get_tick_time();

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
    if (pKeyStates[SDL_SCANCODE_Q]) {
        pos[1] += moveSpeed;
    }
    if (pKeyStates[SDL_SCANCODE_E]) {
        pos[1] -= moveSpeed;
    }
    
    if (pKeyStates[SDL_SCANCODE_1]
    && camTrans.get_type() != draw::transform_type_t::TRANSFORM_TYPE_VIEW_ARC
    ) {
        camTrans.set_type(draw::transform_type_t::TRANSFORM_TYPE_VIEW_ARC);
    }
    if (pKeyStates[SDL_SCANCODE_2]
    && camTrans.get_type() != draw::transform_type_t::TRANSFORM_TYPE_VIEW_FPS
    ) {
        camTrans.set_type(draw::transform_type_t::TRANSFORM_TYPE_VIEW_FPS);
    }
    if (pKeyStates[SDL_SCANCODE_3] && !camTrans.is_y_axis_locked()) {
        camTrans.lock_y_axis(true);
        camTrans.look_at(camTrans.get_position(), math::vec3{0.f}, math::vec3{0.f, 1.f, 0.f});
    }
    if (pKeyStates[SDL_SCANCODE_4]) {
        camTrans.lock_y_axis(false);
    }
    
    if (pKeyStates[SDL_SCANCODE_ESCAPE]) {
        get_parent_system().stop();
    }
    
    if (pKeyStates[SDL_SCANCODE_F11]) {
        global::pDisplay->set_fullscreen(global::pDisplay->is_fullscreen());
    }

    camProjection.update();
    
    camTrans.move(pos);
    camTrans.apply_transform();
    
    vpMatrix = camProjection.get_proj_matrix() * camTrans.get_transform();
}

/*-------------------------------------
 * Stopping state
-------------------------------------*/
void ControlState::on_stop() {
    mouseX = 0;
    mouseY = 0;

    pEvent.reset();
    pKeyStates.reset();
    camProjection = draw::Camera{};
    camTrans = draw::Transform{draw::transform_type_t::TRANSFORM_TYPE_VIEW_ARC_LOCKED_Y};
    vpMatrix = math::mat4{1.f};
}

/*-------------------------------------
 * Key Up Event
-------------------------------------*/
void ControlState::on_key_up_event(const SDL_KeyboardEvent& e) {
    const SDL_Keycode key = e.keysym.scancode;

    pKeyStates[key] = false;
}

/*-------------------------------------
 * Key Down Event
-------------------------------------*/
void ControlState::on_key_down_event(const SDL_KeyboardEvent& e) {
    const SDL_Keycode key = e.keysym.scancode;

    pKeyStates[key] = true;
}

/*-------------------------------------
 * Window Event
-------------------------------------*/
void ControlState::on_window_event(const SDL_WindowEvent& e) {
    if (e.event == SDL_WINDOWEVENT_CLOSE) {
        get_parent_system().stop();
    }
}

/*-------------------------------------
 * Mouse Button Down Event
-------------------------------------*/
void ControlState::on_mouse_down_event(const SDL_MouseButtonEvent& e) {
    // Allow the mouse to enter/exit the window when the user pleases.
    if (e.button == SDL_BUTTON_LEFT) {
        // keep the mouse in the window
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
    else if (e.button == SDL_BUTTON_RIGHT) {
        // let the mouse leave the window
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

/*-------------------------------------
 * Mouse Button Down Event
-------------------------------------*/
void ControlState::on_mouse_move_event(const SDL_MouseMotionEvent& e) {
    // Prevent the orientation from drifting by keeping track of the relative mouse offset
    if (this->get_state() == game::game_state_status_t::PAUSED
        || SDL_GetRelativeMouseMode() == SDL_FALSE
        || ((int)mouseX == e.xrel && (int)mouseY == e.yrel)
        ) {
        // I would rather quit the function than have unnecessary LERPs and
        // quaternion multiplications.
        return;
    }
    rotate_camera((float)e.xrel, (float)e.yrel);
}

/*-------------------------------------
 * Trackpad Movement
-------------------------------------*/
void ControlState::on_track_mouse_event(const SDL_TouchFingerEvent& e) {
    // Prevent the orientation from drifting by keeping track of the relative mouse offset
    if (this->get_state() == game::game_state_status_t::PAUSED
        || (mouseX == e.dx && mouseY == e.dy)
        ) {
        return;
    }
    rotate_camera((float)e.dx, (float)e.dy);
}

/*-------------------------------------
 * Camera Rotation
-------------------------------------*/
void ControlState::rotate_camera(const float xPos, const float yPos) {
    mouseX = xPos;
    mouseY = yPos;

    // Get the current mouse position and LERP from the previous mouse position.
    // The mouse position is divided by the window's resolution in order to normalize
    // the mouse delta between 0 and 1. This allows for the camera's orientation to
    // be LERPed without the need for multiplying it by the last time delta.
    // As a result, the camera's movement becomes as smooth and natural as possible.
    const math::vec2&& fRes = (math::vec2)global::pDisplay->get_resolution();
    const math::vec3&& mouseDelta = math::vec3 {
        mouseX / fRes[0],
        mouseY / fRes[1],
        0.f
    };

    camTrans.rotate(mouseDelta);
    
}

/*-------------------------------------
 * Mouse Button Down Event
-------------------------------------*/
void ControlState::on_wheel_event(const SDL_MouseWheelEvent& e) {
    constexpr float totalAngles = -1.f / 120.f;
    const float horizAngles = (float)e.x;
    const float vertAngles = (float)e.y;

    camTrans.rotate(math::vec3 {horizAngles, 0.f, vertAngles * totalAngles});
}
