
/*
 * File:   MainState.cpp
 * Author: miles
 *
 * Created on February 9, 2016, 12:59 AM
 */

#include <SDL2/SDL.h>

#include "lightsky/utils/Log.h"

#include "lightsky/draw/Setup.h"

#include "lightsky/game/GameSystem.h"

#include "MainState.h"
#include "Display.h"
#include "HelloPrimState.h"
#include "HelloTextState.h"
#include "HelloMeshState.h"
#include "HelloPropertyState.h"

namespace math = ls::math;
namespace draw = ls::draw;



ls::utils::Pointer<Display> global::pDisplay{nullptr};



template <typename data_t = unsigned>
constexpr data_t get_test_window_width() {
    return data_t{1280};
}

template <typename data_t = unsigned>
constexpr data_t get_test_window_height() {
    return data_t{720};
}



/*-------------------------------------
 * Destructor
-------------------------------------*/
MainState::~MainState() {
    // cleaning up the render context here so all other OpenGL data can be
    // deleted during other GameState "on_stop()" methods.
    renderContext.terminate();
    
    global::pDisplay.reset();
    
    if (SDL_WasInit(0)) {
        SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
        SDL_Quit();
    }
}

/*-------------------------------------
 * Contstructor
-------------------------------------*/
MainState::MainState() {
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
MainState::MainState(MainState&& ms) :
    GameState {std::move(ms)}
{}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
MainState& MainState::operator =(MainState&& ms) {
    GameState::operator=(std::move(ms));
    return *this;
}

/*-------------------------------------
 * SDL initialization
-------------------------------------*/
bool MainState::bootstrap_subsystems() {
    if (SDL_WasInit(0) == SDL_INIT_EVERYTHING) {
        return true;
    }

    SDL_SetMainReady();

    constexpr uint32_t sdlInitFlags = 0
        | SDL_INIT_TIMER
        | SDL_INIT_AUDIO
        | SDL_INIT_VIDEO
        | SDL_INIT_EVENTS
        | SDL_INIT_JOYSTICK
        | SDL_INIT_GAMECONTROLLER
        | 0;
    
    SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "opengl");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles2");
    SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "1");

    if (SDL_Init(sdlInitFlags) < 0) {
        LS_LOG_ERR(
            "Unable to initialize SDL due to an internal library error: \"",
            SDL_GetError(), "\"\n",
            "Complain to your local programmer.\n"
        );
        return false;
    }
    
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_CRITICAL);
    
    LS_LOG_MSG("Successfully initialized SDL.\n", SDL_GetError(), '\n');

    /*
     * Setup the necessary parameters for OpenGL 3.3
     */
#ifdef LS_DRAW_BACKEND_GL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
        
#ifdef LS_DEBUG
        | SDL_GL_CONTEXT_DEBUG_FLAG
#endif
    );
    SDL_ClearError();

    return true;
}

/*-------------------------------------
 * Initialize secondary substates
-------------------------------------*/
bool MainState::setup_substates() {
    ls::game::GameSystem& sys = get_parent_system();
    
    if (0
    //||!sys.push_game_state(new(std::nothrow) HelloPropertyState{})
    //|| !sys.push_game_state(new(std::nothrow) HelloTextState{})
    //|| !sys.push_game_state(new(std::nothrow) HelloPrimState{})
    || !sys.push_game_state(new(std::nothrow) HelloMeshState{})
    ) {
        LS_LOG_ERR("Unable to run the internal render systems.\n");
        return false;
    }
        
    LS_LOG_MSG("Successfully created the internal rendering engine.\n");
    
    return true;
}

/*-------------------------------------
 * System Startup
-------------------------------------*/
bool MainState::on_start() {
    if (!bootstrap_subsystems()) {
        return false;
    }
    
    constexpr math::vec2i winSize{(int)get_test_window_width(), (int)get_test_window_height()};
    global::pDisplay.reset(new(std::nothrow) Display{});
    
    if (!global::pDisplay || !global::pDisplay->init(winSize)) {
        std::cerr << "Unable to create a display." << std::endl;
        return false;
    }

    if (!renderContext.init(*global::pDisplay, false)) {
        std::cerr << "Unable to create a render context." << std::endl;
        return false;
    }
    LS_LOG_GL_ERR();

    if (!ls::draw::init_eds_draw()) {
        std::cerr << "Unable to initialize ls Draw." << std::endl;
        return false;
    }
    LS_LOG_GL_ERR();
    
    if (!setup_substates()) {
        return false;
    }

    glClearColor(0.f, 0.f, 0.f, 1.f);

    return true;
}

/*-------------------------------------
 * System Runtime
-------------------------------------*/
void MainState::on_run() {
    LS_LOG_GL_ERR();

    renderContext.make_current(*global::pDisplay);
    LS_LOG_GL_ERR();

    renderContext.flip(*global::pDisplay);
    LS_LOG_GL_ERR();
    
    const char* const pSdlErr = SDL_GetError();
    if (pSdlErr && pSdlErr[0] != '\0') {
        LS_LOG_ERR("SDL_ERROR: ", pSdlErr);
        SDL_ClearError();
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    LS_LOG_GL_ERR();

    const hr_time&& currTime = hr_clock::now();
    frameTime                = currTime - prevTime;
    tickTime                 = frameTime.count();
    prevTime                 = currTime;

    ++currFrames;
    ++totalFrames;
    currSeconds += tickTime;
    totalSeconds += tickTime;

    if (currSeconds >= 0.5f)
    {
        std::cout << "FPS: " << (float)currFrames/currSeconds << std::endl;
        currFrames = 0;
        currSeconds = 0.f;
    }

    /*
    if (totalFrames >= 600)
    {
        get_parent_system().stop();
    }
    */
}

/*-------------------------------------
 * System Stop
-------------------------------------*/
void MainState::on_stop() {
}
