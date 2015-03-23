/* 
 * File:   scriptSerializer_impl.h
 * Author: Miles Lacey
 *
 * Created on March 22, 2015, 4:28 PM
 */

namespace ls {
namespace script {

/*-------------------------------------
 * Get the list of loaded variables (const).
-------------------------------------*/
inline const variableMap_t& scriptSerializer::getVariableList() const {
    return varList;
}

/*-------------------------------------
 * Get the list of loaded variables.
-------------------------------------*/
inline variableMap_t& scriptSerializer::getVariableList() {
    return varList;
}

/*-------------------------------------
 * Get the list of loaded functors (const).
-------------------------------------*/
inline const functorMap_t& scriptSerializer::getFunctorList() const {
    return funcList;
}

/*-------------------------------------
 * Get the list of loaded functors.
------------------------------------*/
inline functorMap_t& scriptSerializer::getFunctorList() {
    return funcList;
}

/*-------------------------------------
 * Load a list of variables.
-------------------------------------*/
inline bool scriptSerializer::loadFile(const std::wstring& filename) {
    return loadFile(utils::convertWtoMb(filename));
}

/*-------------------------------------
 * Write an initial set of data for a script type
-------------------------------------*/
template <typename data_t>
bool scriptSerializer::initialWrite(
    std::ostream& ostr,
    const std::pair<data_t* const, pointer_t<data_t>>& scriptIter
) const {
    const pointer_t<data_t>& pScript = scriptIter.second;
    
    if (!pScript) {
        return false;
    }
    
    const script_base_t baseType = pScript->getScriptType();
    const hash_t hashType = pScript->getScriptSubType();
    
    ostr
        << '\n' << static_cast<typename std::underlying_type<decltype(baseType)>::type>(baseType)
        << ' ' << hashType
        << ' '<< (const void*)pScript;
    
    return true;
}

/*-------------------------------------
 * Save a list of variables.
-------------------------------------*/
inline bool scriptSerializer::saveFile(
    const std::wstring& filename,
    const variableMap_t& inVarList,
    const functorMap_t& inFuncList
) const {
    return saveFile(utils::convertWtoMb(filename), inVarList, inFuncList);
}

} // end script namespace
} // end ls namespace
