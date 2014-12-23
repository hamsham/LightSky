/* 
 * File:   factory.h
 * Author: Miles Lacey
 *
 * Created on June 26, 2013, 5:58 AM
 */

#ifndef __LS_SCRIPT_FACTORY_H__
#define	__LS_SCRIPT_FACTORY_H__

#include "lightsky/script/setup.h"

namespace ls {
namespace script {
    
/*
 * Script Factory Functions
 */
typedef variable* (*varFactory)();

typedef functor* (*funcFactory)();

/*
 * Lookup Trees for factories
 */
typedef ls::utils::bTree<hash_t, varFactory> varFactoryMap;

typedef ls::utils::bTree<hash_t, funcFactory> funcFactoryMap;

extern varFactoryMap gVarFactory;
extern funcFactoryMap gFuncFactory;

/**
 * Create a script variable using the global variable factory
 * 
 * @param hash_t
 * A hash value that determines the type of variable that should be returned.
 * 
 * @return a pointer to the script variable requested. This pointer must be
 * destroyed with the "delete" operator.
 * This function will return NULL if the variable requested could not be
 * instantiated.
 */
variable* createVariable(hash_t);

/**
 * Create a script function using the global functor factory
 * 
 * @param hash_t
 * A hash value that determines the type of functor that should be returned.
 * 
 * @return a pointer to the script functor requested. This pointer must be
 * destroyed with the "delete" operator.
 * This function will return NULL if the functor requested could not be
 * instantiated.
 */
functor* createFunctor(hash_t);

} // end script namespace
} // end ls namespace

#endif	/* __LS_SCRIPT_FACTORY_H__ */
