/* 
 * File:   defaultRenderStage.cpp
 * Author: Miles Lacey
 *
 * Created on January 20, 2015, 9:29 PM
 */

#include "lightsky/draw/camera.h"
#include "lightsky/draw/defaultRenderStage.h"
#include "lightsky/draw/sceneGraph.h"
#include "lightsky/draw/sceneNode.h"

namespace {

/*-------------------------------------
 * Model Matrix Uniform Name
-------------------------------------*/
const char* DEFAULT_MODEL_MATRIX_UNIFORM = "modelMatrix";

/*-------------------------------------
 * Camera/VP Matrix Uniform Name
-------------------------------------*/
const char* DEFAULT_VP_MATRIX_UNIFORM = "vpMatrix";

/*-------------------------------------
 * Default Vertex Shader (with diffuse lighting)
-------------------------------------*/
const char defaultVertShader[] = u8R"***(
#version 300 es

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTex;
layout (location = 2) in vec3 inNorm;

uniform mat4 vpMatrix;
uniform mat4 modelMatrix;

out vec3 fragVertNormal;
out vec3 fragEyeDirection;
out vec2 fragUvCoords;

//const float NEAR = 1.0;
//const float FAR = 10.0;

void main() {
    mat4 mvpMatrix = vpMatrix * modelMatrix;
    gl_Position = mvpMatrix * vec4(inPos, 1.0);

    //gl_Position = mvpMatrix * vec4(inPos, 1.0);
    //gl_Position.z = -log(NEAR * gl_Position.z + 1.0) / log(NEAR * FAR + 1.0);

    fragVertNormal = vec4(modelMatrix * vec4(inNorm, 0.0)).xyz;
    fragEyeDirection = vec3(-vpMatrix[0][3], -vpMatrix[1][3], -vpMatrix[2][3]);
    fragUvCoords = inTex;
}
)***";

/*-------------------------------------
 * Default Fragment Shader (with diffuse lighting)
-------------------------------------*/
const char defaultFragShader[] = u8R"***(
#version 300 es

precision mediump float;

in vec3 fragVertNormal;
in vec3 fragEyeDirection;
in vec2 fragUvCoords;

uniform sampler2D tex;

out vec4 fragOutColor;

float getDiffuseIntensity(in vec3 vertNorm, in vec3 lightDir) {
    float brightness = dot(vertNorm, lightDir);
    //return 0.5 + (0.5 * brightness);
    return brightness;
}

void main() {
    float diffuseIntensity = getDiffuseIntensity(normalize(fragVertNormal), normalize(fragEyeDirection));
    fragOutColor = texture(tex, fragUvCoords) * diffuseIntensity;
}
)***";

} // end anonymous namespace

namespace ls {
namespace draw {

/*-------------------------------------
 * Destructor
-------------------------------------*/
defaultRenderStage::~defaultRenderStage() {
    terminate();
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
defaultRenderStage::defaultRenderStage() {
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
defaultRenderStage::defaultRenderStage(defaultRenderStage&& rs) :
    renderStage{std::move(rs)},
    vpMatUniformId{rs.vpMatUniformId},
    modelMatUniformId{rs.modelMatUniformId},
    vertShader{std::move(rs.vertShader)},
    fragShader{std::move(rs.fragShader)},
    shaderBinary{std::move(rs.shaderBinary)}
{
    rs.vpMatUniformId = -1;
    rs.modelMatUniformId = -1;
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
defaultRenderStage& defaultRenderStage::operator=(defaultRenderStage&& rs) {
    renderStage::operator=(std::move(rs));
    
    vpMatUniformId = rs.vpMatUniformId;
    rs.vpMatUniformId = -1;
    
    modelMatUniformId = rs.modelMatUniformId;
    rs.modelMatUniformId = -1;
    
    vertShader = std::move(rs.vertShader);
    
    fragShader = std::move(rs.fragShader);
    
    shaderBinary = std::move(rs.shaderBinary);

    return *this;
}

/*-------------------------------------
 * Initialization
-------------------------------------*/
bool defaultRenderStage::init() {
    if (shaderBinary.getId() != 0) {
        terminate();
    }

    if (!vertShader.init(defaultVertShader)) {
        LS_LOG_ERR("ERROR: Unable to initialize the default vertex shader.");
        return false;
    }

    if (!fragShader.init(defaultFragShader)) {
        LS_LOG_ERR("ERROR: Unable to initialize the default fragment shader.");
        vertShader.terminate();
        return false;
    }

    if (!shaderBinary.init(vertShader, fragShader)) {
        LS_LOG_ERR("ERROR: Unable to initialize the default shader binary.");
        vertShader.terminate();
        fragShader.terminate();
        return false;
    }

    if (!shaderBinary.link()) {
        terminate();
        LS_LOG_ERR("ERROR: Unable to link the default shader binary.");
        return false;
    }

    LOG_GL_ERR();

    shaderBinary.bind();

    // attach the view-projection uniform to the scene graph
    vpMatUniformId = shaderBinary.getUniformLocation(DEFAULT_VP_MATRIX_UNIFORM);
    if (vpMatUniformId < 0) {
        LS_LOG_ERR("Unable to set the default render stage's view-projection matrix uniform.");
        LOG_GL_ERR();
        shaderBinary.unbind();
        return false;
    }
    
    // attach the model matrix uniform to the scene graph
    modelMatUniformId = shaderBinary.getUniformLocation(DEFAULT_MODEL_MATRIX_UNIFORM);
    if (modelMatUniformId < 0) {
        LS_LOG_ERR("Unable to set the default render stage's model matrix uniform.");
        LOG_GL_ERR();
        shaderBinary.unbind();
        return false;
    }
    
    shaderBinary.unbind();

    LOG_GL_ERR();

    return true;
}

/*-------------------------------------
 * Release Resources
-------------------------------------*/
void defaultRenderStage::terminate() {
    vpMatUniformId = -1;
    modelMatUniformId = -1;
    vertShader.terminate();
    fragShader.terminate();
    shaderBinary.terminate();
}

/*-------------------------------------
 * Draw a scene
-------------------------------------*/
void defaultRenderStage::draw(const sceneGraph& scene, const math::mat4& vpMatrix) {
    shaderBinary.setUniformValue(vpMatUniformId, vpMatrix);
    
    for (const sceneNode& node : scene.getNodeList()) {
        shaderBinary.setUniformValue(modelMatUniformId, node.nodeTransform.getTransform());
        for (const sceneMesh* const pMesh : node.nodeMeshes) {
            pMesh->draw();
        }
    }
}

/*-------------------------------------
 * Draw a scene using indices.
-------------------------------------*/
void defaultRenderStage::draw(
    const sceneGraph& scene,
    const math::mat4& vpMatrix,
    const std::vector<unsigned>& nodeIndices
) {
    
    shaderBinary.setUniformValue(vpMatUniformId, vpMatrix);
    
    const scene_node_list_t& nodes = scene.getNodeList();
    
    for (unsigned index : nodeIndices) {
        const sceneNode& node = nodes[index];
        shaderBinary.setUniformValue(modelMatUniformId, node.nodeTransform.getTransform());
        
        for (const sceneMesh* const pMesh : node.nodeMeshes) {
            pMesh->draw();
        }
    }
}

/*-------------------------------------
 * Bind for rendering
-------------------------------------*/
void defaultRenderStage::bind() {
    shaderBinary.bind();
}

/*-------------------------------------
 * Unbind from OpenGL
-------------------------------------*/
void defaultRenderStage::unbind() {
    shaderBinary.unbind();
}

} // end draw namespace
} // end ls namespace

