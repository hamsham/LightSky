/* 
 * File:   color.h
 * Author: miles
 *
 * Created on June 2, 2014, 8:12 PM
 */

#ifndef __LS_COLOR_H__
#define	__LS_COLOR_H__

#include "lsSetup.h"

typedef math::vec4 lsColor;

static constexpr lsColor lsBlank = {0.f, 0.f, 0.f, 0.f};

static constexpr lsColor lsRed = {1.f, 0.f, 0.f, 1.f};
static constexpr lsColor lsGreen = {0.f, 1.f, 0.f, 1.f};
static constexpr lsColor lsBlue = {0.f, 0.f, 1.f, 1.f};

static constexpr lsColor lsBlack = {0.f, 0.f, 0.f, 1.f};
static constexpr lsColor lsWhite = {1.f, 1.f, 1.f, 1.f};
static constexpr lsColor lsGray = {0.5f, 0.5f, 0.5f, 1.f};

static constexpr lsColor lsTeal = {0.f, 1.f, 1.f, 1.f};
static constexpr lsColor lsMagicPink = {1.f, 0.f, 1.f, 1.f};

#endif	/* __LS_COLOR_H__ */

