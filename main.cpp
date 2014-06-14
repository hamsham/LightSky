
#include <SDL2/SDL.h>

#include "main.h"
#include "testState.h"

bool lsInit(int argc, char** argv);
void lsTerminate();

/*
 * Main
 */
int main(int argc, char* argv[]) {
    if (!lsInit(argc, argv)) {
        lsTerminate();
        return false;
    }
    
    if (!lsGlobal::pSystem->pushGameState(new(std::nothrow) testState())) {
        lsTerminate();
        return -1;
    }
    
    lsGlobal::pSystem->run();
    
    lsTerminate();
    
    return 0;
}