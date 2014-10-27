
namespace ls {
namespace draw {

/*-------------------------------------
    Bind this program to the current context
-------------------------------------*/
inline void shaderProgram::bind() const {
    glUseProgram(programId);
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
inline void shaderProgram::bindAttribute(GLuint index, const GLchar* const name) {
    glBindAttribLocation(programId, index, name);
}

/*-------------------------------------
    Get the location of a vert6ex attribute
-------------------------------------*/
inline GLint shaderProgram::getAttribute(const GLchar* const name) const {
    return glGetAttribLocation(programId, name);
}

/*-------------------------------------
    Get the location of a uniform variable.
    
    @return GLint
    A positive value to indicate the uniform's location in OpenGL or
    -1 for an invalid uniform index.
-------------------------------------*/
inline GLint shaderProgram::getUniformLocation(const GLchar* const name) const {
    return glGetUniformLocation(programId, name);
}

/*-------------------------------------
    Set a single uniform integer variable
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, int val) {
    glUniform1i(uniformId, val);
}

/*-------------------------------------
    Set two uniform integer variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, int val0, int val1) {
    glUniform2i(uniformId, val0, val1);
}

/*-------------------------------------
    Set three uniform integer variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, int val0, int val1, int val2) {
    glUniform3i(uniformId, val0, val1, val2);
}

/*-------------------------------------
    Set four uniform integer variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, int val0, int val1, int val2, int val3) {
    glUniform4i(uniformId, val0, val1, val2, val3);
}

/*-------------------------------------
    Set a uniform 2d vector of integers
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec2i& val) {
    glUniform2iv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 3d vector of integers
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec3i& val) {
    glUniform3iv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 4d vector of integers
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec4i& val) {
    glUniform4iv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a single uniform unsigned int variable
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, unsigned val) {
    glUniform1ui(uniformId, val);
}

/*-------------------------------------
    Set two uniform unsigned int variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, unsigned val0, unsigned val1) {
    glUniform2ui(uniformId, val0, val1);
}

/*-------------------------------------
    Set three uniform unsigned int variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, unsigned val0, unsigned val1, unsigned val2) {
    glUniform3ui(uniformId, val0, val1, val2);
}

/*-------------------------------------
    Set four uniform unsigned int variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, unsigned val0, unsigned val1, unsigned val2, unsigned val3) {
    glUniform4ui(uniformId, val0, val1, val2, val3);
}

/*-------------------------------------
    Set a uniform 2d vector of unsigned ints
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec2ui& val) {
    glUniform2uiv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 3d vector of unsigned ints
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec3ui& val) {
    glUniform3uiv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 4d vector of unsigned ints
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec4ui& val) {
    glUniform4uiv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a single uniform float variable
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, float val) {
    glUniform1f(uniformId, val);
}

/*-------------------------------------
    Set two uniform float variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, float val0, float val1) {
    glUniform2f(uniformId, val0, val1);
}

/*-------------------------------------
    Set three uniform float variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, float val0, float val1, float val2) {
    glUniform3f(uniformId, val0, val1, val2);
}

/*-------------------------------------
    Set four uniform float variables
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, float val0, float val1, float val2, float val3) {
    glUniform4f(uniformId, val0, val1, val2, val3);
}

/*-------------------------------------
    Set a uniform 2d vector of floats
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec2& val) {
    glUniform2fv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 3d vector of floats
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec3& val) {
    glUniform3fv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 4d vector of floats
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::vec4& val) {
    glUniform4fv(uniformId, 1, val.v);
}

/*-------------------------------------
    Set a uniform 2d matrix
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::mat2& val, bool transpose) {
    glUniformMatrix2fv(uniformId, 1, transpose, &val[0]);
}

/*-------------------------------------
    Set a uniform 3d matrix
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::mat3& val, bool transpose) {
    glUniformMatrix3fv(uniformId, 1, transpose, &val[0]);
}

/*-------------------------------------
    Set a uniform 4d matrix
-------------------------------------*/
inline void shaderProgram::setUniformValue(GLint uniformId, const math::mat4& val, bool transpose) {
    glUniformMatrix4fv(uniformId, 1, transpose, &val[0]);
}

/*-------------------------------------
    Bind data to a fragment shader
-------------------------------------*/
inline void shaderProgram::bindFragDataLocation(GLuint colorNum, const GLchar* const name) {
    glBindFragDataLocation(programId, colorNum, name);
}

/*-------------------------------------
    Bind data to a fragment shader
-------------------------------------*/
inline void shaderProgram::bindFragDataLocationIndex(GLuint colorNum, GLuint index, const GLchar* const name) {
    glBindFragDataLocationIndexed(programId, colorNum, index, name);
}

/*-------------------------------------
    Query the bindings of color indices to a user-defined varying out variable
-------------------------------------*/
inline GLint shaderProgram::getFragDataIndex(const GLchar* const name) const {
    return glGetFragDataIndex(programId, name);
}

/*-------------------------------------
    Query the bindings of color numbers to user-defined varying out variables
-------------------------------------*/
inline GLint shaderProgram::getFragDataLocation(const GLchar* const name) const {
    return glGetFragDataLocation(programId, name);
}

} // end draw namespace
} // end ls namespace
