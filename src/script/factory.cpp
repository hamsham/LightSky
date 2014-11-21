/* 
 * File:   factory.cpp
 * Author: Miles Lacey
 * 
 * Created on June 26, 2013, 5:58 AM
 */

#ifdef LS_MT
    #include <mutex>
#endif

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

#ifdef LS_MT

    std::mutex gVarFactoryMutex;
    std::mutex gFuncFactoryMutex;

    variableBase* createVariable(hash_t h) {
        gVarFactoryMutex.lock();
        const varFactory_t pFactory = gVarFactory.at(h);
        gVarFactoryMutex.unlock();

        if (pFactory != nullptr) {
            return pFactory();
        }
        return nullptr;
    }

    functorBase* createFunctor(hash_t h) {
        gFuncFactoryMutex.lock();
        const funcFactory_t pFactory = gFuncFactory.at(h);
        gFuncFactoryMutex.unlock();

        if (pFactory != nullptr) {
            return pFactory();
        }
        return nullptr;
    }

#else /* LS_MT */

    variable* createVariable(hash_t h) {
        const varFactory pFactory = gVarFactory.at(h);

        if (pFactory != nullptr) {
            return pFactory();
        }
        return nullptr;
    }

    functor* createFunctor(hash_t h) {
        const funcFactory pFactory = gFuncFactory.at(h);

        if (pFactory != nullptr) {
            return pFactory();
        }
        return nullptr;
    }

#endif /* LS_MT */

} // end script namespace
} // end ls namespace
