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

#include "lightsky/script/factory.h"

namespace ls {
namespace script {

// Variable and Function factories

// These trees are populated at the program's initialization
// They hold pointers to functions which only return a new instance of
// whichever type is requested
static std::vector<std::pair<hash_t, varFactory>> gVarFactoryList;
static std::vector<std::pair<hash_t, funcFactory>> gFuncFactoryList;

/*
 * Variable and Functor implementations
 */
// Get the corresponding function pointer from gVarFactory/gFuncFactory.
// If the pointer isn't NULL, run the function in order to return a
// new instance of the requested object

variable* createVariable(hash_t factoryId) {
    for (const std::pair<hash_t, varFactory>& iter : gVarFactoryList) {
        if (iter.first == factoryId) {
            return (*iter.second)();
        }
    }
    
    return nullptr;
}

functor* createFunctor(hash_t factoryId) {
    for (const std::pair<hash_t, funcFactory>& iter : gFuncFactoryList) {
        if (iter.first == factoryId) {
            return (*iter.second)();
        }
    }
    
    return nullptr;
}

const varFactory& registerVarFactory(hash_t factoryId, const varFactory& pFactory) {
    for (const std::pair<hash_t, varFactory>& iter : gVarFactoryList) {
        if (iter.first == factoryId) {
            return iter.second;
        }
    }
    
    gVarFactoryList.emplace_back(std::pair<hash_t, varFactory>{factoryId, pFactory});
    return gVarFactoryList.back().second;
}

const funcFactory& registerFuncFactory(hash_t factoryId, const funcFactory& pFactory) {
    for (const std::pair<hash_t, funcFactory>& iter : gFuncFactoryList) {
        if (iter.first == factoryId) {
            return iter.second;
        }
    }
    
    gFuncFactoryList.emplace_back(std::pair<hash_t, funcFactory>{factoryId, pFactory});
    return gFuncFactoryList.back().second;
}


} // end script namespace
} // end ls namespace
