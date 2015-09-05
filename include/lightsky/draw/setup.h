/* 
 * File:   draw/setup.h
 * Author: Miles Lacey
 *
 * Created on November 15, 2013, 8:37 PM
 */

#ifndef __LS_DRAW_SETUP_H__
#define	__LS_DRAW_SETUP_H__

#include "lightsky/setup/setup.h"

#include "lightsky/utils/assertions.h"
#include "lightsky/utils/hash.h"
#include "lightsky/utils/log.h"

#include "lightsky/math/math.h"

/* #include "lightsky/draw/lsgl.h" */

/*-------------------------------------
    OpenGL Header
-------------------------------------*/
#define GL_GLEXT_PROTOTYPES

#ifdef LS_OS_OSX
    #define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
    #include <OpenGL/gl.h>
    #include <OpenGL/gl3.h>
    #include <OpenGL/glext.h>
    #include <OpenGL/gl3ext.h>
#elif defined (LS_OS_IOS) || defined (LS_OS_IOS_SIM)
    #include <OpenGLES/ES3/gl.h>
    #include <OpenGLES/ES3/glext.h>
#else
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
#endif

/*-------------------------------------
    Debugging Various Messages.
-------------------------------------*/
#ifdef LS_DEBUG
    namespace ls {
    namespace draw {
        void printGlError(int line, const char* file);
    } // end draw namespace
    } // end ls namespace
#else
    namespace ls {
    namespace draw {
        inline void printGlError(int, const char*) {}
    } // end draw namespace
    } // end ls namespace
#endif

#ifndef LOG_GL_ERR
    #define LOG_GL_ERR() ls::draw::printGlError(__LINE__, __FILE__)
#endif

#endif	/* __LS_DRAW_SETUP_H__ */
