/* 
 * File:   main.h
 * Author: miles
 *
 * Created on August 5, 2014, 10:21 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <SDL2/SDL.h>

#include "lightsky/lightsky.h"

enum {
    TEST_MAX_KEYBORD_STATES = 282, // according to https://wiki.libsdl.org/SDLScancodeLookup
};

namespace math = ls::math;

namespace global {
    extern ls::game::system* pSystem = nullptr;
    extern ls::draw::display* pDisplay = nullptr;
}

#endif	/* MAIN_H */

