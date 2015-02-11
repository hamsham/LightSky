/* 
 * File:   factory.cpp
 * Author: Miles Lacey
 * 
 * Created on June 26, 2013, 5:58 AM
 */

#include <utility> // std::make_pair<>(...)
#include <vector>

#include "lightsky/utils/log.h"
#include "lightsky/utils/assertions.h"

#include "lightsky/script/variable.h"
#include "lightsky/script/functor.h"
#include "lightsky/script/factory.h"

namespace ls {
namespace script {

/*-----------------------------------------------------------------------------
 * Variable and Function factories
 * 
 * These trees are populated at the program's initialization
 * They hold pointers to functions which only return a new instance of
 * whichever type is requested
-----------------------------------------------------------------------------*/
/**
 * Global Variable Factory
 */
static std::vector<std::pair<hash_t, varFactory_t>> gVarFactoryList;

/**
 * Global Functor Factory
 */
static std::vector<std::pair<hash_t, funcFactory_t>> gFuncFactoryList;

/*-----------------------------------------------------------------------------
 * Factory Method Registration
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Variable Factory Registration
-------------------------------------*/
const varFactory_t& registerVarFactory(hash_t factoryId, const varFactory_t& pFactory) {
    for (const std::pair<hash_t, varFactory_t>& iter : gVarFactoryList) {
        if (iter.first == factoryId) {
            return iter.second;
        }
    }
    
    gVarFactoryList.emplace_back(std::pair<hash_t, varFactory_t>{factoryId, pFactory});
    return gVarFactoryList.back().second;
}

/*-------------------------------------
 * Functor Factory Registration
-------------------------------------*/
const funcFactory_t& registerFuncFactory(hash_t factoryId, const funcFactory_t& pFactory) {
    for (const std::pair<hash_t, funcFactory_t>& iter : gFuncFactoryList) {
        if (iter.first == factoryId) {
            return iter.second;
        }
    }
    
    gFuncFactoryList.emplace_back(std::pair<hash_t, funcFactory_t>{factoryId, pFactory});
    return gFuncFactoryList.back().second;
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
    for (const std::pair<hash_t, varFactory_t>& iter : gVarFactoryList) {
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
    for (const std::pair<hash_t, funcFactory_t>& iter : gFuncFactoryList) {
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
