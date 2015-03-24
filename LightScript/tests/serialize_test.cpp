/* 
 * File:   newsimpletest.cpp
 * Author: hammy
 *
 * Created on Mar 22, 2015, 8:03:41 PM
 */

#include <iostream>

#include "lightsky/script/script.h"

/*-----------------------------------------------------------------------------
 * Test Script File
-----------------------------------------------------------------------------*/
#ifndef TEST_FILE
    #define TEST_FILE u8R"***(test_file.lss)***"
#endif

/*-----------------------------------------------------------------------------
 * Namespacing setup
-----------------------------------------------------------------------------*/
template <class data_t> using lsPointer = ls::script::pointer_t<data_t>;

using lsVariable = ls::script::variable;
using ls::script::createVariable;
using ls::script::destroyVariable;

using lsFunctor = ls::script::functor;
using ls::script::createFunctor;
using ls::script::destroyFunctor;

using ls::script::scriptRunner;
using ls::script::variableMap_t;
using ls::script::functorMap_t;

/*-----------------------------------------------------------------------------
 * Function Entry Point
-----------------------------------------------------------------------------*/
namespace ls {
namespace script {
// dummy value to get the entry points
LS_SCRIPT_DECLARE_FUNC(entry, void);

LS_SCRIPT_DEFINE_FUNC(entry, void) {
    (void)pArgs;
};
} // end script namespace
} // end ls namespace

/*-----------------------------------------------------------------------------
 * Verify that the functors compile.
-----------------------------------------------------------------------------*/
void validateScripts(functorMap_t& funcMap) {
    for (std::pair<lsFunctor* const, lsPointer<lsFunctor>>& funcIter : funcMap) {
        LS_ASSERT(funcIter.second->compile());
    }
}

/*-----------------------------------------------------------------------------
 * Generate the test maps
-----------------------------------------------------------------------------*/
void generateScripts(variableMap_t& varMap, functorMap_t& funcMap) {
    lsPointer<lsFunctor> testFunc1 = createFunctor(ls::script::scriptHash_addInts);
    lsPointer<lsFunctor> testFunc2 = createFunctor(ls::script::scriptHash_subInts);
    lsPointer<lsFunctor> testFunc3 = createFunctor(ls::script::scriptHash_mulInts);
    lsPointer<lsFunctor> testFunc4 = createFunctor(ls::script::scriptHash_divInts);
    lsPointer<lsFunctor> testEntry1 = createFunctor(ls::script::scriptHash_entry);
    
    lsPointer<lsVariable> testVar1 = createVariable(ls::script::scriptHash_int);
    lsPointer<lsVariable> testVar2 = createVariable(ls::script::scriptHash_int);
    lsPointer<lsVariable> testVar3 = createVariable(ls::script::scriptHash_int);
    lsPointer<lsVariable> testVar4 = createVariable(ls::script::scriptHash_string);
    
    LS_SCRIPT_VAR_DATA(testVar1, int) = 1;
    LS_SCRIPT_VAR_DATA(testVar2, int) = 2;
    LS_SCRIPT_VAR_DATA(testVar3, int) = 0; // dummy value
    LS_SCRIPT_VAR_DATA(testVar4, string) = "Hello World!";
    
    testEntry1->setNextFunc(testFunc1);
    
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
    
    validateScripts(funcMap);
    
    varMap[testVar1] = std::move(testVar1);
    varMap[testVar2] = std::move(testVar2);
    varMap[testVar3] = std::move(testVar3);
    varMap[testVar4] = std::move(testVar4);
    
    funcMap[testFunc1] = std::move(testFunc1);
    funcMap[testFunc2] = std::move(testFunc2);
    funcMap[testFunc3] = std::move(testFunc3);
    funcMap[testFunc4] = std::move(testFunc4);
    funcMap[testEntry1] = std::move(testEntry1);
}

/*-----------------------------------------------------------------------------
 * Save the script maps
-----------------------------------------------------------------------------*/
void saveScripts(const variableMap_t& varImporter, const functorMap_t& funcImporter) {
    LS_ASSERT(ls::script::saveScriptFile(TEST_FILE, varImporter, funcImporter));
}

/*-----------------------------------------------------------------------------
 * Save the script maps
-----------------------------------------------------------------------------*/
void loadScripts(variableMap_t& varImporter, functorMap_t& funcImporter) {
    LS_ASSERT(ls::script::loadScriptFile(TEST_FILE, varImporter, funcImporter));
    
    ls::script::remapScriptKeys(varImporter, funcImporter);
}

/*-----------------------------------------------------------------------------
 * Run the scripts
-----------------------------------------------------------------------------*/
bool runScripts(variableMap_t& varMap, functorMap_t& funcMap) {
    scriptRunner runner{};
    
    ls::script::functor* pEntryFunc = nullptr;
    
    for (std::pair<lsFunctor* const, lsPointer<lsFunctor>>& funcIter : funcMap) {
        lsPointer<lsFunctor>& func = funcIter.second;
        
        if (func->getScriptSubType() == ls::script::scriptHash_entry) {
            pEntryFunc = func.get();
            break;
        }
    }
    
    LS_ASSERT(pEntryFunc != nullptr);
    
    runner.run(pEntryFunc);
    
    std::cout << "Successfully ran the script tests." << std::endl;
    std::cout << "The final variable values are:" << std::endl;
    
    for (std::pair<lsVariable* const, lsPointer<lsVariable>>& varIter : varMap) {
        lsPointer<lsVariable>& pVar = varIter.second;
        
        if (pVar->getScriptSubType() == ls::script::scriptHash_int) {
            std::cout << '\t' << LS_SCRIPT_VAR_DATA(pVar, int) << std::endl;
        }
        else if (pVar->getScriptSubType() == ls::script::scriptHash_string) {
            std::cout << '\t' << LS_SCRIPT_VAR_DATA(pVar, string) << std::endl;
        }
    }
    
    return true;
}

/*-----------------------------------------------------------------------------
 * Main()
-----------------------------------------------------------------------------*/
int main() {
    variableMap_t varMap{};
    functorMap_t funcMap{};
    
    generateScripts(varMap, funcMap);
    validateScripts(funcMap);
    runScripts(varMap, funcMap);
    saveScripts(varMap, funcMap);
    
    varMap.clear();
    funcMap.clear();
    
    loadScripts(varMap, funcMap);
    validateScripts(funcMap);
    runScripts(varMap, funcMap);

    return 0;
}

