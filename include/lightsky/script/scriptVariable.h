/* 
 * File:   variable.h
 * Author: Miles Lacey
 *
 * Created on April 13, 2014, 9:05 PM
 */

#ifndef __LS_SCRIPT_VARIABLE_H__
#define	__LS_SCRIPT_VARIABLE_H__

#include <iostream>
#include <fstream>

#include "lightsky/script/setup.h"
#include "lightsky/script/scriptable.h"
#include "lightsky/script/scriptFactory.h"

namespace ls {
namespace script {

/**----------------------------------------------------------------------------
    Variable Base Type
    
    The Variable base object is used as an interface for scriptable data types.
-----------------------------------------------------------------------------*/
class variable : public scriptable {
    public:
        /**
         *  @brief 
         */
        virtual ~variable() = 0;

        /**
         *  @brief Constructor
         *  Constructs *this and the 'scriptable' base class.
         */
        variable();

        /**
         *  @brief Copy Constructor
         *  Copies data from the input parameter into *this.
         *  
         *  @param v
         *  A constant reference to a variable base object.
         */
        variable(const variable& v);

        /**
         *  @brief Move Constructor
         *  Moves data from the input parameter into *this without performing
         *  any copies.
         *  
         *  @param v
         *  An r-value reference to a variable base object.
         */
        variable(variable&& v);
        
        /**
         *  @brief Copy Constructor
         *  Copies data from the input parameter into *this.
         *  
         *  @param v
         *  A constant reference to a variable base object.
         *  
         *  @return
         *  A reference to *this.
         */
        variable& operator =(const variable& v);
        
        /**
         *  @brief Move Operator
         *  Moves data from the input parameter into *this without performing
         *  any copies.
         *  
         *  @param v
         *  An r-value reference to a variable base object.
         *  
         *  @return
         *  A reference to *this.
         */
        variable& operator =(variable&& v);

        /**
         *  @brief getScriptType
         *  Retrieve the type of scripting object *this is.
         *  
         *  @return ls::script::script_base_t::SCRIPT_VAR
         */
        script_base_t getScriptType() const final;
        
        /**
         *  @brief 
         */
        virtual hash_t getScriptSubType() const = 0;
};

/**----------------------------------------------------------------------------
    Extended Variable Template Type
-----------------------------------------------------------------------------*/
template <hash_t hashId, typename type>
class variable_t final : public variable {
    public:
        /**
         *  @brief Data Member
         *  
         *  This class member is meant to be as transparent as a regular
         *  variable in code. Since scripted objects contain no internal
         *  manipulation, it can remain exposed.
         */
        type data;

        /**
         *  @brief Destructor
         *  
         *  Cleans up any resources used by the parent classes.
         */
        virtual ~variable_t();
        
        /**
         *  @brief Constructor
         *  
         *  Initializes all base classes and data members.
         */
        variable_t();

        /**
         *  @brief Copy Constructor
         *  
         *  Copies data from the input parameter into *this.
         *  
         *  @param v
         *  A constant reference to a scripting variable of the same type as
         *  *this.
         */
        variable_t(const variable_t& v);

        /**
         *  @brief Move Constructor
         *  
         *  Moves data from the input parameter into *this without performing
         *  any copies.
         *  
         *  @param v
         *  An r-value reference to a scripting variable of the same type as
         *  *this.
         */
        variable_t(variable_t&& v);

        /**
         *  @brief Copy Operator
         *  
         *  Copies data from the input parameter into *this.
         *  
         *  @param v
         *  A constant reference to a scripting variable of the same type as
         *  *this.
         *  
         *  @return a reference to *this.
         */
        variable_t& operator =(const variable_t& v);
        
        /**
         *  @brief Move Operator
         *  
         *  Moves data from the input parameter into *this without performing
         *  any copies.
         *  
         *  @param v
         *  An r-value reference to a scripting variable of the same type as
         *  *this.
         *  
         *  @return a reference to *this.
         */
        variable_t& operator =(variable_t&& v);

        /**
         *  @brief Load Variable data from an std::istream
         *  
         *  A serialization method to will help reload data from a standard
         *  input stream. This method uses the overloaded input stream operator
         *  'std::istream::operator >> (T)' in order to load variable data into
         *  *this.
         *  
         *  @param istr
         *  A reference to a std::istream object which contains variable data
         *  to be loaded into *this.
         *  
         *  @param varLoader
         *  A variable-loading factory that will be used to map variable data
         *  from the input stream into *this.
         *  
         *  @param funcLoader
         *  A function-loading factory that will be used to map functor data
         *  from the input stream into *this.
         *  
         *  @return a boolean value that will determine if data was
         *  successfully loaded into *this (TRUE) or not (FALSE).
         */
        bool load(std::istream& istr, varImportMap_t& vlm, funcImportMap_t& flm) override;

