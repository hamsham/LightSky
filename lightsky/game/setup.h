/* 
 * File:   game/setup.h
 * Author: Miles Lacey
 *
 * Created on November 15, 2013, 8:37 PM
 */

#ifndef __LS_GAME_SETUP_H__
#define	__LS_GAME_SETUP_H__

#include "lightsky/setup/setup.h"
#include "lightsky/utils/assert.h"
#include "lightsky/utils/hash.h"
#include "lightsky/utils/log.h"
#include "lightsky/math/math.h"

/*-------------------------------------
    Debugging Various Messages.
-------------------------------------*/
#ifdef LS_DEBUG
    #ifndef LS_LOG_GAME_MSG
        #define LS_LOG_GAME_MSG(...) ls::utils::logMsg(__VA_ARGS__)
    #endif
    
    #ifndef LS_LOG_GAME_ERR
        #define LS_LOG_GAME_ERR(...) ls::utils::logErr(__VA_ARGS__)
    #endif
#else
    template <typename Arg>
    constexpr void LS_LOG_GAME_MSG(const Arg&) {
    }

    template <typename Arg, typename... Args>
    constexpr void LS_LOG_GAME_MSG(const Arg&, const Args&...) {
    }

    template <typename Arg>
    constexpr void LS_LOG_GAME_ERR(const Arg&) {
    }

    template <typename Arg, typename... Args>
    constexpr void LS_LOG_GAME_ERR(const Arg&, const Args&...) {
    }
#endif

#endif	/* __LS_GAME_SETUP_H__ */

