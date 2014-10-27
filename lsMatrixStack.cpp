/* 
 * File:   matrixStack.cpp
 * Author: hammy
 * 
 * Created on January 25, 2014, 12:00 PM
 */

#include <utility>
#include "matrixStack.h"

/**
 * Constructor
 */
matrixStack::matrixStack() :
    stacks{
        std::stack<math::mat4>{}, // projections
        std::stack<math::mat4>{}, // view
        std::stack<math::mat4>{} // models
    },
    mvpMatrix{math::mat4(1.f)},
    vpMatrix{math::mat4(1.f)}
{
    stacks[PROJECTION_MATRIX].push(math::mat4(1.f));
    stacks[VIEW_MATRIX].push(math::mat4(1.f));
    stacks[MODEL_MATRIX].push(math::mat4(1.f));
}

/**
 * Move Constructor
 */
matrixStack::matrixStack(matrixStack&& ms) :
    stacks{
        std::move(ms.stacks[PROJECTION_MATRIX]),
        std::move(ms.stacks[VIEW_MATRIX]),
        std::move(ms.stacks[MODEL_MATRIX]),
    },
    mvpMatrix{std::move(ms.mvpMatrix)},
    vpMatrix{std::move(ms.vpMatrix)}
{}

/**
 * Destructor
 */
matrixStack::~matrixStack() {
}

/**
 * Move Operator
 */
matrixStack& matrixStack::operator =(matrixStack&& ms) {
    stacks[PROJECTION_MATRIX] = std::move(ms.stacks[PROJECTION_MATRIX]);
    stacks[VIEW_MATRIX] = std::move(ms.stacks[VIEW_MATRIX]);
    stacks[MODEL_MATRIX] = std::move(ms.stacks[MODEL_MATRIX]);
    
    mvpMatrix = ms.mvpMatrix;
    vpMatrix = ms.vpMatrix;
    
    return *this;
}

/**
 * Push a matrix onto the stack, multiplying it by the current matrix
 */
void matrixStack::pushMatrix(matrix_type mt, const math::mat4& m) {
    // debug modes need to make sure no invalid matrix types are being used.
    #ifdef LS_DEBUG
        if (mt >= matrix_type::MAX_VALUE) {
            LOG_ERR("Unknown matrix type pushed onto the stack: ", mt, '\n');
            return;
        }
    #endif
    
    stacks[mt].emplace(stacks[mt].top() * m);
}

/**
 * Push the identity matrix onto the stack
 */
void matrixStack::pushIdentity(matrix_type mt) {
    // debug modes need to make sure no invalid matrix types are being used.
    #ifdef LS_DEBUG
        if (mt >= matrix_type::MAX_VALUE) {
            LOG_ERR("Unknown matrix type pushed onto the stack: ", mt, '\n');
            return;
        }
    #endif
    
    stacks[mt].emplace(math::mat4{1.f});
}

/**
 * Push a matrix onto the stack without multiplying it by the current matrix.
 */
void matrixStack::emplaceMatrix(matrix_type mt, const math::mat4& m) {
    // debug modes need to make sure no invalid matrix types are being used.
    #ifdef LS_DEBUG
        if (mt >= matrix_type::MAX_VALUE) {
            LOG_ERR("Unknown matrix type pushed onto the stack: ", mt, '\n');
            return;
        }
    #endif
    
    stacks[mt].push(m);
}

/**
 * Set the matrix on top of the stack to the one passed into the function.
 */
void matrixStack::loadMatrix(matrix_type mt, const math::mat4& m) {
    stacks[mt].top() = m;
}

/**
 * Set the current matrix at the top of the stack to the identity matrix.
 */
void matrixStack::loadIdentity(matrix_type mt) {
    stacks[mt].top() = math::mat4(1.f);
}

/**
 * Pop a matrix from the stack.
 */
void matrixStack::popMatrix(matrix_type mt) {
    // debug modes need to make sure no invalid matrix types are being used.
    #ifdef LS_DEBUG
        if (mt >= matrix_type::MAX_VALUE) {
            LOG_ERR("Unknown matrix type popped off the stack: ", mt, '\n');
            return;
        }
    #endif
    
    stacks[mt].pop();
    
    if (stacks[mt].size() == 0) {
        stacks[mt].emplace(math::mat4{1.f});
    }
}
