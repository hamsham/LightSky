/* 
 * File:   framebuffer.h
 * Author: miles
 *
 * Created on June 28, 2014, 10:02 AM
 */

#ifndef FRAMEBUFFER_H
#define	FRAMEBUFFER_H

#include <GL/glew.h>

#include "lsSetup.h"
#include "lsTexture.h"

///////////////////////////////////////////////////////////////////////////////
//      Enumerations used by LightSky Framebuffer Objects.
///////////////////////////////////////////////////////////////////////////////
/**
 * Draw buffers for fbo render targets
 */
enum ls_draw_buffer_t : int {
    LS_COLOR_ATTACHMENT0    = GL_COLOR_ATTACHMENT0,
    LS_COLOR_ATTACHMENT1    = GL_COLOR_ATTACHMENT1,
    LS_COLOR_ATTACHMENT2    = GL_COLOR_ATTACHMENT2,
    LS_COLOR_ATTACHMENT3    = GL_COLOR_ATTACHMENT3,
    LS_COLOR_ATTACHMENT4    = GL_COLOR_ATTACHMENT4,
    LS_COLOR_ATTACHMENT5    = GL_COLOR_ATTACHMENT5,
    LS_COLOR_ATTACHMENT6    = GL_COLOR_ATTACHMENT6,
    LS_COLOR_ATTACHMENT7    = GL_COLOR_ATTACHMENT7,
    LS_COLOR_ATTACHMENT8    = GL_COLOR_ATTACHMENT8,
    LS_COLOR_ATTACHMENT9    = GL_COLOR_ATTACHMENT9,
    LS_COLOR_ATTACHMENT10   = GL_COLOR_ATTACHMENT10,
    LS_COLOR_ATTACHMENT11   = GL_COLOR_ATTACHMENT11,
    LS_COLOR_ATTACHMENT12   = GL_COLOR_ATTACHMENT12,
    LS_COLOR_ATTACHMENT13   = GL_COLOR_ATTACHMENT13,
    LS_COLOR_ATTACHMENT14   = GL_COLOR_ATTACHMENT14,
    LS_COLOR_ATTACHMENT15   = GL_COLOR_ATTACHMENT15,
    
    LS_DEPTH_ATTACHMENT     = GL_DEPTH_ATTACHMENT,
    LS_STENCIL_ATTACHMENT   = GL_STENCIL_ATTACHMENT
};

/**
 * Draw/Read access control for framebuffer objects.
 */
enum ls_fbo_access_t : unsigned {
    LS_DRAW_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER,
    LS_READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER
};

/**
 * Framebuffer status codes
 */
enum ls_fbo_status_t : int {
    LS_FBO_COMPLETE                         = GL_FRAMEBUFFER_COMPLETE,
    LS_FBO_UNDEFINED                        = GL_FRAMEBUFFER_UNDEFINED,
    LS_FBO_INCOMPLETE_ATTACHMENT            = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
    LS_FBO_INCOMPLETE_MISSING_ATTACHMENT    = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
    LS_FBO_INCOMPLETE_DRAW_BUFFER           = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
    LS_FBO_INCOMPLETE_READ_BUFFER           = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
    LS_FBO_UNSUPPORTED                      = GL_FRAMEBUFFER_UNSUPPORTED,
    LS_FBO_INCOMPLETE_MULTISAMPLE           = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
    LS_FBO_INCOMPLETE_LAYER_TARGETS         = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
};

enum ls_fbo_mask_t : int {
    LS_DEPTH_MASK       = GL_DEPTH_BUFFER_BIT,
    LS_STENCIL_MASK     = GL_STENCIL_BUFFER_BIT,
    LS_COLOR_MASK       = GL_COLOR_BUFFER_BIT,
};

enum ls_fbo_filter_t : int {
    LS_FBO_LINEAR       = GL_LINEAR,
    LS_FBO_NEAREST      = GL_NEAREST
};

///////////////////////////////////////////////////////////////////////////////
//      Framebuffer Class
///////////////////////////////////////////////////////////////////////////////
/**
 * Framebuffer Objects
 */
class lsFramebuffer final {
    public:
        /**
         * Get the maximum number of supported color attachments from the
         * current render context.
         * OpenGL requires at least 8 attachments are supported.
         * 
         * @return A signed integral type representing the number of currently
         * supported render targets.
         */
        static int getMaxNumAttachments();

        /**
         * Error code handling for framebuffer creation.
         * 
         * The input FBO must be bound/active in order to report properly.
         * 
         * @param lsFramebuffer
         */
        static void printStatus(const lsFramebuffer& fbo);
        
