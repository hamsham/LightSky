/* 
 * File:   sequence_test.cpp
 * Author: hammy
 *
 * Created on Feb 26, 2015, 12:38:57 AM
 */

#include <cassert>
#include <iostream>
#include "lightsky/script/script.h"

template <class data_t> using lsPointer = ls::script::pointer_t<data_t>;

using lsVariable = ls::script::variable;
using ls::script::createVariable;
using ls::script::destroyVariable;

using lsFunctor = ls::script::functor;
using ls::script::createFunctor;
using ls::script::destroyFunctor;

using ls::script::scriptRunner;

int main() {
    lsPointer<lsFunctor> testFunc1 = createFunctor(ls::script::scriptHash_addInts);
    lsPointer<lsFunctor> testFunc2 = createFunctor(ls::script::scriptHash_subInts);
    lsPointer<lsFunctor> testFunc3 = createFunctor(ls::script::scriptHash_mulInts);
    lsPointer<lsFunctor> testFunc4 = createFunctor(ls::script::scriptHash_divInts);
    
    lsPointer<lsVariable> testVar1 = createVariable(ls::script::scriptHash_int);
    lsPointer<lsVariable> testVar2 = createVariable(ls::script::scriptHash_int);
    lsPointer<lsVariable> testVar3 = createVariable(ls::script::scriptHash_int);
    
    LS_SCRIPT_VAR_DATA(testVar1, int) = 1;
    LS_SCRIPT_VAR_DATA(testVar2, int) = 2;
    LS_SCRIPT_VAR_DATA(testVar3, int) = 0; // dummy value
    
    testFunc1->setArg(0, testVar1); // param 1 = 1
    testFunc1->setArg(1, testVar2); // param 2 = 2
    testFunc1->setArg(2, testVar3); // return value should equal 1+2=3
    testFunc1->setNextFunc(testFunc2);
    
    testFunc2->setArg(0, testVar1);
    testFunc2->setArg(1, testVar2);
    testFunc2->setArg(2, testVar2); // should equal 1-2=-3
    testFunc2->setNextFunc(testFunc3);
    
    testFunc3->setArg(0, testVar1);
    testFunc3->setArg(1, testVar2);
    testFunc3->setArg(2, testVar2); // should equal 1*2=2
    testFunc3->setNextFunc(testFunc4);
    
    testFunc4->setArg(0, testVar1);
    testFunc4->setArg(1, testVar2);
    testFunc4->setArg(2, testVar2); // should equal 1/2=1 (int division)
    testFunc4->setNextFunc(nullptr);
    
    scriptRunner runner{testFunc1};
    
    assert(LS_SCRIPT_VAR_DATA(testVar3, int) == 1/2);
    
    std::cout << "Successfully ran the script tests." << std::endl;
    std::cout << "The final variable values are:" << std::endl;
    std::cout << "\tVariable 1: " << LS_SCRIPT_VAR_DATA(testVar1, int) << std::endl;
    std::cout << "\tVariable 2: " << LS_SCRIPT_VAR_DATA(testVar2, int) << std::endl;
    std::cout << "\tVariable 3: " << LS_SCRIPT_VAR_DATA(testVar3, int) << std::endl;
    
    return 0;
}