        /**
         *  @brief Save all data from *this into an std::ostream.
         *  
         *  @param ostr
         *  A reference to an std::ostream object. Each scripted variable must
         *  make use of the overloaded stream operator
         *  'std::istream::operator >> (T)' in order to save variable data from
         *  *this.
         * 
         * @return TRUE if the data was successfully saved, FALSE if not.
         */
        bool save(std::ostream& ostr) const override;

        /**
         *  @brief getScriptSubType
         *  Retrieve the run-time-type information of the data stored in *this.
         *  
         *  @return A portable hash code, representing the hashed lexical name
         *  of the data type stored in *this.
         */
        hash_t getScriptSubType() const final;
};

} // end script namespace
} // end ls namespace

#include "lightsky/script/generic/scriptVariable_impl.h"

/*-----------------------------------------------------------------------------
    Script Type Registration and Accessibility Macros
-----------------------------------------------------------------------------*/
/**
 *  @brief Script Variable Specifier
 *  
 *  This is simply a convenience macro that can be used to access a
 *  ls::script::variable_t by its data type, rather than specify it by its
 *  template parameters.
 *  
 *  For example, a variable of type 'int' can be accessed in on of three ways:
 *      
 *      ls::script::variable_t<LS_SCRIPT_HASH_FUNC(LS_STRINGIFY(int)), int>
 *      
 *      LS_SCRIPT_VAR_TYPE(int)
 *      
 *      scriptVar_int (if registered using the LS_SCRIPT_DECLARE_VAR macro).
 */
#ifndef LS_SCRIPT_VAR_TYPE
    #define LS_SCRIPT_VAR_TYPE( varType ) \
        ls::script::variable_t<LS_SCRIPT_HASH_FUNC(LS_STRINGIFY(varType)), varType>
#endif /* LS_SCRIPT_VAR_TYPE */

/**
 *  @brief Script Variable Data Access
 *  
 *  This macro is intended to be used in the functor objects, but allows a
 *  scripted variable's data to be accessed in regular code.
 *  
 *  To access the integer member of a scriptVar_int, for example, one could
 *  write the following:
 *      LS_SCRIPT_VAR_DATA(foo, int) = 42.
 */
#ifndef LS_SCRIPT_VAR_DATA
    #define LS_SCRIPT_VAR_DATA( pVar, varName ) \
        static_cast<ls::script::scriptVar_##varName*>((ls::script::variable*)pVar)->data
#endif /* LS_SCRIPT_VAR_DATA */

/**
 *  @brief Variable Declaration for Header Files
 *  
 *  This macro is used to both register a variable with the scripting system's
 *  global variable factory, as well as provide useful typedefs and a portable
 *  hash value to identify the variable type.
 *  
 *  Sample usage would be as follows (for an integer and std::string):
 *      LS_SCRIPT_DECLARE_VAR(int, int);
 *      LS_SCRIPT_DECLARE_VAR(string, std::string);
 *      LS_SCRIPT_DECLARE_VAR(someClassType, someClass::someType);
 *  
 *  Now that there are two registered data types, one can access the hash codes
 *  for these two variable like so:
 *      scriptHash_int
 *      scriptHash_string
 *      scriptHash_someClassType
 *  
 *  You could also create and modify registered variables:
 *  
 *      ls::script::variable* pVar = scriptFactory_int();
 *      LS_SCRIPT_VAR_DATA(pVar, int) = 42;
 *      delete pVar;
 *      
 *      ls::script::variable* pVar = scriptFactory_string();
 *      LS_SCRIPT_VAR_DATA(pVar, std::string) = "Hello World";
 *      delete pVar;
 *  
 *      ls::script::variable* pVar = scriptFactory_someClassType();
 *      LS_SCRIPT_VAR_DATA(pVar, someClass::someType).foo();
 *      delete pVar;
 *  
 *  @note
 *  All data generated by a factory method MUST be deleted using 'delete.'
 */
