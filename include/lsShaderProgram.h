/* 
 * File:   lsShaderProgram.h
 * Author: hammy
 *
 * Created on January 21, 2014, 6:54 PM
 */

#ifndef __LS_SHADER_PROGRAM_H__
#define	__LS_SHADER_PROGRAM_H__

#include <string>
#include <GL/glew.h>

#include "lsSetup.h"
#include "lsShaderObject.h"

/**
 * Shader Program
 * 
 * Represents a combination of OpenGL vertex, fragment, and geometry shader
 * objects.
 */
class lsShaderProgram {
    private:
        /**
         * A handle to the GPU-side shader program within OpenGL.
         */
        GLuint programId = 0;

    public:
        /**
         * Constructor
         */
        lsShaderProgram();
        
        /**
         * Copy Constructor -- Deleted
         */
        lsShaderProgram(const lsShaderProgram&) = delete;
        
        /**
         * Move Constructor
         * Copy the handle to the shader object owned by the input argument,
         * reset the moved object's shader handle to 0.
         */
        lsShaderProgram(lsShaderProgram&&);
        
        /**
         * Copy Operator -- Deleted
         */
        lsShaderProgram& operator=(const lsShaderProgram&) = delete;
        
        /**
         * Move the values of the input argument and reset the moved object's
         * values to 0.
         * 
         * @param A shaderObject to move
         * @return A reference to *this
         */
        lsShaderProgram& operator=(lsShaderProgram&&);
        
        /**
         * Destroy this object and free any GPU memory it uses.
         */
        ~lsShaderProgram();
        
        /**
         * Free all memory used by this shader object.
         */
        void terminate();
        
        /**
         * Attach a shader object to the program
         */
        bool attachShaders(const vertexShader& vs, const fragmentShader& fs);
        
        /**
         * Attach a shader object to the program
         */
        bool attachShaders(
            const vertexShader& vs,
            const geometryShader& gs,
            const fragmentShader& fs
        );
        
        /**
         * Link a final program with its objects
         */
        bool link();
        
        /**
         * Bind this program to the current context
         */
        void bind();
        
        /**
         * Unbind this program from the context.
         */
        void unbind();
        
        /**
         * Bind a vertex attribute to a shader
         */
        void bindAttribute(GLuint index, const GLchar* const name);
        
        /**
         * Get the location of a vert6ex attribute
         */
        void getAttribute(const GLchar* const name) const;
        
        /**
         * Get the location of a uniform variable.
         * 
         * @return GLint
         * A positive value to indicate the uniform's location in OpenGL or
         * -1 for an invalid uniform index.
         */
        GLint getUniformLocation(const GLchar* const name) const;
        
        /**
         * Get information about an active uniform located in a shader.
         * 
         * @param index - indicates the index of the uniform to be queried.
         * 
         * @param varSize - indicates the number of elements contained within
         * the uniform. This will be a value of 1 for all variables that are not
         * arrays.
         * 
         * @param varType - used to determine the variable's data type; such as
         * an int, float, sampler, matrix, or sampler array.
         * 
         * @returns the name of the variable as it is known in the shader
         * source code.
         * 
         */
        std::string getUniformInfo(int index, GLint* const varSize, GLenum* const varType) const;
        
        /**
         * Set a single uniform integer variable
         */
        void setUniformValue(GLint uniformId, int val);
        
        /**
         * Set two uniform integer variables
         */
        void setUniformValue(GLint uniformId, int val0, int val1);
        
        /**
         * Set three uniform integer variables
         */
        void setUniformValue(GLint uniformId, int val0, int val1, int val2);
        
        /**
         * Set four uniform integer variables
         */
        void setUniformValue(GLint uniformId, int val0, int val1, int val2, int val3);
        
        /**
         * Set a uniform 2d vector of integers
         */
        void setUniformValue(GLint uniformId, const math::vec2i& val);
        
        /**
         * Set a uniform 3d vector of integers
         */
        void setUniformValue(GLint uniformId, const math::vec3i& val);
        
        /**
         * Set a uniform 4d vector of integers
         */
        void setUniformValue(GLint uniformId, const math::vec4i& val);
        
