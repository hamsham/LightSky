/*
 * File:   HelloMeshState.cpp
 * Author: miles
 *
 * Created on October 27, 2015, 10:44 PM
 */

#include <cstddef> // offsetof
#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>

#include <SDL2/SDL.h>

#include "lightsky/setup/Setup.h"
#include "lightsky/math/Math.h"
#include "lightsky/utils/Utils.h"
#include "lightsky/draw/Draw.h"
#include "lightsky/game/Game.h"

#include "Display.h"
#include "HelloMeshState.h"
#include "ControlState.h"

namespace math = ls::math;
namespace draw = ls::draw;
namespace utils = ls::utils;
using draw::VAOAttrib;
using draw::ShaderAttribArray;


#ifndef LS_TEST_USE_PBR
    #define LS_TEST_USE_PBR 1
#endif

#ifndef LS_GAME_USE_ANIMS
    #define LS_GAME_USE_ANIMS 0
#endif

#if LS_GAME_USE_ANIMS
    #ifndef LS_GAME_TEST_MESH
        #define LS_GAME_TEST_MESH "testdata/rover/testmesh.dae"
    #else
        #define LS_GAME_TEST_MESH "testdata/sibenik/sibenik.obj"
    #endif /* LS_GAME_TEST_MESH */
#else
    #ifndef LS_GAME_TEST_MESH
        #define LS_GAME_TEST_MESH "testdata/sibenik/sibenik.obj"
    #endif /* LS_GAME_TEST_MESH */
#endif




