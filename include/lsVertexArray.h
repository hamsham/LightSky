/* 
 * File:   vertexArray.h
 * Author: hammy
 *
 * Created on February 7, 2014, 8:01 PM
 */

#ifndef __LS_VERTEX_ARRAY__
#define	__LS_VERTEX_ARRAY__

#include <Gl/glew.h>

class lsVertexArray {
    private:
        /**
         * A handle to the vertex array object residing on the GPU.
         */
        unsigned vao = 0;

    public:
        /**
         * Constructor.
         */
        constexpr lsVertexArray() {}
        
        /**
         * Copy Constructor - DELETED
         */
        lsVertexArray(const lsVertexArray&) = delete;
        
        /**
         * Move Constructor
         * This moves the data contained within the constructor parameter into
         * *this. No copies are performed.
         * 
         * @param va
         * A vertexArray object whose data will be moved into *this.
         */
        lsVertexArray(lsVertexArray&& va) :
            vao{va.vao}
        {
            va.vao = 0;
        }
        
        /**
         * Destructor
         * Releases all resources used by *this.
         */
        ~lsVertexArray() {
            terminate();
        }
        
        /**
         * Copy Operator - DELETED
         */
        lsVertexArray& operator=(const lsVertexArray&) = delete;
        
        /**
         * Move Operator
         * This moves the data contained within the method parameter into *this.
         * No copies are performed.
         * 
         * @param va
         * A vertexArray object whose data will be moved into *this.
         */
        lsVertexArray& operator=(lsVertexArray&& va) {
            vao = va.vao;
            va.vao = 0;
            return *this;
        }
        
        /**
         * Array initialization.
         * Generates a vertex array object on the GPY that will be used to
         * describe the memory layout of a data buffer.
         * 
         * @return true if the buffer was successfully created, false if not.
         */
        inline bool init() {
            if (vao != 0) {
                terminate();
            }
            
            glGenVertexArrays(1, &vao);
            return vao != 0;
        }
        
        /**
         * Terminate the vertex array and release all of its resources back to
         * the GPU.
         */
        inline void terminate() {
            glDeleteVertexArrays(1, &vao);
            vao = 0;
        }
        
        /**
         * Determine if there is data used by this object
         * 
         * @returns true if this object has data residing on GPU memory, false
         * if not.
         */
        inline bool isValid() const {
            return vao != 0;
        }
        
        /**
         * Get the GPU-assigned ID for this VAO
         * 
         * @return an unsigned integral type representing this VAO.
         */
        inline unsigned getId() const {
            return vao;
        }
        
        /**
         * Enable an attribute contained within the vertex array.
         * @param index
         */
        inline void enableAttrib(int index) const {
            glEnableVertexAttribArray(index);
        }
        
        /**
         * Disable an attribute contained in the array.
         * @param index
         */
        inline void disableAttrib(int index) const {
            glDisableVertexAttribArray(index);
        }
        
        /**
         * Set the memory layout/offset of an attribute in the vertex array.
         * @param index
         * The array attribute to be modified
         * 
         * @param elementsPerVert
         * The number of elements contained within the vertex.
         * 
         * @param type
         * The openGL data type.
         * 
         * @param normalize
         * Should the data be normalized to a float?
         * 
         * @param vertexOffset
         * An offset, in bytes, between each vertex in the array.
         * 
         * @param elementOffset
         * A byte-offset from the start of each vertex.
         * 
         */
        inline void setAttribOffset(
            unsigned index,
            unsigned elementsPerVert,
            int type,
            bool normalize,
            int vertexOffset,
            const void* elementOffset
        ) const {
            glVertexAttribPointer(index, elementsPerVert, type, normalize, vertexOffset, elementOffset);
        }
        
        /**
         * Get the byte-offset to an element in the array.
         * 
         * @param index
         * An element's index in the array.
         * 
         * @return a byte-indexed offset to the attribute.
         */
        inline void* getAttribOffset(int index) const {
            void* offset;
            glGetVertexAttribPointerv(index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
            return offset;
        }
        
        /**
         * Set the rate at which an attribute should repeat during instanced
         * draw calls on the GPU.
         * 
         * @param index
         * The attribute's index within the array.
         * 
         * @param instancesPerAttrib
         * The number of instances that should be drawn before repeating
         * another render of the array attribute.
         */
        inline void setAttribInstanceRate(int index, int instancesPerAttrib) const {
            glVertexAttribDivisor(index, instancesPerAttrib);
        }
        
        /**
         * Bind this vertex array to the current global rendering context.
         */
        inline void bind() const {
            glBindVertexArray(vao);
        }
        
        /**
         * Unbind this vertex array object from the current render context.
         */
        inline void unbind() const {
            glBindVertexArray(0);
        }
};

#endif	/* __LS_VERTEX_ARRAY__ */
