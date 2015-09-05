
namespace ls {
namespace draw {

/*-------------------------------------
    Constructor
-------------------------------------*/
template <shader_stage_t shaderType>
shaderObject<shaderType>::shaderObject() {
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
template <shader_stage_t shaderType>
shaderObject<shaderType>::shaderObject(shaderObject&& tempShader) :
    objectId{tempShader.objectId}
{
    tempShader.objectId = 0;
}
    
/*-------------------------------------
    Destructor
-------------------------------------*/
template <shader_stage_t shaderType>
shaderObject<shaderType>::~shaderObject() {
    terminate();
}
        
/*-------------------------------------
    Move the values of the input argument and reset the moved object's values
    to 0.
-------------------------------------*/
template <shader_stage_t shaderType>
shaderObject<shaderType>& shaderObject<shaderType>::operator=(
    shaderObject&& tempShader
) {
    objectId = tempShader.objectId;
    tempShader.objectId = 0;
    return *this;
}

/*-------------------------------------
    Free all memory used by this shader object.
-------------------------------------*/
template <shader_stage_t shaderType>
inline void shaderObject<shaderType>::terminate() {
    glDeleteShader(objectId);
    objectId = 0;
}

/*-------------------------------------
    Shader Loading (single shader).
-------------------------------------*/
template <shader_stage_t shaderType>
inline bool shaderObject<shaderType>::init(const char* data, int size) {
    // If the size is zero, opengl will just look for null-termination in the data
    const int* pSize = (size == 0) ? nullptr : &size;
    return init(1, &data, pSize);
}

/*-------------------------------------
    Shader Loading (multiple shaders).
-------------------------------------*/
template <shader_stage_t shaderType>
bool shaderObject<shaderType>::init(
    const unsigned numStrings,
    const char* const* data,
    const int* sizes
) {
    LS_LOG_MSG("Attempting to load a shader object.");

    terminate();

    GLuint shaderId;
    shaderId = glCreateShader(shaderType);

    // If the size is zero, opengl will just look for null-termination in the data
    glShaderSource(shaderId, numStrings, const_cast<const char**>(data), sizes);
    glCompileShader(shaderId);

    GLint shaderStatus;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderStatus);

    // get the log information for the loaded shader
    if (shaderStatus != GL_TRUE) {
        GLint infoLogLength = 0;
        std::vector<GLchar> infoLogData;

        // Get the length of the shader's error log
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

        // Allocate some memory to temporarilt store the log data
        infoLogData.resize(infoLogLength+1); // +1 for null-termination
        infoLogData[infoLogLength] = '\0';

        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, &infoLogData[0]);
        LS_LOG_ERR("\tShader Compilation error:\n", infoLogData.data(), '\n');

        glDeleteShader(shaderId);
        return false;
    }

    objectId = shaderId;

    LS_LOG_MSG("\tSuccessfully loaded a shader object.\n");
    return true;
}

/*-------------------------------------
    Get a shader's GPU-assigned ID
-------------------------------------*/
template <shader_stage_t shaderType>
inline GLuint shaderObject<shaderType>::getId() const {
    return objectId;
}

} // end draw namespace
} // end ls namespace
