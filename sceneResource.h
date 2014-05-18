/* 
 * File:   sceneResource.h
 * Author: miles
 *
 * Created on May 16, 2014, 9:57 PM
 */

#ifndef __LS_SCENE_RESOURCE_H__
#define	__LS_SCENE_RESOURCE_H__

#include "mesh.h"
#include "resource.h"

class sceneResource final : public resource {
    private:
        unsigned numMeshes = 0;
        
        
        unsigned numTextures = 0;
        unsigned numVertices = 0;
        
    public:
        constexpr sceneResource() {}
        sceneResource(const sceneResource&) = delete;
        sceneResource(sceneResource&&);
        
        virtual ~sceneResource() {
            unload();
        }
        
        sceneResource& operator=(const sceneResource&) = delete;
        sceneResource& operator=(sceneResource&&);
        
        virtual bool loadFile(const char* filename) override;
        
        virtual bool saveFile(const char*) const override {
            return false;
        }
        
        virtual void unload() override {}
};

#endif	/* __LS_SCENE_RESOURCE_H__ */