        /**
         * Get the completion status of a framebuffer based on the currently
         * used ls_fbo_access_t.
         * 
         * An FBO must be bound/active in order to report properly.
         * 
         * @return lsFramebuffer
         */
        static ls_fbo_status_t getStatus(const lsFramebuffer& fbo);
        
    private:
        ls_fbo_access_t access = LS_DRAW_FRAMEBUFFER;
        unsigned fboId = 0;
        
    public:
        lsFramebuffer() {}
        lsFramebuffer(const lsFramebuffer&) = delete;
        lsFramebuffer(lsFramebuffer&&);
        
        ~lsFramebuffer() {terminate();}
        
        lsFramebuffer& operator=(const lsFramebuffer&) = delete;
        lsFramebuffer& operator=(lsFramebuffer&&);
        
        /**
         * Get the GPU-Assigned ID that this object references.
         * 
         * @return A non-zero unsigned integer that is used as a handle to the
         * framebuffer object represented by this object.
         * This value returns 0 if nothing is referenced by *this.
         */
        inline unsigned getId() const {
            return fboId;
        }
        
        ls_fbo_access_t getAccessType() const {
            return access;
        }
        
        void setAccessType(ls_fbo_access_t a) {
            access = a;
        }
        
        /**
         * Bind the current framebuffer to OpenGL
         */
        inline void bind() const;
        
        /**
         * Unbind the current framebuffer to OpenGL
         */
        inline void unbind() const;
        
        /**
         * Initialize an empty framebuffer.
         * 
         * @return TRUE if a new framebuffer object was successfully generated
         * on the GPU, FALSE if otherwise.
         */
        bool init();
        
        /**
         * Release all resources used by this framebuffer object.
         */
        void terminate();
        
        /**
         * Blit (draw) this frame buffer onto another.
         * This buffer must be accessed as LS_READ_BUFFER in order to work
         * properly.
         * 
         * @param srcOrig
         * @param srcSize
         * @param dstOrig
         * @param dstSize
         * @param ls_fbo_mask_t
         * @param ls_fbo_filter_t
         */
        void blit(
            const math::vec2i& srcOrig, const math::vec2i& srcSize,
            const math::vec2i& dstOrig, const math::vec2i& dstSize,
            ls_fbo_mask_t, ls_fbo_filter_t = LS_FBO_LINEAR
        ) const;
        
        /**
         * Clear the color attachment indicated by the input parameter.
         * 
         * @param A bitmask of type ls_fbo_mask_t.
         */
        void clear(ls_fbo_mask_t) const;
        
        /**
         * Set the current draw targets to be used by this.
         * 
         * @param numTargets
         * The number of draw targets contained within the array specified by
         * "targets."
         * 
         * @param targets
         * The set of all render targets that should be rendered to by this.
         */
        void setDrawTargets(unsigned numTargets, const ls_draw_buffer_t* targets);
};

///////////////////////////////////////////////////////////////////////////////
//      Implementations
///////////////////////////////////////////////////////////////////////////////
/*
 * Get the maximum number of supported color attachments.
 */
inline int lsFramebuffer::getMaxNumAttachments() {
    int numAttachments;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &numAttachments);
    return numAttachments;
}

/*
 * Get the status of the current framebuffer.
 */
inline ls_fbo_status_t lsFramebuffer::getStatus(const lsFramebuffer& fbo) {
    LOG_GL_ERR();
    return (ls_fbo_status_t)glCheckFramebufferStatus(fbo.getAccessType());
}

/*
 * Bind the current framebuffer to OpenGL
 */
inline void lsFramebuffer::bind() const {
    glBindFramebuffer(access, fboId);
}

/*
 * Unbind the current framebuffer to OpenGL
 */
inline void lsFramebuffer::unbind() const {
    glBindFramebuffer(access, 0);
}

/*
 * Blit this framebuffer to the current draw buffer.
 */
inline void lsFramebuffer::blit(
    const math::vec2i& srcOrig, const math::vec2i& srcSize,
    const math::vec2i& dstOrig, const math::vec2i& dstSize,
    ls_fbo_mask_t mask, ls_fbo_filter_t filter
) const {
    glBlitFramebuffer(
        srcOrig[0], srcOrig[1], srcSize[0], srcSize[1],
        dstOrig[0], dstOrig[1], dstSize[0], dstSize[1],
        (GLbitfield)mask, (GLenum)filter
    );
}

/*
 * Clear the color attachment indicated by the input parameter.
 */
inline void lsFramebuffer::clear(ls_fbo_mask_t mask) const {
    glClear((int)mask);
}

/*
 * Set the current draw targets to be used by this.
 */
inline void lsFramebuffer::setDrawTargets(unsigned numTargets, const ls_draw_buffer_t* targets) {
    glDrawBuffers(numTargets, (const GLenum*)targets);
}

#endif	/* FRAMEBUFFER_H */

