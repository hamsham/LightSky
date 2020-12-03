/*
 * File:   HelloTextState.cpp
 * Author: miles
 *
 * Created on October 27, 2015, 10:44 PM
 */

#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>

#include "lightsky/utils/DataResource.h"

#include "lightsky/draw/FontResource.h"
#include "lightsky/draw/ShaderUniform.h"
#include "lightsky/draw/ShaderAssembly.h"
#include "lightsky/draw/RenderValidation.h"
#include "lightsky/draw/OcclusionMeshLoader.h"
#include "lightsky/draw/TextMeshLoader.h"
#include "lightsky/draw/TextureAssembly.h"
#include "lightsky/draw/FBOAssembly.h"
#include "lightsky/draw/FBOAttrib.h"
#include "lightsky/draw/RBOAssembly.h"

#include "MainState.h"
#include "Display.h"
#include "HelloTextState.h"
#include "ControlState.h"

namespace math = ls::math;
namespace draw = ls::draw;
namespace utils = ls::utils;
using draw::VAOAttrib;
using draw::ShaderAttribArray;


#ifndef LS_GAME_TEST_FONT
    #define LS_GAME_TEST_FONT "testdata/testfont.ttf"
#endif

///////////////////////////////////////////////////////////////////////////////
//  TEXT SHADER
///////////////////////////////////////////////////////////////////////////////
/*-------------------------------------
 * Camera/VP Matrix Uniform Name
-------------------------------------*/
const char* TEXT_VP_MATRIX_UNIFORM_STR = "vpMatrix";
unsigned TEXT_VP_MATRIX_UNIFORM_ID = -1;

/*-------------------------------------
 * Camera/VP Matrix Uniform Name
-------------------------------------*/
const char* TEXT_COLOR_UNIFORM_STR = "textColor";
unsigned TEXT_COLOR_UNIFORM_ID = -1;

/*-------------------------------------
 * Text Atlas Location
-------------------------------------*/
const char* TEXT_ATLAS_UNIFORM_STR = "textAtlas";
unsigned TEXT_ATLAS_UNIFORM_ID = -1;

/*-------------------------------------
 * Model Matrix Buffer
-------------------------------------*/
const char* TEXT_MODEL_MAT_UNIFORM_STR = "matrixBuffer";
unsigned TEXT_MODEL_MAT_UNIFORM_ID = -1;

/*-------------------------------------
 * Text Vertex Shader
-------------------------------------*/
constexpr char vsTextShaderData[] = u8R"***(
#version 330 core
//#version 300 es

precision mediump float;

layout (location = 0) in vec3 posAttrib;
layout (location = 1) in vec2 uvAttrib;
layout (location = 2) in vec3 normAttrib;
layout (location = 3) in int indexAttrib;

uniform sampler2D matrixBuffer;
uniform mat4 vpMatrix;

out vec2 uvCoords;

mat4 get_model_matrix(const int matId) {
    return mat4(
        texelFetch(matrixBuffer, ivec2(0, matId), 0),
        texelFetch(matrixBuffer, ivec2(1, matId), 0),
        texelFetch(matrixBuffer, ivec2(2, matId), 0),
        texelFetch(matrixBuffer, ivec2(3, matId), 0)
    );
}

void main() {
    mat4 mvp = vpMatrix * get_model_matrix(indexAttrib);
    gl_Position = mvp * vec4(posAttrib, 1.0);
    uvCoords = uvAttrib;
}
)***";

/*-------------------------------------
 * Text Fragment Shader (with pseudo signed-distance field)
-------------------------------------*/
constexpr char fsTextShaderData[] = u8R"***(
#version 330 core
//#version 300 es

precision mediump float;

in vec2 uvCoords;

out vec4 outFragCol;

uniform sampler2D textAtlas;
uniform vec4 textColor;

void main() {
    float mask = texture(textAtlas, uvCoords).r;
    outFragCol = textColor*step(0.5, mask);
}
)***";

///////////////////////////////////////////////////////////////////////////////
//  OCCLUSION SHADER
///////////////////////////////////////////////////////////////////////////////
/*-------------------------------------
 * Camera/VP Matrix Uniform Name
-------------------------------------*/
const char* OCCLUDE_VP_MATRIX_UNIFORM_STR = "vpMatrix";
unsigned OCCLUDE_VP_MATRIX_UNIFORM_ID = -1;

