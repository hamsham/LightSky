
# #####################################
# External build for SDL2
# #####################################
#project(sdl2)

if (NOT CMAKE_SYSTEM_NAME MATCHES "iOS")
    set(CMAKE_THREAD_PREFER_PTHREAD)
    find_package(Threads)
endif()

include(ExternalProject)

# #####################################
# SDL2 VCS Setup
# #####################################
set(SDL2_GIT_BRANCH master)
set(SDL2_INSTALL_PREFIX    ${EXTERNAL_PROJECT_PREFIX})
set(SDL2_BINARY_DIRECTORY  ${SDL2_INSTALL_PREFIX}/src/Sdl2-build)
set(SDL2_SOURCE_DIRECTORY  ${SDL2_INSTALL_PREFIX}/src/Sdl2)
set(SDL2_INCLUDE_DIRECTORY ${SDL2_INSTALL_PREFIX}/include)
set(SDL2_LIBRARY_DIRECTORY ${SDL2_INSTALL_PREFIX}/lib)

set(SDL2_BRANCH "release-2.0.12" CACHE STRING "Git branch or tag for checking out SDL2.")
mark_as_advanced(SDL2_BRANCH)

set(SDL2_BUILD_SHARED OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(SDL2_BUILD_TYPE relwithdebinfo)
else()
    string(TOLOWER ${CMAKE_BUILD_TYPE} SDL2_BUILD_TYPE)
endif()

if (NOT SDL2_BUILD_TYPE OR SDL2_BUILD_TYPE MATCHES "debug")
    set(SDL2_LIB_SUFFIX d)
else()
    set(SDL2_LIB_SUFFIX "")
endif()

if (SDL2_BUILD_TYPE MATCHES "release" OR SDL2_BUILD_TYPE MATCHES "minsizerel")
    set(SDL2_LIB_TYPE Release)
else()
    set(SDL2_LIB_TYPE Debug)
endif()

# #####################################
# Configure build options
# #####################################
if (NOT CMAKE_SYSTEM_NAME MATCHES "Android")
    set(SDL2_BUILD_FLAGS
        -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
        -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
        -DCMAKE_RC_COMPILER:FILEPATH=${CMAKE_RC_COMPILER}
        -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX:FILEPATH=${SDL2_INSTALL_PREFIX}
        -DCMAKE_SYSTEM_NAME:STRING=${CMAKE_SYSTEM_NAME}
        -DCMAKE_LIBRARY_OUTPUT_DIRECTORY:FILEPATH=${SDL2_LIBRARY_DIRECTORY}
        -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY:FILEPATH=${SDL2_LIBRARY_DIRECTORY}
        -DBUILD_SHARED_LIBS:BOOL=${SDL2_BUILD_SHARED}
        -DSNDIO:BOOL=OFF)
else()
    set(SDL2_BUILD_FLAGS
        -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
        -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
        -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
        -DCMAKE_RC_COMPILER:FILEPATH=${CMAKE_RC_COMPILER}
        -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX:FILEPATH=${SDL2_INSTALL_PREFIX}
        -DCMAKE_SYSTEM_NAME:STRING=${CMAKE_SYSTEM_NAME}
        -DCMAKE_LIBRARY_OUTPUT_DIRECTORY:FILEPATH=${SDL2_LIBRARY_DIRECTORY}
        -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY:FILEPATH=${SDL2_LIBRARY_DIRECTORY}
        -DBUILD_SHARED_LIBS:BOOL=${SDL2_BUILD_SHARED}
        -DSNDIO:BOOL=OFF
        -DCMAKE_ANDROID_NDK:FILEPATH=${CMAKE_ANDROID_NDK}
        -DCMAKE_TOOLCHAIN_FILE:FILEPATH=${CMAKE_TOOLCHAIN_FILE}
        -DANDROID_ABI:STRING=${ANDROID_ABI}
        -DANDROID_PLATFORM:STRING=${ANDROID_PLATFORM}
        -DANDROID_ARM_MODE:STRING=${ANDROID_ARM_MODE})
endif()
mark_as_advanced(SDL2_BUILD_FLAGS)

# #####################################
# Build SDL2
# #####################################
if (CMAKE_SYSTEM_NAME MATCHES "iOS")
    find_program(XCODEBUILD_CMD
        xcodebuild
        PATHS
        /usr/bin
        /usr/local/bin)

    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE RelWithDebInfo)
    endif()
    string(TOLOWER ${CMAKE_BUILD_TYPE} SDL_XCODE_BUILD_TYPE)

    if (SDL_XCODE_BUILD_TYPE MATCHES "release" OR SDL_XCODE_BUILD_TYPE MATCHES "minsizerel")
        set(SDL_XCODE_BUILD_STR Release)
    else()
        set(SDL_XCODE_BUILD_STR Debug)
    endif()

    if (LS_BUILD_IOS_SIM)
        set(SDL_XCODE_SDK iphonesimulator)
        set(SDL_XCODE_ARCH -arch x86_64 -arch i386)
    else()
        set(SDL_XCODE_SDK iphoneos)
        set(SDL_XCODE_ARCH -arch armv7 -arch arm64)
    endif()
