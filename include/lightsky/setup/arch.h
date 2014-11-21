/* 
 * File:   setup/arch.h
 * Author: Miles Lacey
 *
 * This file contains preprocessor macros detailing information about the
 * currently targeted architecture.
 *
 */

#ifndef __LS_SETUP_ARCH_H__
#define __LS_SETUP_ARCH_H__

/*
 * x86/x64 Processor Family
 */
#if defined (_WIN64) || defined (__amd64__) || defined (_M_X64)
    #define LS_ARCH_X86 64
    #define LS_ARCH_X86_VER 6 /* Assuming modern processors */

#elif defined (_WIN32) || defined (__i386__) || defined (_M_IX86_) || defined (__THW_INTEL__)
    #ifndef LS_ARCH_x86
        #define LS_ARCH_X86 32
    #endif

    /*
     * x86 Versioning
     */
    #ifdef LS_COMPILER_GNU
        #if defined (__i686__)
            #define LS_ARCH_X86_VER 686
        #elif defined (__i586__)
            #define LS_ARCH_X86_VER 586
        #elif defined (__i486__)
            #define LS_ARCH_X86_VER 486
        #elif defined (__i386__)
            #define LS_ARCH_X86_VER 386
        #endif
    #elif defined (LS_COMPILER_MSC)
        #define LS_ARCH_X86_VER ((_M_IX86) / 100)
    #else
        #define LS_ARCH_X86_VER 386
    #endif
#endif

/*
 * Itanium
 */
#if defined (__IA64__) || defined (_M_IA64) || defined (__itanium__)
    #define LS_ARCH_IA64 1
#endif

/*
 * Arm Processors
 */
#if defined (__arm__) || defined (_M_ARM) || defined (__TARGET_ARCH_ARM)
    #define LS_ARCH_ARM 1
    #define LS_ARCH_ARM_VER LS_MAX( (__TARGET_ARCH_ARM), (_M_ARM) )

    /*
     * Thumb-Mode
     */
    #if defined (__thumb__) || defined (__TARGET_ARCH_THUMB) || defined (_M_ARMT)
        #define LS_ARCH_ARM_THUMB 1
        #define LS_ARCH_ARM_THUMB_VER LS_MAX( (__TARGET_ARCH_THUMB), (_M_ARMT) )

    #endif
#endif

/*
 * PowerPC
 */
#if defined (__ppc__) || defined (_M_PPC) || defined (_ARCH_PPC)
    #define LS_ARCH_PPC 1
#endif

/*
 * Gaming Consoles
 */
#if defined (__SNC__)
    #define LS_ARCH_PS3 1
#endif

#endif /* __LS_SETUP_ARCH_H__ */
