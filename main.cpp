/* 
 * File:   main.cpp
 * Author: hammy
 *
 * Created on November 15, 2013, 8:28 PM
 */

#include "main.h"
#include "system.h"
#include "testState.h"

/**
 * Simple Weekend Game #1
 */
bool startGame();
void endGame();

/******************************************************************************
 * OpenGL Errors
******************************************************************************/
void printGlError(int line, const char* file) {
    GLenum errorCode = glGetError();
    
    switch(errorCode) {
        case GL_INVALID_ENUM:
            LOG_ERR("OpenGL Error: GL_INVALID_ENUM On line ", line, " of file ", file, '\n');
            break;
        case GL_INVALID_VALUE:
            LOG_ERR("OpenGL Error: GL_INVALID_VALUE On line ", line, " of file ", file, '\n');
            break;
        case GL_INVALID_OPERATION:
            LOG_ERR("OpenGL Error: GL_INVALID_OPERATION On line ", line, " of file ", file, '\n');
            break;
        case GL_STACK_OVERFLOW:
            LOG_ERR("OpenGL Error: GL_STACK_OVERFLOW On line ", line, " of file ", file, '\n');
            break;
        case GL_STACK_UNDERFLOW:
            LOG_ERR("OpenGL Error: GL_STACK_UNDERFLOW On line ", line, " of file ", file, '\n');
            break;
        case GL_OUT_OF_MEMORY:
            LOG_ERR("OpenGL Error: GL_OUT_OF_MEMORY On line ", line, " of file ", file, '\n');
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            LOG_ERR("OpenGL Error: GL_INVALID_FRAMEBUFFER_OPERATION On line ", line, " of file ", file, '\n');
            break;
        case GL_NO_ERROR:
        default:
            break;
    }
}

/**
 * Global variables declared in main.h
 */
namespace global {
    display* pDisplay = nullptr;
    subsystem* pSystem = nullptr;
    hamLibs::utils::randomNum* pRandGen = nullptr;
}
    
bool startGame(int argc, char** argv) {
    /*
     * Game Initialization
     */
    LOG_MSG(
        "Parameter count: ", argc, '\n',
        "Parameters:"
    );
    for (int argCount = 0; argCount < argc; ++argCount) {
        LOG_MSG('\t', argCount, ":\t", argv[argCount]);
    }
    
    global::pSystem = new(std::nothrow) subsystem();
    if (!global::pSystem || !global::pSystem->init()) {
        return false;
    }
    
    global::pDisplay = new(std::nothrow) display{};
    if (!global::pDisplay || !global::pDisplay->init(
            math::vec2i{LS_DEFAULT_DISPLAY_WIDTH, LS_DEFAULT_DISPLAY_HEIGHT}, false, true)
    ) {
        return false;
    }
    
    global::pRandGen = new(std::nothrow) hamLibs::utils::randomNum(
        hamLibs::utils::clock::globalSecond()
    );
    if (!global::pRandGen) {
        return false;
    }
    
    return true;
}

/*
 * Main
 */
int main(int argc, char** argv) {
    if (!startGame(argc, argv)) {
        endGame();
        return false;
    }
    
    if (!global::pSystem->pushGameState(new(std::nothrow) testState())) {
        endGame();
        return -1;
    }
    
    
    global::pSystem->run();
    
    endGame();
    
    return 0;
}

/*
 * Game Termination
 */  
void endGame() {
    if (global::pDisplay) {
        global::pDisplay->terminate();
    }
    delete global::pDisplay;
    global::pDisplay = nullptr;
    
    if (global::pSystem) {
        global::pSystem->terminate();
    }
    delete global::pSystem;
    global::pSystem = nullptr;
    
    delete global::pRandGen;
    global::pRandGen = nullptr;
    
    LOG_MSG("Game successfully terminated.\n");
    
    return;
}

