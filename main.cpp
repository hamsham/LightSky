
#include <new> // std::nothrow
#include <SDL2/SDL.h>

#include "lightSky.h"

#include "testState.h"
#include "batchState.h"
#include "lightState.h"
#include "fbState.h"

bool initLs();
void terminateLs();

namespace {
    static lsSubsystem* pSystem;
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
    
    if (
        !pSystem->pushGameState(new(std::nothrow) fbState())
        //!pSystem->pushGameState(new(std::nothrow) lightState())
        //!pSystem->pushGameState(new(std::nothrow) batchState())
        //!pSystem->pushGameState(new(std::nothrow) testState())
    ) {
        terminateLs();
        return -1;
    }
    
    pSystem->run();
    
    terminateLs();
    
    return 0;
}

/*
 * Initialize Light Sky
 */
bool initLs() {
    
    pSystem = new(std::nothrow) lsSubsystem();
    if (!pSystem || !pSystem->init()) {
        std::cerr << "Failed to initialize the LightSky system manager.\n." << std::endl;
        return false;
    }
    
    std::cout << "LightSky Successfully initialized.\n" << std::endl;;
    return true;
}

/*
 * Terminate lightSky
 */
void terminateLs() {
    if (pSystem != nullptr) {
        pSystem->terminate();
    }
    delete pSystem;
    pSystem = nullptr;
    
    std::cout << "LightSky successfully terminated.\n" << std::endl;;
    
    return;
}