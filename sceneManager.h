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
#include "mesh.h"
#include "text.h"
#include "texture.h"
#include "textureAtlas.h"

#define INVALID_SCENE_ID ((unsigned)-1)

/*
 * Manager typedefs
 */
LS_DECLARE_CLASS_TYPE(meshManager, manager, unsigned, mesh);
LS_DECLARE_CLASS_TYPE(textureManager, manager, unsigned, texture);
LS_DECLARE_CLASS_TYPE(atlasManager, manager, unsigned, textureAtlas);
LS_DECLARE_CLASS_TYPE(textManager, manager, unsigned, text);

/**
 * Scene manager class
 * 
 * Contains all visual elements to a scene such as meshes, textures, texture
 * atlases, shaders, etc.
 */
class sceneManager {
    private:
        texture defaultTex;
    
        textureManager texMgr;
        meshManager meshMgr;
        atlasManager atlasMgr;
        textManager stringMgr;
        
        bool initDefaultTexture();
        
    public:
        sceneManager();
        sceneManager(const sceneManager&) = delete;
        sceneManager(sceneManager&&);
        
        ~sceneManager() {
            terminate();
        }
        
        sceneManager& operator=(const sceneManager&) = delete;
        sceneManager& operator=(sceneManager&&);
        
        bool init();
        void terminate();
        
        void clear();
        
        meshManager::map_t& getMeshManager();
        textureManager::map_t& getTextureManager();
        atlasManager::map_t& getAtlasManager();
        textManager::map_t& getTextManager();
        
        const meshManager::map_t& getMeshManager() const;
        const textureManager::map_t& getTextureManager() const;
        const atlasManager::map_t& getAtlasManager() const;
        const textManager::map_t& getTextManager() const;
        
        mesh* getMesh(unsigned id) const;
        texture* getTexture(unsigned id) const;
        textureAtlas* getAtlas(unsigned id) const;
        text* getText(unsigned id) const;
        
        void eraseMesh(unsigned id);
        void eraseTexture(unsigned id);
        void eraseAtlas(unsigned id);
        void eraseText(unsigned id);
        
        unsigned getNumMeshes() const;
        unsigned getNumTextures() const;
        unsigned getNumAtlases() const;
        unsigned getNumTexts() const;
        
        unsigned manageMesh(mesh* const);
        unsigned manageTexture(texture* const);
        unsigned manageAtlas(textureAtlas* const);
        unsigned manageText(text* const);
        
        mesh* unManageMesh(unsigned id);
        texture* unManageTexture(unsigned id);
        textureAtlas* unManageAtlas(unsigned id);
        text* unManageText(unsigned id);
        
        bool containsMesh(const mesh* const) const;
        bool containsTexture(const texture* const) const;
        bool containsAtlas(const textureAtlas* const) const;
        bool containsText(const text* const) const;
};

#endif	/* __LS_SCENE_MANAGER_H__ */

