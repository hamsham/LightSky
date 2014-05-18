/* 
 * File:   shaderProgram.cpp
 * Author: hammy
 * 
 * Created on January 21, 2014, 6:54 PM
 */

#include <utility>
#include "shaderProgram.h"

/******************************************************************************
 * Move Constructor
 *****************************************************************************/
shaderProgram::shaderProgram(shaderProgram&& tempProgram) :
    programId{tempProgram.programId}
{
    tempProgram.programId = 0;
}

/******************************************************************************
 * Move Operator
 *****************************************************************************/
shaderProgram& shaderProgram::operator=(shaderProgram&& tempProgram) {
    programId = tempProgram.programId;
    tempProgram.programId = 0;
    return *this;
}

/******************************************************************************
 * Termination
 *****************************************************************************/
void shaderProgram::terminate() {
    glDeleteProgram(programId);
    programId = 0;
}

/******************************************************************************
 * Attaching Shaders
 *****************************************************************************/
bool shaderProgram::attachShaders(GLuint vertId, GLuint fragId) {
    if (programId != 0) {
        glDeleteProgram(programId);
    }
    else {
        programId = glCreateProgram();
        if (programId == 0) {
            LOG_ERR("Unable to create a GLSL Program Handle.\n");
            return false;
        }
    }
    
    glAttachShader(programId, vertId);
    glAttachShader(programId, fragId);
    return true;
}

/******************************************************************************
 * Attaching Shaders
 *****************************************************************************/
bool shaderProgram::attachShaders(GLuint vertId, GLuint geomId, GLuint fragId) {
    if (programId != 0) {
        glDeleteProgram(programId);
    }
    else {
        programId = glCreateProgram();
        if (programId == 0) {
            LOG_ERR("Unable to create a GLSL Program Handle.\n");
            return false;
        }
    }
    
    glAttachShader(programId, vertId);
    glAttachShader(programId, geomId);
    glAttachShader(programId, fragId);
    return true;
}

/******************************************************************************
 * Linking
 *****************************************************************************/
bool shaderProgram::link() {
    GLint linkResult = 0;
    
    glLinkProgram(programId);
    glGetProgramiv(programId, GL_LINK_STATUS, &linkResult);
    
    if (linkResult != GL_TRUE) {
        GLint logLength = 0;
        GLchar* logData = nullptr;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
        logData = new GLchar[logLength+1];
        logData[logLength] = '\0';

        glGetProgramInfoLog(programId, logLength, nullptr, logData);
        LOG_ERR("Program linkage error:\n", logData, '\n');

        delete [] logData;
        glDeleteProgram(programId);
        programId = 0;
        
        return false;
    }
    
    return true;
}

/*
 * Uniform information
 */
std::string shaderProgram::getUniformInfo(
    int index,
    GLint* const varSize,
    GLenum* const varType
) const {
    GLint maxVarNameLen = 0;
    
    glGetProgramiv(
        programId,
        GL_ACTIVE_UNIFORM_MAX_LENGTH,
        &maxVarNameLen
    );
    
    if (maxVarNameLen < 1) {
        return std::string{};
    }
    
    GLchar* varName = nullptr;
    GLsizei* varNameLen = nullptr;
    
    glGetActiveUniform(
        programId, index, maxVarNameLen,
        varNameLen, varSize, varType, varName
    );
    
    if (varNameLen == nullptr || *varNameLen < 1 || varName == nullptr) {
        return std::string{};
    }
    
    return std::string{varName, (std::size_t)varNameLen};
}
