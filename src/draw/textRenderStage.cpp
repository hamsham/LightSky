/* 
 * File:   textRenderStage.cpp
 * Author: Miles Lacey
 * 
 * Created on January 31, 2015, 4:52 PM
 */

#include "lightsky/draw/camera.h"
#include "lightsky/draw/textRenderStage.h"
#include "lightsky/draw/sceneGraph.h"
#include "lightsky/draw/sceneNode.h"

namespace {

/*-------------------------------------
 * Model Matrix Uniform Name
-------------------------------------*/
const char* TEXT_MODEL_MATRIX_UNIFORM = "modelMatrix";

/*-------------------------------------
 * Camera/VP Matrix Uniform Name
-------------------------------------*/
const char* TEXT_VP_MATRIX_UNIFORM = "vpMatrix";

/*-------------------------------------
 * Camera/VP Matrix Uniform Name
-------------------------------------*/
const char* TEXT_COLOR_UNIFORM = "textColor";

/*-------------------------------------
 * Text Vertex Shader
-------------------------------------*/
const char textVertShader[] = u8R"***(
#version 300 es

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inUv;
layout (location = 2) in vec3 inNorm;

uniform mat4 vpMatrix;
uniform mat4 modelMatrix;

out vec2 uvCoords;

void main() {
    mat4 mvp = vpMatrix * modelMatrix;
    gl_Position = mvp * vec4(inPos, 1.0);
    uvCoords = inUv;
}
)***";

/*-------------------------------------
 * Text Fragment Shader (with pseudo signed-distance field)
-------------------------------------*/
const char textFragShader[] = u8R"***(
#version 300 es

precision lowp float;

in vec2 uvCoords;

out vec4 outFragCol;

uniform sampler2D texSampler;
uniform vec4 textColor = vec4(1.0, 1.0, 1.0, 1.0);

void main() {
    float mask = texture(texSampler, uvCoords).r;
    outFragCol = textColor*step(0.5, mask);
}
)***";

} // end anonymous namespace

namespace ls {
namespace draw {

/*-------------------------------------
 * Destructor
-------------------------------------*/
textRenderStage::~textRenderStage() {
    terminate();
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
textRenderStage::textRenderStage() {
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
textRenderStage::textRenderStage(textRenderStage&& rs) :
    renderStage{std::move(rs)},
    vpMatUniformId{rs.vpMatUniformId},
    modelMatUniformId{rs.modelMatUniformId},
    colorUniformId{rs.colorUniformId},
    textColor{rs.textColor}
{
    rs.vpMatUniformId = -1;
    rs.modelMatUniformId = -1;
    rs.colorUniformId = -1;
    rs.textColor = color::black;
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
textRenderStage& textRenderStage::operator=(textRenderStage&& rs) {
    renderStage::operator=(std::move(rs));
    
    vpMatUniformId = rs.vpMatUniformId;
    rs.vpMatUniformId = -1;
    
    modelMatUniformId = rs.modelMatUniformId;
    rs.modelMatUniformId = -1;
    
    colorUniformId = rs.colorUniformId;
    rs.colorUniformId = -1;
    
    textColor = rs.textColor;
    rs.textColor = color::black;

    return *this;
}

/*-------------------------------------
 * Initialization
-------------------------------------*/
bool textRenderStage::init() {
    shaderProgram& shaderBinary = getShaderProgram();
    
    if (shaderBinary.getId() != 0) {
        terminate();
    }
    
    if (!initShaders(textVertShader, textFragShader)) {
        LS_LOG_ERR("ERROR: Unable to initialize a text renderer's shader data.");
        return false;
    }

    LOG_GL_ERR();

    shaderBinary.bind();

    // attach the view-projection uniform to the scene graph
    vpMatUniformId = shaderBinary.getUniformLocation(TEXT_VP_MATRIX_UNIFORM);
    if (vpMatUniformId < 0) {
        LS_LOG_ERR("Unable to set the text render stage's view-projection matrix uniform.");
        LOG_GL_ERR();
        shaderBinary.unbind();
        return false;
    }
    
    // attach the model matrix uniform to the scene graph
    modelMatUniformId = shaderBinary.getUniformLocation(TEXT_MODEL_MATRIX_UNIFORM);
    if (modelMatUniformId < 0) {
        LS_LOG_ERR("Unable to set the text render stage's model matrix uniform.");
        LOG_GL_ERR();
        shaderBinary.unbind();
        return false;
    }

    // attach the view-projection uniform to the scene graph
    colorUniformId = shaderBinary.getUniformLocation(TEXT_COLOR_UNIFORM);
    if (colorUniformId < 0) {
        LS_LOG_ERR("Unable to set the text render stage's color uniform.");
        LOG_GL_ERR();
        shaderBinary.unbind();
        return false;
    }
    
    // use additive blending for text
    blendObject& blender = getBlendParameters();
    blender.setState(true);
    blender.setBlendEquation(ls::draw::BLEND_EQU_ADD, ls::draw::BLEND_EQU_ADD);
    blender.setBlendFunction(
        ls::draw::BLEND_FNC_ONE, ls::draw::BLEND_FNC_1_SUB_SRC_ALPHA,
        ls::draw::BLEND_FNC_ONE, ls::draw::BLEND_FNC_ZERO
    );
    
    depthObject& depthParams = getDepthParameters();
    depthParams.setDepthMask(false);
    depthParams.setState(false);
    
    shaderBinary.unbind();

    LOG_GL_ERR();

    return true;
}

/*-------------------------------------
 * Release Resources
-------------------------------------*/
void textRenderStage::terminate() {
    renderStage::terminate();
    vpMatUniformId = -1;
    modelMatUniformId = -1;
    colorUniformId = -1;
    textColor = color::black;
}

/*-------------------------------------
 * Draw a scene
-------------------------------------*/
void textRenderStage::draw(const sceneGraph& scene, const math::mat4& vpMatrix) {
    getShaderProgram().setUniformValue(vpMatUniformId, vpMatrix);
    getShaderProgram().setUniformValue(colorUniformId, textColor);
    
    for (const sceneNode& node : scene.getNodeList()) {
        getShaderProgram().setUniformValue(modelMatUniformId, node.nodeTransform.getTransform());
        for (const sceneMesh* const pMesh : node.nodeMeshes) {
            pMesh->draw();
        }
    }
}

/*-------------------------------------
 * Draw a scene using indices.
-------------------------------------*/
void textRenderStage::draw(
    const sceneGraph& scene,
    const math::mat4& vpMatrix,
    const std::vector<unsigned>& nodeIndices
) {
    getShaderProgram().setUniformValue(vpMatUniformId, vpMatrix);
    getShaderProgram().setUniformValue(colorUniformId, textColor);
    
    const scene_node_list_t& nodes = scene.getNodeList();
    
    for (unsigned index : nodeIndices) {
        const sceneNode& node = nodes[index];
        getShaderProgram().setUniformValue(modelMatUniformId, node.nodeTransform.getTransform());
        
        for (const sceneMesh* const pMesh : node.nodeMeshes) {
            pMesh->draw();
        }
    }
}

} // end draw namespace
} // end ls namespace
