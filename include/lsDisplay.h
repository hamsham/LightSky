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

class lsDisplay {
    friend class lsRenderer;
    
    private:
        SDL_Window* pWindow = nullptr;
        lsRenderer renderContext = {};

    public:
        lsDisplay() {}
        lsDisplay(const lsDisplay&) = delete;
        lsDisplay(lsDisplay&&);
        
        ~lsDisplay() {terminate();}
        
        lsDisplay& operator=(const lsDisplay&) = delete;
        lsDisplay& operator=(lsDisplay&&);
        
        bool init(
            const math::vec2i inResolution = math::vec2i{
                LS_DEFAULT_DISPLAY_WIDTH, LS_DEFAULT_DISPLAY_HEIGHT
            },
            bool isFullScreen = false,
            bool useVsync = true
        );
        
        void terminate();
        
        const math::vec2i getResolution() const;
        
        void setResolution(const math::vec2i inResolution);
        
        void setFullscreen(bool fs);
        bool isFullscreen() const;
        
        inline bool isRunning() const {
            return pWindow != nullptr;
        }
        
        inline SDL_Window* getWindow() const {
            return pWindow;
        }
        
        inline lsRenderer& getRenderer() {
            return renderContext;
        }
        
        inline void* getGlContext() const {
            return renderContext.pContext;
        }
        
        inline void makeContextCurrent() const {
            SDL_GL_MakeCurrent(pWindow, renderContext.pContext);
        }
        
        inline void setVsync(bool vsync) {
            SDL_GL_SetSwapInterval((int)vsync);
        }
        
        inline bool getVsync() const {
            return SDL_GL_GetSwapInterval() != 0;
        }
        
        inline void flip() {
            SDL_GL_SwapWindow(pWindow);
        }
};

#endif	/* __LS_DISPLAY_H__ */

