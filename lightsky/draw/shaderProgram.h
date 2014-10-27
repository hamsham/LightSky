/* 
 * File:   draw/shaderProgram.h
 * Author: Miles Lacey
 *
 * Created on January 21, 2014, 6:54 PM
 */

#ifndef __LS_DRAW_SHADER_PROGRAM_H__
#define	__LS_DRAW_SHADER_PROGRAM_H__

#include <string>
#include <GL/glew.h>

#include "lightsky/draw/setup.h"
#include "lightsky/draw/shaderObject.h"

namespace ls {
namespace draw {

/**
 * @brief Shader Program
 * 
 * Represents a combination of OpenGL vertex, fragment, and geometry shader
 * objects.
 */
class shaderProgram {
    private:
        /**
         * A handle to the GPU-side shader program within OpenGL.
         */
        GLuint programId = 0;

    public:
        /**
         * @brief Constructor
         */
        shaderProgram();
        
        /**
         * @brief Copy Constructor -- Deleted
         */
        shaderProgram(const shaderProgram&) = delete;
        
        /**
         * @brief Move Constructor
         * 
         * Copy the handle to the shader object owned by the input argument,
         * reset the moved object's shader handle to 0.
         * 
         * @param sp
         * A, r-value reference to a shader program object to move into *this.
         */
        shaderProgram(shaderProgram&&);
        
        /**
         * @brief Copy Operator -- Deleted
         */
        shaderProgram& operator=(const shaderProgram&) = delete;
        
        /**
         * @brief Move Operator
         * 
         * Move the values of the input argument and reset the moved object's
         * values to 0.
         * 
         * @param sp
         * A, r-value reference to a shader program object to move into *this.
         * 
         * @return A reference to *this
         */
        shaderProgram& operator=(shaderProgram&&);
        
        /**
         * @brief Destructor
         * 
         * Destroy this object and free any GPU memory it uses.
         */
        ~shaderProgram();
        
        /**
         * Free all memory used by this shader object.
         */
        void terminate();
        
        /**
         * Attach a set of shader units to the program
         * 
         * @param vs
         * A vertex shader unit that should be attached to *this.
         * 
         * @param fs
         * A fragment shader unit that should be attached to *this.
         * 
         * @return TRUE if the input shader units were successfully attached to
         * *this.
         */
        bool attachShaders(const vertexShader& vs, const fragmentShader& fs);
        
        /**
         * Attach a set of shader units to the program
         * 
         * @param vs
         * A vertex shader unit that should be attached to *this.
         * 
         * @param gs
         * A geometry shader unit that should be attached to *this.
         * 
         * @param fs
         * A fragment shader unit that should be attached to *this.
         * 
         * @return TRUE if the input shader units were successfully attached to
         * *this.
         */
        bool attachShaders(
            const vertexShader& vs,
            const geometryShader& gs,
            const fragmentShader& fs
        );
        
        /**
         * Link the attached shader units to this and create an entire GPU-side
         * shader program.
         * 
         * @return TRUE if *this object was successfully linked with its
         * attached shader units.
         */
        bool link();
        
        /**
         * Bind this program to the current context
         */
        void bind() const;
        
        /**
         * Unbind this program from the context.
         */
        void unbind() const;
        
        /**
         * Bind a vertex attribute to a shader.
         * 
         * @param index
         * An unsigned integral type which specifies the vertex array location
         * of an attachment to bind.
         * 
         * @param name
         * The exact name of the vertex array attribute in *this to bind.
         */
        void bindAttribute(GLuint index, const GLchar* const name);
        
        /**
         * Get the location of a vertex attribute
         * 
         * @param name
         * The exact name of the vertex array attribute in *this whose index
         * location should be retrieved.
         * 
         * @return GLint
         * A positive value to indicate the attribute's location in OpenGL or
         * -1 for an invalid index.
         */
        GLint getAttribute(const GLchar* const name) const;
        
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
        void bindFragDataLocation(GLuint colorNum, const GLchar* const name);
        
        /**
         * Bind data to a fragment shader
         */
        void bindFragDataLocationIndex(GLuint colorNum, GLuint index, const GLchar* const name);
        
        /**
         * Query the bindings of color indices to a user-defined varying out variable
         */
        GLint getFragDataIndex(const GLchar* const name) const;
        
        /**
         * Query the bindings of color numbers to user-defined varying out variables
         */
        GLint getFragDataLocation(const GLchar* const name) const;
};

} // end draw namespace
} // end ls namespace

#include "lightsky/draw/generic/shaderProgram_impl.h"

#endif	/* __LS_DRAW_SHADER_PROGRAM_H__ */

