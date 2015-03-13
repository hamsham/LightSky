/* 
 * File:   scriptBasicVar.h
 * Author: Miles Lacey
 *
 * Created on March 12, 2015, 12:52 AM
 */

#ifndef __LS_SCRIPT_BASIC_VARIABLE_H__
#define	__LS_SCRIPT_BASIC_VARIABLE_H__

#include "lightsky/script/scriptVariable.h"

namespace ls {
namespace script {

/*-----------------------------------------------------------------------------
    Basic Built-In types
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * char, scriptVar_char
-------------------------------------*/
LS_SCRIPT_DECLARE_VAR(char, char);

/*-------------------------------------
 * short, scriptVar_short
-------------------------------------*/
LS_SCRIPT_DECLARE_VAR(short, short);

/*-------------------------------------
 * int, scriptVar_int
-------------------------------------*/
LS_SCRIPT_DECLARE_VAR(int, int);

/*-------------------------------------
 * uint, scriptVar_uint
-------------------------------------*/
LS_SCRIPT_DECLARE_VAR(uint, unsigned);

/*-------------------------------------
 * long, scriptVar_long
-------------------------------------*/
LS_SCRIPT_DECLARE_VAR(long, long);

/*-------------------------------------
 * ulong, scriptVar_ulong
-------------------------------------*/
LS_SCRIPT_DECLARE_VAR(ulong, unsigned long);

/*-------------------------------------
 * float, scriptVar_float
-------------------------------------*/
LS_SCRIPT_DECLARE_VAR(float, float);

/*-------------------------------------
 * double, scriptvar_double
-------------------------------------*/
LS_SCRIPT_DECLARE_VAR(double, double);

/*-------------------------------------
 * std::string, scriptVar_string
-------------------------------------*/
LS_SCRIPT_OVERRIDE_VAR_LOAD(std::string);
LS_SCRIPT_OVERRIDE_VAR_SAVE(std::string);
LS_SCRIPT_DECLARE_VAR(string, std::string); // scriptVar_string

} // end script namepace
} // end ls namespace

#endif	/* __LS_SCRIPT_BASIC_VARIABLE_H__ */

