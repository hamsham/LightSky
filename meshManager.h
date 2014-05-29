/* 
 * File:   meshManager.h
 * Author: miles
 *
 * Created on May 26, 2014, 11:23 AM
 */

#ifndef __LS_MESH_MANAGER_H__
#define	__LS_MESH_MANAGER_H__

#include "manager.h"
#include "vertexArray.h"
#include "mesh.h"

/**
 * Mesh Manager Class
 * The mesh manager class is responsible for keeping track of each mesh
 * contained within a scene. If a mesh has dependent textures or shaders, this
 * class will keep a running list of those dependencies to that they can all be
 * sorted and drawn with a minimum amount of state changes.
 */
class meshManager {
    private:
        /**
         * Rather than use the implementing manager as a base class, the actual
         * data manager is just going to be used as a manager with some
         * functionality exposed through the manager. Hopefully this will make
         * future additions much easier to implement.
         * 
         * The manager object uses each mesh's VBO ID as the key to a location
         * within a hash table.
         */
        manager<unsigned, mesh> vboMgr;
        
    public:
        meshManager();
        meshManager(const meshManager&) = delete;
        meshManager(meshManager&&);
        
        ~meshManager();
        
        meshManager& operator=(const meshManager&) = delete;
        
        meshManager& operator=(meshManager&& mm);
        
        /**
         * Manage the dynamic memory of an object, given an ID that it can be
         * referenced by.
         * If an object referenced by the "ID" parameter is already managed by
         * *this, then no management operations will be performed. The member
         * function "contains()" should be used before calling "manage()."
         * 
         * @param pData
         * A pointer to a dynamic object that should be managed by *this.
         * 
         * @param id
         * The ID that *this object should be referenced by *this.
         */
        inline void manage(mesh* const pMesh) {
            vboMgr.manage(pMesh, pMesh->vbo.getId());
        }
        
        /**
         * Remove an object from the list of things managed by *this. This
         * function essentially tells the manager that it should forget about
         * an object, leaving the programmer to manage it manually.
         * 
         * @param id
         * The ID used to identify an object.
         * 
         * @return data_t*
         * A pointer to an object (previously) managed by *this.
         */
        inline mesh* unmanage(unsigned id) {
            return vboMgr.unmanage(id);
        }
        
        /**
         * Free the memory used by an object that's managed by *this.
         * This function doe nothing if no object exists at ID.
         * 
         * @param id
         * The ID that is used to reference an object contained within *this.
         */
        inline void erase(unsigned id) {
            vboMgr.erase(id);
        }
        
        /**
         * Determine if an object, referenced by ID, is managed by *this.
         * 
         * @param id
         * The ID that is used to reference objects.
         * 
         * @return
         * TRUE if an object is referenced by *this.
         * FALSE if this object is not managing something at ID.
         */
        inline bool contains(unsigned id) const {
            return vboMgr.contains(id);
        }
        
        /**
         * Retrieve the raw pointer to an object that is currently managed by
         * *this.
         * 
         * @param id
         * The ID that is used to reference a managed object.
         * 
         * @return
         * A const pointer to a managed object, or NULL if nothing at ID exists.
         */
        inline mesh* get(unsigned id) const {
            return vboMgr.get(id);
        }
        
        /**
         * Retrieve the raw pointer to an object that is currently managed by
         * *this.
         * 
         * @param id
         * The ID that is used to reference a managed object.
         * 
         * @return
         * A pointer to a managed object, or NULL if nothing at ID exists.
         */
        inline mesh* get(unsigned id) {
            return vboMgr.get(id);
        }
        
        /**
         * Get a managed object using an index offset, rather tan an ID. This
         * method is meant for convenience only and should not be used for
         * non-performance oriented applications.
         * 
         * @param index
         * The index ID that an object exists at.
         * 
         * @return A pointer to an object managed by *this.
         */
        inline mesh* elementAt(unsigned index) {
            return vboMgr.elementAt(index);
        }
        
        /**
         * Release the memory of all objects managed by *this.
         */
        inline void clear() {
            vboMgr.clear();
        }
        
        /**
         * Get the number of objects that are currently managed by *this.
         * 
         * @return A unsigned integer, representing the number of objects
         * managed by *this.
         */
        inline unsigned size() const {
            return vboMgr.size();
        }
        
        /**
         * Retrieve the implementing hash table that is used internally by this
         * object.
         * 
         * @return A reference to the internal std::unordered_map used by *this.
         */
        inline const std::unordered_map<unsigned, mesh*>& getDataMap() const {
            return vboMgr.getDataMap();
        }
};

#endif	/* __LS_MESH_MANAGER_H__ */

