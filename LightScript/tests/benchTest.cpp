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

int addNums(int x, int y) {
    return x + y;
}

int subNums(int x, int y) {
    return x - y;
}

/******************************************************************************
 * REFERENCE FUNCTION
******************************************************************************/
void nativeFunc() {
    int testVar1 = 42;
    int testVar2 = 77;
    int testVar3 = 13;
    
    hr_time t1, t2;
    t1 = chrono::steady_clock::now();
    int (*pFunc[2])(int, int) = {&addNums, &subNums};
    
    for (unsigned i = 0; i < NUM_TEST_RUNS; ++i) {
        testVar1 = (*pFunc[i%2])(testVar2, testVar3);
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
    ls::script::functor* const testFunc1 = ls::script::createFunctor(ls::script::scriptHash_addInts);
    ls::script::functor* const testFunc2 = ls::script::createFunctor(ls::script::scriptHash_subInts);
    
    ls::script::variable* const testVar1 = ls::script::createVariable(ls::script::scriptHash_int);
    ls::script::variable* const testVar2 = ls::script::createVariable(ls::script::scriptHash_int);
    ls::script::variable* const testVar3 = ls::script::createVariable(ls::script::scriptHash_int);
    
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