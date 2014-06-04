/* 
 * File:   sceneManager.h
 * Author: miles
 *
 * Created on May 26, 2014, 11:22 AM
 */

#ifndef __LS_SCENE_MANAGER_H__
#define	__LS_SCENE_MANAGER_H__

#include <deque>

#include "main.h"
#include "mesh.h"
#include "text.h"
#include "texture.h"
#include "atlas.h"

/*
 * Macros for types needed by the scene manager.
 */
#define INVALID_SCENE_ID ((unsigned)-1)

/*
 * Typedefs for the type of lists/arrays that can be returned by the scene
 * manager.
 */
typedef std::deque<mesh*>      meshList;
typedef std::deque<text*>      textList;
typedef std::deque<texture*>   textureList;
typedef std::deque<atlas*>     atlasList;

/**
 * Scene manager class
 * 
 * Contains all visual elements to a scene such as meshes, textures, texture
 * atlases, shaders, etc.
 */
class sceneManager {
    private:
        texture defaultTex;
    
        textureList texMgr;
        meshList meshMgr;
        atlasList atlasMgr;
        textList stringMgr;
        
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
        
        meshList& getMeshList();
        textureList& getTextureList();
        atlasList& getAtlasList();
        textList& getTextManager();
        
        const meshList& getMeshList() const;
        const textureList& getTextureList() const;
        const atlasList& getAtlasList() const;
        const textList& getTextManager() const;
        
        mesh* getMesh(unsigned index) const;
        texture* getTexture(unsigned index) const;
        atlas* getAtlas(unsigned index) const;
        text* getText(unsigned index) const;
        
        void eraseMesh(unsigned index);
        void eraseTexture(unsigned index);
        void eraseAtlas(unsigned index);
        void eraseText(unsigned index);
        
        unsigned getNumMeshes() const;
        unsigned getNumTextures() const;
        unsigned getNumAtlases() const;
        unsigned getNumTexts() const;
        
        unsigned manageMesh(mesh* const);
        unsigned manageTexture(texture* const);
        unsigned manageAtlas(atlas* const);
        unsigned manageText(text* const);
        
        mesh* unManageMesh(unsigned index);
        texture* unManageTexture(unsigned index);
        atlas* unManageAtlas(unsigned index);
        text* unManageText(unsigned index);
        
        bool containsMesh(const mesh* const) const;
        bool containsTexture(const texture* const) const;
        bool containsAtlas(const atlas* const) const;
        bool containsText(const text* const) const;
};

#endif	/* __LS_SCENE_MANAGER_H__ */

