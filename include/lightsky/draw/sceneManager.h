/* 
 * File:   draw/sceneManager.h
 * Author: Miles Lacey
 *
 * Created on May 26, 2014, 11:22 AM
 */

#ifndef __LS_DRAW_SCENE_MANAGER_H__
#define	__LS_DRAW_SCENE_MANAGER_H__

#include <deque>

#include "lightsky/draw/meshModel.h"
#include "lightsky/draw/setup.h"
#include "lightsky/draw/mesh.h"
#include "lightsky/draw/texture.h"
#include "lightsky/draw/atlas.h"

/*-------------------------------------
 * Extern Template Types
-------------------------------------*/
extern template class std::deque<ls::draw::mesh*>;
extern template class std::deque<ls::draw::meshModel*>;
extern template class std::deque<ls::draw::texture*>;
extern template class std::deque<ls::draw::atlas*>;

namespace ls {
namespace draw {

/*-------------------------------------
 * Typedefs for the type of lists/arrays that can be returned by the scene
 * manager.
-------------------------------------*/
typedef std::deque<mesh*> meshList;
typedef std::deque<meshModel*> drawList;
typedef std::deque<texture*> textureList;
typedef std::deque<atlas*> atlasList;

/**-----------------------------------------------------------------------------
 * Scene manager class
 * 
 * Contains all visual elements to a scene such as meshes, textures, texture
 * atlases, shaders, etc.
------------------------------------------------------------------------------*/
class sceneManager {
    public:
        /**
         * Enums for types needed by the scene manager.
         */
        enum : unsigned {
            INVALID_SCENE_ID = ((unsigned)-1)
        };
    
    private:
        /**
         * The default texture for a mesh. This texture is used upon
         * initializing a mesh so that it can be rendered without error.
         */
        texture defaultTex;
        
        /**
         * Initialization method for the default texture.
         * 
         * @return TRUE if the default texture was initialized properly, FALSE
         * if not.
         */
        bool initDefaultTexture();
        
        textureList texMgr;
        meshList    meshMgr;
        atlasList   atlasMgr;
        drawList    drawMgr;
        
    public:
        sceneManager();
        sceneManager(const sceneManager&) = delete;
        sceneManager(sceneManager&&);
        
        ~sceneManager();
        
        sceneManager& operator=(const sceneManager&) = delete;
        sceneManager& operator=(sceneManager&&);
        
        bool init();
        void terminate();
        
        /**
         * Get the default texture used by freshly loaded models.
         * 
         * @return A constant reference to the default model texture
         */
        const texture& getDefaultTexture() const;
        
        meshList& getMeshList();
        textureList& getTextureList();
        atlasList& getAtlasList();
        drawList& getModelList();
        
        const meshList& getMeshList() const;
        const textureList& getTextureList() const;
        const atlasList& getAtlasList() const;
        const drawList& getModelList() const;
        
        mesh* getMesh(unsigned index) const;
        texture* getTexture(unsigned index) const;
        atlas* getAtlas(unsigned index) const;
        meshModel* getModel(unsigned index) const;
        
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
        unsigned manageModel(meshModel* const);
        
        mesh* unManageMesh(unsigned index);
        texture* unManageTexture(unsigned index);
        atlas* unManageAtlas(unsigned index);
        meshModel* unManageModel(unsigned index);
        
        bool containsMesh(const mesh* const) const;
        bool containsTexture(const texture* const) const;
        bool containsAtlas(const atlas* const) const;
        bool containsModel(const meshModel* const) const;
};

} // end draw namespace
} // end draw namespace

#endif	/* __LS_DRAW_SCENE_MANAGER_H__ */

