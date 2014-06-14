/* 
 * File:   matrixStack.cpp
 * Author: hammy
 * 
 * Created on January 25, 2014, 12:00 PM
 */

#include <utility>
#include "lsMatrixStack.h"

/**
 * Constructor
 */
lsMatrixStack::lsMatrixStack() :
    stacks{
        std::stack<math::mat4>{}, // projections
        std::stack<math::mat4>{}, // view
        std::stack<math::mat4>{} // models
    },
    mvpMatrix{math::mat4(1.f)},
    vpMatrix{math::mat4(1.f)}
{
    stacks[LS_PROJECTION_MATRIX].push(math::mat4(1.f));
    stacks[LS_VIEW_MATRIX].push(math::mat4(1.f));
    stacks[LS_MODEL_MATRIX].push(math::mat4(1.f));
}

/**
 * Move Constructor
 */
lsMatrixStack::lsMatrixStack(lsMatrixStack&& ms) :
    stacks{
        std::move(ms.stacks[LS_PROJECTION_MATRIX]),
        std::move(ms.stacks[LS_VIEW_MATRIX]),
        std::move(ms.stacks[LS_MODEL_MATRIX]),
    },
    mvpMatrix{std::move(ms.mvpMatrix)},
    vpMatrix{std::move(ms.vpMatrix)}
{}

/**
 * Destructor
 */
lsMatrixStack::~lsMatrixStack() {
}

/**
 * Move Operator
 */
lsMatrixStack& lsMatrixStack::operator =(lsMatrixStack&& ms) {
    stacks[LS_PROJECTION_MATRIX] = std::move(ms.stacks[LS_PROJECTION_MATRIX]);
    stacks[LS_VIEW_MATRIX] = std::move(ms.stacks[LS_VIEW_MATRIX]);
    stacks[LS_MODEL_MATRIX] = std::move(ms.stacks[LS_MODEL_MATRIX]);
    
    mvpMatrix = ms.mvpMatrix;
    vpMatrix = ms.vpMatrix;
    
    return *this;
}

/**
 * Push a matrix onto the stack, multiplying it by the current matrix
 */
void lsMatrixStack::pushMatrix(ls_matrix_t mt, const math::mat4& m) {
    // debug modes need to make sure no invalid matrix types are being used.
    #ifdef LS_DEBUG
        if (mt >= LS_MAX_MATRIX_STACKS) {
            LS_LOG_ERR("Unknown matrix type pushed onto the stack: ", mt, '\n');
            return;
        }
    #endif
    
    stacks[mt].emplace(stacks[mt].top() * m);
}

/**
 * Push the identity matrix onto the stack
 */
void lsMatrixStack::pushIdentity(ls_matrix_t mt) {
    // debug modes need to make sure no invalid matrix types are being used.
    #ifdef LS_DEBUG
        if (mt >= LS_MAX_MATRIX_STACKS) {
            LS_LOG_ERR("Unknown matrix type pushed onto the stack: ", mt, '\n');
            return;
        }
    #endif
    
    stacks[mt].emplace(math::mat4{1.f});
}

/**
 * Push a matrix onto the stack without multiplying it by the current matrix.
 */
void lsMatrixStack::emplaceMatrix(ls_matrix_t mt, const math::mat4& m) {
    // debug modes need to make sure no invalid matrix types are being used.
    #ifdef LS_DEBUG
        if (mt >= LS_MAX_MATRIX_STACKS) {
            LS_LOG_ERR("Unknown matrix type pushed onto the stack: ", mt, '\n');
            return;
        }
    #endif
    
    stacks[mt].push(m);
}

/**
 * Set the matrix on top of the stack to the one passed into the function.
 */
void lsMatrixStack::loadMatrix(ls_matrix_t mt, const math::mat4& m) {
    stacks[mt].top() = m;
}

/**
 * Set the current matrix at the top of the stack to the identity matrix.
 */
void lsMatrixStack::loadIdentity(ls_matrix_t mt) {
    stacks[mt].top() = math::mat4(1.f);
}

/**
 * Pop a matrix from the stack.
 */
void lsMatrixStack::popMatrix(ls_matrix_t mt) {
    // debug modes need to make sure no invalid matrix types are being used.
    #ifdef LS_DEBUG
        if (mt >= LS_MAX_MATRIX_STACKS) {
            LS_LOG_ERR("Unknown matrix type popped off the stack: ", mt, '\n');
            return;
        }
    #endif
    
    stacks[mt].pop();
    
    if (stacks[mt].size() == 0) {
        stacks[mt].emplace(math::mat4{1.f});
    }
}
