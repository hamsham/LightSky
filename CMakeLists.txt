cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_DISABLE_IN_SOURCE_BUILDS ON)



# -------------------------------------
# Project Setup
# -------------------------------------
project("LightSky")



# -------------------------------------
# Compiler Options
# -------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    add_definitions(-Wall -Werror -Wextra -pedantic -pedantic-errors)
    set(CMAKE_C_FLAGS "-std=c99 ${CMAKE_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

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


if (CMAKE_BUILD_TYPE MATCHES "[A-Za-z]*[Dd][Ee][Bb][A-Za-z]+")
    message("-- Building LightSky with debug info.")
    add_definitions(-DLS_DEBUG)
endif()



if(BUILD_SHARED_LIBS)
    add_definitions(-DLS_SHARED -DLS_BUILD_SHARED)
endif()



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
