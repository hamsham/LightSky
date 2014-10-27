/* 
 * File:   setup/compiler.h
 * Author: Miles Lacey
 *
 * This file contains preprocessor macros detailing information about the
 * current compiler.
 *
 */

#ifndef __LS_SETUP_COMPILER_H__
#define __LS_SETUP_COMPILER_H__

/*
 * Ensure C++11 Support
 */
#if (__cplusplus < 201103L) || (!defined(__GXX_EXPERIMENTAL_CXX0X__))
    #error "A C++11-compliant compiler is required to build LightSky."
#endif

/*
 * Microsoft Visual C++ compiler
 */
#if defined (_MSC_VER)
    #define LS_COMPILER_MSC _MSC_VER

#elif defined (__GNUC__) || defined (__MINGW32__) || defined (__MINGW_64__)
    #define LS_COMPILER_GNU __GNUC__
    #if defined (__clang__)
        #define LS_COMPILER_CLANG 1
        #define LS_COMPILER_CLANG_MAJ __clang_major__
        #define LS_COMPILER_CLANG_MIN __clang_minor__
    #endif

/*
 * Intel Compiler
 */
#elif defined (__INTEL_COMPILER)
    #define LS_COMPILER_INTEL __INTEL_COMPILER

#elif defined (__BORLANDC__) || defined (__CODEGEARC__)
    #define LS_COMPILER_BORLAND LS_MAX( (__BORLANDC__), (__CODEGEARC__) )

#elif defined (__CC_ARM)
    #define LS_COMPILER_ARM __ARMCC_VERSION

#elif defined (__IBMCPP__)
    #ifdef(__COMPILER_VER__)
        /* IBM z/OS Compiler */
        #define LS_COMPILER_IBM 0
        #define LS_COMPILER_ZOS __IBMCPP__
    #else
        /* IBM XL Compiler */
        #define LS_COMPILER_IBM 1
        #define LS_COMPILER_XL __IBMCPP__
    #endif

#elif defined (__SNC__)
    #define LS_COMPILER_SN __SNC__

#endif

#endif /* __SETUP_LS_COMPILER_H__ */
