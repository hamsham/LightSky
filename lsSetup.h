/* 
 * File:   main.h
 * Author: hammy
 *
 * Created on November 15, 2013, 8:37 PM
 */

#ifndef __LS_MAIN_H__
#define	__LS_MAIN_H__

#include <iostream>
#include <cstdint>
#include "utils/assert.h"
#include "utils/timeObject.h"
#include "utils/hash.h"
#include "utils/randomNum.h"
#include "math/math.h"

/******************************************************************************
 * NAMESPACE SETUP
******************************************************************************/
namespace math = hamLibs::math;
using hamLibs::utils::hashVal_t;

/******************************************************************************
 * GLOBAL MACROS
******************************************************************************/
#ifndef LS_APP_NAME
    #define LS_APP_NAME "Light Skybox Test"
#endif

/*
 * System Defaults
 */
#ifndef LS_DEFAULT_DISPLAY_WIDTH
    #define LS_DEFAULT_DISPLAY_WIDTH 800
#endif

#ifndef LS_DEFAULT_DISPLAY_HEIGHT
    #define LS_DEFAULT_DISPLAY_HEIGHT 600
#endif

/*
 * Compile-Time String Hashing
 */
#ifndef LS_STRINGIFY
    #define LS_STRINGIFY( x ) #x
#endif

#ifndef LS_HASH
    #define LS_HASH( x ) hamLibs::utils::hashFNV1<char>( LS_STRINGIFY(x) )
#endif

/*
 * Get the number of elements contained in a stack-allocated array.
 */
#ifndef LS_ARRAY_SIZE
	#define LS_ARRAY_SIZE( a ) ( sizeof( a ) / sizeof( a[0] ) )
#endif

/**
 * Class Template Declaration
 */
#ifndef LS_DECLARE_CLASS_TYPE
    #define LS_DECLARE_CLASS_TYPE(nickName, name, ...)\
        extern template class name <__VA_ARGS__>;\
        typedef name<__VA_ARGS__> nickName
#endif

/**
 * Class Template Definitions
 */
#ifndef LS_DEFINE_CLASS_TYPE
    #define LS_DEFINE_CLASS_TYPE(name, ...) template class name<__VA_ARGS__>
#endif

/*
 * Debugging
 */
#ifdef LS_DEBUG
    #ifndef LS_DEBUG_LINE
        #define LS_DEBUG_LINE\
            std::cout\
            << "Testing line " << __LINE__\
            << " from file " << __FILE__\
            << std::endl;
    #endif

    #ifndef LS_WARN
        #define LS_WARN HL_WARN
    #endif
#else
    #ifndef LS_DEBUG_LINE
        #define LS_DEBUG_LINE
    #endif
    
    #ifndef LS_WARN
        #define LS_WARN
    #endif
    
#endif

/******************************************************************************
 * GAME LOGGING
******************************************************************************/
template <typename Arg>
void LOG_MSG(const Arg& arg) {
    std::cout << arg << '\n';
    std::cout.flush();
}

template <typename Arg, typename... Args>
void LOG_MSG(const Arg& arg, const Args&... args) {
    std::cout << arg;
    LOG_MSG(args...);
}

template <typename Arg>
void LOG_ERR(const Arg& arg) {
    std::cerr << arg << '\n';
    std::cerr.flush();
}

template <typename Arg, typename... Args>
void LOG_ERR(const Arg& arg, const Args&... args) {
    std::cerr << arg;
    LOG_ERR(args...);
}

void printGlError(int line, const char* file);

#ifdef LS_DEBUG
    #define LOG_GL_ERR() printGlError(__LINE__, __FILE__)
#else
    #define LOG_GL_ERR()
#endif


/******************************************************************************
 * FORWARD DECLARATIONS
******************************************************************************/
/*
 * Subsystems
 */
class gameState;
class display;
class subsystem;

/******************************************************************************
 * GAME GLOBALS
******************************************************************************/
namespace global {
    extern display* pDisplay; // main.cpp
    extern subsystem* pSystem; // main.cpp
    extern hamLibs::utils::randomNum* pRandGen; // main.cpp
}

#endif	/* __LS_MAIN_H__ */

