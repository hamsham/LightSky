
namespace ls {
namespace draw {

/*-------------------------------------
    Get the OpenGL ID used by *this.
-------------------------------------*/
inline unsigned shaderProgram::getId() const {
    return gpuId;
}

/*-------------------------------------
    Bind this program to the current context
-------------------------------------*/
inline void shaderProgram::bind() const {
    glUseProgram(gpuId);
}

/*-------------------------------------
    Unbind this program from the context.
-------------------------------------*/
inline void shaderProgram::unbind() const {
    glUseProgram(0);
}

/*-------------------------------------
    Bind a vertex attribute to a shader
-------------------------------------*/
inline void shaderProgram::bindAttribLocation(GLuint index, const GLchar* const name) const {
    glBindAttribLocation(gpuId, index, name);
}

/*-------------------------------------
    Get the location of a vert6ex attribute
-------------------------------------*/
inline GLint shaderProgram::getAttribLocation(const GLchar* const name) const {
    return glGetAttribLocation(gpuId, name);
}

/*-------------------------------------
    Get the location of a uniform variable.
    
    @return GLint
    A positive value to indicate the uniform's location in OpenGL or
    -1 for an invalid uniform index.
-------------------------------------*/
inline GLint shaderProgram::getUniformLocation(const GLchar* const name) const {
    return glGetUniformLocation(gpuId, name);
}

/*-------------------------------------
    Set a single uniform integer variable
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, int val) const {
    glUniform1i(uniformId, val);
}

/*-------------------------------------
    Set two uniform integer variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, int val0, int val1) const {
    glUniform2i(uniformId, val0, val1);
}

/*-------------------------------------
    Set three uniform integer variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, int val0, int val1, int val2) const {
    glUniform3i(uniformId, val0, val1, val2);
}

/*-------------------------------------
    Set four uniform integer variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, int val0, int val1, int val2, int val3) const {
    glUniform4i(uniformId, val0, val1, val2, val3);
}

/*-------------------------------------
    Set a uniform 2d vector of integers
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec2i& val) const {
    glUniform2iv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 3d vector of integers
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec3i& val) const {
    glUniform3iv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 4d vector of integers
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec4i& val) const {
    glUniform4iv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a single uniform unsigned int variable
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, unsigned val) const {
    glUniform1ui(uniformId, val);
}

/*-------------------------------------
    Set two uniform unsigned int variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, unsigned val0, unsigned val1) const {
    glUniform2ui(uniformId, val0, val1);
}

/*-------------------------------------
    Set three uniform unsigned int variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, unsigned val0, unsigned val1, unsigned val2) const {
    glUniform3ui(uniformId, val0, val1, val2);
}

/*-------------------------------------
    Set four uniform unsigned int variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, unsigned val0, unsigned val1, unsigned val2, unsigned val3) const {
    glUniform4ui(uniformId, val0, val1, val2, val3);
}

/*-------------------------------------
    Set a uniform 2d vector of unsigned ints
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec2ui& val) const {
    glUniform2uiv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 3d vector of unsigned ints
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec3ui& val) const {
    glUniform3uiv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 4d vector of unsigned ints
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec4ui& val) const {
    glUniform4uiv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a single uniform float variable
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, float val) const {
    glUniform1f(uniformId, val);
}

/*-------------------------------------
    Set two uniform float variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, float val0, float val1) const {
    glUniform2f(uniformId, val0, val1);
}

/*-------------------------------------
    Set three uniform float variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, float val0, float val1, float val2) const {
    glUniform3f(uniformId, val0, val1, val2);
}

/*-------------------------------------
    Set four uniform float variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, float val0, float val1, float val2, float val3) const {
    glUniform4f(uniformId, val0, val1, val2, val3);
}

/*-------------------------------------
    Set a uniform 2d vector of floats
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec2& val) const {
    glUniform2fv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 3d vector of floats
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec3& val) const {
    glUniform3fv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 4d vector of floats
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec4& val) const {
    glUniform4fv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 2d matrix
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::mat2& val, bool transpose) const {
    glUniformMatrix2fv(uniformId, 1, transpose ? GL_TRUE : GL_FALSE, &val[0]);
}

/*-------------------------------------
    Set a uniform 3d matrix
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::mat3& val, bool transpose) const {
    glUniformMatrix3fv(uniformId, 1, transpose ? GL_TRUE : GL_FALSE, &val[0]);
}

/*-------------------------------------
    Set a uniform 4d matrix
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::mat4& val, bool transpose) const {
    glUniformMatrix4fv(uniformId, 1, transpose ? GL_TRUE : GL_FALSE, &val[0]);
}

/*-------------------------------------
    Query the bindings of color numbers to user-defined varying out variables
-------------------------------------*/
inline GLint shaderProgram::getFragDataLocation(const GLchar* const name) const {
    return glGetFragDataLocation(gpuId, name);
}

} // end draw namespace
} // end ls namespace
