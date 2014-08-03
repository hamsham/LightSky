/* 
 * File:   display.h
 * Author: hammy
 *
 * Created on November 15, 2013, 8:50 PM
 */

#ifndef __LS_DISPLAY_H__
#define	__LS_DISPLAY_H__

#include "lsSetup.h"

struct SDL_Window;

/**
 * Display Class
 * This class is responsible for Opening an OpenGL 3.3-compatible device context
 * (a window within the OS). It contains the object responsible for rendering or
 * drawing in OpenGL.
 */
class lsDisplay {
    private:
        /**
         * Internal handle to the device context created by SDL.
         */
        SDL_Window* pWindow = nullptr;
        
        /**
         * Keep track of whether a native hardware handle is being used.
         */
        bool windowIsNative = false;

    public:
        /**
         * Constructor
         */
        lsDisplay();
        
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
        ~lsDisplay();
        
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
         * Create an lsDisplay object from a native OS hardware handle.
         * 
         * @param hwnd
         * A pointer to the operating systen's native window type.
         * 
         * @param isFullScreen
         * Determine if the window should be made full-screen.
         * 
         * @return bool
         * TRUE if a window could be successfully created, or
         * FALSE if otherwise.
         */
        bool init(void* const hwnd);
        
        /**
         * Initialize/Open a window within the OS.
         * 
         * @param inResolution
         * The desired window resolution, in pixels.
         * 
         * @param isFullScreen
         * Determine if the window should be made full-screen.
         * 
         * @return TRUE if the display initialized properly, FALSE is not.
         */
        bool init(const math::vec2i inResolution, bool isFullScreen = false);
        
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
         * Determine if the current display is using a native window handle.
         * 
         * @return bool
         * TRUE if this display was created using a previously existing OS
         * window handle, or FALSE if the display was created using an internal
         * method.
         */
        bool usingNativeWindow() const;
};

///////////////////////////////////////////////////////////////////////////////
// Inlined Display Methods
///////////////////////////////////////////////////////////////////////////////
/*
 * Determine if this object holds a handle to an open window.
 */
inline bool lsDisplay::isRunning() const {
    return pWindow != nullptr;
}

/*
 * Determine if the current display is using a native window handle.
 */
inline bool lsDisplay::usingNativeWindow() const {
    return windowIsNative;
}


#endif	/* __LS_DISPLAY_H__ */

