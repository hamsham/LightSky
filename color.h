/* 
 * File:   color.h
 * Author: miles
 *
 * Created on June 2, 2014, 8:12 PM
 */

#ifndef __LS_COLOR_H__
#define	__LS_COLOR_H__

#include "main.h"

namespace color {
    
    typedef math::vec4 color;
    
    static constexpr color blank = {0.f, 0.f, 0.f, 0.f};
    
    static constexpr color red = {1.f, 0.f, 0.f, 1.f};
    static constexpr color green = {0.f, 1.f, 0.f, 1.f};
    static constexpr color blue = {0.f, 0.f, 1.f, 1.f};
    
    static constexpr color black = {0.f, 0.f, 0.f, 1.f};
    static constexpr color white = {1.f, 1.f, 1.f, 1.f};
    static constexpr color gray = {0.5f, 0.5f, 0.5f, 1.f};
    
    static constexpr color teal = {0.f, 1.f, 1.f, 1.f};
    static constexpr color magicPink = {1.f, 0.f, 1.f, 1.f};
}

#endif	/* __LS_COLOR_H__ */

