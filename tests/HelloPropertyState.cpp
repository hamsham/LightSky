/*
 * File:   HelloPropertyState.cpp
 * Author: miles
 *
 * Created on October 27, 2015, 10:44 PM
 */

#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>
#include <locale>
#include <utility>

#include "lightsky/setup/Setup.h"

#include "lightsky/math/Math.h"

#include "lightsky/utils/Utils.h"
#include "lightsky/utils/Copy.h"

#include "lightsky/game/Game.h"
#include "lightsky/draw/Draw.h"

#include "Display.h"
#include "HelloPropertyState.h"



namespace math = ls::math;
namespace draw = ls::draw;
namespace utils = ls::utils;
using draw::VAOAttrib;
using draw::ShaderAttribArray;




///////////////////////////////////////////////////////////////////////////////
//  Mesh Shader
///////////////////////////////////////////////////////////////////////////////
namespace {



/*-------------------------------------
 * Mesh Vertex Shader (with logarithmic Z-depth)
-------------------------------------*/
const std::string vsPropertyShaderData{u8R"***(
#version 330 core
//#version 300 es

precision mediump float;
    
layout (location = 0) in vec3 posAttrib;
layout (location = 1) in vec2 uvAttrib;
layout (location = 2) in vec3 normAttrib;

out vec3 fragEyeDirection;
out vec3 fragVertNormal;
out vec2 fragUvCoords;

layout(std140) uniform BatchProperties {
    vec3 EYE_DIR;
    mat4 VP_MATRIX;
} batchProperties;

layout(shared) uniform InstanceProperties {
    mat4 MODEL_MATRIX;
} instanceProperties;


void main() {
    mat4 MODEL_MAT      = instanceProperties.MODEL_MATRIX;
    mat4 VP_MAT         = batchProperties.VP_MATRIX;
    
    gl_Position         = VP_MAT * MODEL_MAT * vec4(posAttrib, 1.0);
    fragEyeDirection    = vec3(-VP_MAT[0][2], -VP_MAT[1][2], -VP_MAT[2][2]);
    fragVertNormal      = normalize(vec4(MODEL_MAT * vec4(normAttrib, 0.0)).xyz);
    fragUvCoords        = uvAttrib;
}
)***"};

/*-------------------------------------
 * Mesh Fragment Shader
-------------------------------------*/
const std::string fsPropertyShaderData{u8R"***(
#version 330 core
//#version 300 es

precision mediump float;

in vec3 fragEyeDirection;
in vec3 fragVertNormal;
in vec2 fragUvCoords;

uniform sampler2D DIFFUSE_TEXTURE;

layout(std140) uniform DiffuseIntensityLimit {
    float dotProd[10];
} diffuseIntensityLimit;

out vec4 fragOutColor;

float calc_diffuse_intensity(in vec3 vertNorm, in vec3 lightDir) {
    return max(diffuseIntensityLimit.dotProd[1], dot(vertNorm, lightDir));
}

void main() {
    vec3 e              = normalize(fragEyeDirection);
    vec3 n              = normalize(fragVertNormal);
    vec4 baseColor      = texture(DIFFUSE_TEXTURE, fragUvCoords);
    float brightness    = calc_diffuse_intensity(n, e);
    fragOutColor        = baseColor * brightness;
}
)***"};



} // end anonymous namespace



/*-----------------------------------------------------------------------------
 * Test Class
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Destructor
-------------------------------------*/
HelloPropertyState::~HelloPropertyState() {
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
HelloPropertyState::HelloPropertyState() {
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
HelloPropertyState::HelloPropertyState(HelloPropertyState&& state) :
    ls::game::GameState {}
{
    *this = std::move(state);
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
HelloPropertyState& HelloPropertyState::operator =(HelloPropertyState&& state) {
    ls::game::GameState::operator =(std::move(state));
    testShader = std::move(state.testShader);

    return *this;
}

/*-------------------------------------
-------------------------------------*/
void HelloPropertyState::setup_shader(ls::draw::ShaderProgram& s, const std::string& vertData, const std::string& fragData) {
    draw::ShaderObject vMeshShader, fMeshShader;
    constexpr unsigned charSize = sizeof(std::string::value_type);
    
    const auto compile_shader = [](draw::ShaderObject& shaderObj, const draw::shader_stage_t shaderType, const std::string& shaderData)->void {
        if (!shaderObj.init(shaderType, shaderData.c_str(), shaderData.size() * charSize)) {
            LS_LOG_GL_ERR();
            LS_ASSERT(false);
        }
        LS_LOG_GL_ERR();
    };

    compile_shader(vMeshShader, draw::shader_stage_t::SHADER_STAGE_VERTEX, vertData);
    compile_shader(fMeshShader, draw::shader_stage_t::SHADER_STAGE_FRAGMENT, fragData);

    draw::ShaderProgramAssembly shaderMaker;
    LS_ASSERT(shaderMaker.set_vertex_shader(vMeshShader));
    LS_ASSERT(shaderMaker.set_fragment_shader(fMeshShader));
    LS_ASSERT(shaderMaker.is_assembly_valid());
    LS_ASSERT(shaderMaker.assemble(s, false));
    LS_ASSERT(shaderMaker.link(s));

    vMeshShader.terminate();
    fMeshShader.terminate();
    
    s.unbind();
}

/*-------------------------------------
 * System Startup
-------------------------------------*/
bool HelloPropertyState::on_start() {
    using draw::ShaderAttribArray;
    using draw::VAOAttrib;

    setup_shader(testShader, vsPropertyShaderData, fsPropertyShaderData);

    const draw::ShaderAttribArray& uniforms = testShader.get_uniforms();
    
    for (unsigned i = 0; i < uniforms.get_num_attribs(); ++i) {
        const draw::ShaderAttrib& uniform = uniforms.get_attrib(i);
        LS_LOG_MSG("Regular Shader Uniform ", uniform.get_name());
    }

    return true;
}

/*-------------------------------------
 * System Runtime
-------------------------------------*/
void HelloPropertyState::on_run() {
    this->stop_state();
}

/*-------------------------------------
 * System Stop
-------------------------------------*/
void HelloPropertyState::on_stop() {
    testShader.terminate();
}
