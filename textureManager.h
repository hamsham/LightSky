/* 
 * File:   textureManager.h
 * Author: miles
 *
 * Created on May 26, 2014, 11:23 AM
 */

#ifndef __LS_TEXTURE_MANAGER_H__
#define	__LS_TEXTURE_MANAGER_H__

#include "manager.h"
#include "texture.h"
#include "textureAtlas.h"

/**
 * TextureManager
 * 
 * This class, as with the mesh class, represents a similar interface to the
 * manager object it contains. This is meant moreso for future compatibility as
 * more features get added to the framework.
 */
class textureManager {
    private:
        /**
         * Rather than use the implementing manager as a base class, the actual
         * data manager is just going to be used as a manager with some
         * functionality exposed through the manager. Hopefully this will make
         * future additions much easier to implement.
         * 
         * The manager object uses each texture's ID as the key to a location
         * within a hash table.
         */
        manager<unsigned, texture> texMgr;
        
    public:
        textureManager();
        textureManager(const textureManager&) = delete;
        textureManager(textureManager&&);
        
        ~textureManager();
        
        textureManager& operator=(const textureManager&) = delete;
        textureManager& operator=(textureManager&&);
        
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
        inline void manage(texture* const pTex) {
            texMgr.manage(pTex, pTex->getId());
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
        inline texture* unmanage(unsigned id) {
            return texMgr.unmanage(id);
        }
        
        /**
         * Free the memory used by an object that's managed by *this.
         * This function doe nothing if no object exists at ID.
         * 
         * @param id
         * The ID that is used to reference an object contained within *this.
         */
        inline void erase(unsigned id) {
            texMgr.erase(id);
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
            return texMgr.contains(id);
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
        inline texture* get(unsigned id) const {
            return texMgr.get(id);
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
        inline texture* get(unsigned id) {
            return texMgr.get(id);
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
        inline texture* elementAt(unsigned index) {
            return texMgr.elementAt(index);
        }
        
        /**
         * Release the memory of all objects managed by *this.
         */
        inline void clear() {
            texMgr.clear();
        }
        
        /**
         * Get the number of objects that are currently managed by *this.
         * 
         * @return A unsigned integer, representing the number of objects
         * managed by *this.
         */
        inline unsigned size() const {
            return texMgr.size();
        }
        
        /**
         * Retrieve the implementing hash table that is used internally by this
         * object.
         * 
         * @return A reference to the internal std::unordered_map used by *this.
         */
        inline const std::unordered_map<unsigned, texture*>& getDataMap() const {
            return texMgr.getDataMap();
        }
};

#endif	/* __LS_TEXTURE_MANAGER_H__ */

