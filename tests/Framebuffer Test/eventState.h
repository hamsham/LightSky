/* 
 * File:   eventState.h
 * Author: miles
 *
 * Created on November 23, 2014, 9:13 PM
 */

#ifndef EVENTSTATE_H
#define	EVENTSTATE_H

#include <SDL2/SDL_events.h>

#include "lightsky/game/gameSystem.h"

class eventState : virtual public ls::game::gameState {
    public:
        virtual ~eventState() = 0;
        
        virtual void onEvent(const SDL_Event&) {}
};

#endif	/* EVENTSTATE_H */

