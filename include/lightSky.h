/* 
 * File:   lightSky.h
 * Author: miles
 *
 * Created on June 13, 2014, 11:15 PM
 */

#ifndef __LIGHT_SKY_H__
#define	__LIGHT_SKY_H__

#include "lsAtlas.h"
#include "lsBlendObject.h"
#include "lsBoundingBox.h"
#include "lsBufferObject.h"
#include "lsColor.h"
#include "lsContext.h"
#include "lsDataResource.h"
#include "lsDisplay.h"
#include "lsDrawModel.h"
#include "lsDepthObject.h"
#include "lsFontResource.h"
#include "lsFramebuffer.h"
#include "lsGameState.h"
#include "lsGeometry.h"
#include "lsImageResource.h"
#include "lsManager.h"
#include "lsMatrixStack.h"
#include "lsMesh.h"
#include "lsMeshResource.h"
#include "lsRandom.h"
#include "lsRenderer.h"
#include "lsResource.h"
#include "lsSceneManager.h"
#include "lsSetup.h"
#include "lsShaderObject.h"
#include "lsShaderProgram.h"
#include "lsSystem.h"
#include "lsTexture.h"
#include "lsUtil.h"
#include "lsVertex.h"
#include "lsVertexArray.h"

/**
 * LightSky Initialization
 * 
 * @return bool
 * TRUE if the framework was able to initialize properly, or FALSE if not.
 */
bool lsInit();

/**
 * LightSky termination.
 * Frees all extra resources used by the framework.
 */
void lsTerminate();

#endif	/* __LIGHT_SKY_H__ */

