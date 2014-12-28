/* 
 * File:   setup.h
 * Author: Miles Lacey
 *
 * Created on June 26, 2013, 5:18 AM
 */

#ifndef __LS_SCRIPT_SETUP_H__
#define	__LS_SCRIPT_SETUP_H__

#include <map>

#include "lightsky/setup/macros.h"

#include "lightsky/utils/hash.h"
#include "lightsky/utils/pointer.h"

namespace ls {
namespace script {

/*-----------------------------------------------------------------------------
    Hashing Setup
-----------------------------------------------------------------------------*/
/**
 * @brief Hash type used to associate script types to a serializable ID.
 */
using ls::utils::hash_t;

/**
 * @brief Scripting function used internally for generating script IDs.
 */
#define LS_SCRIPT_HASH_FUNC( str ) ls::utils::hashFNV1( str )

/*-----------------------------------------------------------------------------
    Data Type information
-----------------------------------------------------------------------------*/
enum class script_base_t {
    VARIABLE,
    FUNCTOR
};

/*-----------------------------------------------------------------------------
 Forward Declarations
-----------------------------------------------------------------------------*/
class scriptable;
class variable;
class functor;

/*-----------------------------------------------------------------------------
 Dynamic Memory Types
-----------------------------------------------------------------------------*/
/**------------------------------------
 * Dynamic Memory Management for script objects.
------------------------------------*/
template <class data_t> using pointer_t = ls::utils::pointer<data_t>;

/*
 * Create an extern template for the dynamic pointer type.
 */
} // end script namespace
extern template struct ls::utils::pointer<ls::script::variable>;
extern template struct ls::utils::pointer<ls::script::functor>;
namespace script { // continue script namespace

/*-----------------------------------------------------------------------------
    Containers
-----------------------------------------------------------------------------*/
/**
 * @brief File loading map for variable objects.
 */
typedef std::map<void*, pointer_t<variable>> varImportMap_t;

/**
 * @brief File loading map for functor objects.
 */
typedef std::map<void*, pointer_t<functor>> funcImportMap_t;

} // end script namespace
} // end ls namespace

#endif	/* __LS_SCRIPT_SETUP_H__ */