///////////////////////////////////////////////////////////////////////////////
//  Mesh Shader
///////////////////////////////////////////////////////////////////////////////
namespace {

typedef std::chrono::duration<uint64_t, std::milli> milli_duration;
typedef std::chrono::steady_clock scene_clock_t;

/*-------------------------------------
 * Model Matrix Buffer
-------------------------------------*/
const char* MESH_TEXTURE_UNIFORM_STR = "DIFFUSE_TEXTURE";
unsigned MESH_TEXTURE_UNIFORM_ID = -1;
unsigned MESH_TEXTURE_UNIFORM_LOCATION = 0;

/*-------------------------------------
 * Mesh Vertex Shader
-------------------------------------*/
constexpr char vsShaderData[] = u8R"***(
//#version 300 es
#version 330 core

precision mediump float;

layout (location = 0) in vec3 posAttrib;
layout (location = 1) in vec2 uvAttrib;
layout (location = 2) in vec3 normAttrib;

struct Light
{
    vec4 pos;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct PointLight
{
    float constant;
    float linear;
    float quadratic;
    float padding;
};

struct SpotLight
{
    float innerCutoff;
    float outerCutoff;
    vec4 direction;
};

layout(shared) uniform BatchProperties {
    mat4 mvpMatrix;
    mat4 vpMatrix;
    mat4 modelMatrix;

    vec4 camPos;

    Light light;
    PointLight point;
    SpotLight spot;
} batchProperties;

out vec4 fragVertPos;
out vec4 fragVertUV;
out vec4 fragVertNorm;


void main() {
    gl_Position  = batchProperties.mvpMatrix * vec4(posAttrib, 1.0);
    fragVertPos  = batchProperties.modelMatrix * vec4(posAttrib, 1.0);
    fragVertUV   = uvAttrib.xyxy;
    fragVertNorm = normalize(batchProperties.modelMatrix * vec4(normAttrib, 0.0));
}
)***";

/*-------------------------------------
 * Mesh Fragment Shader
-------------------------------------*/
#if LS_TEST_USE_PBR

constexpr char fsShaderData[] = u8R"***(
//#version 300 es
#version 330 core

precision mediump float;

uniform sampler2D DIFFUSE_TEXTURE;

in vec4 fragVertPos;
in vec4 fragVertUV;
in vec4 fragVertNorm;

out vec4 fragOutColor;

struct Light
{
    vec4 pos;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct PointLight
{
    float constant;
    float linear;
    float quadratic;
    float padding;
};

struct SpotLight
{
    float innerCutoff;
    float outerCutoff;
    vec4 direction;
};

layout(shared) uniform BatchProperties {
    mat4 mvpMatrix;
    mat4 vpMatrix;
    mat4 modelMatrix;

    vec4 camPos;

    Light light;
    PointLight point;
    SpotLight spot;
} batchProperties;

// Calculate the metallic component of a surface
vec4 fresnel_schlick(float cosTheta, vec4 surfaceReflection)
{
    return surfaceReflection + (vec4(1.0) - surfaceReflection) * pow(1.0 - cosTheta, 5.0);
}



// normal distribution function within a hemisphere
float distribution_ggx(vec4 norm, vec4 hemisphere, float roughness)
{
    float roughSquared = roughness * roughness;
    float roughQuad    = roughSquared * roughSquared;
    float nDotH        = max(dot(norm, hemisphere), 0.0);
    float nDotH2       = nDotH * nDotH;
    float distribution = nDotH2 * (roughQuad - 1.0) + 1.0;

    return nDotH2 / (3.14159265 * distribution  * distribution);
}



// Determine how a surface's roughness affects how it reflects light
float geometry_schlick_ggx(float normDotView, float roughness)
{
    roughness += 1.0;
    roughness = (roughness*roughness) * 0.125; // 1/8

    float geometry = normDotView * (1. - roughness) + roughness;
    return normDotView / geometry;
}



// PBR Geometry function for determining how light bounces off a surface
float geometry_smith(vec4 norm, vec4 viewDir, vec4 radiance, float roughness)
{
    float normDotView = max(dot(norm, viewDir), 0.0);
    float normDotRad = max(dot(norm, radiance), 0.0);

    return geometry_schlick_ggx(normDotView, roughness) * geometry_schlick_ggx(normDotRad, roughness);
}



void main()
{
    vec4     pos       = vec4(fragVertPos.xyz, 0.0);
    vec2     uv        = fragVertUV.xy;
    vec4     norm      = normalize(vec4(fragVertNorm.xyz, 0.0));
    vec4     pixel     = vec4(texture(DIFFUSE_TEXTURE, fragVertUV.xy).xyz, 1.0);

    // gamma correction
    pixel = pow(pixel, vec4(2.2f, 2.2, 2.2, 1.0));

    // surface model
    vec4        camPos           = batchProperties.camPos;
    vec4        viewDir          = normalize(camPos - pos);
    vec4        lightPos         = batchProperties.light.pos;
    vec4        albedo           = pixel;
    const float metallic         = 0.4;
    const float roughness        = 0.35;
    const float ambientIntensity = 0.275;
    const float diffuseIntensity = 50.0;

    // Metallic reflectance at a normal incidence
    // 0.04f should be close to plastic.
    vec4 surfaceConstant   = vec4(0.4, 0.4, 0.4, 1.0);
    vec4 surfaceReflection = mix(surfaceConstant, albedo, metallic);

    vec4         lightDir0         = vec4(0.0);

    vec4         lightDirN         = lightPos - pos;
    float        distance          = length(lightDirN);
    lightDirN                      = lightDirN / distance; // normalize
    vec4         hemisphere        = normalize(viewDir + lightDirN);
    float        attenuation       = 1.0 / (distance*distance);
    vec4         radianceObj       = batchProperties.light.diffuse * attenuation * diffuseIntensity;

    float        ndf               = distribution_ggx(norm, hemisphere, roughness);
    float        geom              = geometry_smith(norm, viewDir, lightDirN, roughness);
    vec4         fresnel           = fresnel_schlick(max(dot(hemisphere, viewDir), 0.0), surfaceReflection);

    vec4         brdf              = fresnel * ndf * geom;
    float        cookTorrance      = 4.0 * max(dot(norm, viewDir), 0.0) * max(dot(norm, lightDirN), 0.0) + 0.000001;  // avoid divide-by-0
    vec4         specular          = brdf / cookTorrance;

    vec4         specContrib       = fresnel;
    vec4         refractRatio      = (vec4(1.0) - specContrib) * (vec4(1.0) - metallic);

    float        normDotLight      = max(dot(lightDirN, norm), 0.0);
    lightDir0                      += (refractRatio * albedo * 0.318309886 + specular) * radianceObj * normDotLight;

    vec4         ambient           = batchProperties.light.ambient * ambientIntensity;

    // Color normalization and light contribution
    vec4 outRGB = albedo * (ambient + lightDir0);

    // Tone mapping
    //outRGB /= outRGB + vec4(1.0, 1.0, 1.0, 0.0);

    // HDR Tone mapping
    const float exposure = 4.0;
    outRGB   = vec4(1.0) - exp(-outRGB * exposure);
    outRGB.a = 1.0;

    // Gamma correction
    //const vec3 gamma = vec3(1.0 / 2.2f);
    //outRGB.rgb = clamp(pow(outRGB.rgb, gamma), vec3(0.0), vec3(1.0));
    //outRGB.a = 1.0;

    fragOutColor = outRGB;
}


)***";

#else

constexpr char fsShaderData[] = u8R"***(
//#version 300 es
#version 330 core

precision mediump float;

uniform sampler2D DIFFUSE_TEXTURE;

in vec4 fragVertPos;
in vec4 fragVertUV;
in vec4 fragVertNorm;

out vec4 fragOutColor;

struct Light
{
    vec4 pos;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct PointLight
{
    float constant;
    float linear;
    float quadratic;
    float padding;
};

struct SpotLight
{
    float innerCutoff;
    float outerCutoff;
    vec4 direction;
};

layout(shared) uniform BatchProperties {
    mat4 mvpMatrix;
    mat4 vpMatrix;
    mat4 modelMatrix;

    vec4 camPos;

    Light light;
    PointLight point;
    SpotLight spot;
} batchProperties;



void main() {
    vec3 pos   = fragVertPos.xyz;
    vec3 uv    = fragVertUV.xyz;
    vec3 norm  = fragVertNorm.xyz;
    vec3 pixel = texture(DIFFUSE_TEXTURE, fragVertUV.xy).xyz;

    pixel.r = pixel.r == 0.0 ? 1.0 : pixel.r;
    pixel.g = pixel.g == 0.0 ? 1.0 : pixel.g;
    pixel.b = pixel.b == 0.0 ? 1.0 : pixel.b;

    float attenuation;
    vec3 diffuse, specular;

    // Light direction calculation
    Light l         = batchProperties.light;
    vec3  lightDir  = batchProperties.camPos.xyz - pos;
    float lightDist = length(lightDir);

    lightDir = normalize(lightDir);

    // Diffuse light calculation
    {
        float lightAngle = max(dot(lightDir, norm), 0.0);
        float constant   = batchProperties.point.constant;
        float linear     = batchProperties.point.linear;
        float quadratic  = batchProperties.point.quadratic;

        attenuation = 1.0 / (constant + (linear * lightDist) + (quadratic * lightDist * lightDist));
        diffuse     = l.diffuse.xyz * (lightAngle * attenuation);
    }

    // Specular light calculation
    {
        SpotLight s         = batchProperties.spot;
        float epsilon       = s.innerCutoff - s.outerCutoff;
        float theta         = dot(lightDir, s.direction.xyz);
        float spotIntensity = clamp((theta - s.outerCutoff) / epsilon, 0.0, 1.0);

        specular = l.specular.xyz * (spotIntensity * attenuation);
    }

    // output composition
    pixel = pixel * (diffuse + specular);
    fragOutColor = vec4(min(pixel, vec3(1.0)), 1.0);
}


)***";

#endif /* LS_TEST_USE_PBR */



/******************************************************************************
 * Normal/Tangent/Bitangent Visualizer
 ******************************************************************************/
constexpr char enbtVS[] = u8R"***(
//#version 300 es
#version 330 core

precision mediump float;

layout (location = 0) in vec3 posAttrib;
layout (location = 1) in vec3 normAttrib;

struct Light
{
    vec4 pos;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct PointLight
{
    float constant;
    float linear;
    float quadratic;
    float padding;
};

struct SpotLight
{
    float innerCutoff;
    float outerCutoff;
    vec4 direction;
};

layout(shared) uniform BatchProperties {
    mat4 mvpMatrix;
    mat4 vpMatrix;
    mat4 modelMatrix;

    vec4 camPos;

    Light light;
    PointLight point;
    SpotLight spot;
} batchProperties;

out vec4 normPos;

void main() {
    mat4 vpMat  = batchProperties.vpMatrix;
    mat4 mvpMat = vpMat * batchProperties.modelMatrix;
    gl_Position = mvpMat * vec4(posAttrib, 1.0);
    normPos     = mvpMat * vec4(normAttrib, 0.0);
}
)***";



const char enbtGS[] = u8R"***(
#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 21) out;

uniform bool showEdges      = true;
uniform bool showNormals    = true;

in vec4 normPos[];
out vec4 lineCol;

void main() {

    if (showNormals) {
        for (int i = 0; i < 3; ++i) {
            vec4 origin = gl_in[i].gl_Position;
            lineCol = vec4(0.0, 1.0, 0.0, 1.0);
            gl_Position = origin;
            EmitVertex();
            gl_Position = origin + normPos[i] * 0.025;
            EmitVertex();
            EndPrimitive();
        }
    }

    if (showEdges) {
        lineCol = vec4(1.0, 0.0, 1.0, 1.0);
        vec4 a = gl_in[0].gl_Position;
        vec4 b = gl_in[1].gl_Position;
        vec4 c = gl_in[2].gl_Position;
        gl_Position = a;
        EmitVertex();
        gl_Position = b;
        EmitVertex();
        EndPrimitive();
        gl_Position = b;
        EmitVertex();
        gl_Position = c;
        EmitVertex();
        EndPrimitive();
        gl_Position = c;
        EmitVertex();
        gl_Position = a;
        EmitVertex();
        EndPrimitive();
    }
}
)***";



