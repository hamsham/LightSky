
#include <new> // std::nothrow

#include "lightsky/lightsky.h"

#include "controlState.h"
#include "fbState.h"
#include "uiState.h"

bool initLs();
void terminateLs();

namespace global {
    ls::game::system* pSystem = nullptr;
    ls::draw::display* pDisplay = nullptr;
    //ls::draw::context* pContext = nullptr;
}

/*
 * Main
 */
int main(int argc, char** argv) {
    std::cout << "Initializing LightSky.\n";
    
    /*
     * Game Initialization
     */
    std::cout << "Parameter count: " << argc;
    for (int argCount = 0; argCount < argc; ++argCount) {
        std::cout << '\t' << argCount << ":\t" << argv[argCount] << '\n';
    }
    std::cout << std::endl;
    
    if (!initLs()) {
        terminateLs();
        return false;
    }
    
    // push some states and run the game
    if (!global::pSystem->pushGameState(new controlState{})
    ||  !global::pSystem->pushGameState(new fbState{})
    ||  !global::pSystem->pushGameState(new uiState{})
    ) {
        terminateLs();
        return -1;
    }
    
    while (global::pSystem->isRunning()) {
        global::pSystem->run();
    }
    
    terminateLs();
    
    return 0;
}

/*
 * Initialize Light Sky
 */
bool initLs() {
    if (!ls::game::global::init()) {
        std::cerr
            << "Unable to initialize LightSky."
            << std::endl;
        return false;
    }
    
    global::pDisplay = new(std::nothrow) ls::draw::display{};
    if (!global::pDisplay || !global::pDisplay->init(ls::math::vec2i{800, 600})) {
        std::cerr << "Unable to create a display object for LightSky." << std::endl;
        return false;
    }
    
    global::pSystem = new(std::nothrow) ls::game::system();
    if (!global::pSystem || !global::pSystem->init()) {
        std::cerr << "Failed to initialize the LightSky system manager.\n" << std::endl;
        return false;
    }
    
    std::cout << "LightSky Successfully initialized.\n" << std::endl;;
    return true;
}

/*
 * Terminate lightSky
 */
void terminateLs() {
    delete global::pSystem;
    global::pSystem = nullptr;
    
    delete global::pDisplay;
    global::pDisplay = nullptr;
    
    ls::game::global::terminate();
    
    std::cout << "LightSky successfully terminated.\n" << std::endl;
}