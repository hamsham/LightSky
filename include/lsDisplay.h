/* 
 * File:   display.h
 * Author: hammy
 *
 * Created on November 15, 2013, 8:50 PM
 */

#ifndef __LS_DISPLAY_H__
#define	__LS_DISPLAY_H__

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

#include "lsSetup.h"
#include "lsRenderer.h"

struct SDL_Window;

/**
 * Display Class
 * This class is responsible for Opening an OpenGL 3.3-compatible device context
 * (a window within the OS). It contains the object responsible for rendering or
 * drawing in OpenGL.
 */
class lsDisplay {
    friend class lsRenderer;
    
    private:
        /**
         * Internal handle to the device context created by SDL.
         */
        SDL_Window* pWindow = nullptr;
        
        /**
         * Internal OpenGL 3.3 renderer.
         */
        lsRenderer renderContext = {};

    public:
        /**
         * Constructor
         */
        lsDisplay() {}
        
        /**
         * Copy Constructor - DELETED
         */
        lsDisplay(const lsDisplay&) = delete;
        
        /**
         * Move operator
         * Moves all members from the input parameter into *this. No copies are
         * performed. Any existing window handles will be invalidated.
         * 
         * @param lsDisplay&&
         */
        lsDisplay(lsDisplay&&);
        
        /**
         * Destructor.
         * 
         * Closes the window and frees all resources used by *this.
         */
        ~lsDisplay() {terminate();}
        
        /**
         * Copy Operator - DELETED
         */
        lsDisplay& operator=(const lsDisplay&) = delete;
        
        /**
         * Move operator
         * Moves all members from the input parameter into *this. No copies are
         * performed. Any existing window handles will be invalidated.
         * 
         * @param lsDisplay&&
         */
        lsDisplay& operator=(lsDisplay&&);
        
        /**
         * Initialize/Open a window within the OS.
         * 
         * @param inResolution
         * The desired window resolution, in pixels.
         * 
         * @param isFullScreen
         * Determine if the window should be made full-screen.
         * 
         * @param useVsync
         * Determine if the display should have VSync enabled.
         * 
         * @return TRUE if the display initialized properly, FALSE is not.
         */
        bool init(
            const math::vec2i inResolution = math::vec2i{
                LS_DEFAULT_DISPLAY_WIDTH, LS_DEFAULT_DISPLAY_HEIGHT
            },
            bool isFullScreen = false,
            bool useVsync = true
        );
        
        /**
         * Close the window and free all memory/resources used by *this.
         */
        void terminate();
        
        /**
         * Get the resolution, in pixels, of the display referenced by *this.
         * 
         * @return math::vec2i
         */
        const math::vec2i getResolution() const;
        
        /**
         * Set the resolution, in pixels, that this display should be.
         * 
         * @param math::vec2i
         */
        void setResolution(const math::vec2i inResolution);
        
        /**
         * Set whether or not this display should be made fullscreen.
         * 
         * @param bool
         * TRUE to enable a fullscreen window, FALSE to reduce the display down
         * to a simple window.
         */
        void setFullscreen(bool fs);
        
        /**
         * Determine if the current display is in fullscreen mode.
         * 
         * @return TRUE if the display is in fullscreen mode, FALSE if not.
         */
        bool isFullscreen() const;
        
        /**
         * Determine if this object holds a handle to an open window.
         * 
         * @return TRUE if a window is open, FALSE if not.
         */
        bool isRunning() const;
        
        /**
         * Get a handle to the SDL_Window responsible for the window that this
         * object references.
         * 
         * @return SDL_Window.
         */
        SDL_Window* getWindow() const;
        
        /**
         * Get a reference to the object responsible for managing the OpenGL
         * render context.
         * 
         * @return lsRenderer&
         */
        lsRenderer& getRenderer();
        
        /**
         * Get a pointer to the SDL_GLContext that is used by the active
         * renderer.
         * 
         * @return A void pointer that can be safely casted to a SDL_GLContext.
         */
        void* getGlContext() const;
        
        /**
         * Activate the render context used in this window.
         */
        void makeContextCurrent() const;
        
        /**
         * Enable/Disable VSync
         * 
         * @param TRUE if vsync is desired, FALSE to disable it.
         */
        void setVsync(bool vsync);
        
        /**
         * Determine if VSync is enabled or disabled within the current window.
         * 
         * @return TRUE if VSync is enabled, FALSE if not.
         */
        bool getVsync() const;
        
        /**
         * Swap the current display's front and back buffers.
         */
        void flip();
};

///////////////////////////////////////////////////////////////////////////////
// Inlined Display Method
///////////////////////////////////////////////////////////////////////////////
/*
 * Determine if this object holds a handle to an open window.
 */
inline bool lsDisplay::isRunning() const {
    return pWindow != nullptr;
}

/*
 * Get a handle to the SDL_Window responsible for the window that this
 * object references.
 */
inline SDL_Window* lsDisplay::getWindow() const {
    return pWindow;
}

/*
 * Get a reference to the object responsible for managing the OpenGL
 * render context.
 */
inline lsRenderer& lsDisplay::getRenderer() {
    return renderContext;
}

/*
 * Get a pointer to the SDL_GLContext that is used by the active
 * renderer.
 */
inline void* lsDisplay::getGlContext() const {
    return renderContext.pContext;
}

/*
 * Activate the render context used in this window.
 */
inline void lsDisplay::makeContextCurrent() const {
    SDL_GL_MakeCurrent(pWindow, renderContext.pContext);
}

/*
 * Enable/Disable VSync
 */
inline void lsDisplay::setVsync(bool vsync) {
    SDL_GL_SetSwapInterval((int)vsync);
}

/*
 * Determine if VSync is enabled or disabled within the current window.
 */
inline bool lsDisplay::getVsync() const {
    return SDL_GL_GetSwapInterval() != 0;
}

/*
 * Swap the current display's front and back buffers.
 */
inline void lsDisplay::flip() {
    SDL_GL_SwapWindow(pWindow);
}

#endif	/* __LS_DISPLAY_H__ */

