/* 
 * File:   lsContext.h
 * Author: miles
 *
 * Created on August 2, 2014, 8:44 PM
 */

#ifndef __LS_CONTEXT_H__
#define	__LS_CONTEXT_H__

#include "lsDisplay.h"

class lsContext final {
    private:
        void* pContext = nullptr;
    
    public:
        /**
         * Constructor
         */
        lsContext();
        
        /**
         * Copy Constructor -- DELETED
         */
        lsContext(const lsContext&) = delete;
        
        /**
         * Move Constructor.
         * Moves all render context data from the input parameter into *this. No
         * copies are performed.
         * 
         * @param lsContext&&
         * An R-Value reference to an lsContext.
         */
        lsContext(lsContext&&);
        
        /**
         * Destructor.
         * Frees all hardware handles and memory resources used by *this. This
         * effectively does the same thing as "terminate()."
         * Make sure the display object that this was created with has not yet
         * been destroyed.
         */
        ~lsContext();
        
        /**
         * Copy Operator -- DELETED
         */
        lsContext& operator=(const lsContext&) = delete;
        
        /**
         * Move Operator.
         * Moves all render context data from the input parameter into *this. No
         * copies are performed.
         * 
         * @param lsContext&&
         * An R-Value reference to an lsContext.
         */
        lsContext& operator=(lsContext&&);
        
        /**
         * Initializer method for *this.
         * 
         * @param lsDisplay&
         * A reference to a constant lsDisplay object. This display object must
         * have already been initialized and created with OpenGL 3.3 core
         * attributes.
         * 
         * @return bool
         * TRUE if a context was able to be created from the input display
         * object, FALSE if not.
         */
        bool init(const lsDisplay&, bool useVsync = true);
        
        /**
         * Destructor.
         * Frees all hardware handles and memory resources used by *this.
         * Make sure the display object that this was created with has not yet
         * been destroyed.
         */
        void terminate();
        
        /**
         * Bind this render context to the active display
         */
        void makeCurrent(const lsDisplay&) const;
        
        /**
         * Get a pointer to the SDL_GLContext that is used by the active
         * display.
         * This context must have been made current in order to be used.
         * 
         * @return A void pointer that can be safely casted to a SDL_GLContext.
         */
        void* getContext() const;
        
        /**
         * Enable/Disable VSync
         * This context must have been made current in order to be used.
         * 
         * @param TRUE if vsync is desired, FALSE to disable it.
         */
        void setVsync(bool vsync);
        
        /**
         * Determine if VSync is enabled or disabled within the current window.
         * This context must have been made current in order to be used.
         * 
         * @return TRUE if VSync is enabled, FALSE if not.
         */
        bool getVsync() const;
        
        /**
         * Swap the current display's front and back buffers.
         * 
         * This context must have been made current in order to be used.
         */
        void flip(const lsDisplay& display) const;
};

///////////////////////////////////////////////////////////////////////////////
//      Inline methods
///////////////////////////////////////////////////////////////////////////////
/*
 * Activate the render context used in this window.
 */
inline void lsContext::makeCurrent(const lsDisplay& display) const {
    SDL_GL_MakeCurrent(display.getWindow(), pContext);
}

/*
 * Get a pointer to the SDL_GLContext that is used by the active
 * renderer.
 */
inline void* lsContext::getContext() const {
    return pContext;
}

#endif	/* __LS_CONTEXT_H__ */