constexpr char enbtFS[] = u8R"***(
//#version 300 es
#version 330 core

precision mediump float;

in vec4 lineCol;
out vec4 fragCol;

void main() {
    fragCol = lineCol;
}
)***";



} // end anonymous namespace



/*-----------------------------------------------------------------------------
 * Test Class
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Destructor
-------------------------------------*/
HelloMeshState::~HelloMeshState() {
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
HelloMeshState::HelloMeshState() {
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
HelloMeshState::HelloMeshState(HelloMeshState&& state) :
    GameState{}
{
    *this = std::move(state);
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
HelloMeshState& HelloMeshState::operator =(HelloMeshState&& state) {
    GameState::operator =(std::move(state));

    testShader = std::move(state.testShader);

    testData = std::move(state.testData);

    prevTime = std::move(state.prevTime);

    currentAnimationId = state.currentAnimationId;
    state.currentAnimationId = 0;

    currentAnimation = std::move(state.currentAnimation);

    uniformBlock = std::move(state.uniformBlock);

    meshShaderUboIndex = state.meshShaderUboIndex;
    state.meshShaderUboIndex = 0;
    enbtShaderUboIndex = state.enbtShaderUboIndex;
    state.enbtShaderUboIndex = 0;

    return *this;
}

/*-------------------------------------
-------------------------------------*/
void HelloMeshState::bind_shader_uniforms(const draw::ShaderProgram& s) {
    s.bind();
    LS_LOG_GL_ERR();

    const ShaderAttribArray& uniforms = s.get_uniforms();

    for (unsigned i = 0; i < uniforms.get_num_attribs(); ++i) {

        const utils::Pointer<GLchar[]>& uniformName = uniforms.get_attrib_name(i);
        const GLint index = s.get_uniform_location(uniformName.get());

        if (index < 0) {
            continue;
        }

        if (strcmp(uniformName.get(), MESH_TEXTURE_UNIFORM_STR) == 0) {
            LS_LOG_MSG("Found 2D Texture Uniform ", index, ": ", uniformName);
            MESH_TEXTURE_UNIFORM_ID = index;
            draw::set_shader_uniform_int(MESH_TEXTURE_UNIFORM_ID, draw::tex_slot_t::TEXTURE_SLOT_0);
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
void HelloMeshState::unbind_shader_uniforms() {
    LS_LOG_GL_ERR();

    MESH_TEXTURE_UNIFORM_ID = -1;
    MESH_TEXTURE_UNIFORM_LOCATION = 0;
}

/*-------------------------------------
-------------------------------------*/
void HelloMeshState::setup_shader(
    draw::ShaderProgram& s,
    const char* const vertData,
    const char* const fragData,
    const char* const geomData
) {
    draw::ShaderProgramAssembly shaderMaker;
    draw::ShaderObject vMeshShader, fMeshShader;

    LS_ASSERT(vMeshShader.init(draw::shader_stage_t::SHADER_STAGE_VERTEX, vertData, 0));
    LS_LOG_GL_ERR();
    LS_ASSERT(shaderMaker.set_vertex_shader(vMeshShader));

    LS_ASSERT(fMeshShader.init(draw::shader_stage_t::SHADER_STAGE_FRAGMENT, fragData, 0));
    LS_LOG_GL_ERR();
    LS_ASSERT(shaderMaker.set_fragment_shader(fMeshShader));

#ifdef LS_DRAW_BACKEND_GL
    draw::ShaderObject gMeshShader;
    if (geomData) {
        LS_ASSERT(gMeshShader.init(draw::shader_stage_t::SHADER_STAGE_GEOMETRY, geomData, 0));
        LS_LOG_GL_ERR();
        LS_ASSERT(shaderMaker.set_geometry_shader(gMeshShader));
    }
#endif
    // unused parameter warning
    (void)geomData;
    (void)enbtVS;
    (void)enbtFS;
    (void)enbtGS;

    LS_ASSERT(shaderMaker.is_assembly_valid());
    LS_ASSERT(shaderMaker.assemble(s, false));
    LS_ASSERT(shaderMaker.link(s));

    bind_shader_uniforms(s);

    vMeshShader.terminate();
    fMeshShader.terminate();

#ifdef LS_DRAW_BACKEND_GL
    gMeshShader.terminate();
#endif

    LS_LOG_GL_ERR();
}

/*-------------------------------------
 * Animation Setup
-------------------------------------*/
void HelloMeshState::setup_animations() {
    std::vector<draw::Animation>& sceneAnims = testData.animations;

    for (std::vector<draw::AnimationChannel>& animList : testData.nodeAnims) {
        for (draw::AnimationChannel& track : animList) {
            track.animationMode = draw::animation_flag_t::ANIM_FLAG_INTERPOLATE;
        }
    }

    LS_LOG_MSG("Running ", sceneAnims.size(), " animations.");

    currentAnimationId = 0;
    currentAnimation.set_play_state(draw::ANIM_STATE_PLAYING);
    currentAnimation.set_num_plays(draw::AnimationPlayer::PLAY_ONCE);
    currentAnimation.set_time_dilation(1.0);
}

/*-------------------------------------
 * System Startup
-------------------------------------*/
void HelloMeshState::setup_uniform_blocks() {
    int uboIndex = -1;

    LS_ASSERT(uniformBlock.init());
    LS_LOG_GL_ERR();

    uniformBlock.bind();
    LS_LOG_GL_ERR();

    LS_ASSERT(uniformBlock.setup_attribs(testShader, 0));
    LS_LOG_GL_ERR();

    {
        uboIndex = testShader.get_matching_uniform_block_index(uniformBlock);
        LS_ASSERT(uboIndex >= 0);

        meshShaderUboIndex = (unsigned)uboIndex;
        LS_ASSERT(draw::are_attribs_compatible(testShader, meshShaderUboIndex, uniformBlock) >= 0);
    }

    {
        math::vec4 val = {3.f, -5.f, 0.f, 1.f};
        uniformBlock.modify(offsetof(MeshUniforms, light.pos), sizeof(math::vec4), val.v);
        LS_LOG_GL_ERR();
    }
    {
        math::vec4 val = {0.25f, 0.25f, 0.25f, 1.f};
        uniformBlock.modify(offsetof(MeshUniforms, light.ambient), sizeof(math::vec4), val.v);
        LS_LOG_GL_ERR();
    }
    {
        math::vec4 val = {1.f, 1.f, 1.f, 1.f};
        uniformBlock.modify(offsetof(MeshUniforms, light.specular), sizeof(math::vec4), val.v);
        LS_LOG_GL_ERR();
    }
    {
        math::vec4 val = {0.5f, 0.5f, 0.5f, 1.f};
        uniformBlock.modify(offsetof(MeshUniforms, light.diffuse), sizeof(math::vec4), val.v);
        LS_LOG_GL_ERR();
    }
    {
        float val = 1.f;
        uniformBlock.modify(offsetof(MeshUniforms, point.constant), sizeof(float), &val);
        LS_LOG_GL_ERR();
    }
    {
        float val = 0.045f;
        uniformBlock.modify(offsetof(MeshUniforms, point.linear), sizeof(float), &val);
        LS_LOG_GL_ERR();
    }
    {
        float val = 0.009f;
        uniformBlock.modify(offsetof(MeshUniforms, point.quadratic), sizeof(float), &val);
        LS_LOG_GL_ERR();
    }
    {
        float val = std::cos(LS_DEG2RAD(6.5f));
        uniformBlock.modify(offsetof(MeshUniforms, spot.innerCutoff), sizeof(float), &val);
        LS_LOG_GL_ERR();
    }
    {
        float val = std::cos(LS_DEG2RAD(13.f));
        uniformBlock.modify(offsetof(MeshUniforms, spot.outerCutoff), sizeof(float), &val);
        LS_LOG_GL_ERR();
    }
    {
        math::vec4 val = {0.f, 0.f, -1.f, 1.f};
        uniformBlock.modify(offsetof(MeshUniforms, spot.direction), sizeof(math::vec4), val.v);
        LS_LOG_GL_ERR();
    }

#ifdef LS_DRAW_BACKEND_GL
    {
        uboIndex = enbtShader.get_matching_uniform_block_index(uniformBlock);
        LS_ASSERT(uboIndex >= 0);

        enbtShaderUboIndex = (unsigned)uboIndex;
        LS_ASSERT(draw::are_attribs_compatible(enbtShader, enbtShaderUboIndex, uniformBlock) >= 0);
    }
#endif

    uniformBlock.unbind();
    LS_LOG_GL_ERR();
}

/*-------------------------------------
 * Rendering Scene Nodes
-------------------------------------*/
uint32_t HelloMeshState::render_scene_node(uint32_t currentVao, const draw::SceneNode& n) {
    const ControlState* const pController = get_parent_system().get_game_state<ControlState>();
    const math::mat4& vpMat = pController->get_camera_view_projection();

    unsigned materialId = draw::material_property_t::INVALID_MATERIAL;
    size_t meshDataId = n.dataId;

    const std::vector<unsigned>& meshCounts = testData.nodeMeshCounts;
    const unsigned numMeshes = meshCounts[meshDataId];

    const std::vector<utils::Pointer<draw::DrawCommandParams[]>>& drawParamArray = testData.nodeMeshes;
    const utils::Pointer<draw::DrawCommandParams[]>& drawParams = drawParamArray[meshDataId];

    const std::vector<math::mat4>& matrices = testData.modelMatrices;
    const math::mat4& modelMatrix = matrices[n.nodeId];
    const math::mat4&& mvpMat = modelMatrix * vpMat;

    for (unsigned i = 0; i < numMeshes; ++i) {
        const draw::DrawCommandParams& params = drawParams[i];

        if (currentVao != params.vaoId) {
            currentVao = params.vaoId;
            glBindVertexArray(currentVao);
        }

#ifdef LS_DRAW_BACKEND_GL
        if (params.drawMode != draw::draw_mode_t::DRAW_MODE_TRIS) {
            continue;
        }
#endif

        materialId = params.materialId;

        if (materialId != draw::material_property_t::INVALID_MATERIAL) {
            testData.materials[materialId].bind();
        }

        uniformBlock.modify(offsetof(MeshUniforms, mvpMatrix), sizeof(math::mat4), &mvpMat);
        uniformBlock.modify(offsetof(MeshUniforms, modelMatrix), sizeof(math::mat4), &modelMatrix);

        LS_LOG_GL_ERR();

        switch (params.drawFunc) {
            case draw::draw_func_t::DRAW_ARRAYS:
                glDrawArrays(params.drawMode, params.first, params.count);
                LS_LOG_GL_ERR();
                break;

            case draw::draw_func_t::DRAW_ELEMENTS:
                glDrawElements(params.drawMode, params.count, params.indexType, params.offset);
                LS_LOG_GL_ERR();
                break;

            default:
                LS_ASSERT(false);
        }

        LS_LOG_GL_ERR();

        if (materialId != draw::material_property_t::INVALID_MATERIAL) {
            testData.materials[materialId].unbind();
        }
    }

    return currentVao;
}

/*-------------------------------------
 * Scene Graph Rendering
-------------------------------------*/
void HelloMeshState::render_scene_graph(const draw::ShaderProgram& s, const unsigned uboBindIndex) {
    uint32_t currentVao = 0;

    s.bind();
    LS_LOG_GL_ERR();

    uniformBlock.bind_base(uboBindIndex);
    LS_LOG_GL_ERR();

    for (const draw::SceneNode& node : testData.nodes) {
        if (node.type != draw::scene_node_t::NODE_TYPE_MESH) {
            continue;
        }

        currentVao = render_scene_node(currentVao, node);
    }

    glBindVertexArray(0);

    uniformBlock.unbind();
    LS_LOG_GL_ERR();

    s.unbind();
    LS_LOG_GL_ERR();
}

/*-------------------------------------
 * Animation updating
-------------------------------------*/
void HelloMeshState::update_animations() {
    if (testData.animations.empty()) {
        return;
    }

    const scene_clock_t::time_point&& currTime = scene_clock_t::now();
    const scene_clock_t::duration&& tickDuration = currTime - prevTime;
    prevTime = currTime;
    const milli_duration&& tickTime = std::chrono::duration_cast<milli_duration>(tickDuration);

    // Play the current animation until it stops. Then move onto the next animation.
    if (currentAnimation.is_stopped()) {
        std::vector<draw::Animation>& animations = testData.animations;
        currentAnimationId = (currentAnimationId + 1) % animations.size();
        
        // reset the transformations in a graph to those at the beginning of an animation
        draw::Animation& initialState = testData.animations[currentAnimationId];
        initialState.init(testData);

        currentAnimation.set_play_state(draw::animation_state_t::ANIM_STATE_PLAYING);
        currentAnimation.set_num_plays(draw::AnimationPlayer::PLAY_ONCE);
    }

    currentAnimation.tick(testData, currentAnimationId, tickTime.count());
}

/*-------------------------------------
 * System Startup
-------------------------------------*/
bool HelloMeshState::on_start() {
    srand(time(nullptr));
    setup_shader(testShader, vsShaderData, fsShaderData);

#ifdef LS_DRAW_BACKEND_GL
    setup_shader(enbtShader, enbtVS, enbtFS, enbtGS);
#endif

    setup_uniform_blocks();

    preloader = std::async(std::launch::async, [&]()->draw::SceneFilePreLoader {
        draw::SceneFilePreLoader loader;
        loader.load(LS_GAME_TEST_MESH);
        return loader;
    });

    //utils::Pointer<draw::SceneFileLoader> meshLoader {new draw::SceneFileLoader{}};

    LS_LOG_GL_ERR();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    //prevTime = std::move(scene_clock_t::now());
    prevTime = scene_clock_t::now();

    return true;
}

/*-------------------------------------
 * System Runtime
-------------------------------------*/
void HelloMeshState::on_run() {
    // this statement cannot be called from another function (GCC/CLang bug)
    if (preloader.valid() && preloader.wait_for(std::chrono::milliseconds{0}) == std::future_status::ready) {
        draw::SceneFileLoader loader;
        loader.load(preloader.get());

        testData = std::move(loader.get_loaded_data());
        setup_animations();
    }
    else {
        update_animations();
        testData.update();
    }

    uniformBlock.bind();
    LS_LOG_GL_ERR();

    const ControlState* const pController = get_parent_system().get_game_state<ControlState>();
    {
        const math::mat4& vpMat = pController->get_camera_view_projection();
        uniformBlock.modify(offsetof(MeshUniforms, vpMatrix), sizeof(math::mat4), vpMat.m);
        LS_LOG_GL_ERR();
    }
    {
        const draw::Transform& camTrans = pController->get_camera_transformation();
        const math::vec3&&     camPos3  = -camTrans.get_position();
        const math::vec4       camPos   = {camPos3[0], camPos3[1], camPos3[2], 1.f};
        const math::mat4&      viewMat  = camTrans.get_transform();
        const math::vec4&&     spotDir  = math::normalize(math::vec4{viewMat[0][2], viewMat[1][2], viewMat[2][2], 0.f});

        uniformBlock.modify(offsetof(MeshUniforms, camPos), sizeof(math::vec4), &camPos);
        uniformBlock.modify(offsetof(MeshUniforms, light.pos), sizeof(math::vec4), math::vec4{3.f, -5.f, 0.f, 1.f}.v);
        uniformBlock.modify(offsetof(MeshUniforms, spot.direction), sizeof(spotDir), &spotDir.v);
    }
    LS_LOG_GL_ERR();

    uniformBlock.unbind();
    LS_LOG_GL_ERR();

    render_scene_graph(testShader, meshShaderUboIndex);

#ifdef LS_DRAW_BACKEND_GL
    //render_scene_graph(enbtShader, enbtShaderUboIndex);
#endif
}

/*-------------------------------------
 * System Stop
-------------------------------------*/
void HelloMeshState::on_stop() {
    testShader.terminate();
    enbtShader.terminate();
    testData.terminate();
    currentAnimationId = 0;
    currentAnimation.reset();
    uniformBlock.terminate();
}
