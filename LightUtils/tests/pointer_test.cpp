/* 
 * File:   pointer_test.cpp
 * Author: miles
 *
 * Created on Nov 10, 2014, 10:34:16 PM
 * 
 * Testing the use of a std::unique_ptr
 * 
 * g++ -std=c++11 -Wall -Wextra -pedantic -pedantic-errors unique_ptr.cpp -o unique_ptr
 */

#include <iostream>
#include <memory>

#include "lightsky/utils/pointer.h"

/**------------------------------------
 * Test Structure
-------------------------------------*/
struct point {
    float x, y, z;
    
    point() {
        std::cout << "Constructing a point!" << std::endl;
    }
    
    point(const point& p) {
        std::cout << "Copy-Constructing a point!" << std::endl;
        x = p.x;
        y = p.y;
        z = p.z;
    }
    
    point(point&& p) {
        std::cout << "Move-Constructing a point!" << std::endl;
        x = p.x;
        y = p.y;
        z = p.z;
    }
    
    point& operator=(const point& p) {
        std::cout << "Copying a point!" << std::endl;
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }
    
    point& operator=(point&& p) {
        std::cout << "Moving a point!" << std::endl;
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }
    
    ~point() {
        std::cout << "Destroying a point!" << std::endl;
    }
};

/*-------------------------------------
 * Typedef's to test
-------------------------------------*/
//#define point_ptr std::unique_ptr

#define point_ptr ls::utils::pointer
/**------------------------------------
 * Main()
-------------------------------------*/
int main() {
    std::cout << "Creating a new point:\n\t";
    point_ptr<point[]> pPoint{new point[42]};
    
    std::cout << "Creating a second point:\n\t";
    pPoint = point_ptr<point[]>{new point[42]};
    
    *pPoint = point{};
    pPoint[0] = point{};
    
    std::cout << "Sizeof unique point pointer: " << sizeof(point_ptr<point[]>) << std::endl;
    
    return 0;
}