/* 
 * File:   main.cpp
 * Author: hammy
 *
 * Created on November 15, 2013, 8:28 PM
 */

#include "lsSetup.h"
#include "lsSystem.h"

/******************************************************************************
 * OpenGL Errors
******************************************************************************/
void lsPrintGlError(int line, const char* file) {
    GLenum errorCode = glGetError();
    
    switch(errorCode) {
        case GL_INVALID_ENUM:
            LS_LOG_ERR("OpenGL Error: GL_INVALID_ENUM On line ", line, " of file ", file, '\n');
            break;
        case GL_INVALID_VALUE:
            LS_LOG_ERR("OpenGL Error: GL_INVALID_VALUE On line ", line, " of file ", file, '\n');
            break;
        case GL_INVALID_OPERATION:
            LS_LOG_ERR("OpenGL Error: GL_INVALID_OPERATION On line ", line, " of file ", file, '\n');
            break;
        case GL_STACK_OVERFLOW:
            LS_LOG_ERR("OpenGL Error: GL_STACK_OVERFLOW On line ", line, " of file ", file, '\n');
            break;
        case GL_STACK_UNDERFLOW:
            LS_LOG_ERR("OpenGL Error: GL_STACK_UNDERFLOW On line ", line, " of file ", file, '\n');
            break;
        case GL_OUT_OF_MEMORY:
            LS_LOG_ERR("OpenGL Error: GL_OUT_OF_MEMORY On line ", line, " of file ", file, '\n');
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            LS_LOG_ERR("OpenGL Error: GL_INVALID_FRAMEBUFFER_OPERATION On line ", line, " of file ", file, '\n');
            break;
        case GL_NO_ERROR:
        default:
            break;
    }
}

/**
 * Global variables declared in main.h
 */
namespace lsGlobal {
    lsDisplay* pDisplay = nullptr;
    lsSubsystem* pSystem = nullptr;
    hamLibs::utils::randomNum* pRandGen = nullptr;
}

/*
 * Initialize Light Sky
 */
bool lsInit(int argc, char** argv) {
    LS_LOG_MSG("Initializing LightSky.");
    
    /*
     * Game Initialization
     */
    LS_LOG_MSG(
        "LightSky Parameter count: ", argc, '\n',
        "LightSky Parameters:"
    );
    
    for (int argCount = 0; argCount < argc; ++argCount) {
        LS_LOG_MSG('\t', argCount, ":\t", argv[argCount]);
    }
    
    lsGlobal::pSystem = new(std::nothrow) lsSubsystem();
    if (!lsGlobal::pSystem || !lsGlobal::pSystem->init()) {
        LS_LOG_ERR("\tFailed to initialize the LightSky system manager.\n.");
        return false;
    }
    
    lsGlobal::pDisplay = new(std::nothrow) lsDisplay{};
    if (!lsGlobal::pDisplay || !lsGlobal::pDisplay->init(
            math::vec2i{LS_DEFAULT_DISPLAY_WIDTH, LS_DEFAULT_DISPLAY_HEIGHT}, false, true)
    ) {
        LS_LOG_ERR("\tFailed to initialize the LightSky global display.\n.");
        return false;
    }
    
    lsGlobal::pRandGen = new(std::nothrow) hamLibs::utils::randomNum(
        hamLibs::utils::clock::globalSecond()
    );
    if (!lsGlobal::pRandGen) {
        return false;
        LS_LOG_ERR("\tFailed to initialize the LightSky PRNG.\n.");
    }
    
    LS_LOG_MSG("\tLightSky Successfully initialized.\n");
    return true;
}

/*
 * Terminate lightSky
 */
void lsTerminate() {
    if (lsGlobal::pDisplay) {
        lsGlobal::pDisplay->terminate();
    }
    delete lsGlobal::pDisplay;
    lsGlobal::pDisplay = nullptr;
    
    if (lsGlobal::pSystem) {
        lsGlobal::pSystem->terminate();
    }
    delete lsGlobal::pSystem;
    lsGlobal::pSystem = nullptr;
    
    delete lsGlobal::pRandGen;
    lsGlobal::pRandGen = nullptr;
    
    LS_LOG_MSG("LightSky successfully terminated.\n");
    
    return;
}
