
#include <new> // std::nothrow
#include <iostream>

#include "ControlState.h"
#include "MainState.h"

namespace math = ls::math;



/*-------------------------------------
 * main()
-------------------------------------*/
int main(int argc, char* argv[]) {
    ls::game::GameSystem sys {};

    for (int i = 0; i < argc; ++i) {
        std::cout << "Argument " << i << ": " << argv[i] << '\n';
    }

    if (!sys.start()
    || !sys.push_game_state(new(std::nothrow) MainState{})
    || !sys.push_game_state(new(std::nothrow) ControlState{})
    ) {
        std::cerr << "Unable to create the main program.\n" << std::endl;
        sys.stop();
    }
    else {
        std::cout << "Successfully created the internal rendering engine.\n" << std::endl;
    }

    while (sys.is_runnable()) {
        sys.run();
    }

    sys.stop();
    std::cout << "ls Renderer successfully terminated.\n" << std::endl;

    return 0;
}
