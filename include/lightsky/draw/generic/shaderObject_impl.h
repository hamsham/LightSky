
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
    Shader Loading
-------------------------------------*/
template <shader_stage_t shaderType>
bool shaderObject<shaderType>::init(const char* data, int size) {
    LS_LOG_MSG("Attempting to load a shader object.");
    
    terminate();
    
    GLuint tempId = glCreateShader(shaderType);
    
    if (!tempId) {
        LS_LOG_ERR("\tFailed to create a shader object.");
        return false;
    }
    
    // If the size is zero, opengl will just look for null-termination in the data
    if (size == 0) {
        glShaderSource(tempId, 1, &data, nullptr);
    }
    else {
        glShaderSource(tempId, 1, &data, &size);
    }
    
    glCompileShader(tempId);
    
    GLint shaderStatus;
    glGetShaderiv(tempId, GL_COMPILE_STATUS, &shaderStatus);
    
    if (shaderStatus != GL_TRUE) {
        GLint infoLogLength = 0;
        GLchar* infoLogData = nullptr;

        // Get the length of the shader's error log
        glGetShaderiv(tempId, GL_INFO_LOG_LENGTH, &infoLogLength);

        // Allocate some memory to temporarilt store the log data
        infoLogData = new GLchar[infoLogLength+1]; // +1 for null-termination
        infoLogData[infoLogLength] = '\0';

        glGetShaderInfoLog(tempId, infoLogLength, nullptr, infoLogData);
        LS_LOG_ERR("\tShader Compilation error:\n", infoLogData, '\n');

        delete [] infoLogData;
        glDeleteShader(tempId);
        return false;
    }
    
    objectId = tempId;
    
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
