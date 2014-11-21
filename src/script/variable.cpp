/* 
 * File:   variable.cpp
 * Author: Miles Lacey
 * 
 * Created on April 13, 2014, 9:05 PM
 */

#include "lightsky/script/variable.h"

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

} // end script namespace
} // end ls namespace

/*-----------------------------------------------------------------------------
    Built-In types
-----------------------------------------------------------------------------*/
LS_SCRIPT_DEFINE_VAR(char, char);
LS_SCRIPT_DEFINE_VAR(short, short);
LS_SCRIPT_DEFINE_VAR(int, int);
LS_SCRIPT_DEFINE_VAR(long, long);
LS_SCRIPT_DEFINE_VAR(float, float);
LS_SCRIPT_DEFINE_VAR(double, double);
LS_SCRIPT_DEFINE_VAR(string, std::string);