/* 
 * File:   benchTest.cpp
 * Author: hammy
 *
 * Created on Dec 12, 2014, 7:26:20 AM
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <utility> /* std::move */
#include "lightsky/script/Script.h"

template <class data_t> using lsPointer = ls::script::Pointer_t<data_t>;

using lsVariable = ls::script::Variable;
using ls::script::create_variable;
using ls::script::destroy_variable;

using lsFunctor = ls::script::Functor;
using ls::script::create_functor;
using ls::script::destroy_functor;

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
    lsPointer<lsFunctor>&& testFunc1 = create_functor(ls::script::ScriptHash_AddInts);
    lsPointer<lsFunctor>&& testFunc2 = create_functor(ls::script::ScriptHash_SubInts);
    
    lsPointer<lsVariable>&& testVar1 = create_variable(ls::script::ScriptHash_int);
    lsPointer<lsVariable>&& testVar2 = create_variable(ls::script::ScriptHash_int);
    lsPointer<lsVariable>&& testVar3 = create_variable(ls::script::ScriptHash_int);
    
    LS_SCRIPT_VAR_DATA(testVar1, int) = 42;
    LS_SCRIPT_VAR_DATA(testVar2, int) = 77;
    LS_SCRIPT_VAR_DATA(testVar3, int) = 13;
    
    testFunc1->set_arg(0, testVar1);
    testFunc1->set_arg(1, testVar2);
    testFunc1->set_arg(2, testVar3);
    
    testFunc2->set_arg(2, testVar3);
    testFunc2->set_arg(0, testVar2);
    testFunc2->set_arg(1, testVar1);
    
    testFunc1->set_next_func(testFunc2);
    testFunc2->set_next_func(testFunc1);
    
    if (!testFunc1->compile() || !testFunc2->compile()) {
        std::cerr << "Error: Unable to compile the test functions." << std::endl;
        return;
    }
    
    hr_time t1, t2;
    t1 = chrono::steady_clock::now();
    lsFunctor* pFunc = testFunc1.get();
    
    for (unsigned i = 0; i < NUM_TEST_RUNS; ++i) {
        pFunc->run();
        pFunc = pFunc->get_next_func();
    }
    
    t2 = chrono::steady_clock::now();
    std::cout.precision(std::numeric_limits<double>::digits10);
    std::cout
        << "Script benchmark: "
        << chrono::duration_cast< hr_prec >(t2 - t1).count() / 1000.0
        << std::endl;
    
    destroy_functor(testFunc2);
    destroy_functor(testFunc1);
    
    destroy_variable(testVar3);
    destroy_variable(testVar2);
    destroy_variable(testVar1);
    
    return;
}

int main() {
    for (unsigned i = 5; i-->0;) {
        std::thread t2{&nativeFunc};
        std::thread t1{&scriptBench};

        t2.join();
        t1.join();
    }
    
    return 0;
}