        /**
         * Set a single uniform unsigned int variable
         */
        void setUniformValue(GLint uniformId, unsigned val);
        
        /**
         * Set two uniform unsigned int variables
         */
        void setUniformValue(GLint uniformId, unsigned val0, unsigned val1);
        
        /**
         * Set three uniform unsigned int variables
         */
        void setUniformValue(GLint uniformId, unsigned val0, unsigned val1, unsigned val2);
        
        /**
         * Set four uniform unsigned int variables
         */
        void setUniformValue(GLint uniformId, unsigned val0, unsigned val1, unsigned val2, unsigned val3);
        
        /**
         * Set a uniform 2d vector of unsigned ints
         */
        void setUniformValue(GLint uniformId, const math::vec2ui& val);
        
        /**
         * Set a uniform 3d vector of unsigned ints
         */
        void setUniformValue(GLint uniformId, const math::vec3ui& val);
        
        /**
         * Set a uniform 4d vector of unsigned ints
         */
        void setUniformValue(GLint uniformId, const math::vec4ui& val);
        
        /**
         * Set a single uniform float variable
         */
        void setUniformValue(GLint uniformId, float val);
        
        /**
         * Set two uniform float variables
         */
        void setUniformValue(GLint uniformId, float val0, float val1);
        
        /**
         * Set three uniform float variables
         */
        void setUniformValue(GLint uniformId, float val0, float val1, float val2);
        
        /**
         * Set four uniform float variables
         */
        void setUniformValue(GLint uniformId, float val0, float val1, float val2, float val3);
        
        /**
         * Set a uniform 2d vector of floats
         */
        void setUniformValue(GLint uniformId, const math::vec2& val);
        
        /**
         * Set a uniform 3d vector of floats
         */
        void setUniformValue(GLint uniformId, const math::vec3& val);
        
        /**
         * Set a uniform 4d vector of floats
         */
        void setUniformValue(GLint uniformId, const math::vec4& val);
        
        /**
         * Set a uniform 2d matrix
         */
        void setUniformValue(GLint uniformId, const math::mat2& val, bool transpose = false);
        
        /**
         * Set a uniform 3d matrix
         */
        void setUniformValue(GLint uniformId, const math::mat3& val, bool transpose = false);
        
        /**
         * Set a uniform 4d matrix
         */
        void setUniformValue(GLint uniformId, const math::mat4& val, bool transpose = false);
        
        /**
         * Bind data to a fragment shader
         */
        void bindFragDataLocation(GLuint color, const GLchar* const name);
        
        /**
         * Bind data to a fragment shader
         */
        void bindFragDataLocationIndex(GLuint color, GLuint index, const GLchar* const name);
        
        /**
         * Query the bindings of color indices to a user-defined varying out variable
         */
        GLint getFragDataIndex(const GLchar* const name) const;
        
        /**
         * Query the bindings of color numbers to user-defined varying out variables
         */
        GLint getFragDataLocation(const GLchar* const name) const;
};

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/*
 * Bind this program to the current context
 */
inline void lsShaderProgram::bind() {
    glUseProgram(programId);
}

/*
 * Unbind this program from the context.
 */
inline void lsShaderProgram::unbind() {
    glUseProgram(0);
}

/*
 * Bind a vertex attribute to a shader
 */
inline void lsShaderProgram::bindAttribute(GLuint index, const GLchar* const name) {
    glBindAttribLocation(programId, index, name);
}

/*
 * Get the location of a vert6ex attribute
 */
inline void lsShaderProgram::getAttribute(const GLchar* const name) const {
    glGetAttribLocation(programId, name);
}

/*
 * Get the location of a uniform variable.
 * 
 * @return GLint
 * A positive value to indicate the uniform's location in OpenGL or
 * -1 for an invalid uniform index.
 */
inline GLint lsShaderProgram::getUniformLocation(const GLchar* const name) const {
    return glGetUniformLocation(programId, name);
}

