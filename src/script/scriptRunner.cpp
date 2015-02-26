/* 
 * File:   scriptRunner.cpp
 * Author: hammy
 * 
 * Created on February 25, 2015, 9:42 PM
 */

#include <utility> // std::move()

#include "lightsky/setup/macros.h"

#include "lightsky/script/scriptFunctor.h"
#include "lightsky/script/scriptRunner.h"

namespace ls {
namespace script {

/*-------------------------------------
 * Destructor
-------------------------------------*/
scriptRunner::~scriptRunner() {
}

/*-------------------------------------
 * Run Constructor
-------------------------------------*/
scriptRunner::scriptRunner(functor* const pEntryFunction, const functor* const pSentinel) {
    run(pEntryFunction, pSentinel);
}

/*-------------------------------------
 * Basic Constructor
-------------------------------------*/
scriptRunner::scriptRunner() {
}

/*-------------------------------------
 * Copy Constructor
-------------------------------------*/
scriptRunner::scriptRunner(const scriptRunner&) {
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
scriptRunner::scriptRunner(scriptRunner&&) {
}

/*-------------------------------------
 * Copy Constructor
-------------------------------------*/
scriptRunner& scriptRunner::operator=(const scriptRunner&) {
    return *this;
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
scriptRunner& scriptRunner::operator=(scriptRunner&&) {
    return *this;
}

/*-------------------------------------
 * Script Running
-------------------------------------*/
bool scriptRunner::run(functor* const pEntryFunction, const functor* const pSentinel) {
    functor* pFunc = pEntryFunction;
    
    while (pFunc != pSentinel) {
        pFunc->run();
        pFunc = pFunc->getNextFunc();
    }
    
    return true;
}

} // end script namespace
} // end ls namespace
