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
#include "util.h"

/*
 * Forward declarations of dependencies.
 */
class sceneManager;

/**
 * Mesh Manager Class
 * The mesh manager class is responsible for keeping track of each mesh
 * contained within a scene. If a mesh has dependent textures or shaders, this
 * class will keep a running list of those dependencies to that they can all be
 * sorted and drawn with a minimum amount of state changes.
 */
class meshManager final : public manager<unsigned, mesh> {
    public:
        meshManager();
        meshManager(const meshManager&) = delete;
        meshManager(meshManager&&);
        
        ~meshManager();
        
        meshManager& operator=(const meshManager&) = delete;
        meshManager& operator=(meshManager&&);
        
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
        inline void manage(mesh* const pData, const unsigned& id) {
            if (this->contains(id) == false) {
                dataMap[id] = pData;
            }
        }
        
        /**
         * Remove an object from the list of things managed by *this. This
         * function essentially tells the manager that it should forget about
         * an object, leaving the programmer to manage it manually.
         * 
         * @param id
         * The ID used to identify an object.
         * 
         * @return mesh*
         * A pointer to an object (previously) managed by *this.
         */
        inline mesh* unmanage(const unsigned& id) {
            mesh* pData = nullptr;
            
            if (this->contains(id)) {
                pData = dataMap.at(id);
                dataMap.erase(id);
            }
            
            return pData;
        }
        
        /**
         * Free the memory used by an object that's managed by *this.
         * This function doe nothing if no object exists at ID.
         * 
         * @param id
         * The ID that is used to reference an object contained within *this.
         */
        inline void erase(const unsigned& id) {
            if (this->contains(id) == false) {
                return;
            }
            
            mesh* const pData = dataMap.at(id);
            dataMap.erase(id);
            delete pData;
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
        inline bool contains(const unsigned& id) const {
            return dataMap.find(id) != dataMap.end();
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
        inline mesh* get(const unsigned& id) const {
            return this->contains(id) ? dataMap.at(id) : nullptr;
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
        inline mesh* get(const unsigned& id) {
            return this->contains(id) ? dataMap.at(id) : nullptr;
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
            if (index >= dataMap.size()) {
                return nullptr;
            }

            typename map_t::iterator iter = dataMap.begin();
            std::advance(iter, index);
            return iter->second;
        }
        
        /**
         * Release the memory of all objects managed by *this.
         */
        inline void clear() {
            typename map_t::iterator iter;
            for (iter = dataMap.begin(); iter != dataMap.end(); ++iter) {
                delete iter->second;
            }
            dataMap.clear();
        }
        
        /**
         * Get the number of objects that are currently managed by *this.
         * 
         * @return A unsigned integer, representing the number of objects
         * managed by *this.
         */
        inline unsigned size() const {
            return dataMap.size();
        }
        
        /**
         * Retrieve the implementing hash table that is used internally by this
         * object.
         * 
         * @return A reference to the internal std::unordered_map used by *this.
         */
        inline const std::unordered_map<unsigned, mesh*>& getDataMap() const {
            return dataMap;
        }
};

#endif	/* __LS_MESH_MANAGER_H__ */

