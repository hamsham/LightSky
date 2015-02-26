/* 
 * File:   variable.cpp
 * Author: Miles Lacey
 * 
 * Created on April 13, 2014, 9:05 PM
 */

#include "lightsky/script/scriptVariable.h"

/*-----------------------------------------------------------------------------
    Non-Templated Class Definitions
-----------------------------------------------------------------------------*/
namespace ls {
namespace script {

/*-------------------------------------
    Variable Object Destructor
-------------------------------------*/
variable::~variable() {
}

/*-------------------------------------
    Variable Object Constructor
-------------------------------------*/
variable::variable() :
    scriptable{}
{}

/*-------------------------------------
    Variable Object Copy Constructor
-------------------------------------*/
variable::variable(const variable& v) :
    scriptable{v}
{}

/*-------------------------------------
    Variable Object Move Constructor
-------------------------------------*/
variable::variable(variable&& v) :
    scriptable{std::move(v)}
{}

/*-----------------------------------------------------------------------------
    Built-In types
-----------------------------------------------------------------------------*/
LS_SCRIPT_DEFINE_VAR(char,      char);
LS_SCRIPT_DEFINE_VAR(short,     short);
LS_SCRIPT_DEFINE_VAR(int,       int);
LS_SCRIPT_DEFINE_VAR(uint,      unsigned);
LS_SCRIPT_DEFINE_VAR(long,      long);
LS_SCRIPT_DEFINE_VAR(ulong,     unsigned long);
LS_SCRIPT_DEFINE_VAR(float,     float);
LS_SCRIPT_DEFINE_VAR(double,    double);
LS_SCRIPT_DEFINE_VAR(string,    std::string);

/*-----------------------------------------------------------------------------
    Built-In type overrides
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * String Serialization
-------------------------------------*/
LS_SCRIPT_OVERRIDE_VAR_SAVE(std::string) {
    const std::string::size_type len = data.size()*sizeof(std::string::value_type);
    ostr << len;
    ostr.write(data.data(), len);
    return ostr.good();
}

/*-------------------------------------
 * String Deserialization
-------------------------------------*/
LS_SCRIPT_OVERRIDE_VAR_LOAD(std::string) {
    (void)varImporter;
    (void)funcImporter;
    std::string::size_type len = 0;
    istr >> len;

    data.resize(len, '\0');
    istr.read(&data[0], len);
    
    if (data.size() != len) {
        data.clear();
        return false;
    }
    
    return istr.good() || istr.eof();
}

} // end script namespace
} // end ls namespace