/*-------------------------------------
 * Model Matrix Buffer
-------------------------------------*/
const char* OCCLUDE_MODEL_MAT_UNIFORM_STR = "matrixBuffer";
unsigned OCCLUDE_MODEL_MAT_UNIFORM_ID = -1;

/*-------------------------------------
 * Occlusion Vertex Shader
-------------------------------------*/
constexpr char const* vsTextOccludeData = u8R"***(
#version 330 core
//#version 300 es

precision mediump float;

layout (location = 0) in vec3 posAttrib;
layout (location = 1) in vec3 bboxTRRAttrib;
layout (location = 2) in vec3 bboxBFLAttrib;

uniform sampler2D matrixBuffer;
uniform mat4 vpMatrix;

flat out int meshId;

mat4 get_model_matrix(const in int matId) {
    return mat4(
        texelFetch(matrixBuffer, ivec2(0, matId), 0),
        texelFetch(matrixBuffer, ivec2(1, matId), 0),
        texelFetch(matrixBuffer, ivec2(2, matId), 0),
        texelFetch(matrixBuffer, ivec2(3, matId), 0)
    );
}

vec3 get_bounding_box_extent(const in int vertId) {
    switch (vertId) {
        case 0: return  vec3(bboxTRRAttrib.x, bboxTRRAttrib.y, bboxBFLAttrib.z);
        case 1: return  vec3(bboxBFLAttrib.x, bboxTRRAttrib.y, bboxBFLAttrib.z);
        case 2: return  vec3(bboxTRRAttrib.x, bboxTRRAttrib.y, bboxTRRAttrib.z);
        case 3: return  vec3(bboxBFLAttrib.x, bboxTRRAttrib.y, bboxTRRAttrib.z);
    
        case 4: return  vec3(bboxBFLAttrib.x, bboxBFLAttrib.y, bboxTRRAttrib.z);
        case 5: return  vec3(bboxBFLAttrib.x, bboxTRRAttrib.y, bboxBFLAttrib.z);
        case 6: return  vec3(bboxBFLAttrib.x, bboxBFLAttrib.y, bboxBFLAttrib.z);
        case 7: return  vec3(bboxTRRAttrib.x, bboxTRRAttrib.y, bboxBFLAttrib.z);
    
        case 8: return  vec3(bboxTRRAttrib.x, bboxBFLAttrib.y, bboxBFLAttrib.z);
        case 9: return  vec3(bboxTRRAttrib.x, bboxTRRAttrib.y, bboxTRRAttrib.z);
        case 10: return vec3(bboxTRRAttrib.x, bboxBFLAttrib.y, bboxTRRAttrib.z);
        case 11: return vec3(bboxBFLAttrib.x, bboxTRRAttrib.y, bboxTRRAttrib.z);
    
        case 12: return vec3(bboxBFLAttrib.x, bboxBFLAttrib.y, bboxTRRAttrib.z);
        case 13: return vec3(bboxBFLAttrib.x, bboxBFLAttrib.y, bboxBFLAttrib.z);
        case 14: return vec3(bboxTRRAttrib.x, bboxBFLAttrib.y, bboxTRRAttrib.z);
        case 15: return vec3(bboxTRRAttrib.x, bboxBFLAttrib.y, bboxBFLAttrib.z);
    
        default: break;
    }
    
    return vec3(-1.0);
}

void main() {
    meshId = gl_InstanceID;
    
    mat4 mvp = vpMatrix * get_model_matrix(gl_InstanceID);
    vec3 bbVertPos = get_bounding_box_extent(gl_VertexID);
    gl_Position = mvp * vec4(bbVertPos, 1.0);
}
)***";

/*-------------------------------------
 * Occlusion frag shader
-------------------------------------*/
constexpr char fsTextOccludeData[] = u8R"***(
#version 330 core
//#version 300 es

precision highp float;

flat in int meshId;

out vec4 outFragCol;

vec4 instance_id_to_color(in int objId) {
    const float normFactor = 1.0 / 255.0;
    
    return vec4(
        float((objId & 0x000000FF) >> 0) * normFactor,
        float((objId & 0x0000FF00) >> 8) * normFactor,
        float((objId & 0x00FF0000) >> 16) * normFactor,
        1.f
    );
}

void main() {
    outFragCol = instance_id_to_color(meshId);
}
)***";



