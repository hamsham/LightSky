/* 
 * File:   glsl_common.h
 * Author: Miles Lacey
 *
 * Created on September 4, 2015, 11:04 PM
 */

#ifndef __LS_DRAW_GLSL_COMMON_H__
#define	__LS_DRAW_GLSL_COMMON_H__

namespace ls {
namespace draw {

/*-------------------------------------
 * Shader Versions
-------------------------------------*/
#if defined(EDS_OS_IOS) || defined(EDS_OS_IOS_SIM)
    constexpr char const GLSL_DEFAULT_VERSION[] = "#version 300 es\n";
#else
    constexpr char const GLSL_DEFAULT_VERSION[] = "#version 330\n";
#endif

/*-------------------------------------
 * Shader Precision
-------------------------------------*/
constexpr char const GLSL_PRECISION_LOWP_F[] = "precision lowp float;\n";
constexpr char const GLSL_PRECISION_MEDP_F[] = "precision mediump float;\n";
constexpr char const GLSL_PRECISION_HIGHP_F[] = "precision highp float;\n";

#if defined(EDS_OS_IOS) || defined(EDS_OS_IOS_SIM)
    constexpr char const GLSL_PRECISION_DEFAULT[] = "precision mediump float;\n";
#else
    constexpr char const GLSL_PRECISION_DEFAULT[] = "precision mediump float\n";
#endif

} // end draw namespace
} // end ls namespace

#endif	/* __LS_DRAW_GLSL_COMMON_H__ */

