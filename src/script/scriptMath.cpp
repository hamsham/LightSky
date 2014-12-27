/* 
 * File:   scriptMath.cpp
 * Author: hammy
 * 
 * Created on December 27, 2014, 1:53 AM
 */

#include "lightsky/script/scriptMath.h"

/*-----------------------------------------------------------------------------
    Built-In Math Types
-----------------------------------------------------------------------------*/
namespace ls {
namespace script {

LS_SCRIPT_DEFINE_FUNC(addInts, scriptVar_int, scriptVar_int, scriptVar_int) {
    LS_SCRIPT_PARAM(0, int) = LS_SCRIPT_PARAM(1, int) + LS_SCRIPT_PARAM(2, int);
};

LS_SCRIPT_DEFINE_FUNC(subInts, scriptVar_int, scriptVar_int, scriptVar_int) {
    LS_SCRIPT_PARAM(0, int) = LS_SCRIPT_PARAM(1, int) - LS_SCRIPT_PARAM(2, int);
};


} // end script namespace
} // end ls namespace
