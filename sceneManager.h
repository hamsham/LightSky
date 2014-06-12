/* 
 * File:   sceneManager.h
 * Author: miles
 *
 * Created on May 26, 2014, 11:22 AM
 */

#ifndef __LS_SCENE_MANAGER_H__
#define	__LS_SCENE_MANAGER_H__

#include <deque>

#include "drawModel.h"
#include "main.h"
#include "mesh.h"
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
typedef std::deque<drawModel*> drawList;
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
        drawList drawMgr;
        
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
        drawList& getModelManager();
        
        const meshList& getMeshList() const;
        const textureList& getTextureList() const;
        const atlasList& getAtlasList() const;
        const drawList& getModelManager() const;
        
        mesh* getMesh(unsigned index) const;
        texture* getTexture(unsigned index) const;
        atlas* getAtlas(unsigned index) const;
        drawModel* getModel(unsigned index) const;
        
        void eraseMesh(unsigned index);
        void eraseTexture(unsigned index);
        void eraseAtlas(unsigned index);
        void eraseModel(unsigned index);
        
        unsigned getNumMeshes() const;
        unsigned getNumTextures() const;
        unsigned getNumAtlases() const;
        unsigned getNumModels() const;
        
        unsigned manageMesh(mesh* const);
        unsigned manageTexture(texture* const);
        unsigned manageAtlas(atlas* const);
        unsigned manageModel(drawModel* const);
        
        mesh* unManageMesh(unsigned index);
        texture* unManageTexture(unsigned index);
        atlas* unManageAtlas(unsigned index);
        drawModel* unManageModel(unsigned index);
        
        bool containsMesh(const mesh* const) const;
        bool containsTexture(const texture* const) const;
        bool containsAtlas(const atlas* const) const;
        bool containsModel(const drawModel* const) const;
};

#endif	/* __LS_SCENE_MANAGER_H__ */

