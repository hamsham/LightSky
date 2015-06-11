
#include "lightsky/draw/draw.h"

namespace ls {
namespace draw {

/*-------------------------------------
 * Initialize LightDraw
-------------------------------------*/
bool init() {
    glewExperimental = GL_TRUE;
    const GLenum errCode = glewInit();
    
    if (errCode != GLEW_OK) {
        LS_LOG_ERR("Unable to initialize the LightSky Drawing system.");
        LS_LOG_ERR("\tError Message: ", glewGetErrorString(errCode));
        return false;
    }
    
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
