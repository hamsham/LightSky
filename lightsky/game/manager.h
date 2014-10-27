/* 
 * File:   game/manager.h
 * Author: Miles Lacey
 *
 * Created on May 25, 2014, 9:07 PM
 */

#ifndef __LS_GAME_MANAGER_H__
#define	__LS_GAME_MANAGER_H__

#include <utility>
#include <unordered_map>

namespace ls {
namespace game {

/**
 * @brief Manager Object
 *
 * The default implementation takes ownership of raw dynamic pointers and will
 * delete them upon destruction. A custom implementation is necessary to delete
 * dynamic arrays.
 * 
 * Remember, this non-specialized implementation takes pointers to data
 * allocated with the 'new' operator.
 */
template <typename hash_t, typename data_t>
class manager {
    public:
        /**
         * @brief map_t
         * The specific type of hash map contained within *this template object.
         */
        typedef std::unordered_map<hash_t, data_t*> map_t;
        
    private:
        /**
         * @brief dataMap
         * 
         * A hash table which can be used to easily and quickly reference and
         * manage objects.
         */
        map_t dataMap;
        
    public:
        /**
         * @brief Constructor
         */
        manager();
        
        /**
         * Copy Constructor -- DELETED
         */
        manager(const manager&) = delete;
        
        /**
         * @brief Move Constructor
         * Moves all managed object from the input parameter into *this.
         * 
         * @param m
         * An r-value reference to a manager object
         */
        manager(manager&& m);
        
        /**
         * @brief Destructor
         * 
         * Deletes all managed objects contained within *this, freeing all
         * memory.
         */
        ~manager();
        
        /**
         * @brief Copy Operator -- DELETED
         */
        manager& operator=(const manager&) = delete;
        
        /**
         * @brief Move Operator
         * 
         * @param m
         * An r-value reference to a manager object.
         * 
         * @return A reference to *this.
         */
        manager& operator=(manager&& m);
        
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
        void manage(const hash_t& id, data_t* const pData);
        
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
        data_t* unmanage(const hash_t& id);
        
        /**
         * Free the memory used by an object that's managed by *this.
         * This function doe nothing if no object exists at ID.
         * 
         * @param id
         * The ID that is used to reference an object contained within *this.
         */
        void erase(const hash_t& id);
        
        /**
         * Determine if an object, referenced by ID, is managed by *this.
         * 
         * @param id
         * The ID that is used to reference objects.
         * 
         * @return
         * TRUE if an object is referenced by *this, FALSE if this object is
         * not managing something at ID.
         */
        bool contains(const hash_t& id) const;
        
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
        data_t* get(const hash_t& id) const;
        
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
        data_t* get(const hash_t& id);
        
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
        data_t* elementAt(unsigned index);
        
        /**
         * Release the memory of all objects managed by *this.
         */
        void clear();
        
        /**
         * Get the number of objects that are currently managed by *this.
         * 
         * @return A unsigned integer, representing the number of objects
         * managed by *this.
         */
        unsigned size() const;
        
        /**
         * Retrieve the implementing hash table that is used internally by this
         * object.
         * 
         * @return A reference to the internal std::unordered_map used by *this.
         */
        const map_t& getDataMap() const;
        
        /**
         * Retrieve the implementing hash table that is used internally by this
         * object.
         * 
         * @return A reference to the internal std::unordered_map used by *this.
         */
        map_t& getDataMap();
};

} // end game namespace
} // end ls namespace

#include "lightsky/game/generic/manager_impl.h"

#endif	/* __LS_GAME_MANAGER_H__ */
