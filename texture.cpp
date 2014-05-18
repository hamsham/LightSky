/* 
 * File:   texture.cpp
 * Author: hammy
 * 
 * Created on January 27, 2014, 8:35 PM
 */

#include <Gl/glew.h>
#include "main.h"
#include "texture.h"

/******************************************************************************
 * Texture Template Definitions
******************************************************************************/
HL_DEFINE_CLASS_TYPE(texture, TEXTURE_TYPE_1D, TEX_1D);
HL_DEFINE_CLASS_TYPE(texture, TEXTURE_TYPE_2D, TEX_2D);
HL_DEFINE_CLASS_TYPE(texture, TEXTURE_TYPE_3D, TEX_3D);
HL_DEFINE_CLASS_TYPE(texture, TEXTURE_TYPE_2D, TEX_RECT);