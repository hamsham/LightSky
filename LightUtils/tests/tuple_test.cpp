/* 
 * File:   tuple_test.cpp
 * Author: miles
 *
 * Created on Sep 17, 2015, 11:42:37 PM
 */

#include <iostream>

#include "lightsky/utils/tuple.h"

typedef ls::utils::tuple_t<int, float, char> ifc_tuple;
typedef ls::utils::tuple_t<int, float, float> iff_tuple;
typedef ls::utils::tuple_t<int, int, float> iif_tuple;

int main() {
    ifc_tuple ifc;
    
    *ifc.getObject<int>() = 42;
    *ifc.getObject<float>() = 4.2f;
    *ifc.getObject<char>() = 'a';
    
    std::cout
        << "The test tuple contains "
        << *ifc.getObject<int>() << ", "
        << *ifc.getObject<float>() << ", and "
        << *ifc.getObject<char>() << '.'
        << std::endl;
    
    *((int*)ifc.getObject(0)) = 24;
    *((float*)ifc.getObject(1)) = 2.4f;
    *((char*)ifc.getObject(2)) = 'b';
    
    std::cout
        << "The test tuple contains "
        << *ifc.getObject<int>() << ", "
        << *ifc.getObject<float>() << ", and "
        << *ifc.getObject<char>() << '.'
        << std::endl;
    
    return 0;
}

