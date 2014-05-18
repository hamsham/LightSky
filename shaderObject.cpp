/* 
 * File:   shaderObject.cpp
 * Author: hammy
 * 
 * Created on January 21, 2014, 6:54 PM
 */

#include "shaderObject.h"

/******************************************************************************
 * Move Constructor
 *****************************************************************************/
shaderObject::shaderObject(shaderObject&& tempShader) :
    objectId{tempShader.objectId}
{
    tempShader.objectId = 0;
}

/******************************************************************************
 * Move Operator
 *****************************************************************************/
shaderObject& shaderObject::operator=(shaderObject&& tempShader) {
    objectId = tempShader.objectId;
    tempShader.objectId = 0;
    return *this;
}

/******************************************************************************
 * Termination
 *****************************************************************************/
void shaderObject::terminate() {
    glDeleteShader(objectId);
    objectId = 0;
}

/******************************************************************************
 * Data Loading
 *****************************************************************************/
bool shaderObject::compile(shaderType type, const char* data, int size) {
    GLint shaderStatus;
    GLuint shaderId;
    
    terminate();
    
    shaderId = glCreateShader(type);
    
    // If the size is zero, opengl will just look for null-termination in the data
    if (size == 0) {
        glShaderSource(shaderId, 1, &data, nullptr);
    }
    else {
        glShaderSource(shaderId, 1, &data, &size);
    }
    
    glCompileShader(shaderId);
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
        LOG_ERR("Shader Compilation error:\n", infoLogData, '\n');

        delete [] infoLogData;
        glDeleteShader(shaderId);
        return false;
    }
    
    objectId = shaderId;
    return true;
}
