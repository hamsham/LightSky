/*
 * File:   HelloPrimState.cpp
 * Author: miles
 *
 * Created on January 29, 2015
 */

#include <cassert>
#include <ctime>
#include <memory>
#include <cstring>

#include "lightsky/setup/Macros.h"

#include "lightsky/math/Math.h"

#include "lightsky/utils/Log.h"
#include "lightsky/utils/Pointer.h"

#include "lightsky/game/GameState.h"
#include "lightsky/game/GameSystem.h"

#include "lightsky/draw/PackedVertex.h"
#include "lightsky/draw/ShaderAssembly.h"
#include "lightsky/draw/ShaderAttrib.h"
#include "lightsky/draw/ShaderAttribArray.h"
#include "lightsky/draw/ShaderObject.h"
#include "lightsky/draw/ShaderUniform.h"
#include "lightsky/draw/VAOAssembly.h"
#include "lightsky/draw/VAOAttrib.h"
#include "lightsky/draw/VertexUtils.h"

#include "HelloPrimState.h"
#include "ControlState.h"
#include "Display.h"
#include "HelloMeshState.h"



namespace draw = ls::draw;
namespace math = ls::math;
namespace utils = ls::utils;

///////////////////////////////////////////////////////////////////////////////
//  Private Variables
///////////////////////////////////////////////////////////////////////////////
namespace {
/*-------------------------------------
 * Model Matrix Uniform Name
-------------------------------------*/
const char* PRIM_MODEL_MAT_UNIFORM_STR = "modelMatrix";
int PRIM_MODEL_MAT_UNIFORM_ID = -1;

/*-------------------------------------
 * Camera/VP Matrix Uniform Name
-------------------------------------*/
const char* PRIM_VP_MAT_UNIFORM_STR = "vpMatrix";
int PRIM_VP_MAT_UNIFORM_ID = -1;

/*-------------------------------------
 * Vertex Shader
-------------------------------------*/
constexpr char vsPrimShaderData[] = u8R"***(
#version 330 core

precision mediump float;

layout (location = 0) in vec3 posAttrib;
layout (location = 1) in vec2 uvAttrib;
layout (location = 2) in vec3 normAttrib;

uniform mat4 vpMatrix;
uniform mat4 modelMatrix;

out vec2 uvCoords;
out vec3 normCoords;

void main() {
    mat4 mvp = vpMatrix * modelMatrix;
    gl_Position = mvp * vec4(posAttrib, 1.0);
    uvCoords = uvAttrib;
    normCoords = normAttrib;
}
)***";

/*-------------------------------------
 * Fragment Shader
-------------------------------------*/
constexpr char fsPrimShaderData[] = u8R"***(
#version 330 core

precision mediump float;

uniform vec4 primColor;

in vec2 uvCoords;
in vec3 normCoords;

out vec4 fragOutColor;

void main() {
    fragOutColor = vec4(uvCoords.rg, normCoords.z, 1.0);
}
)***";

/*-------------------------------------
 * Primitive vertex data
-------------------------------------*/
static constexpr math::vec3 testPositions[3] = {
    math::vec3{-1.f, -1.f, 0.f},
    math::vec3{1.f, -1.f, 0.f},
    math::vec3{0.f, 1.f, 0.f},
};


static constexpr math::vec2 testTextures[3] = {
    math::vec2{0.f, 0.f},
    math::vec2{1.f, 0.f},
    math::vec2{0.5f, 1.f}
};

static const int32_t testNormals[3] = {
    ls::draw::pack_vertex_normal(math::vec3{0.f, 0.f, 1.f}),
    ls::draw::pack_vertex_normal(math::vec3{0.f, 0.f, 1.f}),
    ls::draw::pack_vertex_normal(math::vec3{0.f, 0.f, 1.f})
};

static const unsigned testPosStride = 0;
static const unsigned testTexStride = sizeof(math::vec3);
static const unsigned testNormStride = testTexStride + sizeof(math::vec2);
static const unsigned testVertStride = testNormStride + sizeof(int32_t);

