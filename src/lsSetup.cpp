/* 
 * File:   main.cpp
 * Author: hammy
 *
 * Created on November 15, 2013, 8:28 PM
 */

#include <GL/glew.h>

#include "lsSetup.h"

/*
 * OpenGL Errors
 */
#ifdef LS_DEBUG
void lsPrintGlError(int line, const char* file) {
    const GLenum errorCode = glGetError();
    
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
#endif