/*
 * Set a single uniform integer variable
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, int val) {
    glUniform1i(uniformId, val);
}

/*
 * Set two uniform integer variables
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, int val0, int val1) {
    glUniform2i(uniformId, val0, val1);
}

/*
 * Set three uniform integer variables
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, int val0, int val1, int val2) {
    glUniform3i(uniformId, val0, val1, val2);
}

/*
 * Set four uniform integer variables
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, int val0, int val1, int val2, int val3) {
    glUniform4i(uniformId, val0, val1, val2, val3);
}

/*
 * Set a uniform 2d vector of integers
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::vec2i& val) {
    glUniform2iv(uniformId, 1, val.v);
}

/*
 * Set a uniform 3d vector of integers
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::vec3i& val) {
    glUniform3iv(uniformId, 1, val.v);
}

/*
 * Set a uniform 4d vector of integers
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::vec4i& val) {
    glUniform4iv(uniformId, 1, val.v);
}

/*
 * Set a single uniform unsigned int variable
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, unsigned val) {
    glUniform1ui(uniformId, val);
}

/*
 * Set two uniform unsigned int variables
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, unsigned val0, unsigned val1) {
    glUniform2ui(uniformId, val0, val1);
}

/*
 * Set three uniform unsigned int variables
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, unsigned val0, unsigned val1, unsigned val2) {
    glUniform3ui(uniformId, val0, val1, val2);
}

/*
 * Set four uniform unsigned int variables
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, unsigned val0, unsigned val1, unsigned val2, unsigned val3) {
    glUniform4ui(uniformId, val0, val1, val2, val3);
}

/*
 * Set a uniform 2d vector of unsigned ints
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::vec2ui& val) {
    glUniform2uiv(uniformId, 1, val.v);
}

/*
 * Set a uniform 3d vector of unsigned ints
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::vec3ui& val) {
    glUniform3uiv(uniformId, 1, val.v);
}

/*
 * Set a uniform 4d vector of unsigned ints
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::vec4ui& val) {
    glUniform4uiv(uniformId, 1, val.v);
}

/*
 * Set a single uniform float variable
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, float val) {
    glUniform1f(uniformId, val);
}

/*
 * Set two uniform float variables
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, float val0, float val1) {
    glUniform2f(uniformId, val0, val1);
}

/*
 * Set three uniform float variables
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, float val0, float val1, float val2) {
    glUniform3f(uniformId, val0, val1, val2);
}

/*
 * Set four uniform float variables
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, float val0, float val1, float val2, float val3) {
    glUniform4f(uniformId, val0, val1, val2, val3);
}

/*
 * Set a uniform 2d vector of floats
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::vec2& val) {
    glUniform2fv(uniformId, 1, val.v);
}

/*
 * Set a uniform 3d vector of floats
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::vec3& val) {
    glUniform3fv(uniformId, 1, val.v);
}

/*
 * Set a uniform 4d vector of floats
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::vec4& val) {
    glUniform4fv(uniformId, 1, val.v);
}

/*
 * Set a uniform 2d matrix
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::mat2& val, bool transpose) {
    glUniformMatrix2fv(uniformId, 1, transpose, &val[0]);
}

/*
 * Set a uniform 3d matrix
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::mat3& val, bool transpose) {
    glUniformMatrix3fv(uniformId, 1, transpose, &val[0]);
}

/*
 * Set a uniform 4d matrix
 */
inline void lsShaderProgram::setUniformValue(GLint uniformId, const math::mat4& val, bool transpose) {
    glUniformMatrix4fv(uniformId, 1, transpose, &val[0]);
}

/*
 * Bind data to a fragment shader
 */
inline void lsShaderProgram::bindFragDataLocation(GLuint color, const GLchar* const name) {
    glBindFragDataLocation(programId, color, name);
}

/*
 * Bind data to a fragment shader
 */
inline void lsShaderProgram::bindFragDataLocationIndex(GLuint color, GLuint index, const GLchar* const name) {
    glBindFragDataLocationIndexed(programId, color, index, name);
}

/*
 * Query the bindings of color indices to a user-defined varying out variable
 */
inline GLint lsShaderProgram::getFragDataIndex(const GLchar* const name) const {
    return glGetFragDataIndex(programId, name);
}

/*
 * Query the bindings of color numbers to user-defined varying out variables
 */
inline GLint lsShaderProgram::getFragDataLocation(const GLchar* const name) const {
    return glGetFragDataLocation(programId, name);
}

#endif	/* __LS_SHADER_PROGRAM_H__ */

