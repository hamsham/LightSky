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

} // end script namespace
} // end ls namespace