#ifndef LS_SCRIPT_DECLARE_VAR
    #define LS_SCRIPT_DECLARE_VAR( varName, varType ) \
        \
        enum : ls::script::hash_t { \
            scriptHash_##varName = LS_SCRIPT_HASH_FUNC(LS_STRINGIFY(varType)) \
        }; \
        \
        extern const ls::script::varFactory_t& scriptFactory_##varName; \
        \
        typedef ls::script::variable_t<scriptHash_##varName, varType> scriptVar_##varName; \
        \
        extern template class ls::script::variable_t<scriptHash_##varName, varType>
#endif /* LS_SCRIPT_DECLARE_VAR */

/**
 *  @brief Variable Definition for Source Files
 *  
 *  This macro allows variable types to be defined in source compilation units.
 *  The macro explicitly instantiates the ls::script::variable_t<> class
 *  template, defines the variable's factory function, and adds the factory to
 *  the global factory map.
 *  
 *  To use this macro, simply type:
 *      LS_SCRIPT_DEFINE_VAR(int, int);
 *      LS_SCRIPT_DEFINE_VAR(string, std::string);
 *      LS_SCRIPT_DEFINE_VAR(someClassType, someClass::someType);
 *  
 *  In addition, the global scripting factory can then be used like so:
 *      ls::script::variable* pVar;
 *      pVar = ls::script::createScriptVar(scriptHash_int);
 *      ...
 *      delete pVar;
 */
#ifndef LS_SCRIPT_DEFINE_VAR
    #define LS_SCRIPT_DEFINE_VAR( varName, varType ) \
        \
        template class ls::script::variable_t<scriptHash_##varName, varType>; \
        \
        const varFactory_t& scriptFactory_##varName = ls::script::registerVarFactory( \
            scriptHash_##varName, []()->ls::script::pointer_t<ls::script::variable> { \
                return ls::script::pointer_t<ls::script::variable>{new scriptVar_##varName}; \
            } \
        )
#endif /* LS_SCRIPT_DEFINE_VAR */

/**
 * @brief Decalre/define an override for the load method of a script variable.
 * 
 * Place this in a header file with a semicolon appended in order to declare
 * the override.
 * 
 * Place it in a *.cpp/translation unit, with brackets, to define the override
 * method.
 * 
 * The following variables will be made available in the override function:
 *      *this       - Refers to the scriptVar_##varName being overriden.
 *      this->data  - The data represented by *this (of type "varType").
 *      istr        - An std::istream reference which should be used to read
 *                  - data (deserialize) back into *this.
 *      varImporter - A reference to a varImportMap_t, containing pointers to
 *                  - other variable objects that *this may reference.
 *      funcImporter- A reference to a funcImportMap_t, which will contain
 *                  - pointers to any other functions that *this references.
 * 
 * @param varType
 * The C++ type of the data contained within the specialized script object.
 */
#ifndef LS_SCRIPT_OVERRIDE_VAR_LOAD
    #define LS_SCRIPT_OVERRIDE_VAR_LOAD( varType ) \
    \
    template <> \
    bool ls::script::variable_t<LS_SCRIPT_HASH_FUNC(LS_STRINGIFY(varType)), varType>::load( \
        std::istream&       istr, \
        varImportMap_t&     varImporter, \
        funcImportMap_t&    funcImporter \
    )
#endif /* LS_SCRIPT_OVERRIDE_VAR_LOAD */

/**
 * @brief Decalre/define an override for the save method of a script variable.
 * 
 * Place this in a header file with a semicolon appended in order to declare
 * the override.
 * 
 * Place it in a *.cpp/translation unit, with brackets, to define the override
 * method.
 * 
 * The following variables will be made available in the override function:
 *      *this       - Refers to the scriptVar_##varName being overriden.
 *      this->data  - The data represented by *this (of type "varType").
 *      ostr        - An std::ostream reference which should be used to export
 *                  - or serialize the data in *this.
 * 
 * @param varType
 * The C++ type of the data contained within the specialized script object.
 */
#ifndef LS_SCRIPT_OVERRIDE_VAR_SAVE
    #define LS_SCRIPT_OVERRIDE_VAR_SAVE( varType ) \
    \
    template <> \
    bool ls::script::variable_t<LS_SCRIPT_HASH_FUNC(LS_STRINGIFY(varType)), varType>::save(std::ostream& ostr) const
#endif /* LS_SCRIPT_OVERRIDE_VAR_SAVE */

#endif	/* __LS_SCRIPT_VARIABLE_H__ */
