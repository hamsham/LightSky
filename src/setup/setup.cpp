/* 
 * File:   setup/setup.cpp
 * Author: Miles Lacey
 *
 * This file contains easy-to-use functions for accessing meta-data for the
 * current platform, OS, compiler, and build target.
 */

#include "lightsky/setup/setup.h"

namespace ls {

/*-------------------------------------
 * Get the current build platform.
-------------------------------------*/
ls::platform::platform_t get_target_platform() {
    return LS_PLATFORM;
}

} // end ls namespace
