/* 
 * File:   scriptIO.cpp
 * Author: Miles LAcey
 * 
 * Created on March 24, 2015, 8:48 PM
 */

#include "lightsky/script/scriptIO.h"

/*-----------------------------------------------------------------------------
 Data Input/Output
-----------------------------------------------------------------------------*/
namespace ls {
namespace script {

/*-------------------------------------
 * Standard Output
-------------------------------------*/
LS_SCRIPT_DEFINE_VAR(stdPrint, void*);

/*-----------------------------------------------------------------------------
 * Print functions for basic data types
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Because this library needs more macros.
-------------------------------------*/
#define LS_SCRIPT_DEFINE_VAR_PRINT(formalName, basicName, dataType) \
    LS_SCRIPT_DEFINE_FUNC(stdPrint##formalName, scriptVar_stdPrint, scriptVar_##basicName) { \
        (void)pArgs; \
        std::cout << LS_SCRIPT_PARAM(1, dataType); \
    }

LS_SCRIPT_DEFINE_VAR_PRINT(Char, char, char);
LS_SCRIPT_DEFINE_VAR_PRINT(Short, short, short);
LS_SCRIPT_DEFINE_VAR_PRINT(Int, int, int);
LS_SCRIPT_DEFINE_VAR_PRINT(Uint, uint, unsigned);
LS_SCRIPT_DEFINE_VAR_PRINT(Long, long, long);
LS_SCRIPT_DEFINE_VAR_PRINT(Ulong, ulong, unsigned long);
LS_SCRIPT_DEFINE_VAR_PRINT(Float, float, float);
LS_SCRIPT_DEFINE_VAR_PRINT(Double, double, double);
LS_SCRIPT_DEFINE_VAR_PRINT(String, string, std::string);

#undef LS_SCRIPT_DEFINE_VAR_PRINT

} // end script namespace
} // end ls namespace
