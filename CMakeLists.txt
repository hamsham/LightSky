cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_DISABLE_IN_SOURCE_BUILDS ON)



# -------------------------------------
# Project Setup
# -------------------------------------
project("LightSky Game Development Framework")



# -------------------------------------
# Output Folder Setup
# -------------------------------------
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

link_directories()
get_directory_property(CURR_LINK_DIRS LINK_DIRECTORIES)

if("${CURR_LINK_DIRS}")
    link_directories("${CURR_LINK_DIRS}" "${LIBRARY_OUTPUT_PATH}")
else()
    link_directories("${LIBRARY_OUTPUT_PATH}")
endif()



# -------------------------------------
# Compiler-Specific Naming Conventions
# -------------------------------------
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU"
    OR
    "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang"
)
    if(WIN32)
        set(LS_STATIC_LIB_PREFIX "lib")
        set(LS_STATIC_LIB_SUFFIX ".a")

        set(LS_SHARED_LIB_PREFIX "lib")
        set(LS_SHARED_LIB_SUFFIX ".dll")

        set(LS_BINARY_PREFIX "")
        set(LS_BINARY_SUFFIX "exe")
        
    else()
        set(LS_STATIC_LIB_PREFIX "lib")
        set(LS_STATIC_LIB_SUFFIX ".a")

        set(LS_SHARED_LIB_PREFIX "lib")
        set(LS_SHARED_LIB_SUFFIX ".so")

        set(LS_BINARY_PREFIX "")
        set(LS_BINARY_SUFFIX "")

    endif(WIN32)
    
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    set(LS_STATIC_LIB_PREFIX "")
    set(LS_STATIC_LIB_SUFFIX ".lib")

    set(LS_SHARED_LIB_PREFIX "")
    set(LS_SHARED_LIB_SUFFIX ".dll")

    set(LS_BINARY_PREFIX "")
    set(LS_BINARY_SUFFIX "")
    
endif()



# -------------------------------------
# Compiler Options
# -------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    set(LS_COMPILER_WARNINGS "-Wall -Werror -Wextra -pedantic -pedantic-errors")
    set(LS_COMMON_COMPILER_FLAGS "")
    set(LS_C_COMPILER_FLAGS "-std=c99 ${LS_COMMON_COMPILER_FLAGS} ${LS_COMPILER_WARNINGS}")
    set(LS_CXX_COMPILER_FLAGS "-std=c++11 ${LS_COMMON_COMPILER_FLAGS} ${LS_COMPILER_WARNINGS}")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LS_C_COMPILER_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LS_CXX_COMPILER_FLAGS}")
    
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

    set(LS_COMPILER_WARNINGS "/Wall /sdl /W3 /WX")
    set(LS_COMMON_COMPILER_FLAGS "/Za /Zc:rvalueCast /Zc:strictStrings /Zc:inline")
    set(LS_C_COMPILER_FLAGS "${LS_COMMON_COMPILER_FLAGS} ${LS_COMPILER_WARNINGS}")
    set(LS_CXX_COMPILER_FLAGS "${LS_COMMON_COMPILER_FLAGS} ${LS_COMPILER_WARNINGS}")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LS_C_COMPILER_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LS_CXX_COMPILER_FLAGS}")

else()

    message(FATAL_ERROR "Your compiler is currently unsupported: ${CMAKE_CXX_COMPILER_ID}")
    
endif()


set(LS_BUILD_SHARED_LIBS TRUE CACHE BOOL FORCE "Build shared libraries for LightSky where applicable.")
if(LS_BUILD_SHARED_LIBS)
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



# -------------------------------------
# Library Tests
# -------------------------------------
set(LS_SCRIPT_BUILD_TESTS TRUE CACHE BOOL "Build tests for the LightScript library.")

if(LS_SCRIPT_BUILD_TESTS)
    add_subdirectory("tests")
endif()
