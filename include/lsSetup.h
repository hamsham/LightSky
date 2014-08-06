/* 
 * File:   lsSetup.h
 * Author: hammy
 *
 * Created on November 15, 2013, 8:37 PM
 */

#ifndef __LS_SETUP_H__
#define	__LS_SETUP_H__

#include <iostream>

#include "utils/assert.h"
#include "utils/hash.h"
#include "math/math.h"

//-----------------------------------------------------------------------------
//      Global Macros
//-----------------------------------------------------------------------------
#ifndef LS_APP_NAME
    #define LS_APP_NAME "Light Sky"
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
        typedef name<__VA_ARGS__> nickName;\
        extern template class name <__VA_ARGS__>
#endif

/**
 * Class Template Definitions
 */
#ifndef LS_DEFINE_CLASS_TYPE
    #define LS_DEFINE_CLASS_TYPE(name, ...) template class name<__VA_ARGS__>
#endif

//-----------------------------------------------------------------------------
//      Namespace Setup
//-----------------------------------------------------------------------------
namespace math {
    using namespace hamLibs::math;
    
    // hamLibs doesn't have typedefs for unsigned vectors or matrices
    typedef vec2_t<unsigned> vec2ui;
    typedef vec3_t<unsigned> vec3ui;
    typedef vec4_t<unsigned> vec4ui;
    typedef mat2_t<unsigned> mat2ui;
    typedef mat3_t<unsigned> mat3ui;
    typedef mat4_t<unsigned> mat4ui;
}

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

//-----------------------------------------------------------------------------
//      Simple Logging for Debugging
//-----------------------------------------------------------------------------
#ifdef LS_DEBUG
    template <typename Arg>
    void LS_LOG_MSG(const Arg& arg) {
        std::cout << arg << '\n';
        std::cout.flush();
    }

    template <typename Arg, typename... Args>
    void LS_LOG_MSG(const Arg& arg, const Args&... args) {
        std::cout << arg;
        LS_LOG_MSG(args...);
    }

    template <typename Arg>
    void LS_LOG_ERR(const Arg& arg) {
        std::cerr << arg << '\n';
        std::cerr.flush();
    }

    template <typename Arg, typename... Args>
    void LS_LOG_ERR(const Arg& arg, const Args&... args) {
        std::cerr << arg;
        LS_LOG_ERR(args...);
    }

    void lsPrintGlError(int line, const char* file);
#else
    template <typename Arg>
    void LS_LOG_MSG(const Arg&) {
    }

    template <typename Arg, typename... Args>
    void LS_LOG_MSG(const Arg&, const Args&...) {
    }

    template <typename Arg>
    void LS_LOG_ERR(const Arg&) {
    }

    template <typename Arg, typename... Args>
    void LS_LOG_ERR(const Arg&, const Args&...) {
    }

    inline void lsPrintGlError(int, const char*) {}
#endif

#ifndef LOG_GL_ERR
    #define LOG_GL_ERR() lsPrintGlError(__LINE__, __FILE__)
#endif

#endif	/* __LS_SETUP_H__ */