endif()

if (CMAKE_SYSTEM_NAME MATCHES "iOS")
    ExternalProject_Add(
        Sdl2
        PREFIX
            ${SDL2_INSTALL_PREFIX}
        GIT_REPOSITORY
            "https://github.com/SDL-mirror/SDL.git"
        GIT_TAG
            "${SDL2_BRANCH}"
        CONFIGURE_COMMAND
            ${CMAKE_COMMAND} -E make_directory ${SDL2_LIBRARY_DIRECTORY} &&
            ${CMAKE_COMMAND} -E make_directory ${SDL2_INCLUDE_DIRECTORY}
        BUILD_COMMAND
            ${XCODEBUILD_CMD} SYMROOT=${SDL2_LIBRARY_DIRECTORY} -sdk ${SDL_XCODE_SDK} only_active_arch=no -scheme libSDL-iOS -configuration ${SDL_XCODE_BUILD_STR} -project "${SDL2_SOURCE_DIRECTORY}/Xcode-iOS/SDL/SDL.xcodeproj"
        INSTALL_DIR
            ${SDL2_INSTALL_PREFIX}
        INSTALL_COMMAND
            ${CMAKE_COMMAND} -E copy_if_different "${SDL2_INSTALL_PREFIX}/${SDL2_LIB_TYPE}-${SDL_XCODE_SDK}/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2${SDL2_LIB_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX}" "${SDL2_INSTALL_PREFIX}/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2${SDL2_LIB_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX}" &&
            ${CMAKE_COMMAND} -E copy_directory ${SDL2_SOURCE_DIRECTORY}/include ${SDL2_INSTALL_PREFIX}/include/SDL2
    )
else()
    ExternalProject_Add(
        Sdl2
        PREFIX
            ${SDL2_INSTALL_PREFIX}
        GIT_REPOSITORY
            "https://github.com/SDL-mirror/SDL.git"
        GIT_TAG
            "${SDL2_BRANCH}"
        CMAKE_COMMAND
            ${CMAKE_COMMAND}
        CMAKE_CACHE_ARGS
            ${SDL2_BUILD_FLAGS}
        BUILD_COMMAND
            ${CMAKE_COMMAND} -E make_directory ${SDL2_LIBRARY_DIRECTORY} &&
            ${CMAKE_COMMAND} -E make_directory ${SDL2_INCLUDE_DIRECTORY} &&
            ${CMAKE_COMMAND} -E chdir ${SDL2_BINARY_DIRECTORY} ${CMAKE_COMMAND} --build . --config ${CMAKE_CFG_INTDIR}
        INSTALL_DIR
            ${SDL2_INSTALL_PREFIX}
        INSTALL_COMMAND
            ${CMAKE_COMMAND} -E chdir ${SDL2_BINARY_DIRECTORY} ${CMAKE_COMMAND} --build . --config ${CMAKE_CFG_INTDIR} --target install
    )
endif()



