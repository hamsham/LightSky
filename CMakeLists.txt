cmake_minimum_required(VERSION 3.2)

set(CMAKE_DISABLE_IN_SOURCE_BUILDS ON)
set(CMAKE_CXX_STANDARD 11)



# -------------------------------------
# Project Setup
# -------------------------------------
project("LightSky")



# -------------------------------------
# Compiler Options
# -------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions(-Wall)
    add_definitions(-Werror)
    add_definitions(-Wextra)
    add_definitions(-pedantic)
    add_definitions(-pedantic-errors)
    add_definitions(-Wno-implicit-fallthrough)
    add_definitions(-Wno-pessimizing-move)
    add_definitions(-ftree-vectorize)
    add_definitions(-ffast-math)
    add_definitions(-funsafe-math-optimizations)
    add_definitions(-static)

    # Tested on Linux, all static libraries need to be compiled with the -fPIC
    # flag in order to be linked into shared libs. This is going to destroy all
    # benchmarks due to extra assembly instructions being compiled in.
    if(NOT WIN32)
        add_definitions(-fPIC)
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_definitions(/Wall /sdl /W3 /WX)
    add_definitions(/Za /Zc:rvalueCast /Zc:strictStrings /Zc:inline)
else()
    message(FATAL_ERROR "Your compiler is currently unsupported: ${CMAKE_CXX_COMPILER_ID}")
endif()



if (CMAKE_BUILD_TYPE)
    string(TOLOWER ${CMAKE_BUILD_TYPE} _CURRENT_BUILD_TYPE)
    
	if(${_CURRENT_BUILD_TYPE} STREQUAL debug OR ${_CURRENT_BUILD_TYPE} STREQUAL relwithdebinfo)
		message("-- Debug mode enabled.")
		add_definitions(-D LS_DEBUG)
	else()
		message("-- Release mode enabled.")
	endif()
endif()



if(BUILD_SHARED_LIBS)
    add_definitions(-DLS_SHARED -DLS_BUILD_SHARED)
endif()



option(ENABLE_PROFILING "Enable profiling (recommended for release builds with debug information)." OFF)
if (ENABLE_PROFILING)
    message("-- Profiling enabled")
    add_definitions(-pg)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
endif()



option(ENABLE_ARM_OPTIMIZATIONS "Enable arm-specific compiler optimization flags." OFF)
if (ENABLE_ARM_OPTIMIZATIONS)
    message("-- ARM compiler optimizations enabled.")
    add_definitions(-mhard-float)
    add_definitions(-mfloat-abi=hard)
    add_definitions(-mfpu=neon-vfpv4)
    add_definitions(-march=armv7-a+simd+fp16+neon-vfpv4)
endif(ENABLE_ARM_OPTIMIZATIONS)



option(ENABLE_X86_OPTIMIZATIONS "Enable x86-specific compiler optimization flags." OFF)
if (ENABLE_X86_OPTIMIZATIONS)
    message("-- x86 compiler optimizations enabled.")
    add_definitions(-msse)
    add_definitions(-msse2)
    add_definitions(-mmmx)
    add_definitions(-march=native)
endif(ENABLE_X86_OPTIMIZATIONS)



# -------------------------------------
# External Project Setup
# -------------------------------------
include(external_deps.cmake)



# -------------------------------------
# Sub-Projects
# -------------------------------------
#
#   LS Setup
#
set(LS_BUILD_SETUP_MODULE TRUE CACHE BOOL "Build the LS Setup module.")

if(LS_BUILD_SETUP_MODULE)
    add_subdirectory("LightSetup")
    include_directories("LightSetup/include")

endif(LS_BUILD_SETUP_MODULE)

#
#   LS Utils
#
if(LS_BUILD_SETUP_MODULE)
    set(LS_BUILD_UTILS_MODULE TRUE CACHE BOOL "Build the LS Utility module.")
else()
    set(LS_BUILD_UTILS_MODULE FALSE CACHE BOOL "LS Utility module dependencies not met." FORCE)
endif()

if(LS_BUILD_UTILS_MODULE)
    add_subdirectory("LightUtils")
    include_directories("LightUtils/include")
endif(LS_BUILD_UTILS_MODULE)

#
#   LS Math
#
if(LS_BUILD_SETUP_MODULE)
    set(LS_BUILD_MATH_MODULE TRUE CACHE BOOL "Build the LS Math module.")
else()
    set(LS_BUILD_MATH_MODULE FALSE CACHE BOOL "LS Math module dependencies not met." FORCE)
endif()

if(LS_BUILD_MATH_MODULE)
    add_subdirectory("LightMath")
    include_directories("LightMath/include")
endif(LS_BUILD_MATH_MODULE)

#
#   LS Draw
#
if(LS_BUILD_MATH_MODULE AND LS_BUILD_UTILS_MODULE)
    set(LS_BUILD_DRAW_MODULE TRUE CACHE BOOL "Build the LS Draw module.")
else()
    set(LS_BUILD_DRAW_MODULE FALSE CACHE BOOL "LS Draw module dependencies not met." FORCE)
endif()

if(LS_BUILD_DRAW_MODULE)
    add_subdirectory("LightDraw")
    include_directories("LightDraw/include")
endif(LS_BUILD_DRAW_MODULE)

#
#   LS Game
#
if(LS_BUILD_MATH_MODULE AND LS_BUILD_UTILS_MODULE AND LS_BUILD_DRAW_MODULE)
    set(LS_BUILD_GAME_MODULE TRUE CACHE BOOL "Build the LS Game module.")
else()
    set(LS_BUILD_GAME_MODULE FALSE CACHE BOOL "LS Game module dependencies not met." FORCE)
endif()

if(LS_BUILD_GAME_MODULE)
    add_subdirectory("LightGame")
    include_directories("LightGame/include")
endif(LS_BUILD_GAME_MODULE)

#
#   LS Script
#
if(LS_BUILD_MATH_MODULE AND LS_BUILD_UTILS_MODULE AND LS_BUILD_SHARED_LIBS)
    set(LS_BUILD_SCRIPT_MODULE TRUE CACHE BOOL "Build the LS Script module.")
else()
    set(LS_BUILD_SCRIPT_MODULE FALSE CACHE BOOL "LS Script module dependencies not met." FORCE)
endif()

if(LS_BUILD_SCRIPT_MODULE)
    add_subdirectory("LightScript")
    include_directories("LightScript/include")
endif(LS_BUILD_SCRIPT_MODULE)
