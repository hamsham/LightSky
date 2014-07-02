/* 
 * File:   framebuffer.cpp
 * Author: miles
 * 
 * Created on June 28, 2014, 10:02 AM
 */

#include "lsSetup.h"

#include "framebuffer.h"

///////////////////////////////////////////////////////////////////////////////
// FBO Error handling
///////////////////////////////////////////////////////////////////////////////
void lsFramebuffer::printStatus(const lsFramebuffer& fbo) {
    LOG_GL_ERR();
    
    const ls_fbo_status_t err = getStatus(fbo);
    
    switch (err) {
        case LS_FBO_COMPLETE:
            LS_LOG_MSG("Framebuffer ", fbo.getId(), " completed.");
            break;
        case LS_FBO_UNDEFINED:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " undefined.");
            break;
        case LS_FBO_INCOMPLETE_ATTACHMENT:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " contains an incomplete attachment.");
            break;
        case LS_FBO_INCOMPLETE_MISSING_ATTACHMENT:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " is missing attachments.");
            break;
        case LS_FBO_INCOMPLETE_DRAW_BUFFER:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " contains an incomplete draw buffer.");
            break;
        case LS_FBO_INCOMPLETE_READ_BUFFER:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " contains an incomplete read buffer.");
            break;
        case LS_FBO_UNSUPPORTED:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " uses unsupported formats.");
            break;
        case LS_FBO_INCOMPLETE_MULTISAMPLE:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " uses alternating samples.");
            break;
        case LS_FBO_INCOMPLETE_LAYER_TARGETS:
            LS_LOG_ERR("Framebuffer ", fbo.getId(), " has incomplete layer targets.");
            break;
    }
}

/*
 * Move constructor
 */
lsFramebuffer::lsFramebuffer(lsFramebuffer&& fb) :
    access{fb.access},
    fboId{fb.fboId}
{
    fb.access = LS_DRAW_FRAMEBUFFER;
    fb.fboId = 0;
}

/*
 * Move operator
 */
lsFramebuffer& lsFramebuffer::operator=(lsFramebuffer&& fb) {
    access = fb.access;
    fb.access = LS_DRAW_FRAMEBUFFER;
    
    fboId = fb.fboId;
    fb.fboId = 0;
    
    return *this;
}

/*
 * Initialization
 */
bool lsFramebuffer::init() {
    terminate();
    glGenFramebuffers(1, &fboId);
    return fboId != 0;
}

/*
 * Termination
 */
void lsFramebuffer::terminate() {
    access = LS_DRAW_FRAMEBUFFER;
    glDeleteFramebuffers(1, &fboId);
    fboId = 0;
}
