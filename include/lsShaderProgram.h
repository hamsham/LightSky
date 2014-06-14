/* 
 * File:   shaderProgram.h
 * Author: hammy
 *
 * Created on January 21, 2014, 6:54 PM
 */

#ifndef __LS_SHADER_PROGRAM_H__
#define	__LS_SHADER_PROGRAM_H__

#include <string>
#include <GL/glew.h>
#include "lsShaderObject.h"

class lsShaderProgram {
    private:
        GLuint programId = 0;

    public:
        /**
         * Constructor
         */
        lsShaderProgram() {}
        
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
        ~lsShaderProgram() {terminate();}
        
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
        inline void bind() const {
            glUseProgram(programId);
        }
        
        ///////////////////////////////////////////////////////////////////////
        //                      Shader Attributes
        ///////////////////////////////////////////////////////////////////////
        /**
         * Bind a vertex attribute to a shader
         */
        inline void bindAttribute(GLuint index, const GLchar* const name) const {
            glBindAttribLocation(programId, index, name);
        }
        
        /**
         * Get the location of a vert6ex attribute
         */
        inline void getAttribute(const GLchar* const name) const {
            glGetAttribLocation(programId, name);
        }
        
        ///////////////////////////////////////////////////////////////////////
        //                      Shader Uniforms
        ///////////////////////////////////////////////////////////////////////
        /**
         * Get the location of a uniform variable.
         * 
         * @return GLint
         * A positive value to indicate the uniform's location in OpenGL or
         * -1 for an invalid uniform index.
         */
        inline GLint getUniformLocation(const GLchar* const name) const {
            return glGetUniformLocation(programId, name);
        }
        
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
        
        ///////////////////////////////////////////////////////////////////////
        //                      Setting Integral Uniforms
        ///////////////////////////////////////////////////////////////////////
        /**
         * Set a single uniform integer variable
         */
        inline void setUniformValue(GLint uniformId, int val) const {
            glUniform1i(uniformId, val);
        }
        
        /**
         * Set two uniform integer variables
         */
        inline void setUniformValue(GLint uniformId, int val0, int val1) const {
            glUniform2i(uniformId, val0, val1);
        }
        
        /**
         * Set three uniform integer variables
         */
        inline void setUniformValue(GLint uniformId, int val0, int val1, int val2) const {
            glUniform3i(uniformId, val0, val1, val2);
        }
        
        /**
         * Set four uniform integer variables
         */
        inline void setUniformValue(GLint uniformId, int val0, int val1, int val2, int val3) const {
            glUniform4i(uniformId, val0, val1, val2, val3);
        }
        
        /**
         * Set a uniform 2d vector of integers
         */
        inline void setUniformValue(GLint uniformId, hamLibs::math::vec2_t<int>& val) const {
            glUniform2iv(uniformId, 1, val.v);
        }
        
        /**
         * Set a uniform 3d vector of integers
         */
        inline void setUniformValue(GLint uniformId, hamLibs::math::vec3_t<int>& val) const {
            glUniform3iv(uniformId, 1, val.v);
        }
        
        /**
         * Set a uniform 4d vector of integers
         */
        inline void setUniformValue(GLint uniformId, hamLibs::math::vec4_t<int>& val) const {
            glUniform4iv(uniformId, 1, val.v);
        }
        
        ///////////////////////////////////////////////////////////////////////
        //              Setting Unsigned Integral Uniforms
        ///////////////////////////////////////////////////////////////////////
        /**
         * Set a single uniform unsigned int variable
         */
        inline void setUniformValue(GLint uniformId, unsigned val) const {
            glUniform1ui(uniformId, val);
        }
        
        /**
         * Set two uniform unsigned int variables
         */
        inline void setUniformValue(GLint uniformId, unsigned val0, unsigned val1) const {
            glUniform2ui(uniformId, val0, val1);
        }
        
        /**
         * Set three uniform unsigned int variables
         */
        inline void setUniformValue(GLint uniformId, unsigned val0, unsigned val1, unsigned val2) const {
            glUniform3ui(uniformId, val0, val1, val2);
        }
        
        /**
         * Set four uniform unsigned int variables
         */
        inline void setUniformValue(GLint uniformId, unsigned val0, unsigned val1, unsigned val2, unsigned val3) const {
            glUniform4ui(uniformId, val0, val1, val2, val3);
        }
        
