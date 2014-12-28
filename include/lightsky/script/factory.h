/* 
 * File:   factory.h
 * Author: Miles Lacey
 *
 * Created on June 26, 2013, 5:58 AM
 */

#ifndef __LS_SCRIPT_FACTORY_H__
#define	__LS_SCRIPT_FACTORY_H__

#include <unordered_map>

#include "lightsky/script/setup.h"

namespace ls {
namespace script {

/*-----------------------------------------------------------------------------
 * Script Factory Functions
-----------------------------------------------------------------------------*/
/**
 * @brief varFactory_t
 * 
 * This type represents a pointer to a function which instantiates a particular
 * variable type.
 */
typedef pointer_t<variable> (*varFactory_t)();

/**
 * @brief funcFactory_t
 * 
 * This type represents a pointer to a function which instantiates a particular
 * function type.
 */
typedef pointer_t<functor> (*funcFactory_t)();

/*-----------------------------------------------------------------------------
 * Script Factory Maps
 * 
 * A Factory map will map the hashed IDs of scriptable objects to their factory
 * functions. This allows script objects to be created through a simple map
 * for ease of use.
-----------------------------------------------------------------------------*/
/**
 * @brief varFactoryMap_t
 * 
 * This type maps script variables to their factory functions.
 */
typedef std::unordered_map<hash_t, varFactory_t> varFactoryMap_t;

/**
 * @brief varFactoryMap_t
 * 
 * This type maps script functors to their factory functions.
 */
typedef std::unordered_map<hash_t, funcFactory_t> funcFactoryMap_t;

/*-----------------------------------------------------------------------------
 * Factory Method Registration
-----------------------------------------------------------------------------*/
/**
 * @brief registerVarFactory
 * 
 * Register a global factory method for a particular variable type and map it
 * to the hashId provided. This will allow a variable to be instantiated using
 * the function "createVariable(...)," combined with the same hash.
 * 
 * @param factoryId
 * The hash value which will be used to map the provided factory method to the
 * global variable map.
 * 
 * @param pFactory
 * A constant reference to the function object which instantiates a particular
 * variable object.
 * 
 * @return A constant reference to the global factory method responsible for
 * creating a variable object using the hash provided.
 */
const varFactory_t& registerVarFactory(hash_t factoryId, const varFactory_t& pFactory);
/**
 * @brief registerFuncFactory
 * 
 * Register a global factory method for a particular function type and map it
 * to the hashId provided. This will allow a function to be instantiated using
 * the function "createFunctor(...)," combined with the same hash.
 * 
 * @param factoryId
 * The hash value which will be used to map the provided factory method to the
 * global function map.
 * 
 * @param pFactory
 * A constant reference to the function object which instantiates a particular
 * function object.
 * 
 * @return A constant reference to the global factory method responsible for
 * creating a function object using the hash provided.
 */
const funcFactory_t& registerFuncFactory(hash_t factoryId, const funcFactory_t& pFactory);

/*-----------------------------------------------------------------------------
 * Script Object Creation/Instantiation
-----------------------------------------------------------------------------*/
/**
 * Create a script variable using the global variable factory
 * 
 * @param factoryId
 * A hash value that determines the type of variable that should be returned.
 * 
 * @return a pointer to the script variable requested. This pointer must be
 * destroyed with the "delete" operator.
 * This function will return NULL if the variable requested could not be
 * instantiated.
 */
pointer_t<variable> createVariable(hash_t factoryId);

/**
 * Create a script function using the global functor factory
 * 
 * @param factoryId
 * A hash value that determines the type of functor that should be returned.
 * 
 * @return a pointer to the script functor requested. This pointer must be
 * destroyed with the "delete" operator.
 * This function will return NULL if the functor requested could not be
 * instantiated.
 */
pointer_t<functor> createFunctor(hash_t factoryId);

} // end script namespace
} // end ls namespace

#endif	/* __LS_SCRIPT_FACTORY_H__ */
