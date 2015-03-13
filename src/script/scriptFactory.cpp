/* 
 * File:   factory.cpp
 * Author: Miles Lacey
 * 
 * Created on June 26, 2013, 5:58 AM
 */

#include <utility> // std::make_pair<>(...)
#include <unordered_map>

#include "lightsky/utils/log.h"
#include "lightsky/utils/assertions.h"

#include "lightsky/script/script.h"

namespace ls {
namespace script {

namespace {
/*-----------------------------------------------------------------------------
 * Variable and Function factories
 * 
 * These maps are populated at the program's initialization (before main()).
 * 
 * They hold pointers to functions which only return a new instance of
 * whichever type is requested
 * 
 * They are retrieved from functions as static variables in order to ensure a
 * proper order-of-creation. The MUST be instantiated and initialized before
 * any other script variable used in client code to prevent crashing at
 * startup.
 * 
 * See the following for additional details on order-of-creation:
 *      http://stackoverflow.com/questions/25857340/access-violation-inserting-element-into-global-map?lq=1
 * 
 *      http://stackoverflow.com/questions/13353519/access-violation-when-inserting-element-into-global-map
-----------------------------------------------------------------------------*/
/**
 * Global Variable Factory
 */
inline std::unordered_map<hash_t, varFactory_t>& getVarFactory() {
    static std::unordered_map<hash_t, varFactory_t> gVarFactoryList{};
    return gVarFactoryList;
}

/**
 * Global Functor Factory
 */
inline std::unordered_map<hash_t, funcFactory_t>& getFuncFactory() {
    static std::unordered_map<hash_t, funcFactory_t> gFuncFactoryList{};
    return gFuncFactoryList;
}

} // end anonymous namespace
/*-----------------------------------------------------------------------------
 * Factory Method Registration
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Variable Factory Registration
-------------------------------------*/
const varFactory_t& registerVarFactory(hash_t factoryId, const varFactory_t& pFactory) {
    if (getVarFactory().count(factoryId)) {
        return getVarFactory()[factoryId];
    }
    
    getVarFactory().insert(std::pair<hash_t, varFactory_t>{factoryId, pFactory});
    return getVarFactory()[factoryId];
}

/*-------------------------------------
 * Functor Factory Registration
-------------------------------------*/
const funcFactory_t& registerFuncFactory(hash_t factoryId, const funcFactory_t& pFactory) {
    if (getFuncFactory().count(factoryId)) {
        return getFuncFactory()[factoryId];
    }
    
    getFuncFactory().insert(std::pair<hash_t, funcFactory_t>{factoryId, pFactory});
    return getFuncFactory()[factoryId];
}

/*-----------------------------------------------------------------------------
 * Script Object Creation/Instantiation
 * 
 * Get the corresponding function pointer from gVarFactory/gFuncFactory.
 * If the pointer isn't NULL, run the function in order to return a
 * new instance of the requested object
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Variable Creation
-------------------------------------*/
pointer_t<variable> createVariable(hash_t factoryId) {
    for (const std::pair<hash_t, varFactory_t>& iter : getVarFactory()) {
        if (iter.first == factoryId) {
            return (*iter.second)();
        }
    }
    
    return pointer_t<variable>{nullptr};
}

/*-------------------------------------
 * Variable Deletion
-------------------------------------*/
void destroyVariable(pointer_t<variable>& pVariable) {
    pVariable.release();
}

/*-------------------------------------
 * Functor Creation
-------------------------------------*/
pointer_t<functor> createFunctor(hash_t factoryId) {
    for (const std::pair<hash_t, funcFactory_t>& iter : getFuncFactory()) {
        if (iter.first == factoryId) {
            return (*iter.second)();
        }
    }
    
    return pointer_t<functor>{nullptr};
}

/*-------------------------------------
 * Functor Deletion
-------------------------------------*/
void destroyFunctor(pointer_t<functor>& pFunc) {
    pFunc.release();
}

} // end script namespace
} // end ls namespace
