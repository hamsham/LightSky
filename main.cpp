
#include <new> // std::nothrow

#include "lightSky.h"

#include "testState.h"
#include "batchState.h"
#include "lightState.h"
#include "fbState.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <windef.h>

bool initLs();
void terminateLs();

namespace {
    lsSubsystem* pSystem = nullptr;
    lsDisplay* pDisplay = nullptr;
    GLFWwindow* pWindow = nullptr;
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
    
    while (pSystem->isRunning()) {
        pSystem->run();
    }
    
    terminateLs();
    
    return 0;
}

/*
 * Initialize Light Sky
 */
bool initLs() {
    if (!lsInit()) {
        std::cerr
            << "Unable to initialize LightSky."
            << std::endl;
        return false;
    }
    
    if (!glfwInit()) {
        std::cerr
            << "Unable to initialize GLFW for a native window handle test"
            << std::endl;
        return false;
    }
    
    pWindow = glfwCreateWindow(800, 600, "Native Window Test", nullptr, nullptr);
    if (pWindow == nullptr) {
        std::cerr << "Unable to create a native window to test with." << std::endl;
        return false;
    }
    
    pDisplay = new(std::nothrow) lsDisplay{};
    if (!pDisplay || !pDisplay->init(glfwGetWin32Window(pWindow))) {
        std::cerr << "Unable to create a display object for LightSky." << std::endl;
        return false;
    }
    
    pSystem = new(std::nothrow) lsSubsystem();
    if (!pSystem || !pSystem->init(*pDisplay, true)) {
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
    if (pSystem != nullptr) {
        pSystem->terminate();
    }
    delete pSystem;
    pSystem = nullptr;
    
    delete pDisplay;
    pDisplay = nullptr;
    
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    pWindow = nullptr;
    
    lsTerminate();
    
    std::cout << "LightSky successfully terminated.\n" << std::endl;
}