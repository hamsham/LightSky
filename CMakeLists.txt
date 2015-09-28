cmake_minimum_required(VERSION 2.8)

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
set(LS_STATIC_LIB_PREFIX "lib")
set(LS_STATIC_LIB_SUFFIX ".a")

set(LS_SHARED_LIB_PREFIX "lib")
set(LS_SHARED_LIB_SUFFIX ".so")

set(LS_BINARY_PREFIX "")
set(LS_BINARY_SUFFIX "")



# -------------------------------------
# Compiler Options
# -------------------------------------
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU"
    OR
    "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang"
)
    set(warnings "-Wall -Werror -Wextra -pedantic -pedantic-errors")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 ${warnings}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${warnings}")

    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG} -std=c99 ${warnings}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 ${warnings}")

    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE} -std=c99 ${warnings}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 ${warnings}")
else()
    message(FATAL_ERROR "Your compiler is currently unsupported.")
endif()



# -------------------------------------
# Sub-Projects
# -------------------------------------
add_subdirectory("LightSetup")
include_directories("LightSetup/include")

add_subdirectory("LightUtils")
include_directories("LightUtils/include")

add_subdirectory("LightMath")
include_directories("LightMath/include")

add_subdirectory("LightScript")
include_directories("LightScript/include")



# -------------------------------------
# Library Tests
# -------------------------------------
set(LS_SCRIPT_BUILD_TESTS FALSE CACHE BOOL "Build tests for the LightScript library.")

if(LS_SCRIPT_BUILD_TESTS)
    add_subdirectory("tests")
endif()
