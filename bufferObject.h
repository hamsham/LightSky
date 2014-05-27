/* 
 * File:   bufferObject.h
 * Author: miles
 *
 * Created on March 31, 2014, 8:00 PM
 */

#ifndef __LS_BUFFER_OBJECT__
#define	__LS_BUFFER_OBJECT__

#include <Gl/glew.h>

/**
 * This enumeration outlines the basic types of buffers are available for use
 * in a render context. It will be updated as more features are written.
 */
enum buffer_t : GLenum {
    ARRAY_BUFFER                = GL_ARRAY_BUFFER,
    ELEMENT_BUFFER              = GL_ELEMENT_ARRAY_BUFFER,
    TEXTURE_BUFFER              = GL_TEXTURE_BUFFER,
    TRANSFORM_FEEDBACK_BUFFER   = GL_TRANSFORM_FEEDBACK_BUFFER,
    UNIFORM_BUFFER              = GL_UNIFORM_BUFFER
};

/**
 * Different usage parameters that determine how a buffer may be used.
 */
enum buffer_usage_t : GLenum {
    STATIC_READ     = GL_STATIC_READ,
    STATIC_DRAW     = GL_STATIC_DRAW,
    STATIC_COPY     = GL_STATIC_COPY,
    
    STREAM_READ     = GL_STREAM_READ,
    STREAM_DRAW     = GL_STREAM_DRAW,
    STREAM_COPY     = GL_STREAM_COPY,
    
    DYNAMIC_READ    = GL_DYNAMIC_READ,
    DYNAMIC_DRAW    = GL_DYNAMIC_DRAW,
    DYNAMIC_COPY    = GL_DYNAMIC_COPY
    
};

/**
 * Memory mapping bit flags used for DMA transfers between CPU and GPU memory.
 */
enum buffer_access_t : GLbitfield {
    MAP_READ_BIT                = GL_MAP_READ_BIT,
    MAP_WRITE_BIT               = GL_MAP_WRITE_BIT,
    MAP_INVALIDATE_RANGE_BIT    = GL_MAP_INVALIDATE_RANGE_BIT,
    MAP_INVALIDATE_BUFFER_BIT   = GL_MAP_INVALIDATE_BUFFER_BIT,
    MAP_FLUSH_EXPLICIT_BIT      = GL_MAP_FLUSH_EXPLICIT_BIT,
    MAP_UNSYNCHRONIZED_BIT      = GL_MAP_UNSYNCHRONIZED_BIT,
    MAP_PERSISTENT_BIT          = GL_MAP_PERSISTENT_BIT,
    MAP_COHERENT_BIT            = GL_MAP_COHERENT_BIT
};

/**
 * Useful typedefs
 */
template<buffer_t> class bufferObject;
typedef bufferObject<ARRAY_BUFFER>      vertexBuffer;
typedef bufferObject<ELEMENT_BUFFER>    indexBuffer;
typedef bufferObject<ARRAY_BUFFER>      uvBuffer;
typedef bufferObject<ARRAY_BUFFER>      colorBuffer;

/**
 * Vertex Buffer Object
 */
template <buffer_t bufferType>
class bufferObject {
    private:
        /**
         * A handle to the vertex buffer object residing on the GPU.
         */
        GLuint vbo = 0;
        
    public:
        /**
         * Constructor.
         */
        constexpr bufferObject() {}
        
        /**
         * Copy Constructor - DELETED
         */
        bufferObject(const bufferObject&) = delete;
        
        /**
         * Move Constructor
         * This moves the data contained within the constructor parameter into
         * *this. No copies are performed.
         * 
         * @param vb
         * A vertex buffer object whose data will be moved into *this.
         */
        bufferObject(bufferObject&& vb) :
            vbo{vb.vbo}
        {
            vb.vbo = 0;
        }
        
        /**
         * Destructor
         * Releases all resources used by *this.
         */
        ~bufferObject() {
            terminate();
        }
        
        /**
         * Copy Operator - DELETED
         */
        bufferObject& operator=(const bufferObject&) = delete;
        
        /**
         * Move Operator
         * This moves the data contained within the method parameter into *this.
         * No copies are performed.
         * 
         * @param vb
         * A vertex buffer object whose data will be moved into *this.
         */
        bufferObject& operator=(bufferObject&& vb) {
            vbo = vb.vbo;
            vb.vbo = 0;
            return *this;
        }
        
        /**
         * Buffer initialization.
         * Generates a vertex buffer object on the GPY that will be used to
         * contain a large pool of data.
         * 
         * @return true if the buffer was successfully created, false if not.
         */
        inline bool init() {
            glGenBuffers(1, &vbo);
            return vbo != 0;
        }
        
        /**
         * Terminate the vertex buffer and release all of its resources back to
         * the GPU.
         */
        inline void terminate() {
            glDeleteBuffers(1, &vbo);
            vbo = 0;
        }
        
        /**
         * Determine if there is data used by this object
         * 
         * @returns true if this object has data residing on GPU memory, false
         * if not.
         */
        inline bool isValid() const {
            return vbo != 0;
        }
        
        /**
         * Bind this vertex buffer to the current global rendering context.
         */
        inline void bind() const {
            glBindBuffer(bufferType, vbo);
        }
        
        /**
         * Unbind this vertex buffer object from the current render context.
         */
        inline void unbind() const {
            glBindBuffer(bufferType, 0);
        }
        
        /**
         * Set the data within the buffer to whatever is set at "pData."
         * 
         * @param size
         * The size, in bytes, of the data that the buffer should contain.
         * 
         * @param pData
         * A pointer to the data contained within the buffer. This argument can
         * be NULL to indicate that an empty buffer should be allocated and
         * will have its contents filled later.
         * 
         * @param usage
         * The usage of this buffer. This can indicate that the buffer is
         * static, should be used to stream data occasionally, or the data is
         * dynamic and will be updated on a regular basis.
         * 
         */
        inline void setData(ptrdiff_t size, const void* pData, buffer_usage_t usage) const {
            glBufferData(bufferType, size, pData, usage);
        }
        
        /**
         * Modify the data within a buffer to contain whatever is in "pData."
         * at an offset of a specified amount of bytes.
         * 
         * @param size
         * The size, in bytes, of the data that the buffer should contain.
         * 
         * @param offset
         * The offset, in bytes, to where the data should be placed in *this.
         * 
         * @param pData
         * A pointer to the data contained within the buffer.
         * 
         */
        inline void setSubData(ptrdiff_t offset, ptrdiff_t size, const void* pData) const {
            glBufferSubData(bufferType, offset, size, pData);
        }
        
        /**
         * Map the contents of the buffer into memory in order to perform a DMA
         * transfer of data to the GPU.
         * 
         * @param offset
         * The offset, in bytes, to where the data should be placed in *this.
         * 
         * @param range
         * The range of bytes that will be mapped to memory.
         * 
         * @param access
         * Specifies a combination of access flags indicating the desired
         * access to the range of memory.
         * 
         * @returns void*
         * A pointer to the location in memory where the data will be mapped.
         * A NULL pointer may be returned, indicating an error that may have
         * occurred while attempting to map the buffer to memory.
         * 
         */
        inline void* mapData(ptrdiff_t offset, ptrdiff_t range, buffer_access_t access) const {
            return glMapBufferRange(bufferType, offset, range, access);
        }
        
        /**
         * Notify the GPU that all data has been uploaded to the requested
         * location in memory and that the DMA transfer can now be performed.
         */
        inline bool unmapData() const {
            return glUnmapBuffer(bufferType);
        }
};

#endif	/* __LS_BUFFER_OBJECT__ */

