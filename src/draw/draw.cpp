
#include "lightsky/draw/draw.h"

namespace ls {
namespace draw {

/*-------------------------------------
 * Initialize LightDraw
-------------------------------------*/
bool init() {
    #ifdef __LS_GL_LOADER_H__
        if (lsgl_init() <= 0) {
            LS_LOG_ERR("Unable to initialize the LightSky Drawing system.");
            return false;
        }
    #endif
    
    LS_LOG_MSG("Successfully initialized the LightSky Drawing system.");
    
    return true;
}

/*-------------------------------------
 * Terminate LightDraw
-------------------------------------*/
void terminate() {
    // wheee!
}

} // end draw namespace
} // end ls namespace
