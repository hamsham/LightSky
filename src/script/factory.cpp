/* 
 * File:   factory.cpp
 * Author: Miles Lacey
 * 
 * Created on June 26, 2013, 5:58 AM
 */

#include "lightsky/script/factory.h"

namespace ls {
namespace script {

// Variable and Function factories

// These trees are populated at the program's initialization
// They hold pointers to functions which only return a new instance of
// whichever type is requested
varFactoryMap  gVarFactory;
funcFactoryMap gFuncFactory;

/*
 * Variable and Functor implementations
 */
// Get the corresponding function pointer from gVarFactory/gFuncFactory.
// If the pointer isn't NULL, run the function in order to return a
// new instance of the requested object

variable* createVariable(hash_t h) {
    const varFactory* pFactory = gVarFactory.getData(h);

    if (pFactory != nullptr) {
        return (*pFactory)();
    }
    return nullptr;
}

functor* createFunctor(hash_t h) {
    const funcFactory* pFactory = gFuncFactory.getData(h);

    if (pFactory != nullptr) {
        return (*pFactory)();
    }
    return nullptr;
}


} // end script namespace
} // end ls namespace
