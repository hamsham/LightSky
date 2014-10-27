/* 
 * File:   setup/os.h
 * Author: Miles Lacey
 *
 * This file contains preprocessor macros detailing information about the
 * current operating system.
 *
 */

#ifndef __LS_SETUP_OS_H__
#define __LS_SETUP_OS_H__

/* Android */
#if defined (__ANDROID__)
    #define LS_OS_ANDROID 1
    #define LS_OS_ANDROID_VER __ANDROID_API__
#endif

/* CygWin */
#if defined (__CYGWIN__)
    #define LS_OS_CYGWIN 1
#endif

/* FreeBSD */
#if defined (__FreeBSD__)
    #define LS_OS_BSD 1
    #define LS_OS_BSD_VER __FreeBSD__
#endif

/* GNU/Linux */
#if defined (__GNU__)
    #define LS_OS_GNU 1
#endif

/* Mac OSX */
#if defined (macintosh) || defined (Macintosh) || defined (__APPLE__) || defined (__MACH__)
    #define LS_OS_OSX 1
#endif

/* Unix */
#if defined (__unix__) || defined (__unix)
    #define LS_OS_UNIX 1
#endif

/* Windows */
#if defined (_WIN32) || defined (_WIN64) || defined (__WINDOWS__) || defined (__WIN32__)
    #if defined (_WIN64)
        #define LS_OS_WINDOWS 64
    #else 
        #define LS_OS_WINDOWS 32
    #endif
#endif

#endif /* __LS_SETUP_OS_H__ */
