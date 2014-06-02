/* 
 * File:   sceneManager.h
 * Author: miles
 *
 * Created on May 26, 2014, 11:22 AM
 */

#ifndef __LS_SCENE_MANAGER_H__
#define	__LS_SCENE_MANAGER_H__

#include "main.h"
#include "manager.h"

/*
 * Manager typedefs
 */
LS_DECLARE_CLASS_TYPE(meshManager, manager, unsigned, mesh);
LS_DECLARE_CLASS_TYPE(textureManager, manager, unsigned, texture);
LS_DECLARE_CLASS_TYPE(atlasManager, manager, unsigned, textureAtlas);

/**
 * Scene manager class
 * 
 * Contains all visual elements to a scene such as meshes, textures, texture
 * atlases, shaders, etc.
 */
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
        
        void clear();
};

#endif	/* __LS_SCENE_MANAGER_H__ */

