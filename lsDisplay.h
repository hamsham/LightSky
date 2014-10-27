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
#include "main.h"
#include "renderer.h"

struct SDL_Window;

class display {
    private:
        SDL_Window* pWindow = nullptr;
        void* pContext = nullptr;
        renderer renderContext;

    public:
        constexpr display() {}
        display(const display&) = delete;
        display(display&&) = delete;
        
        ~display() { terminate(); }
        
        display operator=(const display&) = delete;
        display operator=(display&&) = delete;
        
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
        
        inline void* getGlContext() const {
            return pContext;
        }
        
        inline renderer& getRenderer() {
            return renderContext;
        }
        
        inline void makeContextCurrent() const {
                SDL_GL_MakeCurrent(pWindow, pContext);
        }
        
        inline void flip() {
                SDL_GL_SwapWindow(pWindow);
        }
};

#endif	/* __LS_DISPLAY_H__ */

