/* 
 * File:   scriptSerializer_impl.h
 * Author: Miles Lacey
 *
 * Created on March 22, 2015, 4:28 PM
 */

namespace ls {
namespace script {

/*-------------------------------------
 * Load a list of variables.
-------------------------------------*/
inline bool loadScriptFile(const std::wstring& filename, variableMap_t& varList, functorMap_t& funcList) {
    return loadScriptFile(utils::convertWtoMb(filename), varList, funcList);
}

/*-------------------------------------
 * Save a list of variables.
-------------------------------------*/
inline bool saveScriptFile(
    const std::wstring& filename,
    const variableMap_t& inVarList,
    const functorMap_t& inFuncList
) {
    return saveScriptFile(utils::convertWtoMb(filename), inVarList, inFuncList);
}

} // end script namespace
} // end ls namespace
