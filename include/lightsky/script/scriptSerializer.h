/* 
 * File:   scriptSerializer.h
 * Author: Miles Lacey
 *
 * Created on March 13, 2015, 9:26 PM
 */

#ifndef __LS_SCRIPT_SERIALIZER_H__
#define	__LS_SCRIPT_SERIALIZER_H__

#include "lightsky/utils/string_utils.h"

#include "lightsky/script/setup.h"

namespace ls {
namespace script {

class variable;
class functor;

/**
 * @brief Load a file
 * 
 * @param filename
 * A string object containing the relative path name to a file that
 * should be loadable into memory.
 * 
 * @param outVarMap
 * A reference to an iteratable container object which will hold a set of
 * scriptable variable objects.
 * 
 * @param outFuncMap
 * A reference to an iteratable container object which will hold a set of
 * scriptable functor objects.
 * 
 * @return true if the file was successfully loaded. False if not.
 */
bool loadScriptFile(
    const std::string& filename,
    variableMap_t& outVarMap,
    functorMap_t& outFuncMap
);

/**
 * @brief Load a file using a c-style wide string.
 * 
 * This method merely converts the filename into a multi-byte string
 * and calls "openFile()" using the ANSI equivalent string.
 * 
 * @param filename
 * A string object containing the relative path name to a file that
 * should be loadable into memory.
 * 
 * @param outVarMap
 * A reference to an iteratable container object which will hold a set of
 * scriptable variable objects.
 * 
 * @param outFuncMap
 * A reference to an iteratable container object which will hold a set of
 * scriptable functor objects.
 * 
 * @return true if the file was successfully loaded. False if not.
 */
bool loadScriptFile(
    const std::wstring& filename,
    variableMap_t& outVarMap,
    functorMap_t& outFuncMap
);

/**
 * @brief Remap the keys of a variable and functor map which had recently been
 * loaded.
 * 
 * It is recommended to use this function after loading data from a file in
 * order to directly map all key values in the input maps to the pointers which
 * store their data.
 * 
 * @param outVarMap
 * A reference to an iteratable container object which will hold a set of
 * scriptable variable objects.
 * 
 * @param outFuncMap
 * A reference to an iteratable container object which will hold a set of
 * scriptable functor objects.
 */
void remapScriptKeys(variableMap_t& outVarMap, functorMap_t& outFuncMap);

/**
 * @brief Save a file
 *
 * Use this method to save data to a file, specific to the type of
 * resource used by derived classes.
 * 
 * @param filename
 * A string object containing the relative path name to a file that
 * should be saved to the computer.
 * 
 * @param inVarList
 * A constant reference to an iteratable container object which holds
 * a set of scriptable variable objects.
 * 
 * @param inFuncList
 * A constant reference to an iteratable container object which holds
 * a set of scriptable functor objects.
 * 
 * @return true if the file was successfully saved. False if not.
 */
bool saveScriptFile(
    const std::string& filename,
    const variableMap_t& inVarList,
    const functorMap_t& inFuncList
);

/**
 * @brief Save a file using a c-style string of wide (UTF-8) characters
 * 
 * This method merely converts the filename into a multi-byte string
 * and calls "saveFile()" using the ANSI equivalent string.
 * 
 * @param filename
 * A string object containing the relative path name to a file that
 * should be saved to the computer.
 * 
 * @param inVarList
 * A constant reference to an iteratable container object which holds
 * a set of scriptable variable objects.
 * 
 * @param inFuncList
 * A constant reference to an iteratable container object which holds
 * a set of scriptable functor objects.
 * 
 * @return true if the file was successfully saved. False if not.
 */
bool saveScriptFile(
    const std::wstring& filename,
    const variableMap_t& inVarList,
    const functorMap_t& inFuncList
);

} // end script namespace
} // end ls namespace

#include "lightsky/script/generic/scriptSerializer_impl.h"

#endif	/* __LS_SCRIPT_SERIALIZER_H__ */
