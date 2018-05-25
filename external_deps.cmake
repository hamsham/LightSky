
# #####################################
# External Project Setup
# #####################################
# Include the CMake module to support the builds of 3rd-party dependencies
include(ExternalProject)

# Sub-directories within the build folder (not installation folder).
set(EXTERNAL_PROJECT_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/external" CACHE STRING "Build prefix for 3rd-party libraries.")
mark_as_advanced(EXTERNAL_PROJECT_PREFIX)

# Include directory for 3rd-party libraries
include_directories(BEFORE SYSTEM ${EXTERNAL_PROJECT_PREFIX}/include)



# #####################################
# Folders for the external data
# #####################################
file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_PREFIX})
file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_PREFIX}/include)
file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_PREFIX}/lib)



# #####################################
# External build for GLM (for testing only)
# #####################################
set(GLM_BRANCH "master" CACHE STRING "Git branch or tag for checking out GLM.")
mark_as_advanced(GLM_BRANCH)

# Configure build options
set(GLM_BUILD_FLAGS
    -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
    -DCMAKE_INSTALL_PREFIX:STRING=${EXTERNAL_PROJECT_PREFIX}
    -DGLM_TEST_ENABLE:BOOL=OFF
    -DGLM_TEST_ENABLE_CXX_11:BOOL=ON
    -DGLM_TEST_ENABLE_FAST_MATH:BOOL=ON)
mark_as_advanced(GLM_BUILD_FLAGS)

# Compiler settings for GLM
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

# Build GLM
ExternalProject_Add(
    Glm
    PREFIX
    ${EXTERNAL_PROJECT_PREFIX}
    GIT_REPOSITORY
        "https://github.com/g-truc/glm.git"
    GIT_SHALLOW
        TRUE
    GIT_PROGRESS
        TRUE
    GIT_TAG
        "${GLM_BRANCH}"
    CMAKE_COMMAND
        ${CMAKE_COMMAND}
    CMAKE_CACHE_ARGS
        ${GLM_BUILD_FLAGS}
    CMAKE_ARGS
        ${GLM_BUILD_FLAGS}
    BUILD_COMMAND
        make
    INSTALL_DIR
        ${EXTERNAL_PROJECT_PREFIX}
    INSTALL_COMMAND
        make install
)



# #####################################
# External build for ASSIMP
# #####################################
set(ASSIMP_BRANCH "master" CACHE STRING "Git branch or tag for checking out Assimp.")
mark_as_advanced(ASSIMP_BRANCH)

# Configure build options
set(ASSIMP_BUILD_FLAGS
    -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
    -DCMAKE_INSTALL_PREFIX:STRING=${EXTERNAL_PROJECT_PREFIX}
    -DBUILD_SHARED_LIBS:BOOL=OFF
    -DASSIMP_BUILD_ZLIB:BOOL=ON
    -DASSIMP_BUILD_TESTS:BOOL=OFF
    -DASSIMP_BUILD_SAMPLES:BOOL=OFF
    -DASSIMP_BUILD_ASSIMP_TOOLS:BOOL=OFF)
mark_as_advanced(ASSIMP_BUILD_FLAGS)

# Build Assimp
ExternalProject_Add(
    Assimp
    PREFIX
        ${EXTERNAL_PROJECT_PREFIX}
    GIT_REPOSITORY
        "https://github.com/assimp/assimp.git"
    GIT_SHALLOW
        TRUE
    GIT_PROGRESS
        TRUE
    GIT_TAG
        "${ASSIMP_BRANCH}"
    CMAKE_COMMAND
        ${CMAKE_COMMAND}
    CMAKE_CACHE_ARGS
        ${ASSIMP_BUILD_FLAGS}
    BUILD_COMMAND
        make
    INSTALL_DIR
        ${EXTERNAL_PROJECT_PREFIX}
    INSTALL_COMMAND
        make install
)