/*-------------------------------------
 * Helper function to load text data.
-------------------------------------*/
std::string load_test_text(const std::string& filename = u8R"(testdata/lorem_ipsum.txt)") {
    using ls::utils::DataResource;

    DataResource inFile;

    if (!inFile.load_file(filename)) {
        return "Hello\nWorld!";
    }

    return inFile.get_data_as_str();
}



/*-----------------------------------------------------------------------------
 * Test Class
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Destructor
-------------------------------------*/
HelloTextState::~HelloTextState() {
}

/*-------------------------------------
 * Constructor
-------------------------------------*/
HelloTextState::HelloTextState() {
}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
HelloTextState::HelloTextState(HelloTextState&& state) :
    GameState{}
{
    *this = std::move(state);
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
HelloTextState& HelloTextState::operator =(HelloTextState&& state) {
    GameState::operator =(std::move(state));
    
    useOcclusionBuffer = state.useOcclusionBuffer;
    state.useOcclusionBuffer = false;

    textShader      = std::move(state.textShader);
    occlusionShader = std::move(state.occlusionShader);
    atlas           = std::move(state.atlas);
    occlusionFbo    = std::move(state.occlusionFbo);
    occlusionDepth  = std::move(state.occlusionDepth);
    occlusionTarget = std::move(state.occlusionTarget);
    matrixBuf       = std::move(state.matrixBuf);
    textMesh        = std::move(state.textMesh);
    occlusionMeshes = std::move(state.occlusionMeshes);
    meshesInScene   = std::move(state.meshesInScene);
    
    currentPbo = state.currentPbo;
    state.currentPbo = 0;
    
    for (unsigned i = 0; i < LS_ARRAY_SIZE(occlusionPbos); ++i) {
        occlusionPbos[i] = std::move(state.occlusionPbos[i]);
    }

    return *this;
}

/*-------------------------------------
-------------------------------------*/
void HelloTextState::setup_text_shader() {
    draw::ShaderObject vTextShader, fTextShader;

    if (!vTextShader.init(draw::SHADER_STAGE_VERTEX, vsTextShaderData, 0)) {
        LS_LOG_GL_ERR();
        LS_ASSERT(false);
    }
    LS_LOG_GL_ERR();

    if (!fTextShader.init(draw::SHADER_STAGE_FRAGMENT, fsTextShaderData, 0)) {
        LS_LOG_GL_ERR();
        LS_ASSERT(false);
    }
    LS_LOG_GL_ERR();

    draw::ShaderProgramAssembly shaderMaker;
    LS_ASSERT(shaderMaker.set_vertex_shader(vTextShader));
    LS_ASSERT(shaderMaker.set_fragment_shader(fTextShader));
    LS_ASSERT(shaderMaker.is_assembly_valid());
    LS_ASSERT(shaderMaker.assemble(textShader, false));
    LS_ASSERT(shaderMaker.link(textShader));

    const ShaderAttribArray& uniforms = textShader.get_uniforms();

    for (unsigned i = 0; i < uniforms.get_num_attribs(); ++i) {
        const utils::Pointer<GLchar[]>& uniformName = uniforms.get_attrib_name(i);
        const GLint index = textShader.get_uniform_location(uniformName.get());

        if (index < 0) {
            continue;
        }

        if (strcmp(uniformName.get(), TEXT_VP_MATRIX_UNIFORM_STR) == 0) {
            LS_LOG_MSG("Found VP Matrix Uniform ", index, ": ", uniformName);
            TEXT_VP_MATRIX_UNIFORM_ID = index;
        }
        else if (strcmp(uniformName.get(), TEXT_COLOR_UNIFORM_STR) == 0) {
            LS_LOG_MSG("Found Text Color Uniform ", index, ": ", uniformName);
            TEXT_COLOR_UNIFORM_ID = index;
        }
        else if (strcmp(uniformName.get(), TEXT_ATLAS_UNIFORM_STR) == 0) {
            LS_LOG_MSG("Found Text Atlas Uniform ", index, ": ", uniformName);
            TEXT_ATLAS_UNIFORM_ID = index;
        }
        else if (strcmp(uniformName.get(), TEXT_MODEL_MAT_UNIFORM_STR) == 0) {
            LS_LOG_MSG("Found Model Matrix Buffer Uniform ", index, ": ", uniformName);
            TEXT_MODEL_MAT_UNIFORM_ID = index;
        }
    }

    vTextShader.terminate();
    fTextShader.terminate();
}

/*-------------------------------------
-------------------------------------*/
void HelloTextState::setup_occlusion_shader() {
    draw::ShaderObject vOccludeShader, fOccludeShader;
    
    if (!vOccludeShader.init(draw::SHADER_STAGE_VERTEX, vsTextOccludeData, 0)) {
        LS_LOG_GL_ERR();
        LS_ASSERT(false);
    }
    LS_LOG_GL_ERR();

    if (!fOccludeShader.init(draw::SHADER_STAGE_FRAGMENT, fsTextOccludeData, 0)) {
        LS_LOG_GL_ERR();
        LS_ASSERT(false);
    }
    LS_LOG_GL_ERR();

    draw::ShaderProgramAssembly shaderMaker;
    LS_ASSERT(shaderMaker.set_vertex_shader(vOccludeShader));
    LS_ASSERT(shaderMaker.set_fragment_shader(fOccludeShader));
    LS_ASSERT(shaderMaker.is_assembly_valid());
    LS_ASSERT(shaderMaker.assemble(occlusionShader, false));
    LS_ASSERT(shaderMaker.link(occlusionShader));

    const ShaderAttribArray& uniforms = occlusionShader.get_uniforms();

    for (unsigned i = 0; i < uniforms.get_num_attribs(); ++i) {
        const utils::Pointer<GLchar[]>& uniformName = uniforms.get_attrib_name(i);
        const GLint index = occlusionShader.get_uniform_location(uniformName.get());

        if (index < 0) {
            continue;
        }

        if (strcmp(uniformName.get(), OCCLUDE_VP_MATRIX_UNIFORM_STR) == 0) {
            LS_LOG_MSG("Found VP Matrix Uniform ", index, ": ", uniformName);
            OCCLUDE_VP_MATRIX_UNIFORM_ID = index;
        }
        else if (strcmp(uniformName.get(), OCCLUDE_MODEL_MAT_UNIFORM_STR) == 0) {
            LS_LOG_MSG("Found Model Matrix Buffer Uniform ", index, ": ", uniformName);
            OCCLUDE_MODEL_MAT_UNIFORM_ID = index;
        }
    }
    
    vOccludeShader.terminate();
    fOccludeShader.terminate();
}

/*-------------------------------------
-------------------------------------*/
void HelloTextState::setup_occlusion_fbo() {
    namespace utils = ls::utils;
    namespace draw = ls::draw;
    namespace math = ls::math;

    const math::vec2i fboRes = {256, 128};
    draw::TextureAttrib texAttrib;

    {
        draw::RBOAttrib rboAttrib;
        rboAttrib.set_internal_format(draw::rbo_format_t::RBO_FMT_DEPTH_16);

        utils::Pointer<draw::RBOAssembly> rboAssembly {new(std::nothrow) draw::RBOAssembly {}};
        LS_ASSERT(rboAssembly->set_attribs(rboAttrib));
        LS_ASSERT(rboAssembly->set_size_attrib(fboRes));
        LS_ASSERT(rboAssembly->assemble(occlusionDepth));
    }
    {
        texAttrib.set_internal_format(draw::pixel_format_t::COLOR_FMT_DEFAULT_RGBA);
        texAttrib.set_filtering(draw::tex_filter_t::TEX_FILTER_NEAREST, draw::tex_filter_t::TEX_FILTER_NEAREST);

        utils::Pointer<draw::TextureAssembly> texAssembly {new(std::nothrow) draw::TextureAssembly {}};
        LS_ASSERT(texAssembly->set_attribs(texAttrib));
        LS_ASSERT(texAssembly->set_size_attrib(fboRes));
        LS_ASSERT(texAssembly->assemble(occlusionTarget));
    }
    {
        utils::Pointer<draw::FBOAssembly> fboAssembly {new(std::nothrow) draw::FBOAssembly {}};

        LS_ASSERT(fboAssembly->set_attrib(0, occlusionTarget, draw::fbo_attach_t::FBO_ATTACHMENT_0));
        LS_ASSERT(fboAssembly->set_attrib(1, occlusionDepth, draw::fbo_attach_t::FBO_ATTACHMENT_DEPTH));
        LS_ASSERT(fboAssembly->assemble(occlusionFbo));
    }
    {
        const unsigned components       = draw::get_num_pixel_components(texAttrib.get_internal_format());
        const unsigned bytesPerPixel    = draw::get_num_color_bytes(texAttrib.get_color_type());
        const unsigned numPixels        = fboRes[0] * fboRes[1];
        const unsigned numBytes         = numPixels * components * bytesPerPixel;
        
        for (draw::PixelBuffer& pbo : occlusionPbos) {
            pbo.set_transfer_mode(draw::pixel_transfer_t::PIXEL_TRANSFER_DOWNLOAD);
            LS_ASSERT(pbo.init());
            
            pbo.bind();
            LS_LOG_GL_ERR();
            
            pbo.set_data(numBytes, nullptr, draw::buffer_access_t::VBO_STREAM_DRAW);
            LS_LOG_GL_ERR();
            
            pbo.unbind();
            LS_LOG_GL_ERR();
        }
    }
}

/*-------------------------------------
-------------------------------------*/
void HelloTextState::setup_atlas() {
    ls::utils::Pointer<draw::FontResource> pFont;

    pFont.reset(new draw::FontResource {});

    assert(pFont->load_file(LS_GAME_TEST_FONT, 72));
    assert(atlas.init(*pFont));
}

/*-------------------------------------
-------------------------------------*/
void HelloTextState::create_matrix_buffer() {
    const size_t numMeshes = textMesh.meshes.size();
    const math::vec2i bufSize {4, (int)numMeshes};

    {
        ls::utils::Pointer<draw::TextureAssembly> texAssembly {new draw::TextureAssembly{}};
        texAssembly->set_size_attrib(bufSize, draw::tex_type_t::TEX_TYPE_2D, draw::tex_2d_type_t::TEX_SUBTYPE_2D);
        texAssembly->set_format_attrib(draw::pixel_format_t::COLOR_FMT_RGBA_32F);
        texAssembly->set_int_attrib(draw::tex_param_t::TEX_PARAM_MIN_FILTER, draw::tex_filter_t::TEX_FILTER_NEAREST);
        texAssembly->set_int_attrib(draw::tex_param_t::TEX_PARAM_MAG_FILTER, draw::tex_filter_t::TEX_FILTER_NEAREST);
        texAssembly->set_int_attrib(draw::tex_param_t::TEX_PARAM_WRAP_S, draw::tex_wrap_t::TEX_WRAP_CLAMP);
        texAssembly->set_int_attrib(draw::tex_param_t::TEX_PARAM_WRAP_T, draw::tex_wrap_t::TEX_WRAP_CLAMP);
        LS_ASSERT(texAssembly->assemble(matrixBuf, nullptr));
    }

    matrixBuf.bind();
    LS_LOG_GL_ERR();

    // async copy of model matrices into a texture object.
    // Hopefully this prevents any pipeline stalls
    {
        const size_t numBytes = sizeof (math::mat4) * numMeshes;
        draw::PixelBuffer matrixPbo;
        
        LS_ASSERT(matrixPbo.init());
        LS_LOG_GL_ERR();

        matrixPbo.bind();
        LS_LOG_GL_ERR();
        
        matrixPbo.set_data((ptrdiff_t)numBytes, nullptr, draw::buffer_access_t::VBO_STREAM_DRAW);
        LS_LOG_GL_ERR();

        math::mat4 * const pMatrices = (math::mat4*)matrixPbo.map_data(0, (ptrdiff_t)numBytes, draw::TextMeshLoader::DEFAULT_VBO_MAP_FLAGS);
        LS_LOG_GL_ERR();

        std::fill(pMatrices, pMatrices + numMeshes, math::mat4 {1.f});
        matrixPbo.unmap_data();
        LS_LOG_GL_ERR();

        matrixBuf.modify(draw::tex_2d_type_t::TEX_SUBTYPE_2D, math::vec2i {0}, bufSize, matrixPbo);
        LS_LOG_GL_ERR();

        matrixPbo.unbind();
        LS_LOG_GL_ERR();
        
        matrixPbo.terminate();
        LS_LOG_GL_ERR();
    }
}

/*-------------------------------------
-------------------------------------*/
void HelloTextState::setup_occluders() {
    draw::OcclusionMeshLoader loader;
    const std::vector<draw::BoundingBox>& textBoxes = textMesh.bounds;
    
    LS_ASSERT(loader.load((unsigned)textBoxes.size()));
    
    occlusionMeshes = std::move(loader.get_mesh());
    
    draw::VertexBuffer& boundsVbo = occlusionMeshes.renderData.vbos.back();
    
    boundsVbo.bind();
    LS_LOG_GL_ERR();
    
    // inject bounding boxes from the text mesh into the occlusion fbo
    const size_t numBytes = textBoxes.size() * sizeof(draw::BoundingBox);
    LS_LOG_MSG("UPLOADING ", numBytes, " BYTES OF DATA FOR AN OCCLUSION VBO");
    boundsVbo.modify(0, (ptrdiff_t)numBytes, textBoxes.data());
    LS_LOG_GL_ERR();
    
    boundsVbo.unbind();
    LS_LOG_GL_ERR();
}

/*-------------------------------------
-------------------------------------*/
void HelloTextState::setup_text() {
    using draw::common_vertex_t;

    constexpr common_vertex_t vertTypes = (common_vertex_t)(0
        | common_vertex_t::POSITION_VERTEX
        | common_vertex_t::TEXTURE_VERTEX
        | common_vertex_t::INDEX_VERTEX
        | 0);

    ls::utils::Pointer<draw::TextMeshLoader> textLoader {new draw::TextMeshLoader{}};
    const std::string&& text = load_test_text();
    const unsigned numTextIndices = textLoader->load(text, vertTypes, atlas, true);
    textMesh = std::move(textLoader->get_mesh());

    LS_ASSERT(numTextIndices > 0);

    textShader.bind();
    LS_LOG_GL_ERR();

    draw::set_shader_uniform(TEXT_COLOR_UNIFORM_ID, ls::math::vec4 {0.f, 1.f, 0.f, 1.f});
    LS_LOG_GL_ERR();

    draw::set_shader_uniform_int(TEXT_ATLAS_UNIFORM_ID, draw::TEXTURE_SLOT_0);
    LS_LOG_GL_ERR();

    draw::set_shader_uniform_int(TEXT_MODEL_MAT_UNIFORM_ID, draw::TEXTURE_SLOT_1);
    LS_LOG_GL_ERR();

    textShader.unbind();
    LS_LOG_GL_ERR();
}

/*-------------------------------------
 * Render visible text
-------------------------------------*/
void HelloTextState::draw_occlusion_data(const ls::math::mat4& vpMatrix) {
    const math::vec2i&& displayRes = {occlusionFbo.get_size()[0], occlusionFbo.get_size()[1]};
    glViewport(0, 0, displayRes[0], displayRes[1]);
    
    occlusionFbo.bind(draw::fbo_access_t::FBO_ACCESS_W);
    LS_LOG_GL_ERR();
    occlusionFbo.set_draw_targets();
    LS_LOG_GL_ERR();
    occlusionFbo.clear_depth_buffer(0.f);
    LS_LOG_GL_ERR();
    occlusionFbo.clear_color_buffer(draw::fbo_attach_t::FBO_ATTACHMENT_0, draw::color::white);
    LS_LOG_GL_ERR();

    occlusionShader.bind();
    LS_LOG_GL_ERR();

    draw::set_shader_uniform(OCCLUDE_VP_MATRIX_UNIFORM_ID, vpMatrix);
    LS_LOG_GL_ERR();

    occlusionMeshes.renderData.vaos.front().bind();
    LS_LOG_GL_ERR();

    glActiveTexture(draw::TEXTURE_SLOT_GPU_OFFSET + draw::TEXTURE_SLOT_0);
    LS_LOG_GL_ERR();
    matrixBuf.bind();
    LS_LOG_GL_ERR();

    constexpr unsigned vertCount = draw::OCCLUSION_BOX_NUM_VERTS;
    const unsigned numInstances = (unsigned)occlusionMeshes.bounds.size();
    glDrawArraysInstanced(draw::draw_mode_t::DRAW_MODE_TRIS, 0, vertCount, numInstances);
    LS_LOG_GL_ERR();
    
    glActiveTexture(draw::TEXTURE_SLOT_GPU_OFFSET + draw::TEXTURE_SLOT_0);
    LS_LOG_GL_ERR();
    matrixBuf.unbind();
    LS_LOG_GL_ERR();

    occlusionMeshes.renderData.vaos.front().bind();
    LS_LOG_GL_ERR();

    occlusionShader.unbind();
    LS_LOG_GL_ERR();
    
    occlusionFbo.unbind();
    LS_LOG_GL_ERR();
}

/*-------------------------------------
-------------------------------------*/
void HelloTextState::read_occlusion_data() {
    const math::vec3i& dimens       = occlusionTarget.get_size();
    const draw::TextureAttrib& a    = occlusionTarget.get_attribs();
    const unsigned components       = draw::get_num_pixel_components(a.get_internal_format());
    const unsigned bytesPerPixel    = draw::get_num_color_bytes(a.get_color_type());
    const unsigned numPixels        = dimens[0] * dimens[1];
    const unsigned numBytes         = numPixels * components * bytesPerPixel;
    
    
    meshesInScene.clear();
    meshesInScene.reserve(numBytes);
    
    draw::FrameBuffer::bind_default_framebuffer(draw::fbo_access_t::FBO_ACCESS_W);
    LS_LOG_GL_ERR();
    
    occlusionFbo.bind(draw::fbo_access_t::FBO_ACCESS_R);
    LS_LOG_GL_ERR();
    
    occlusionFbo.set_read_target(0);
    
    // Tell openGL to copy the current framebuffer to a PBO
    {
        const draw::PixelBuffer& readPbo = occlusionPbos[currentPbo];
        readPbo.bind();
        LS_LOG_GL_ERR();

        glReadPixels(0, 0, dimens[0], dimens[1], a.get_internal_format(), a.get_color_type(), nullptr);
        LS_LOG_GL_ERR();

        readPbo.unbind();
        LS_LOG_GL_ERR();
    }
    
    // Switch to a PBO that's not queued for writing to RAM. This allows PBO
    // data to be inspected asynchronously
    currentPbo = (currentPbo + 1) % LS_ARRAY_SIZE(occlusionPbos);
    
    {
        const draw::PixelBuffer& writePbo = occlusionPbos[currentPbo];
        writePbo.bind();
        LS_LOG_GL_ERR();

        const draw::color::colorub_t* const pPixels =
            (draw::color::colorub_t*)writePbo.map_data(0, numBytes, draw::buffer_map_t::VBO_MAP_BIT_READ);
        LS_LOG_GL_ERR();

        for (unsigned i = 0; i < numPixels; ++i) {
            const draw::color::colorub_t c = pPixels[i];

            if (c != draw::color::color_float_to_int<unsigned char>(draw::color::white)) {
                const unsigned meshId = draw::color::color_to_id(c);
                meshesInScene.push_back(meshId);
            }
        }

        writePbo.unmap_data();
        LS_LOG_GL_ERR();

        writePbo.unbind();
        LS_LOG_GL_ERR();
    }
    
    //occlusionFbo.blit({0, 0}, {256, 128}, {0, 0}, {800, 600}, draw::fbo_mask_t::FBO_COLOR_BIT, draw::tex_filter_t::TEX_FILTER_LINEAR);
    //LS_LOG_GL_ERR();
    
    occlusionFbo.unbind();
    LS_LOG_GL_ERR();
    
    draw::FrameBuffer::bind_default_framebuffer(draw::fbo_access_t::FBO_ACCESS_RW);
    LS_LOG_GL_ERR();
}

/*-------------------------------------
-------------------------------------*/
void HelloTextState::do_frustum_cull(const ls::math::mat4& vpMatrix) {
    
    const std::vector<draw::BoundingBox>& textBounds = textMesh.bounds;
    const math::mat4&& testTransform = vpMatrix * math::mat4{1.f};
    
    // standard implementations just do a memset() when clearing a vector rather
    // than reallocate.
    meshesInScene.clear();
    meshesInScene.reserve(textBounds.size());
    
    for (unsigned i = 0; i < textBounds.size(); ++i) {
        if (draw::is_visible(textBounds[i], testTransform, 1.15f)) {
            meshesInScene.push_back(i);
        }
    }
}

/*-------------------------------------
 * Render visible text
-------------------------------------*/
void HelloTextState::draw_text_data(const ls::math::mat4& vpMatrix) {
    const math::vec2i& displayRes = global::pDisplay->get_resolution();
    glViewport(0, 0, displayRes[0], displayRes[1]);
    
    draw::BlendObject blender;
    blender.set_state(true);
    blender.set_blend_equation(draw::BLEND_EQU_ADD, draw::BLEND_EQU_ADD);
    blender.set_blend_function(
        draw::BLEND_FNC_ONE, draw::BLEND_FNC_1_SUB_SRC_ALPHA,
        draw::BLEND_FNC_ONE, draw::BLEND_FNC_ZERO
    );
    
    blender.bind();

    textShader.bind();
    LS_LOG_GL_ERR();

    draw::set_shader_uniform(TEXT_VP_MATRIX_UNIFORM_ID, vpMatrix);
    LS_LOG_GL_ERR();

    textMesh.renderData.vaos.front().bind();
    LS_LOG_GL_ERR();

    glActiveTexture(draw::TEXTURE_SLOT_GPU_OFFSET + draw::TEXTURE_SLOT_0);
    LS_LOG_GL_ERR();
    
    atlas.bind();
    LS_LOG_GL_ERR();

    glActiveTexture(draw::TEXTURE_SLOT_GPU_OFFSET + draw::TEXTURE_SLOT_1);
    LS_LOG_GL_ERR();
    
    matrixBuf.bind();
    LS_LOG_GL_ERR();

    const draw::IndexBuffer& ibo = textMesh.renderData.ibos.front();
    const draw::index_element_t indexType = ibo.get_attrib(0).get_attrib_type();
   
    const std::vector<draw::SceneMesh>& submeshes = textMesh.meshes;
    
    unsigned meshesDrawn = 0;
    for (unsigned i = 0; i < meshesInScene.size(); ++i) {
        if (meshesInScene[i] >= submeshes.size()) {
            continue;
        }
        const draw::DrawCommandParams& s = submeshes[meshesInScene[i]].drawParams;
        glDrawElements(s.drawMode, s.count, indexType, s.offset);
        ++meshesDrawn;
    }
    
    LS_LOG_GL_ERR();

    glActiveTexture(draw::TEXTURE_SLOT_GPU_OFFSET + draw::TEXTURE_SLOT_1);
    LS_LOG_GL_ERR();
    
    matrixBuf.unbind();
    LS_LOG_GL_ERR();

    glActiveTexture(draw::TEXTURE_SLOT_GPU_OFFSET + draw::TEXTURE_SLOT_0);
    LS_LOG_GL_ERR();
    
    atlas.unbind();
    LS_LOG_GL_ERR();

    textMesh.renderData.vaos.front().bind();
    LS_LOG_GL_ERR();

    textShader.unbind();
    LS_LOG_GL_ERR();

    blender.unbind();
}

/*-------------------------------------
 * System Startup
-------------------------------------*/
bool HelloTextState::on_start() {
    using draw::ShaderAttribArray;
    using draw::VAOAttrib;

    setup_atlas();
    setup_text_shader();
    setup_occlusion_shader();
    setup_occlusion_fbo();
    setup_text();
    create_matrix_buffer();
    setup_occluders();

    LS_DEBUG_ASSERT(draw::are_attribs_compatible(textShader, textMesh.renderData.vaos.front()));
    LS_LOG_GL_ERR();

    LS_LOG_MSG("Max 2D Texture Layers: ", draw::get_gl_int(GL_MAX_ARRAY_TEXTURE_LAYERS));
    LS_LOG_MSG("Max 3D Texture Size: ", draw::get_gl_int(GL_MAX_ARRAY_TEXTURE_LAYERS));

    return true;
}

/*-------------------------------------
 * System Runtime
-------------------------------------*/
void HelloTextState::on_run() {
    const ControlState* const pController = get_parent_system().get_game_state<ControlState>();
    const math::mat4& vpMat = pController->get_camera_view_projection();
    const utils::Pointer<bool[]>& pKeyStates = pController->get_key_states();
    
    if (pKeyStates[SDL_SCANCODE_O]) {
        useOcclusionBuffer = true;
    }
    else if (pKeyStates[SDL_SCANCODE_P]) {
        useOcclusionBuffer = false;
    }
    
    glDisable(GL_CULL_FACE);
    LS_LOG_GL_ERR();

    if (useOcclusionBuffer) {
        draw_occlusion_data(vpMat);
        read_occlusion_data();
        
        LS_LOG_GL_ERR();
    }
    else {
        do_frustum_cull(vpMat);
    }
    
    draw_text_data(vpMat);
}

/*-------------------------------------
 * System Stop
-------------------------------------*/
void HelloTextState::on_stop() {
    useOcclusionBuffer = false;
    
    textShader.terminate();
    occlusionShader.terminate();
    
    atlas.terminate();
    
    occlusionFbo.terminate();
    occlusionDepth.terminate();
    occlusionTarget.terminate();
    
    for (draw::PixelBuffer& pbo : occlusionPbos) {
        pbo.terminate();
    }
    
    matrixBuf.terminate();
    textMesh.terminate();
    occlusionMeshes.terminate();
    
    textBoxes.clear();
    meshesInScene.clear();
}
