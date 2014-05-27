/* 
 * File:   sceneManager.h
 * Author: miles
 *
 * Created on May 26, 2014, 11:22 AM
 */

#ifndef __LS_SCENE_MANAGER_H__
#define	__LS_SCENE_MANAGER_H__

#include "meshManager.h"
#include "textureManager.h"

class sceneManager {
    private:
        textureManager texMgr;
        meshManager meshMgr;
        
    public:
        sceneManager();
        sceneManager(const sceneManager&) = delete;
        sceneManager(sceneManager&&);
        
        ~sceneManager();
        
        sceneManager& operator=(const sceneManager&) = delete;
        sceneManager& operator=(sceneManager&&);
};

#endif	/* __LS_SCENE_MANAGER_H__ */

