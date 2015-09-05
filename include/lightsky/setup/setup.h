/* 
 * File:   setup/setup.h
 * Author: Miles Lacey
 *
 * This file contains all preprocessor macros and definitions that will help in
 * in building LightSky and its modules.
 */

#ifndef __LS_SETUP_SETUP_H__
#define __LS_SETUP_SETUP_H__

#include "lightsky/setup/compiler.h"
#include "lightsky/setup/arch.h"
#include "lightsky/setup/os.h"
#include "lightsky/setup/macros.h"

namespace ls {
namespace platform {

enum class platform_t {
    DESKTOP,
    MOBILE
};

} // end platform namespace

/**
 * @brief Helper function to determine if the current platform is Mobile or
 * Desktop.
 * 
 * @return ls::platform::platform_t::DESKTOP if the current build is targeting
 * a desktop platform, MOBILE if otherwise.
 */
ls::platform::platform_t get_target_platform();

} // end ls namespace

/*
 * LS_PLATFORM
 *
 * Defines what platform the current app system is on (mobile or desktop)
 */
#if defined LS_OS_WINDOWS || defined (LS_OS_UNIX) || defined (LS_OS_OSX)
    #define LS_PLATFORM_DESKTOP ls::platform::platform_t::DESKTOP
    #define LS_PLATFORM LS_PLATFORM_DESKTOP

#elif defined (LS_OS_ANDROID) || defined (LS_OS_IOS)
    #define LS_PLATFORM_MOBILE ls::platform::platform_t::MOBILE
    #define LS_PLATFORM LS_PLATFORM_MOBILE

#endif /* LS_PLATFORM */

#endif /* __LS_SETUP_SETUP_H__ */
