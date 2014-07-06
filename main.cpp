
#include <new> // std::nothrow
#include <SDL2/SDL.h>

#include "lightSky.h"

#include "testState.h"
#include "batchState.h"
#include "lightState.h"

bool initLs();
void terminateLs();

namespace {
    static lsSubsystem* pSystem;
}

/*
 * Main
 */
int main(int argc, char* argv[]) {
    LS_LOG_MSG("Initializing LightSky.");
    
    /*
     * Game Initialization
     */
    LS_LOG_MSG("Parameter count: ", argc);
    for (int argCount = 0; argCount < argc; ++argCount) {
        LS_LOG_MSG('\t', argCount, ":\t", argv[argCount], '\n');
    }
    
    if (!initLs()) {
        terminateLs();
        return false;
    }
    
    if (
        //!pSystem->pushGameState(new(std::nothrow) lightState())
        !pSystem->pushGameState(new(std::nothrow) batchState())
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
        LS_LOG_ERR("\tFailed to initialize the LightSky system manager.\n.");
        return false;
    }
    
    LS_LOG_MSG("LightSky Successfully initialized.\n");
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
    
    LS_LOG_MSG("LightSky successfully terminated.\n");
    
    return;
}