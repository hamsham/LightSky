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

namespace ls {
namespace script {

/*-----------------------------------------------------------------------------
    Hashing Setup
-----------------------------------------------------------------------------*/
using ls::utils::hash_t;

#define LS_SCRIPT_HASH_FUNC( str ) ls::utils::hashFNV1( str )

/*-----------------------------------------------------------------------------
    Data Type information
-----------------------------------------------------------------------------*/
enum class script_base_t {
    SCRIPT_VAR,
    SCRIPT_FUNC
};

/*-----------------------------------------------------------------------------
    Scripting Object Declarations
-----------------------------------------------------------------------------*/
// Base class
class scriptable;

/*
 * variable types
 */
class variable;

template <hash_t, typename> class
variable_t;

/*
 * function types
 */
class functor;

/*
 * Functor with multiple arguments
 */
template <hash_t hashId, typename...>
class functor_t;

/*
 * Functor with no arguments
 */
template <hash_t hashId>
class functor_t<hashId, void>;

/*
 * Void/NULL functor
 */
template <>
class functor_t<0, void>;

typedef functor_t<0, void > emptyFunc;

/*-----------------------------------------------------------------------------
    Containers
-----------------------------------------------------------------------------*/
/*
 * File loading maps
 */
typedef std::map<void*, variable*> varLoaderMap;

typedef std::map<void*, functor*> funcLoaderMap;

} // end script namespace
} // end ls namespace

#endif	/* __LS_SCRIPT_SETUP_H__ */