# Add the imported library target
add_library(assimp STATIC IMPORTED)
set_target_properties(assimp PROPERTIES IMPORTED_LOCATION ${EXTERNAL_PROJECT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}assimp${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies(assimp Assimp)

add_library(IrrXML STATIC IMPORTED)
set_target_properties(IrrXML PROPERTIES IMPORTED_LOCATION ${EXTERNAL_PROJECT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}IrrXML${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies(IrrXML Assimp)

add_library(zlibstatic STATIC IMPORTED)
set_target_properties(zlibstatic PROPERTIES IMPORTED_LOCATION ${EXTERNAL_PROJECT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}zlibstatic${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies(zlibstatic Assimp)

set(ASSIMP_LIBS assimp IrrXML zlibstatic)



# #####################################
# External build for FreeImage
# #####################################
set(FIMG_BRANCH "master" CACHE STRING "Git branch or tag for checking out FreeImage.")
mark_as_advanced(FIMG_BRANCH)

# FreeImage needs a few environment variables to build correctly.
# Use a configure file to setup the environment and run the build.
configure_file(${PROJECT_SOURCE_DIR}/build_freeimage.sh ${EXTERNAL_PROJECT_PREFIX}/build_freeimage.sh @ONLY)

# Build FreeImage
ExternalProject_Add(
    FreeImage
    PREFIX
        ${EXTERNAL_PROJECT_PREFIX}
    GIT_REPOSITORY
        "https://github.com/MonoGame/FreeImage.git"
    GIT_SHALLOW
        TRUE
    GIT_PROGRESS
        TRUE
    GIT_TAG
        "${FIMG_BRANCH}"
    UPDATE_COMMAND
        git fetch
    CONFIGURE_COMMAND
        bash ${EXTERNAL_PROJECT_PREFIX}/build_freeimage.sh --configure
    BUILD_COMMAND
        bash ${EXTERNAL_PROJECT_PREFIX}/build_freeimage.sh --make
    BUILD_IN_SOURCE
        1
    INSTALL_COMMAND
        bash ${EXTERNAL_PROJECT_PREFIX}/build_freeimage.sh --install
)

# Add the imported library target
add_library(freeimage STATIC IMPORTED)
set_target_properties(freeimage PROPERTIES IMPORTED_LOCATION ${EXTERNAL_PROJECT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}freeimage${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies(freeimage FreeImage)

set(FREEIMAGE_LIBS freeimage)



# #####################################
# External build for FreeType
# #####################################
set(FREETYPE_BRANCH "master" CACHE STRING "Git branch or tag for checking out FreeType.")
mark_as_advanced(FREETYPE_BRANCH)

# Configure build options
set(FREETYPE_BUILD_FLAGS
    -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
    -DCMAKE_INSTALL_PREFIX:STRING=${EXTERNAL_PROJECT_PREFIX}
    -DBUILD_SHARED_LIBS:BOOL=FALSE
    -DCMAKE_DISABLE_FIND_PACKAGE_HarfBuzz:BOOL=TRUE)
mark_as_advanced(FREETYPE_BUILD_FLAGS)

# Build FreeType
ExternalProject_Add(
    FreeType
    PREFIX
        ${EXTERNAL_PROJECT_PREFIX}
    GIT_REPOSITORY
        "https://git.savannah.nongnu.org/r/freetype/freetype2.git"
    GIT_SHALLOW
        TRUE
    GIT_PROGRESS
        TRUE
    GIT_TAG
        "${FREETYPE_BRANCH}"
    CMAKE_COMMAND
        ${CMAKE_COMMAND}
    CMAKE_CACHE_ARGS
        ${FREETYPE_BUILD_FLAGS}
    BUILD_COMMAND
        make
    INSTALL_DIR
        ${EXTERNAL_PROJECT_PREFIX}
    INSTALL_COMMAND
        make install
)

# Add the imported library target
add_library(freetype STATIC IMPORTED)
set_target_properties(freetype PROPERTIES IMPORTED_LOCATION ${EXTERNAL_PROJECT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}freetype${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies(freetype FreeType)

include_directories(BEFORE SYSTEM ${EXTERNAL_PROJECT_PREFIX}/include/freetype2)

set(FREETYPE_LIBS freetype)



# #####################################
# External build for Boost-Regex
# #####################################
set(BOOST_BRANCH "master" CACHE STRING "Git branch or tag for checking out Boost-Regex.")
mark_as_advanced(BOOST_BRANCH)

# Include Boost
ExternalProject_Add(
    Boost_Regex
    PREFIX
        ${EXTERNAL_PROJECT_PREFIX}
    GIT_REPOSITORY
        "https://github.com/boostorg/regex.git"
    GIT_SHALLOW
        TRUE
    GIT_PROGRESS
        TRUE
    GIT_TAG
        "${BOOST_BRANCH}"
    CONFIGURE_COMMAND
        ""
    BUILD_COMMAND
        ""
    INSTALL_DIR
        ${EXTERNAL_PROJECT_PREFIX}
    INSTALL_COMMAND
        ${CMAKE_COMMAND} -E copy_directory include "${EXTERNAL_PROJECT_PREFIX}"
)

# Add the imported library
set(BOOST_REGEX_HEADER ${EXTERNAL_PROJECT_PREFIX}/include/boost/regex.hpp)



# #####################################
# External build for SDL2
# #####################################
set(SDL2_BRANCH "release-2.0.8" CACHE STRING "Git branch or tag for checking out SDL2.")
mark_as_advanced(SDL2_BRANCH)

# Configure build options
set(SDL2_BUILD_FLAGS
    -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
    -DCMAKE_INSTALL_PREFIX:STRING=${EXTERNAL_PROJECT_PREFIX}
    -DBUILD_SHARED_LIBS:BOOL=FALSE
    -DSNDIO:BOOL=OFF)
mark_as_advanced(FREETYPE_BUILD_FLAGS)

# Build SDL2
ExternalProject_Add(
    Sdl2
    PREFIX
        ${EXTERNAL_PROJECT_PREFIX}
    HG_REPOSITORY
        "https://hg.libsdl.org/SDL"
    HG_TAG
        "${SDL2_BRANCH}"
    CMAKE_COMMAND
        ${CMAKE_COMMAND}
    CMAKE_CACHE_ARGS
        ${SDL2_BUILD_FLAGS}
    BUILD_COMMAND
        make
    INSTALL_DIR
        ${EXTERNAL_PROJECT_PREFIX}
    INSTALL_COMMAND
        make install
)

# Add the imported library target
add_library(SDL2 STATIC IMPORTED)
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION ${EXTERNAL_PROJECT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies(SDL2 Sdl2)

set(SDL2_LIBS SDL2 pthread dl)
