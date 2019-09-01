/*
 * File:   draw/context.cpp
 * Author: Miles Lacey
 *
 * Created on August 2, 2014, 8:44 PM
 */

#include <iostream>

#include "lightsky/draw/Setup.h" // pull in OpenGL's headers

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#include "lightsky/utils/Log.h"
#include "lightsky/math/vec2.h"
#include "lightsky/draw/Color.h"
#include "lightsky/game/Game.h"
namespace math = ls::math;

#include "Display.h"
#include "Context.h"

/*-------------------------------------
    Render Context constructor
-------------------------------------*/
Context::Context() :
    pContext {nullptr}
{
}

/*-------------------------------------
    Render Context move constructor
-------------------------------------*/
Context::Context(Context&& r) :
    pContext {r.pContext}
{
    r.pContext = nullptr;
}

/*-------------------------------------
    Render Context move operator
-------------------------------------*/
Context& Context::operator =(Context&& r) {
    pContext = r.pContext;
    r.pContext = nullptr;

    return *this;
}

/*-------------------------------------
    Render Context destructor
-------------------------------------*/
Context::~Context() {
    terminate();
}

/*-------------------------------------
    Render Context initialization
-------------------------------------*/
bool Context::init(const Display& disp, bool useVsync) {
    terminate();

    if (disp.is_running() == false) {
        LS_LOG_ERR("\tAttempted to initialize a render context with no display.\n");
        return false;
    }

    // Attach the OpenGL context to our window handle
    LS_LOG_MSG("Initializing an OpenGL rendering context.");
    pContext = SDL_GL_CreateContext(disp.get_window());

    if (!pContext) {
        LS_LOG_ERR(
            "\tUnable to create a render context through SDL.",
            "\n\t", SDL_GetError(),
            '\n'
            );
        terminate();
        return false;
    }
    LS_LOG_MSG("\tSuccessfully created a basic render context.");

    // Quick setup in order to normalize OpenGL to the display coordinates.
    this->make_current(disp);

    const math::vec2i&& displayRes = disp.get_resolution();
    glViewport(0, 0, displayRes[0], displayRes[1]);
    LS_LOG_GL_ERR();

    // Set the default back buffer color
    const ls::draw::color::color& mgcPnk = ls::draw::color::magenta;
    glClearColor(mgcPnk[0], mgcPnk[1], mgcPnk[2], mgcPnk[3]);
    LS_LOG_GL_ERR();

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    LS_LOG_GL_ERR();

    set_vsync(useVsync);

    LS_LOG_MSG(
        "\tSuccessfully initialized a OpenGL 3.3-compatible render context:"
        "\n\tV-Sync: ", get_vsync()
        );

    LS_LOG_MSG("\tSuccessfully initialized the OpenGL 3.3 render context.\n");

    return true;
}

/*-------------------------------------
    Renderer resource termination
-------------------------------------*/
void Context::terminate() {
    //ls::draw::terminate();

    if (pContext) {
        SDL_GL_DeleteContext(pContext);
    }
    pContext = nullptr;
}

/*-------------------------------------
    Activate the render context used in this window.
-------------------------------------*/
void Context::make_current(const Display& disp) const {
    SDL_GL_MakeCurrent(disp.get_window(), pContext);
}

/*-------------------------------------
    Enable/Disable VSync
-------------------------------------*/
void Context::set_vsync(bool vsync) {
    SDL_GL_SetSwapInterval((int)vsync);
}

/*-------------------------------------
    Determine if VSync is enabled or disabled within the current window.
-------------------------------------*/
bool Context::get_vsync() const {
    return SDL_GL_GetSwapInterval() != 0;
}

/*-------------------------------------
    Swap the current display's front and back buffers.
-------------------------------------*/
void Context::flip(const Display& disp) const {
    SDL_GL_SwapWindow(disp.get_window());
}
