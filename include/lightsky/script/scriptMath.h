/* 
 * File:   scriptMath.h
 * Author: hammy
 *
 * Created on December 27, 2014, 1:53 AM
 */

#ifndef __LS_SCRIPT_MATH_H__
#define	__LS_SCRIPT_MATH_H__

#include "lightsky/script/variable.h"
#include "lightsky/script/functor.h"

/*-----------------------------------------------------------------------------
    Built-In Math Types
-----------------------------------------------------------------------------*/
namespace ls {
namespace script {

LS_SCRIPT_DECLARE_FUNC(addInts, scriptVar_int, scriptVar_int, scriptVar_int);
LS_SCRIPT_DECLARE_FUNC(subInts, scriptVar_int, scriptVar_int, scriptVar_int);

} // end script namespace
} // end ls namespace

#endif	/* __LS_SCRIPT_MATH_H__ */

