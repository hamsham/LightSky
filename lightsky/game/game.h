/* 
 * File:   game/game.h
 * Author: Miles Lacey
 *
 * Created on June 13, 2014, 11:15 PM
 */

#ifndef __LS_GAME_H__
#define	__LS_GAME_H__

#include "lightsky/game/setup.h"

#include "lightsky/game/dispatcher.h"
#include "lightsky/game/event.h"
#include "lightsky/game/gameState.h"
#include "lightsky/game/manager.h"
#include "lightsky/game/subscriber.h"
#include "lightsky/game/system.h"

namespace ls {
namespace game {
namespace global {

/**
 *  @brief LightSky Initialization
 *  
 *  @return TRUE if the framework was able to initialize properly, or FALSE if
 *  not.
 */
bool init();

/**
 *  @brief LightSky termination.
 *  
 *  Frees all extra resources used by the framework.
 */
void terminate();

} // end global namespace
} // end game namespace
} // end ls namespace

#endif	/* __LS_GAME_H__ */
