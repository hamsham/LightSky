/*
 * File:   ControlState.h
 * Author: miles
 *
 * Created on August 5, 2014, 9:50 PM
 */

#ifndef CONTROLSTATE_H
#define CONTROLSTATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include "lightsky/math/mat4.h"

#include "lightsky/utils/Pointer.h"

#include "lightsky/draw/Camera.h"
#include "lightsky/draw/Transform.h"

#include "lightsky/game/GameState.h"

class TestRenderState;



/**----------------------------------------------------------------------------
 * Global Controller testing state
-----------------------------------------------------------------------------*/
class ControlState final : virtual public ls::game::GameState {
    private:
        float mouseX;
        
        float mouseY;
        
        ls::utils::Pointer<SDL_Event> pEvent;
        
        ls::utils::Pointer<bool[]> pKeyStates;
        
        ls::draw::Transform camTrans;
        
        ls::draw::Camera camProjection;
        
        ls::math::mat4 vpMatrix;
    
        void setup_camera();

        void on_window_event(const SDL_WindowEvent&);
        
        void on_key_up_event(const SDL_KeyboardEvent&);
        
        void on_key_down_event(const SDL_KeyboardEvent&);
        
        void on_mouse_move_event(const SDL_MouseMotionEvent&);
        
        void on_mouse_down_event(const SDL_MouseButtonEvent&);
        
        void on_track_mouse_event(const SDL_TouchFingerEvent&);
        
        void on_wheel_event(const SDL_MouseWheelEvent&);

        void rotate_camera(const float xPos, const float yPos);

    public:
        virtual ~ControlState();

        ControlState();
        
        ControlState(const ControlState&) = delete;
        
        ControlState(ControlState&&);

        ControlState& operator=(const ControlState&) = delete;
        
        ControlState& operator=(ControlState&&);

        bool on_start() override;
        
        void on_run() override;
        
        void on_stop() override;
        
        const ls::utils::Pointer<bool[]>& get_key_states() const;
        
        const ls::draw::Camera& get_camera_projection() const;
        
        const ls::draw::Transform& get_camera_transformation() const;
        
        const ls::math::mat4& get_camera_view_projection() const;
};



inline const ls::utils::Pointer<bool[]>& ControlState::get_key_states() const {
    return pKeyStates;
}



inline const ls::draw::Camera& ControlState::get_camera_projection() const {
    return camProjection;
}



inline const ls::draw::Transform& ControlState::get_camera_transformation() const {
    return camTrans;
}



inline const ls::math::mat4& ControlState::get_camera_view_projection() const {
    return vpMatrix;
}



#endif  /* CONTROLSTATE_H */