        /**
         * Set a uniform 2d vector of unsigned ints
         */
        inline void setUniformValue(GLint uniformId, const hamLibs::math::vec2_t<unsigned>& val) const {
            glUniform2uiv(uniformId, 1, val.v);
        }
        
        /**
         * Set a uniform 3d vector of unsigned ints
         */
        inline void setUniformValue(GLint uniformId, const hamLibs::math::vec3_t<unsigned>& val) const {
            glUniform3uiv(uniformId, 1, val.v);
        }
        
        /**
         * Set a uniform 4d vector of unsigned ints
         */
        inline void setUniformValue(GLint uniformId, const hamLibs::math::vec4_t<unsigned>& val) const {
            glUniform4uiv(uniformId, 1, val.v);
        }
        
        ///////////////////////////////////////////////////////////////////////
        //                      Setting Float Uniforms
        ///////////////////////////////////////////////////////////////////////
        /**
         * Set a single uniform float variable
         */
        inline void setUniformValue(GLint uniformId, float val) const {
            glUniform1f(uniformId, val);
        }
        
        /**
         * Set two uniform float variables
         */
        inline void setUniformValue(GLint uniformId, float val0, float val1) const {
            glUniform2f(uniformId, val0, val1);
        }
        
        /**
         * Set three uniform float variables
         */
        inline void setUniformValue(GLint uniformId, float val0, float val1, float val2) const {
            glUniform3f(uniformId, val0, val1, val2);
        }
        
        /**
         * Set four uniform float variables
         */
        inline void setUniformValue(GLint uniformId, float val0, float val1, float val2, float val3) const {
            glUniform4f(uniformId, val0, val1, val2, val3);
        }
        
        /**
         * Set a uniform 2d vector of floats
         */
        inline void setUniformValue(GLint uniformId, const hamLibs::math::vec2_t<float>& val) const {
            glUniform2fv(uniformId, 1, val.v);
        }
        
        /**
         * Set a uniform 3d vector of floats
         */
        inline void setUniformValue(GLint uniformId, const hamLibs::math::vec3_t<float>& val) const {
            glUniform3fv(uniformId, 1, val.v);
        }
        
        /**
         * Set a uniform 4d vector of floats
         */
        inline void setUniformValue(GLint uniformId, const hamLibs::math::vec4_t<float>& val) const {
            glUniform4fv(uniformId, 1, val.v);
        }
        
        ///////////////////////////////////////////////////////////////////////
        //                      Setting Matrix Uniforms
        ///////////////////////////////////////////////////////////////////////
        /**
         * Set a uniform 2d matrix
         */
        inline void setUniformValue(GLint uniformId, const hamLibs::math::mat2_t<float>& val, bool transpose = false) const {
            glUniformMatrix2fv(uniformId, 1, transpose, val.m[0]);
        }
        
        /**
         * Set a uniform 3d matrix
         */
        inline void setUniformValue(GLint uniformId, const hamLibs::math::mat3_t<float>& val, bool transpose = false) const {
            glUniformMatrix3fv(uniformId, 1, transpose, val.m[0]);
        }
        
        /**
         * Set a uniform 4d matrix
         */
        inline void setUniformValue(GLint uniformId, const hamLibs::math::mat4_t<float>& val, bool transpose = false) const {
            glUniformMatrix4fv(uniformId, 1, transpose, val.m[0]);
        }
        
        ///////////////////////////////////////////////////////////////////////
        //                      Shader Fragment Outputs
        ///////////////////////////////////////////////////////////////////////
        /**
         * Bind data to a fragment shader
         */
        inline void bindFragDataLocation(GLuint color, const GLchar* const name) const {
            glBindFragDataLocation(programId, color, name);
        }
        
        /**
         * Bind data to a fragment shader
         */
        inline void bindFragDataLocationIndex(GLuint color, GLuint index, const GLchar* const name) const {
            glBindFragDataLocationIndexed(programId, color, index, name);
        }
        
        /**
         * Query the bindings of color indices to a user-defined varying out variable
         */
        inline GLint getFragDataIndex(const GLchar* const name) const {
            return glGetFragDataIndex(programId, name);
        }
        
        /**
         * Query the bindings of color numbers to user-defined varying out variables
         */
        inline GLint getFragDataLocation(const GLchar* const name) const {
            return glGetFragDataLocation(programId, name);
        }
};

#endif	/* __LS_SHADER_PROGRAM_H__ */

