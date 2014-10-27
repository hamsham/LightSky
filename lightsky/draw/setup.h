/* 
 * File:   draw/setup.h
 * Author: Miles Lacey
 *
 * Created on November 15, 2013, 8:37 PM
 */

#ifndef __LS_DRAW_SETUP_H__
#define	__LS_DRAW_SETUP_H__

#include "lightsky/setup/setup.h"
#include "lightsky/utils/assert.h"
#include "lightsky/utils/hash.h"
#include "lightsky/utils/log.h"
#include "lightsky/math/math.h"

/*-----------------------------------------------------------------------------
    Default Display Resolution
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Default Display Width
-------------------------------------*/
#ifndef LS_DRAW_DEFAULT_DISPLAY_WIDTH
    #define LS_DRAW_DEFAULT_DISPLAY_WIDTH 800
#endif

/*-------------------------------------
    Default Display Height
-------------------------------------*/
#ifndef LS_DRAW_DEFAULT_DISPLAY_HEIGHT
    #define LS_DRAW_DEFAULT_DISPLAY_HEIGHT 600
#endif

/*-------------------------------------
    Debugging Various Messages.
-------------------------------------*/
#ifdef LS_DEBUG
    #ifndef LS_LOG_MSG
        #define LS_LOG_MSG(...) ls::utils::logMsg(__VA_ARGS__)
    #endif
    
    #ifndef LS_LOG_ERR
        #define LS_LOG_ERR(...) ls::utils::logErr(__VA_ARGS__)
    #endif
    
namespace ls {
namespace draw {
    void lsPrintGlError(int line, const char* file);
} // end draw namespace
} // end ls namespace

#else
    template <typename Arg>
    constexpr void LS_LOG_MSG(const Arg&) {
    }

    template <typename Arg, typename... Args>
    constexpr void LS_LOG_MSG(const Arg&, const Args&...) {
    }

    template <typename Arg>
    constexpr void LS_LOG_ERR(const Arg&) {
    }

    template <typename Arg, typename... Args>
    constexpr void LS_LOG_ERR(const Arg&, const Args&...) {
    }
    
namespace ls {
namespace draw {
    void lsPrintGlError(int, const char*) {}
} // end draw namespace
} // end ls namespace

#endif

#ifndef LOG_GL_ERR
    #define LOG_GL_ERR() ls::draw::lsPrintGlError(__LINE__, __FILE__)
#endif

#endif	/* __LS_DRAW_SETUP_H__ */

