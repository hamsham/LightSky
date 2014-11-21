/* 
 * File:   draw/framebuffer.cpp
 * Author: Miles Lacey
 * 
 * Created on Jult 30, 2014, 10:02 PM
 */

#include "lightsky/draw/setup.h"
#include "lightsky/draw/framebuffer.h"

namespace ls {
namespace draw {

/*-------------------------------------
    FBO Error handling
-------------------------------------*/
void framebuffer::printStatus(const framebuffer& fbo) {
    LOG_GL_ERR();
    
    const fbo_status_t err = getStatus(fbo);
    
    switch (err) {
        case FBO_COMPLETE:
            LS_LOG_MSG("Framebuffer ", fbo.getId(), " completed.");
            break;
        case FBO_UNDEFINED:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " undefined.");
            break;
        case FBO_INCOMPLETE_ATTACHMENT:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " contains an incomplete attachment.");
            break;
        case FBO_INCOMPLETE_MISSING_ATTACHMENT:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " is missing attachments.");
            break;
        case FBO_INCOMPLETE_DRAW_BUFFER:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " contains an incomplete draw buffer.");
            break;
        case FBO_INCOMPLETE_READ_BUFFER:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " contains an incomplete read buffer.");
            break;
        case FBO_UNSUPPORTED:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " uses unsupported formats.");
            break;
        case FBO_INCOMPLETE_MULTISAMPLE:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " uses alternating samples.");
            break;
        case FBO_INCOMPLETE_LAYER_TARGETS:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " has incomplete layer targets.");
            break;
    }
}

/*-------------------------------------
    Move constructor
-------------------------------------*/
framebuffer::framebuffer(framebuffer&& fb) :
    access{fb.access},
    fboId{fb.fboId}
{
    fb.access = FBO_ACCESS_RW;
    fb.fboId = 0;
}

/*-------------------------------------
    Destructor
-------------------------------------*/
framebuffer::~framebuffer() {
    terminate();
}

/*-------------------------------------
    constructor
-------------------------------------*/
framebuffer::framebuffer() {
}

/*-------------------------------------
    Move operator
-------------------------------------*/
framebuffer& framebuffer::operator=(framebuffer&& fb) {
    access = fb.access;
    fb.access = FBO_ACCESS_RW;
    
    fboId = fb.fboId;
    fb.fboId = 0;
    
    return *this;
}

/*-------------------------------------
    Initialization
-------------------------------------*/
bool framebuffer::init() {
    terminate();
    glGenFramebuffers(1, &fboId);
    return fboId != 0;
}

/*-------------------------------------
    Termination
-------------------------------------*/
void framebuffer::terminate() {
    access = FBO_ACCESS_RW;
    glDeleteFramebuffers(1, &fboId);
    fboId = 0;
}

/*-------------------------------------
    Attach a texture to the currently bound framebuffer
-------------------------------------*/
void framebuffer::attachTexture(
    fbo_attach_t attachment,
    texture_target_t target,
    const texture& tex,
    int mipmapLevel,
    int layer
) {
    const tex_desc_t desc = tex.getTextType();
    const unsigned texId = tex.getId();
    
    if (desc == TEX_DESC_1D) {
        glFramebufferTexture1D(access, attachment, target, texId, mipmapLevel);
    }
    else if (desc == TEX_DESC_2D || desc == TEX_DESC_RECT) {
        glFramebufferTexture2D(access, attachment, target, texId, mipmapLevel);
    }
    else if (desc == TEX_DESC_3D) {
        glFramebufferTexture3D(access, attachment, target, texId, mipmapLevel, layer);
    }
    else {
        LS_LOG_ERR("Attempting to load an unsupported texture type into a framebuffer.");
    }
}

} // end draw namespace
} // end ls namespace
