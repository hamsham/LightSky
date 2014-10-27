/* 
 * File:   shaderObject.h
 * Author: hammy
 *
 * Created on January 21, 2014, 6:54 PM
 */

#ifndef __LS_SHADER_OBJECT_H__
#define	__LS_SHADER_OBJECT_H__

#include <utility>
#include <GL/glew.h>
#include "main.h"

/******************************************************************************
 * Shader types
 *****************************************************************************/
enum shaderType : unsigned {
    VERTEX_SHADER   = GL_VERTEX_SHADER,
    GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

template <shaderType>
class shaderObject_t;
typedef shaderObject_t<VERTEX_SHADER>    vertexShader;
typedef shaderObject_t<GEOMETRY_SHADER>  geometryShader;
typedef shaderObject_t<FRAGMENT_SHADER>  fragmentShader;

/******************************************************************************
 * Shader Object Base Class
 * Shader objects are attached to programs in order to manipulate the GPU
 *****************************************************************************/
class shaderObject {
    friend class shaderProgram;
    
    protected:
        GLuint objectId = 0;
        
        /**
         * Compile a shader of a specific type
         * @param type
         * @param data
         * @param size
         * @return True if the shader compiled successfully
         */
        bool compile(shaderType type, const char* data, int size);
        
    public:
        /**
         * Constructor
         */
        shaderObject() {}
        
        /**
         * Copy Constructor -- Deleted
         */
        shaderObject(const shaderObject&) = delete;
        
        /**
         * Move Constructor
         * Copy the handle to the shader object owned by the input argument,
         * reset the moved object's shader handle to 0.
         */
        shaderObject(shaderObject&&);
        
        /**
         * Copy Operator -- Deleted
         */
        shaderObject& operator=(const shaderObject&) = delete;
        
        /**
         * Move the values of the input argument and reset the moved object's
         * values to 0.
         * 
         * @param A shaderObject to move
         * @return A reference to *this
         */
        shaderObject& operator=(shaderObject&&);
        
        /**
         * Destroy this object and free any GPU memory it uses.
         */
        ~shaderObject() { terminate(); }
        
        /**
         * Free all memory used by this shader object.
         */
        void terminate();
        
        /**
         * Compile a shader and put it into GPU memory.
         * 
         * @param The type of shader that will be used by this object.
         * 
         * @param data A pointer to a string which contains the shader's textual
         * content.
         * 
         * @param size the size, in bytes, of the shader's text data. Let this
         * remain zero if you are sure that the data string is null-terminated.
         * 
         * @return True if the shader was successfully compiled.
         */
        virtual bool compile(const char* data, int size) = 0;
        
        /**
         * Get a shader's ID
         */
        inline GLuint getShaderId() const {
            return objectId;
        }
};

/******************************************************************************
 * Shader type to be specialized for each shader type
 *****************************************************************************/
template <shaderType type>
class shaderObject_t final : public shaderObject {
    public:
        /**
         * Constructor
         */
        shaderObject_t() {}
        
        /**
         * Copy Constructor -- Deleted
         */
        shaderObject_t(const shaderObject_t&) = delete;
        
        /**
         * Move Constructor
         */
        shaderObject_t(shaderObject_t&& so) :
            shaderObject(std::move(so))
        {}
        
        /**
         * Copy Operator -- Deleted
         */
        shaderObject_t& operator=(const shaderObject_t&) = delete;
        
        /**
         * Move the values of the input argument and reset the moved object's
         * values to 0.
         * 
         * @param A shaderObject to move
         * @return A reference to *this
         */
        shaderObject_t& operator=(shaderObject_t&& so) {
            shaderObject::operator=(std::move(so));
            return *this;
        }
        
        /**
         * Compile a shader
         * @return True if the shader compiled successfully.
         */
        inline bool compile(const char* data, int size = 0) override {
            return shaderObject::compile(type, data, size);
        }
};

#endif	/* __LS_SHADER_OBJECT_H__ */

