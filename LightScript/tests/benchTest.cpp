/* 
 * File:   benchTest.cpp
 * Author: hammy
 *
 * Created on Dec 12, 2014, 7:26:20 AM
 */

#include <iostream>
#include <chrono>
#include <utility> /* std::move */
#include "lightsky/script/script.h"

/******************************************************************************
 * Benchmark Setup
******************************************************************************/
#define NUM_TEST_RUNS 1000000000
namespace chrono = std::chrono;
typedef chrono::steady_clock::time_point hr_time;
typedef chrono::milliseconds hr_prec;

/******************************************************************************
 * Generic Functions
******************************************************************************/
void printHello() {
    std::cout << "Hello World" << std::endl;
}

int addNums(int num1, int num2) {
    //std::cout << "Adding: " << num1 << '+' << num2 << '=' << num1+num2 << std::endl;
    return num1 + num2;
}

int subNums(int num1, int num2) {
    //std::cout << "Subtracting: " << num1 << '-' << num2 << '=' << num1-num2 << std::endl;
    return num1 - num2;
}

/******************************************************************************
 * Script Registration
******************************************************************************/
LS_SCRIPT_DECLARE_FUNC(printHello, void);
LS_SCRIPT_DEFINE_FUNC(printHello, void) {
    (void)pArgs;
    printHello();
};

/*
 * Bencharks without std::move
 */
LS_SCRIPT_DECLARE_FUNC(addNums, scriptVar_int, scriptVar_int, scriptVar_int);
LS_SCRIPT_DEFINE_FUNC(addNums, scriptVar_int, scriptVar_int, scriptVar_int) {
    LS_SCRIPT_PARAM(0, int) = addNums(LS_SCRIPT_PARAM(1, int), LS_SCRIPT_PARAM(2, int));
};

LS_SCRIPT_DECLARE_FUNC(subNums, scriptVar_int, scriptVar_int, scriptVar_int);
LS_SCRIPT_DEFINE_FUNC(subNums, scriptVar_int, scriptVar_int, scriptVar_int) {
    LS_SCRIPT_PARAM(0, int) = subNums(LS_SCRIPT_PARAM(1, int), LS_SCRIPT_PARAM(2, int));
};

/******************************************************************************
 * REFERENCE FUNCTION
******************************************************************************/
void nativeFunc() {
    int testVar1 = 42;
    int testVar2 = 77;
    int testVar3 = 13;
    
    hr_time t1, t2;
    t1 = chrono::steady_clock::now();
    int (*pFunc)(int, int) = &addNums;
    
    for (unsigned i = 0; i < NUM_TEST_RUNS; ++i) {
        testVar1 = pFunc(testVar2, testVar3);
        pFunc = i%2 == 0 ? &subNums : &addNums;
    }
    
    (void)testVar1;
    
    t2 = chrono::steady_clock::now();
    std::cout.precision(std::numeric_limits<double>::digits10);
    std::cout
        << "Native Benchmark: "
        << chrono::duration_cast< hr_prec >(t2 - t1).count() / 1000.0
        << std::endl;
    
    return;
}

/******************************************************************************
 * SCRIPTED BENCHMARK
******************************************************************************/
void scriptBench() {
    std::cout << "Add Hash: " << scriptHash_addNums << std::endl;
    std::cout << "Sub Hash: " << scriptHash_subNums << std::endl;
    std::cout << "Int Hash: " << scriptHash_int << std::endl;
    
    ls::script::gFuncFactory[scriptHash_addNums] = scriptFactory_addNums;
    ls::script::gFuncFactory[scriptHash_subNums] = scriptFactory_subNums;
    
    std::cout << "Global functor factory size: " << ls::script::gFuncFactory.size() << std::endl;
    std::cout << "Global functor factory size: " << ls::script::gVarFactory.size() << std::endl;
    
    ls::script::functor* const testFunc1 = ls::script::createFunctor(scriptHash_addNums);
    ls::script::functor* const testFunc2 = ls::script::createFunctor(scriptHash_subNums);
    
    ls::script::variable* const testVar1 = ls::script::createVariable(scriptHash_int);
    ls::script::variable* const testVar2 = ls::script::createVariable(scriptHash_int);
    ls::script::variable* const testVar3 = ls::script::createVariable(scriptHash_int);
/*
    ls::script::functor* const testFunc1 = scriptFactory_addNums();
    ls::script::functor* const testFunc2 = scriptFactory_subNums();
    
    ls::script::variable* const testVar1 = scriptFactory_int();
    ls::script::variable* const testVar2 = scriptFactory_int();
    ls::script::variable* const testVar3 = scriptFactory_int();
*/
    LS_SCRIPT_VAR_DATA(testVar1, int) = 42;
    LS_SCRIPT_VAR_DATA(testVar2, int) = 77;
    LS_SCRIPT_VAR_DATA(testVar3, int) = 13;
    
    testFunc1->setArg(0, testVar1);
    testFunc1->setArg(1, testVar2);
    testFunc1->setArg(2, testVar3);
    
    testFunc2->setArg(2, testVar3);
    testFunc2->setArg(0, testVar2);
    testFunc2->setArg(1, testVar1);
    
    testFunc1->setNextFunc(testFunc2);
    testFunc2->setNextFunc(testFunc1);
    
    if (!testFunc1->compile() || !testFunc2->compile()) {
        std::cerr << "Error: Unable to compile the test functions." << std::endl;
        return;
    }
    
    hr_time t1, t2;
    t1 = chrono::steady_clock::now();
    ls::script::functor* pFunc = testFunc1;
    
    for (unsigned i = 0; i < NUM_TEST_RUNS; ++i) {
        pFunc->run();
        pFunc = pFunc->getNextFunc();
    }
    
    t2 = chrono::steady_clock::now();
    std::cout.precision(std::numeric_limits<double>::digits10);
    std::cout
        << "Script benchmark: "
        << chrono::duration_cast< hr_prec >(t2 - t1).count() / 1000.0
        << std::endl;
    
    delete testFunc2;
    delete testFunc1;
    
    delete testVar3;
    delete testVar2;
    delete testVar1;
    
    return;
}

int main() {
    scriptBench();
    nativeFunc();
    
    return 0;
}