static const math::mat4 modelMatrix = {1.f};



} // end anonymous namespace

/*-------------------------------------
 * Destructor
-------------------------------------*/
HelloPrimState::~HelloPrimState() {
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
HelloPrimState::HelloPrimState() {
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
HelloPrimState::HelloPrimState(HelloPrimState&& state) :
    GameState{}
{
    *this = std::move(state);
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
HelloPrimState& HelloPrimState::operator =(HelloPrimState&& state) {
    GameState::operator =(std::move(state));

    shader = std::move(state.shader);
    vbo = std::move(state.vbo);
    vao = std::move(state.vao);

    return *this;
}

/*-------------------------------------
 * Update the colors or all triangle vertices
-------------------------------------*/
void HelloPrimState::update_vert_color(const unsigned vertIndex, const bool isVisible) {
    math::vec2 colors = {1.f, 0.f};

    if (!isVisible) {
        colors[0] = 0.f;
        colors[1] = 1.f;
    }

    vbo.bind();
    LS_LOG_GL_ERR();

    vbo.modify((vertIndex * testVertStride) + testTexStride, sizeof (math::vec2), colors.v);
    LS_LOG_GL_ERR();

    vbo.unbind();
    LS_LOG_GL_ERR();
}

/*-------------------------------------
 * Generate a triangle
-------------------------------------*/
std::unique_ptr<char[] > HelloPrimState::gen_vertex_data() {
    std::unique_ptr<char[] > pData {new char[testVertStride * 3]};

    // interleave all vertex data
    for (unsigned i = 0; i < 3; ++i) {
        *reinterpret_cast<math::vec3*>(pData.get() + (i * testVertStride) + testPosStride) = testPositions[i];
        *reinterpret_cast<math::vec2*>(pData.get() + (i * testVertStride) + testTexStride) = testTextures[i];
        *reinterpret_cast<int32_t*>(pData.get() + (i * testVertStride) + testNormStride) = testNormals[i];
    }

    return pData;
}

/*-------------------------------------
-------------------------------------*/
void HelloPrimState::setup_shaders() {
    ls::draw::ShaderProgramAssembly shaderMaker{};
    ls::draw::ShaderObject vShader;
    ls::draw::ShaderObject fShader;

    if (!vShader.init(ls::draw::SHADER_STAGE_VERTEX, vsPrimShaderData, 0)) {
        LS_LOG_GL_ERR();
        LS_ASSERT(false);
    }
    else {
        LS_ASSERT(shaderMaker.set_vertex_shader(vShader));
    }

#ifdef LS_DRAW_BACKEND_GL
    shaderMaker.clear_geometry_shader();
#endif

    if (!fShader.init(ls::draw::SHADER_STAGE_FRAGMENT, fsPrimShaderData, 0)) {
        LS_LOG_GL_ERR();
        LS_ASSERT(false);
    }
    else {
        LS_ASSERT(shaderMaker.set_fragment_shader(fShader));
    }

    LS_ASSERT(shaderMaker.is_assembly_valid());
    LS_ASSERT(shaderMaker.assemble(shader, true));
    
    setup_uniforms(shader);
    
    vShader.terminate();
    fShader.terminate();
}

/*-------------------------------------
-------------------------------------*/
void HelloPrimState::setup_uniforms(const ls::draw::ShaderProgram& s) {
    s.bind();
    LS_LOG_GL_ERR();
    
    const draw::ShaderAttribArray& uniforms = s.get_uniforms();

    for (unsigned i = 0; i < uniforms.get_num_attribs(); ++i) {
        
        const utils::Pointer<GLchar[]>& uniformName = uniforms.get_attrib_name(i);
        const GLint index = s.get_uniform_location(uniformName.get());

        if (index < 0) {
            continue;
        }

        if (strcmp(uniformName.get(), PRIM_MODEL_MAT_UNIFORM_STR) == 0) {
            LS_LOG_MSG("Found Model Matrix Uniform ", index, ": ", uniformName);
            PRIM_MODEL_MAT_UNIFORM_ID = index;
        }
        else if (strcmp(uniformName.get(), PRIM_VP_MAT_UNIFORM_STR) == 0) {
            LS_LOG_MSG("Found VP Matrix Uniform ", index, ": ", uniformName);
            PRIM_VP_MAT_UNIFORM_ID = index;
        }
        else {
            LS_LOG_MSG("Unknown shader uniform found: ", uniformName);
        }
    }
    
    s.unbind();
    LS_LOG_GL_ERR();
}

/*-------------------------------------
-------------------------------------*/
void HelloPrimState::setup_prims() {
    namespace draw = ls::draw;
    using draw::common_vertex_t;
    using draw::vertex_data_t;

    assert(vbo.init());
    vbo.bind();
    
    const std::unique_ptr<char[]>&& pData = gen_vertex_data();
    vbo.setup_attribs(draw::STANDARD_VERTEX);
    vbo.set_data(3 * draw::get_vertex_byte_size(draw::STANDARD_VERTEX), pData.get(), draw::buffer_access_t::VBO_STATIC_DRAW);
    vbo.unbind();

    draw::VAOAssembly * const pAssembly = new(std::nothrow) draw::VAOAssembly {};

    pAssembly->set_vbo_attribs(vbo);

    LS_ASSERT(pAssembly->set_attrib_name(0, draw::VERT_ATTRIB_NAME_POSITION));
    LS_ASSERT(pAssembly->set_attrib_name(1, draw::VERT_ATTRIB_NAME_TEXTURE));
    LS_ASSERT(pAssembly->set_attrib_name(2, draw::VERT_ATTRIB_NAME_NORMAL));
    LS_ASSERT(pAssembly->assemble(vao));

    LS_LOG_MSG("Validating there are 3 attributes within a VAO.");
    LS_ASSERT(vao.get_num_attribs() == 3);

    LS_LOG_MSG("Validating a VAO was successfully created.");
    LS_ASSERT(vao.is_valid());

    delete pAssembly;

}

/*-------------------------------------
 * System Startup
-------------------------------------*/
bool HelloPrimState::on_start() {
    using ls::draw::ShaderAttribArray;
    using ls::draw::VAOAttrib;

    setup_shaders();
    setup_prims();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);


    return true;
}

/*-------------------------------------
 * System Runtime
-------------------------------------*/
void HelloPrimState::on_run() {
    this->shader.bind();
    LS_LOG_GL_ERR();

    const ControlState* const pController = get_parent_system().get_game_state<ControlState>();
    const math::mat4& vpMatrix = pController->get_camera_view_projection();
    const math::mat4&& mvpMat = vpMatrix * modelMatrix;

    ls::draw::set_shader_uniform(PRIM_MODEL_MAT_UNIFORM_ID, modelMatrix);
    LS_LOG_GL_ERR();

    ls::draw::set_shader_uniform(PRIM_VP_MAT_UNIFORM_ID, vpMatrix);
    LS_LOG_GL_ERR();

    for (unsigned i = 0; i < LS_ARRAY_SIZE(testPositions); ++i) {
        const bool invisible = !draw::is_visible(testPositions[i], mvpMat);
        if (invisible) {
            LS_LOG_MSG(clock(), " CULLED POINT ", i, '!');
        }

        update_vert_color(i, invisible);
    }

    this->vao.bind();
    LS_LOG_GL_ERR();
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    LS_LOG_GL_ERR();
    
    this->vao.unbind();
    LS_LOG_GL_ERR();
    
    this->shader.unbind();
    LS_LOG_GL_ERR();
}

/*-------------------------------------
 * System Stop
-------------------------------------*/
void HelloPrimState::on_stop() {
    shader.terminate();
    vao.terminate();
    vbo.terminate();
}