# Add the imported library target
add_library(SDL2 STATIC IMPORTED)
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION ${EXTERNAL_PROJECT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2${SDL2_LIB_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies(SDL2 Sdl2)

add_library(SDL2_MAIN STATIC IMPORTED)
set_target_properties(SDL2_MAIN PROPERTIES IMPORTED_LOCATION ${EXTERNAL_PROJECT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2main${SDL2_LIB_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies(SDL2_MAIN Sdl2)

add_dependencies(SDL2 Sdl2)



# #####################################
# Final Library Output
# #####################################
function(sdl2_locate_apple_framework outVariable framework)
    find_library(temp ${framework} REQUIRED)

    if (temp MATCHES temp-NOTFOUND)
        message(FATAL_ERROR "-- Unable to find ${framework} for linking with SDL2.")
    else()
        message("-- Found ${framework}: ${temp}")
        set(${outVariable} "-framework ${framework}" PARENT_SCOPE)
    endif()
endfunction()

function(sdl2_locate_library outVariable libName)
    find_library(temp ${libName} REQUIRED)

    if (temp MATCHES temp-NOTFOUND)
        message(FATAL_ERROR "-- Unable to find ${libName} for linking with SDL2.")
    else()
        message("-- Found ${libName}: ${temp}")
        set(${outVariable} "${libName}" PARENT_SCOPE)
    endif()
endfunction()

if (WIN32)
    find_package(OpenGL REQUIRED)

    set(SDL2_LIBRARIES SDL2 ${OPENGL_LIBRARIES} Threads::Threads Setupapi Version Imm32 User32 Kernel32)
elseif (CMAKE_SYSTEM_NAME MATCHES "Android")
    find_path(GLES2_INCLUDE_DIR GLES2/gl2.h HINTS ${ANDROID_NDK})
    find_library(GLES2_LIBRARY libGLESv2.so HINTS "${GLES2_INCLUDE_DIR}/../lib")

    find_path(GLES3_INCLUDE_DIR GLES3/gl3.h HINTS ${ANDROID_NDK})
    find_library(GLES3_LIBRARY libGLESv3.so HINTS "${GLES3_INCLUDE_DIR}/../lib")

    find_path(EGL_INCLUDE_DIR EGL/egl.h HINTS ${ANDROID_NDK})
    find_library(EGL_LIBRARY libEGL.so HINTS "${EGL_INCLUDE_DIR}/../lib")

    find_path(ANDROID_INCLUDE_DIR android/ndk-version.h HINTS ${ANDROID_NDK})
    find_library(ANDROID_LIBRARY libandroid.so HINTS "${ANDROID_INCLUDE_DIR}/../lib")
    find_library(ANDROID_LOG_LIBRARY liblog.so HINTS "${ANDROID_INCLUDE_DIR}/../lib")

    if (NOT GLES2_LIBRARY)
        message(FATAL_ERROR "Error: Unable to locate OpenGLES 2")
    else()
        message("-- Found OpenGLES 2: ${GLES2_LIBRARY}")
    endif()

    if (NOT GLES3_LIBRARY)
        message(FATAL_ERROR "Error: Unable to locate OpenGLES 3")
    else()
        message("-- Found OpenGLES 3: ${GLES3_LIBRARY}")
    endif()

    if (NOT EGL_LIBRARY)
        message(FATAL_ERROR "Error: Unable to locate EGL")
    else()
        message("-- Found EGL: ${EGL_LIBRARY}")
    endif()

    if (NOT ANDROID_LIBRARY)
        message(FATAL_ERROR "Error: Unable to locate Android library")
    else()
        message("-- Found Android libs: ${ANDROID_LIBRARY}")
    endif()

    if (NOT ANDROID_LOG_LIBRARY)
        message(FATAL_ERROR "Error: Unable to locate Android logging library")
    else()
        message("-- Found Android logging library: ${ANDROID_LOG_LIBRARY}")
    endif()

    set(SDL2_LIBRARIES SDL2 SDL2_MAIN ${OPENGL_LIBRARIES} ${GLES2_LIBRARY} ${GLES3_LIBRARY} ${EGL_LIBRARY} ${ANDROID_LOG_LIBRARY} ${ANDROID_LIBRARY} Threads::Threads)
elseif(NOT APPLE)
    find_package(OpenGL REQUIRED)
    find_library(DYNAMIC_LIBRARY dl REQUIRED)

    if (DYNAMIC_LIBRARY-NOTFOUND)
        message(FATAL_ERROR "-- Unable to find libdl for linking with SDL2.")
    endif()

    set(SDL2_LIBRARIES SDL2 SDL2_MAIN ${OPENGL_LIBRARIES} Threads::Threads ${DYNAMIC_LIBRARY})

elseif(APPLE)
    set(CMAKE_FIND_FRAMEWORK LAST)

    if (CMAKE_SYSTEM_NAME MATCHES "iOS")
        sdl2_locate_apple_framework(AUDIO_TOOLBOX_LIBRARY AudioToolbox)
        sdl2_locate_apple_framework(AV_FOUNDATION_LIBRARY AVFoundation)
        sdl2_locate_apple_framework(CORE_AUDIO_LIBRARY CoreAudio)
        sdl2_locate_apple_framework(CORE_BT_LIBRARY CoreBluetooth)
        sdl2_locate_apple_framework(CORE_GRAPHICS_LIBRARY CoreGraphics)
        sdl2_locate_apple_framework(CORE_MOTION_LIBRARY CoreMotion)
        sdl2_locate_apple_framework(GAME_CONTROOLER_LIBRARY GameController)
        sdl2_locate_apple_framework(IO_KIT_LIBRARY IOKit)
        sdl2_locate_apple_framework(GLES_LIBRARY OpenGLES)
        sdl2_locate_apple_framework(METAL_LIBRARY Metal)
        sdl2_locate_apple_framework(QUARTZ_CORE_LIBRARY QuartzCore)
        sdl2_locate_apple_framework(UIKit_LIBRARY UIKit)

        set(SDL2_LIBRARIES SDL2 "${GLES_LIBRARY}" "${METAL_LIBRARY}" "${CORE_BT_LIBRARY}" "${AV_FOUNDATION_LIBRARY}" "${AUDIO_TOOLBOX_LIBRARY}" "${CORE_GRAPHICS_LIBRARY}" "${CORE_AUDIO_LIBRARY}" "${CORE_MOTION_LIBRARY}" "${IO_KIT_LIBRARY}" "${UIKit_LIBRARY}" "${QUARTZ_CORE_LIBRARY}" "${GAME_CONTROOLER_LIBRARY}")
    else()
        sdl2_locate_apple_framework(CARBON_LIBRARY Carbon)
        sdl2_locate_apple_framework(COCOA_LIBRARY Cocoa)
        sdl2_locate_apple_framework(OPENGL_LIBRARY OpenGL)
        sdl2_locate_apple_framework(METAL_LIBRARY Metal)
        sdl2_locate_apple_framework(FORCEFEEDBACK_LIBRARY ForceFeedback)
        sdl2_locate_apple_framework(CORE_BT_LIBRARY CoreBluetooth)
        sdl2_locate_apple_framework(AV_FOUNDATION_LIBRARY AVFoundation)
        sdl2_locate_apple_framework(AUDIO_TOOLBOX_LIBRARY AudioToolbox)
        sdl2_locate_apple_framework(CORE_GRAPHICS_LIBRARY CoreGraphics)
        sdl2_locate_apple_framework(CORE_AUDIO_LIBRARY CoreAudio)
        sdl2_locate_apple_framework(IO_KIT_LIBRARY IOKit)
        sdl2_locate_apple_framework(QUARTZ_CORE_LIBRARY QuartzCore)
        sdl2_locate_apple_framework(GAME_CONTROOLER_LIBRARY GameController)
        sdl2_locate_library(ICONV_LIBRARY iconv)

        set(SDL2_LIBRARIES SDL2 "${COCOA_LIBRARY}" "${CARBON_LIBRARY}" "${OPENGL_LIBRARY}" "${METAL_LIBRARY}" "${FORCEFEEDBACK_LIBRARY}" "${CORE_BT_LIBRARY}" "${AV_FOUNDATION_LIBRARY}" "${AUDIO_TOOLBOX_LIBRARY}" "${CORE_GRAPHICS_LIBRARY}" "${CORE_AUDIO_LIBRARY}" "${IO_KIT_LIBRARY}" "${QUARTZ_CORE_LIBRARY}" "${GAME_CONTROOLER_LIBRARY}" ${ICONV_LIBRARY} Threads::Threads)
    endif()
endif()
