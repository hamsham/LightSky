/* 
 * File:   lsMatrixStack.h
 * Author: hammy
 *
 * Created on January 25, 2014, 12:00 PM
 */

#ifndef __LS_MATRIX_STACK_H__
#define	__LS_MATRIX_STACK_H__

#include <stack>

#include "lsSetup.h"

//-----------------------------------------------------------------------------
//      Enumerations
//-----------------------------------------------------------------------------
/**
 * Enumeration to facilitate matrix manipulations within the matrix stack,
 */
enum ls_matrix_t : unsigned {
    LS_INVALID_MATRIX       = (unsigned)-1,
    LS_PROJECTION_MATRIX    = 0,
    LS_VIEW_MATRIX          = 1,
    LS_MODEL_MATRIX         = 2,
    
    LS_MAX_MATRIX_STACKS    = 3
};

//-----------------------------------------------------------------------------
//      Classes
//-----------------------------------------------------------------------------
/**
 * The Matrix Stack
 * 
 * This object can be used to make life MUCH easier when dealing with matrices
 * within OpenGL. Usage was designed to be fairly close to the original OpenGL
 * 1.0 spec.
 */
class lsMatrixStack {
    private:
        std::stack<math::mat4> stacks[3]; // model, view, & projection
        math::mat4 mvpMatrix = {1.f};
        math::mat4 vpMatrix = {1.f};
        
    public:
        /**
         * Cosntructor
         */
        lsMatrixStack();
        
        /**
         * Copy Constructor -- DELETED
         */
        lsMatrixStack(const lsMatrixStack&) = delete;
        
        /**
        * Move Constructor
        * @param A reference to a temporary matrix stack
        */
        lsMatrixStack(lsMatrixStack&&);
        
        /**
         * Destructor
         * The matrix stack only accepts pre-constructed objects.
         */
        ~lsMatrixStack();
        
        /**
         * Copy Operator -- DELETED
         */
        lsMatrixStack& operator= (const lsMatrixStack&) = delete;
        
        /**
         * Move Operator
         * @param A reference to a temporary matrix stack
         * @return A reference to *this
         */
        lsMatrixStack& operator= (lsMatrixStack&&);
        
        /**
         * Push a matrix onto the stack. The current matrix will be copied into
         * a new matrix and pushed onto the stack. This matrix this then
         * multiplied by the one passed into the function.
         * 
         * @param The type of matrix to be used on the stack.
         * @param A 4x4 matrix.
         */
        void pushMatrix(ls_matrix_t, const math::mat4&);
        
        /**
         * Push an identity matrix onto the stack. The current matrix will be
         * stored and an identity matrix will be pushed onto the stack.
         * 
         * @param The type of matrix to be used on the stack.
         */
        void pushIdentity(ls_matrix_t);
        
        /**
         * Push a matrix onto the stack. This function pushes a pre-constructed
         * matrix onto the stack. Unlike "pushMatrix(...)," this method does
         * not multiply the current matrix with the one being pushed.
         * 
         * @param The type of matrix to be used on the stack.
         * @param A 4x4 matrix.
         */
        void emplaceMatrix(ls_matrix_t, const math::mat4&);
        
        /**
         * Remove a matrix from a specified stack.
         * @param The type of matrix to be removed from the stack.
         */
        void popMatrix(ls_matrix_t);
        
        /**
         * Set the matrix on top of the stack to the one passed into the
         * function.
         * @param The type of matrix to set.
         * @param The matrix to be used on top of the stack
         */
        void loadMatrix(ls_matrix_t, const math::mat4&);
        
        /**
         * Set the selected matrix to an identity matrix
         * @param The type of matrix to be reset.
         */
        void loadIdentity(ls_matrix_t);
        
        /**
         * Multiply the selected matrix by the one passed into the function.
         * @param The type of matrix to multiply
         * @param the matrix to multiply against the on on the stack.
         */
        void multMatrix(ls_matrix_t, const math::mat4&);
        
        /**
         * Get the current model matrix
         */
        const math::mat4& getMatrix(ls_matrix_t mt) const;
        
        /**
         * Multiply the model, view, and projection stacks together
         */
        void constructMvp();
        
        /**
         * Multiply only the view and projection stacks together
         */
        void constructVp();
        
        /**
         * Get the MVP Matrix
         */
        const math::mat4& getMvpMatrix() const;
        
        /**
         * Get the VP Matrix
         */
        const math::mat4& getVpMatrix() const;
        
        /**
         * Clear a specific Stack
         */
        unsigned size(ls_matrix_t);
};

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/**
 * Multiply the selected matrix with the one passed into the function.
 */
inline void lsMatrixStack::multMatrix(ls_matrix_t mt, const math::mat4& m) {
    stacks[mt].top() = m * stacks[mt].top();
}

/**
 * Multiply the matrix stack
 */
inline void lsMatrixStack::constructMvp() {
    this->constructVp();
    mvpMatrix = vpMatrix * stacks[LS_MODEL_MATRIX].top();
}

/**
 * Multiply the view and projection stacks
 */
inline void lsMatrixStack::constructVp() {
    vpMatrix = stacks[LS_PROJECTION_MATRIX].top() * stacks[LS_VIEW_MATRIX].top();
}

/*
 * Get the current model matrix
 */
inline const math::mat4& lsMatrixStack::getMatrix(ls_matrix_t mt) const {
    return stacks[mt].top();
}

/*
 * Get the MVP Matrix
 */
inline const math::mat4& lsMatrixStack::getMvpMatrix() const {
    return mvpMatrix;
}

/*
 * Get the VP Matrix
 */
inline const math::mat4& lsMatrixStack::getVpMatrix() const {
    return vpMatrix;
}

/*
 * Clear a specific Stack
 */
inline unsigned lsMatrixStack::size(ls_matrix_t mt) {
    return stacks[mt].size();
}

#endif	/* __LS_MATRIX_STACK_H__ */

