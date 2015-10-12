/* 
 * File:   newsimpletest.cpp
 * Author: hammy
 *
 * Created on Mar 22, 2015, 8:03:41 PM
 */

#include <iostream>

#include "lightsky/script/Script.h"

/*-----------------------------------------------------------------------------
 * Test Script File
-----------------------------------------------------------------------------*/
#ifndef TEST_FILE
    #define TEST_FILE u8R"***(test_file.lss)***"
#endif

/*-----------------------------------------------------------------------------
 * Namespacing setup
-----------------------------------------------------------------------------*/
template <class data_t> using lsPointer = ls::script::Pointer_t<data_t>;

using lsVariable = ls::script::Variable;
using ls::script::create_variable;
using ls::script::destroy_variable;

using lsFunctor = ls::script::Functor;
using ls::script::create_functor;
using ls::script::destroy_functor;

using ls::script::ScriptRunner;
using ls::script::VariableMap_t;
using ls::script::FunctorMap_t;

/*-----------------------------------------------------------------------------
 * Function Entry Point
-----------------------------------------------------------------------------*/
namespace ls {
namespace script {
// dummy value to get the entry points
LS_SCRIPT_DECLARE_FUNC(Entry, void);

LS_SCRIPT_DEFINE_FUNC(Entry, void) {
    (void)pArgs;
};
} // end script namespace
} // end ls namespace

/*-----------------------------------------------------------------------------
 * Verify that the functors compile.
-----------------------------------------------------------------------------*/
void validateScripts(FunctorMap_t& funcMap) {
    for (std::pair<lsFunctor* const, lsPointer<lsFunctor>>& funcIter : funcMap) {
        LS_ASSERT(funcIter.second->compile());
    }
}

/*-----------------------------------------------------------------------------
 * Generate the test maps
-----------------------------------------------------------------------------*/
void generateScripts(VariableMap_t& varMap, FunctorMap_t& funcMap) {
    lsPointer<lsFunctor> testFunc1 = create_functor(ls::script::ScriptHash_AddInts);
    lsPointer<lsFunctor> testFunc2 = create_functor(ls::script::ScriptHash_SubInts);
    lsPointer<lsFunctor> testFunc3 = create_functor(ls::script::ScriptHash_MulInts);
    lsPointer<lsFunctor> testFunc4 = create_functor(ls::script::ScriptHash_DivInts);
    lsPointer<lsFunctor> testEntry1 = create_functor(ls::script::ScriptHash_Entry);
    
    lsPointer<lsVariable> testVar1 = create_variable(ls::script::ScriptHash_int);
    lsPointer<lsVariable> testVar2 = create_variable(ls::script::ScriptHash_int);
    lsPointer<lsVariable> testVar3 = create_variable(ls::script::ScriptHash_int);
    lsPointer<lsVariable> testVar4 = create_variable(ls::script::ScriptHash_string);
    
    LS_SCRIPT_VAR_DATA(testVar1, int) = 1;
    LS_SCRIPT_VAR_DATA(testVar2, int) = 2;
    LS_SCRIPT_VAR_DATA(testVar3, int) = 0; // dummy value
    LS_SCRIPT_VAR_DATA(testVar4, string) = "Hello World!";
    
    testEntry1->set_next_func(testFunc1);
    
    testFunc1->set_arg(0, testVar1); // param 1 = 1
    testFunc1->set_arg(1, testVar2); // param 2 = 2
    testFunc1->set_arg(2, testVar3); // return value should equal 1+2=3
    testFunc1->set_next_func(testFunc2);
    
    testFunc2->set_arg(0, testVar1);
    testFunc2->set_arg(1, testVar2);
    testFunc2->set_arg(2, testVar2); // should equal 1-2=-3
    testFunc2->set_next_func(testFunc3);
    
    testFunc3->set_arg(0, testVar1);
    testFunc3->set_arg(1, testVar2);
    testFunc3->set_arg(2, testVar2); // should equal 1*2=2
    testFunc3->set_next_func(testFunc4);
    
    testFunc4->set_arg(0, testVar1);
    testFunc4->set_arg(1, testVar2);
    testFunc4->set_arg(2, testVar2); // should equal 1/2=1 (int division)
    testFunc4->set_next_func(nullptr);
    
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
void saveScripts(const VariableMap_t& varImporter, const FunctorMap_t& funcImporter) {
    LS_ASSERT(ls::script::save_script_file(TEST_FILE, varImporter, funcImporter));
}

/*-----------------------------------------------------------------------------
 * Save the script maps
-----------------------------------------------------------------------------*/
void loadScripts(VariableMap_t& varImporter, FunctorMap_t& funcImporter) {
    LS_ASSERT(ls::script::load_script_file(TEST_FILE, varImporter, funcImporter));
    
    ls::script::remap_script_keys(varImporter, funcImporter);
}

/*-----------------------------------------------------------------------------
 * Run the scripts
-----------------------------------------------------------------------------*/
bool runScripts(VariableMap_t& varMap, FunctorMap_t& funcMap) {
    ScriptRunner runner{};
    
    ls::script::Functor* pEntryFunc = nullptr;
    
    for (std::pair<lsFunctor* const, lsPointer<lsFunctor>>& funcIter : funcMap) {
        lsPointer<lsFunctor>& func = funcIter.second;
        
        if (func->get_script_subtype() == ls::script::ScriptHash_Entry) {
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
        
        if (pVar->get_script_subtype() == ls::script::ScriptHash_int) {
            std::cout << '\t' << LS_SCRIPT_VAR_DATA(pVar, int) << std::endl;
        }
        else if (pVar->get_script_subtype() == ls::script::ScriptHash_string) {
            std::cout << '\t' << LS_SCRIPT_VAR_DATA(pVar, string) << std::endl;
        }
    }
    
    return true;
}

/*-----------------------------------------------------------------------------
 * Main()
-----------------------------------------------------------------------------*/
int main() {
    VariableMap_t varMap{};
    FunctorMap_t funcMap{};
    
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

