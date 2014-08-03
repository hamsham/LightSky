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

#include "lsSetup.h"

//-----------------------------------------------------------------------------
//      Enumerations
//-----------------------------------------------------------------------------
/**
 * Enumeration to determine the type of shader that should be created on the GPU
 */
enum ls_shader_t : unsigned {
    LS_VERTEX_SHADER    = GL_VERTEX_SHADER,
    LS_GEOMETRY_SHADER  = GL_GEOMETRY_SHADER,
    LS_FRAGMENT_SHADER  = GL_FRAGMENT_SHADER
};

//-----------------------------------------------------------------------------
//      Classes
//-----------------------------------------------------------------------------
/**
 * Shader Object Base Class
 * 
 * Shader objects are attached to programs in order to manipulate the GPU
 */
template <ls_shader_t shaderType>
class lsShaderObject {
    friend class lsShaderProgram;
    
    private:
        /**
         * Handle to the GPU-side shader object.
         */
        GLuint objectId = 0;
        
    public:
        /**
         * Constructor
         */
        lsShaderObject();
        
        /**
         * Copy Constructor -- Deleted
         */
        lsShaderObject(const lsShaderObject&) = delete;
        
        /**
         * Move Constructor
         * Copy the handle to the shader object owned by the input argument,
         * reset the moved object's shader handle to 0.
         */
        lsShaderObject(lsShaderObject&&);
        
        /**
         * Copy Operator -- Deleted
         */
        lsShaderObject& operator=(const lsShaderObject&) = delete;
        
        /**
         * Move the values of the input argument and reset the moved object's
         * values to 0.
         * 
         * @param A shaderObject to move
         * @return A reference to *this
         */
        lsShaderObject& operator=(lsShaderObject&&);
        
        /**
         * Destroy this object and free any GPU memory it uses.
         */
        ~lsShaderObject();
        
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
        bool compile(const char* data, int size = 0);
        
        /**
         * Get a shader's GPU-assigned ID
         */
        GLuint getId() const;
};

//-----------------------------------------------------------------------------
//      Template Definitions
//-----------------------------------------------------------------------------
/*
 * Constructor
 */
template <ls_shader_t shaderType>
lsShaderObject<shaderType>::lsShaderObject() {
}
        
/*
 * Move Constructor
 */
template <ls_shader_t shaderType>
lsShaderObject<shaderType>::lsShaderObject(lsShaderObject&& tempShader) :
    objectId{tempShader.objectId}
{
    tempShader.objectId = 0;
}
    
/*
 * Destructor
 */
template <ls_shader_t shaderType>
lsShaderObject<shaderType>::~lsShaderObject() {
    terminate();
}
        
/*
 * Move the values of the input argument and reset the moved object's
 * values to 0.
 */
template <ls_shader_t shaderType>
lsShaderObject<shaderType>& lsShaderObject<shaderType>::operator=(
    lsShaderObject&& tempShader
) {
    objectId = tempShader.objectId;
    tempShader.objectId = 0;
    return *this;
}
        
/*
 * Free all memory used by this shader object.
 */
template <ls_shader_t shaderType>
inline void lsShaderObject<shaderType>::terminate() {
    glDeleteShader(objectId);
    objectId = 0;
}

/*
 * Shader Loading
 */
template <ls_shader_t shaderType>
bool lsShaderObject<shaderType>::compile(const char* data, int size) {
    LS_LOG_MSG("Attempting to load a shader object.");
    
    terminate();
    
    GLuint shaderId;
    shaderId = glCreateShader(shaderType);
    
    // If the size is zero, opengl will just look for null-termination in the data
    if (size == 0) {
        glShaderSource(shaderId, 1, &data, nullptr);
    }
    else {
        glShaderSource(shaderId, 1, &data, &size);
    }
    
    glCompileShader(shaderId);
    
    GLint shaderStatus;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderStatus);
    
    if (shaderStatus != GL_TRUE) {
        GLint infoLogLength = 0;
        GLchar* infoLogData = nullptr;

        // Get the length of the shader's error log
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

        // Allocate some memory to temporarilt store the log data
        infoLogData = new GLchar[infoLogLength+1]; // +1 for null-termination
        infoLogData[infoLogLength] = '\0';

        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, infoLogData);
        LS_LOG_ERR("\tShader Compilation error:\n", infoLogData, '\n');

        delete [] infoLogData;
        glDeleteShader(shaderId);
        return false;
    }
    
    objectId = shaderId;
    
    LS_LOG_MSG("\tSuccessfully loaded a shader object.\n");
    return true;
}

/*
 * Get a shader's GPU-assigned ID
 */
template <ls_shader_t shaderType>
inline GLuint lsShaderObject<shaderType>::getId() const {
    return objectId;
}

//-----------------------------------------------------------------------------
//      Typedefs and external templates
//-----------------------------------------------------------------------------
LS_DECLARE_CLASS_TYPE(vertexShader, lsShaderObject, LS_VERTEX_SHADER);
LS_DECLARE_CLASS_TYPE(geometryShader, lsShaderObject, LS_GEOMETRY_SHADER);
LS_DECLARE_CLASS_TYPE(fragmentShader, lsShaderObject, LS_FRAGMENT_SHADER);

#endif	/* __LS_SHADER_OBJECT_H__ */

