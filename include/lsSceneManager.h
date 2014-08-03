/* 
 * File:   lsSceneManager.h
 * Author: miles
 *
 * Created on May 26, 2014, 11:22 AM
 */

#ifndef __LS_SCENE_MANAGER_H__
#define	__LS_SCENE_MANAGER_H__

#include <deque>

#include "lsDrawModel.h"
#include "lsSetup.h"
#include "lsMesh.h"
#include "lsTexture.h"
#include "lsAtlas.h"

//-----------------------------------------------------------------------------
//      Enumerations
//-----------------------------------------------------------------------------
/**
 * Enums for types needed by the scene manager.
 */
enum : unsigned {
    LS_INVALID_SCENE_ID = ((unsigned)-1)
};

//-----------------------------------------------------------------------------
//      Typedefs
//-----------------------------------------------------------------------------
/*
 * Typedefs for the type of lists/arrays that can be returned by the scene
 * manager.
 */
typedef std::deque<lsMesh*>      lsMeshList;
typedef std::deque<lsDrawModel*> lsDrawList;
typedef std::deque<lsTexture*>   lsTextureList;
typedef std::deque<lsAtlas*>     lsAtlasList;

//-----------------------------------------------------------------------------
//      Classes
//-----------------------------------------------------------------------------
/**
 * Scene manager class
 * 
 * Contains all visual elements to a scene such as meshes, textures, texture
 * atlases, shaders, etc.
 */
class lsSceneManager {
    private:
        lsTextureList texMgr;
        lsMeshList meshMgr;
        lsAtlasList atlasMgr;
        lsDrawList drawMgr;
        
    public:
        lsSceneManager();
        lsSceneManager(const lsSceneManager&) = delete;
        lsSceneManager(lsSceneManager&&);
        
        ~lsSceneManager();
        
        lsSceneManager& operator=(const lsSceneManager&) = delete;
        lsSceneManager& operator=(lsSceneManager&&);
        
        bool init();
        void terminate();
        
        lsMeshList& getMeshList();
        lsTextureList& getTextureList();
        lsAtlasList& getAtlasList();
        lsDrawList& getModelList();
        
        const lsMeshList& getMeshList() const;
        const lsTextureList& getTextureList() const;
        const lsAtlasList& getAtlasList() const;
        const lsDrawList& getModelList() const;
        
        lsMesh* getMesh(unsigned index) const;
        lsTexture* getTexture(unsigned index) const;
        lsAtlas* getAtlas(unsigned index) const;
        lsDrawModel* getModel(unsigned index) const;
        
        void eraseMesh(unsigned index);
        void eraseTexture(unsigned index);
        void eraseAtlas(unsigned index);
        void eraseModel(unsigned index);
        
        unsigned getNumMeshes() const;
        unsigned getNumTextures() const;
        unsigned getNumAtlases() const;
        unsigned getNumModels() const;
        
        unsigned manageMesh(lsMesh* const);
        unsigned manageTexture(lsTexture* const);
        unsigned manageAtlas(lsAtlas* const);
        unsigned manageModel(lsDrawModel* const);
        
        lsMesh* unManageMesh(unsigned index);
        lsTexture* unManageTexture(unsigned index);
        lsAtlas* unManageAtlas(unsigned index);
        lsDrawModel* unManageModel(unsigned index);
        
        bool containsMesh(const lsMesh* const) const;
        bool containsTexture(const lsTexture* const) const;
        bool containsAtlas(const lsAtlas* const) const;
        bool containsModel(const lsDrawModel* const) const;
};

#endif	/* __LS_SCENE_MANAGER_H__ */

