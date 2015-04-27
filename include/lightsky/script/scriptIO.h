/* 
 * File:   scriptIO.h
 * Author: Miles LAcey
 *
 * Created on March 24, 2015, 8:48 PM
 */

#ifndef __LS_SCRIPT_IO_H__
#define	__LS_SCRIPT_IO_H__

#include <iostream>

#include "lightsky/script/scriptVariable.h"

#include "lightsky/script/scriptFunctor.h"

#include "lightsky/script/scriptBasicVar.h"

/*-----------------------------------------------------------------------------
 Data Input/Output
-----------------------------------------------------------------------------*/
namespace ls {
namespace script {

/*-------------------------------------
 * Standard Output
-------------------------------------*/
LS_SCRIPT_DECLARE_VAR(stdPrint, void*);

/*-----------------------------------------------------------------------------
 * Print functions for basic data types
-----------------------------------------------------------------------------*/
LS_SCRIPT_DECLARE_FUNC(stdPrintChar, scriptVar_stdPrint, scriptVar_char);
LS_SCRIPT_DECLARE_FUNC(stdPrintShort, scriptVar_stdPrint, scriptVar_short);
LS_SCRIPT_DECLARE_FUNC(stdPrintInt, scriptVar_stdPrint, scriptVar_int);
LS_SCRIPT_DECLARE_FUNC(stdPrintUint, scriptVar_stdPrint, scriptVar_uint);
LS_SCRIPT_DECLARE_FUNC(stdPrintLong, scriptVar_stdPrint, scriptVar_long);
LS_SCRIPT_DECLARE_FUNC(stdPrintUlong, scriptVar_stdPrint, scriptVar_ulong);
LS_SCRIPT_DECLARE_FUNC(stdPrintFloat, scriptVar_stdPrint, scriptVar_float);
LS_SCRIPT_DECLARE_FUNC(stdPrintDouble, scriptVar_stdPrint, scriptVar_double);
LS_SCRIPT_DECLARE_FUNC(stdPrintString, scriptVar_stdPrint, scriptVar_string);

} // end script namespace
} // end ls namespace

#endif	/* __LS_SCRIPT_IO_H__ */

