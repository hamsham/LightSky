/* 
 * File:   renderer.h
 * Author: hammy
 *
 * Created on January 25, 2014, 12:00 PM
 */

#ifndef __LS_MATRIX_STACK_H__
#define	__LS_MATRIX_STACK_H__

#include <stack>
#include "main.h"

enum matrix_type : unsigned {
    INVALID_MATRIX      = (unsigned)-1,
    PROJECTION_MATRIX   = 0,
    VIEW_MATRIX         = 1,
    MODEL_MATRIX        = 2,
    
    MAX_VALUE           = 3
};

class matrixStack {
    private:
        std::stack<math::mat4> stacks[matrix_type::MAX_VALUE];
        math::mat4 mvpMatrix = {1.f};
        
    public:
        /**
         * Cosntructor
         */
        matrixStack();
        
        /**
         * Copy Constructor -- DELETED
         */
        matrixStack(const matrixStack&) = delete;
        
        /**
        * Move Constructor
        * @param A reference to a temporary matrix stack
        */
        matrixStack(matrixStack&&);
        
        /**
         * Destructor
         * The matrix stack only accepts pre-constructed objects.
         */
        ~matrixStack();
        
        /**
         * Copy Operator -- DELETED
         */
        matrixStack& operator= (const matrixStack&) = delete;
        
        /**
         * Move Operator
         * @param A reference to a temporary matrix stack
         * @return A reference to *this
         */
        matrixStack& operator= (matrixStack&&);
        
        /**
         * Push a matrix onto the stack. The current matrix will be copied into
         * a new matrix and pushed onto the stack. This matrix this then
         * multiplied by the one passed into the function.
         * 
         * @param The type of matrix to be used on the stack.
         * @param A 4x4 matrix.
         */
        void pushMatrix(matrix_type, const math::mat4&);
        
        /**
         * Push an identity matrix onto the stack. The current matrix will be
         * stored and an identity matrix will be pushed onto the stack.
         * 
         * @param The type of matrix to be used on the stack.
         */
        void pushIdentity(matrix_type);
        
        /**
         * Push a matrix onto the stack. This function pushes a pre-constructed
         * matrix onto the stack. Unlike "pushMatrix(...)," this method does
         * not multiply the current matrix with the one being pushed.
         * 
         * @param The type of matrix to be used on the stack.
         * @param A 4x4 matrix.
         */
        void emplaceMatrix(matrix_type, const math::mat4&);
        
        /**
         * Remove a matrix from a specified stack.
         * @param The type of matrix to be removed from the stack.
         */
        void popMatrix(matrix_type);
        
        /**
         * Set the matrix on top of the stack to the one passed into the
         * function.
         * @param The type of matrix to set.
         * @param The matrix to be used on top of the stack
         */
        void loadMatrix(matrix_type, const math::mat4&);
        
        /**
         * Set the selected matrix to an identity matrix
         * @param The type of matrix to be reset.
         */
        void loadIdentity(matrix_type);
        
        /**
         * Multiply the selected matrix by the one passed into the function.
         * @param The type of matrix to multiply
         * @param the matrix to multiply against the on on the stack.
         */
        void multMatrix(matrix_type, const math::mat4&);
        
        /**
         * Get the current model matrix
         */
        const math::mat4& getMatrix(matrix_type mt) const {
            return stacks[mt].top();
        }
        
        /**
         * Multiply the stacks together
         */
        void constructMvp();
        
        /**
         * Get the MVP Matrix
         */
        const math::mat4& getMvpMatrix() const {
            return mvpMatrix;
        }
        
        /**
         * Clear a specific Stack
         */
        unsigned size(matrix_type mt) {
            return stacks[mt].size();
        }
};

#endif	/* __LS_MATRIX_STACK_H__ */

