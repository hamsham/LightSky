/* 
 * File:   fbState.cpp
 * Author: miles
 * 
 * Created on July 30, 2014, 9:50 PM
 */

#include <chrono>
#include <utility>

#include <SDL2/SDL_events.h>

#include "display.h"
#include "fbState.h"

namespace draw = ls::draw;

typedef math::perlinNoise_t<float> perlinNoise;

enum {
    TEST_MAX_SCENE_OBJECTS = 32,
    TEST_MAX_SCENE_INSTANCES = TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS,
    TEST_NOISE_RESOLUTION = 1024,
    TEST_NOISE_SAMPLES = 32
};

#define TEST_PROJECTION_FOV 60.f
#define TEST_PROJECTION_NEAR 0.01f
#define TEST_PROJECTION_FAR 10.f
#define TEST_INSTANCE_RADIUS 0.5f

#define VP_MATRIX_UNIFORM "vpMatrix"
#define CAMERA_POSITION_UNIFORM "camPos"

/*
 * This shader uses a Logarithmic Z-Buffer, thanks to
 * http://www.gamasutra.com/blogs/BranoKemen/20090812/2725/Logarithmic_Depth_Buffer.php
 */
static const char meshVSData[] = R"***(
#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inUv;
layout (location = 2) in vec3 inNorm;
layout (location = 3) in mat4 inModelMat;

uniform mat4 vpMatrix;
uniform vec3 camPos = vec3(0.0, 0.0, 1.0);

out vec3 eyeDir;
out vec3 nrmCoords;
out vec2 uvCoords;

const float NEAR = 1.0;
const float FAR = 10.0;

void main() {
    mat4 mvpMatrix = vpMatrix * inModelMat;
    gl_Position = mvpMatrix * vec4(inPos, 1.0);
    gl_Position.z = -log(NEAR * gl_Position.z + 1.0) / log(NEAR * FAR + 1.0);
    
    // Use this to make the camera act as either a specular or point light
    //eyeDir = camPos - inPos;

    eyeDir = camPos;
    nrmCoords = inNorm;
    uvCoords = inUv;
}
)***";

/*
 * Testing Alpha Masking for font rendering.
 */
static const char meshFSData[] = R"***(
#version 330 core

in vec3 eyeDir;
in vec3 nrmCoords;
in vec2 uvCoords;

uniform sampler2D tex;

out vec4 outFragCol;

void main() {
    float lightIntensity = dot(eyeDir, normalize(nrmCoords));
    outFragCol = texture(tex, uvCoords).rrra * lightIntensity;
}
)***";

/******************************************************************************
 * Tests for loading perlin noise on another thread
******************************************************************************/
std::vector<float> generateNoiseTexture(int w, int h) {
    std::vector<float> noiseTable;
    noiseTable.resize(w*h);
    const float width = (float)w;
    const float height = (float)h;
    perlinNoise noise{};
    
    for (int i = 0; i < h; ++i) {
        // cache all casts to reduce how many are done per iteration
        const float hIter = (float)i;
        
        for (int j = 0; j < w; ++j) {
            const float wIter = (float)j;
            
            const math::vec3&& pos = math::vec3{wIter/width, hIter/height, 0.5f};
            const float perlin = noise.getOctaveNoise(pos*TEST_NOISE_SAMPLES, 4, 0.25f);
            noiseTable[i * h + j] = 0.5f * (0.5f+perlin);
        }
    }
    
    return noiseTable;
}

/******************************************************************************
 * Constructor & Destructor
******************************************************************************/
fbState::fbState() :
    gameState()
{
    SDL_StopTextInput();
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

fbState::fbState(fbState&& state) :
    gameState{}
{
    SDL_StopTextInput();
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    *this = std::move(state);
}

fbState::~fbState() {
}

fbState& fbState::operator=(fbState&& state) {
    gameState::operator=(std::move(state));
    
    mouseX = state.mouseX;
    state.mouseX = 0;
    
    mouseX = state.mouseY;
    state.mouseY = 0;
    
    meshProg = std::move(state.meshProg);
    
    testFb = std::move(state.testFb);
    
    pMatStack = state.pMatStack;
    state.pMatStack = nullptr;
    
    pScene = state.pScene;
    state.pScene = nullptr;
    
    pKeyStates = state.pKeyStates;
    state.pKeyStates = nullptr;
    
    pModelMatrices = state.pModelMatrices;
    state.pModelMatrices = nullptr;
    
    fbRes = state.fbRes;
    state.fbRes = math::vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT};
    
    orientation = state.orientation;
    state.orientation = math::quat{};
    
    futureNoise = std::move(state.futureNoise);
    
    return *this;
}

/******************************************************************************
 * System Events
******************************************************************************/
void fbState::onEvent(const SDL_Event& e) {
    switch (e.type) {
        case SDL_WINDOWEVENT:   this->onWindowEvent(e.window);      break;
        case SDL_KEYUP:         this->onKeyboardUpEvent(e.key);     break;
        case SDL_KEYDOWN:       this->onKeyboardDownEvent(e.key);   break;
        case SDL_MOUSEMOTION:   this->onMouseMoveEvent(e.motion);   break;
        case SDL_MOUSEWHEEL:    this->onMouseWheelEvent(e.wheel);  break;
        default: break;
    }
}

/******************************************************************************
 * Key Up Event
******************************************************************************/
void fbState::onKeyboardUpEvent(const SDL_KeyboardEvent& e) {
    const SDL_Keycode key = e.keysym.scancode;
    
    pKeyStates[key] = false;
    
    // Allow noise textures to be generated on another thread if one is not
    // being generated already
    if (key == SDL_SCANCODE_SPACE
    && futureNoise.wait_for(std::chrono::seconds{0}) == std::future_status::ready
    ) {
        regenerateNoise();
    }
}

/******************************************************************************
 * Key Down Event
******************************************************************************/
void fbState::onKeyboardDownEvent(const SDL_KeyboardEvent& e) {
    const SDL_Keycode key = e.keysym.scancode;
    pKeyStates[key] = true;
}

/******************************************************************************
 * Keyboard States
******************************************************************************/
void fbState::updateKeyStates() {
    const float moveSpeed = 0.05f * (float)getTickTime();
    math::vec3 pos = {0.f};
    
    if (pKeyStates[SDL_SCANCODE_W]) {
        pos[2] += moveSpeed;
    }
    if (pKeyStates[SDL_SCANCODE_S]) {
        pos[2] -= moveSpeed;
    }
    if (pKeyStates[SDL_SCANCODE_A]) {
        pos[0] += moveSpeed;
    }
    if (pKeyStates[SDL_SCANCODE_D]) {
        pos[0] -= moveSpeed;
    }
    
    const math::vec3&& translation = {
        math::dot(math::getAxisX(orientation), pos),
        math::dot(math::getAxisY(orientation), pos),
        math::dot(math::getAxisZ(orientation), pos)
    };
    
    const math::mat4& viewMatrix = pMatStack->getMatrix(draw::MATRIX_USE_VIEW);
    const math::mat4&& movement = math::translate(viewMatrix, translation);
    pMatStack->loadMatrix(draw::MATRIX_USE_VIEW, movement);
}

/******************************************************************************
 * Window Event
******************************************************************************/
void fbState::onWindowEvent(const SDL_WindowEvent& e) {
    if (e.event == SDL_WINDOWEVENT_RESIZED) {
        resetGlViewport();
        pMatStack->loadMatrix(draw::MATRIX_USE_PROJECTION, get3dViewport());
    }
}

/******************************************************************************
 * Mouse Move Event
******************************************************************************/
void fbState::onMouseMoveEvent(const SDL_MouseMotionEvent& e) {
    // Prevent the orientation from drifting by keeping track of the relative mouse offset
    if (this->getState() == ls::game::game_state_t::PAUSED
    || SDL_GetRelativeMouseMode() == SDL_FALSE
    || (mouseX == e.xrel && mouseY == e.yrel)
    ) {
        // I would rather quit the function than have unnecessary LERPs and
        // quaternion multiplications.
        return;
    }
    
    mouseX = e.xrel;
    mouseY = e.yrel;
    
    // Get the current mouse position and LERP from the previous mouse position.
    // The mouse position is divided by the window's resolution in order to normalize
    // the mouse delta between 0 and 1. This allows for the camera's orientation to
    // be LERPed without the need for multiplying it by the last time delta.
    // As a result, the camera's movement becomes as smooth and natural as possible.
    
    const math::vec2&& fRes = (math::vec2)global::pDisplay->getResolution();
    const math::vec2&& mouseDelta = math::vec2{(float)mouseX, (float)mouseY} / fRes;
    
    // Always lerp to the 
    const math::quat&& lerpX = math::lerp(
        math::quat{0.f, 0.f, 0.f, 1.f}, math::quat{mouseDelta[1], 0.f, 0.f, 1.f}, 1.f
    );
    
    const math::quat&& lerpY = math::lerp(
        math::quat{0.f, 0.f, 0.f, 1.f}, math::quat{0.f, mouseDelta[0], 0.f, 1.f}, 1.f
    );
        
    orientation *= lerpY * lerpX;
    orientation = math::normalize(orientation);
}

/******************************************************************************
 * Mouse Wheel Event
******************************************************************************/
void fbState::onMouseWheelEvent(const SDL_MouseWheelEvent& e) {
    fbRes += e.y * 10;
    
    const math::vec2i displayRes =global::pDisplay->getResolution();
    fbRes[0] = math::clamp(fbRes[0], (int)TEST_FRAMEBUFFER_WIDTH, displayRes[0]);
    fbRes[1] = math::clamp(fbRes[1], (int)TEST_FRAMEBUFFER_HEIGHT, displayRes[1]);
    
    draw::texture* fbDepthTex = pScene->getTexture(0);
    draw::texture* fbColorTex = pScene->getTexture(1);
    
    fbDepthTex->init(0, draw::COLOR_FMT_GRAY_8, fbRes, draw::COLOR_LAYOUT_GRAY, draw::COLOR_TYPE_UNSIGNED_BYTE, nullptr);
    fbColorTex->init(0, draw::COLOR_FMT_RGB_8, fbRes, draw::COLOR_LAYOUT_RGB, draw::COLOR_TYPE_UNSIGNED_BYTE, nullptr);
    
}

/******************************************************************************
 * Allocate internal class memory
******************************************************************************/
bool fbState::initMemory() {
    pMatStack       = new draw::matrixStack{};
    pScene          = new draw::sceneManager{};
    pKeyStates      = new bool[TEST_MAX_KEYBORD_STATES];
    pModelMatrices  = new math::mat4[TEST_MAX_SCENE_INSTANCES];
    
    if (pMatStack == nullptr
    ||  pScene == nullptr
    ||  !pScene->init()
    ||  pKeyStates == nullptr
    ||  pModelMatrices == nullptr
    ||  !testFb.init()
    ) {
        return false;
    }
    
    // initialize the keybord
    for (int i = 0;  i < TEST_MAX_KEYBORD_STATES; ++i) {
        pKeyStates[i] = false;
    }
    
    futureNoise = std::move(std::async(
        std::launch::async,
        &generateNoiseTexture,
        (int)TEST_NOISE_RESOLUTION,
        (int)TEST_NOISE_RESOLUTION
    ));
    
    return true;
}

/******************************************************************************
 * Initialize resources from files
******************************************************************************/
bool fbState::initFileData() {
    
    draw::meshResource* pMeshLoader = new draw::meshResource{};
    draw::mesh* pSphereMesh         = new draw::mesh{};
    draw::texture* fbDepthTex       = new draw::texture{};
    draw::texture* fbColorTex       = new draw::texture{};
    draw::texture* noiseTex         = new draw::texture{};
    bool ret                        = true;
    
    if (!pMeshLoader
    || !pSphereMesh
    || !pMeshLoader->loadSphere(16)
    || !pSphereMesh->init(*pMeshLoader)
    || !fbDepthTex->init(0, draw::COLOR_FMT_GRAY_8, math::vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT}, draw::COLOR_LAYOUT_GRAY, draw::COLOR_TYPE_UNSIGNED_BYTE, nullptr)
    || !fbColorTex->init(0, draw::COLOR_FMT_RGB_8, math::vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT}, draw::COLOR_LAYOUT_RGB, draw::COLOR_TYPE_UNSIGNED_BYTE, nullptr)
    || !noiseTex->init(0, draw::COLOR_FMT_R_32F, math::vec2i{TEST_NOISE_RESOLUTION}, draw::COLOR_LAYOUT_R, draw::COLOR_TYPE_FLOAT, nullptr)
    ) {
        ret = false;
    }
    else {
        pScene->manageMesh(pSphereMesh); // test data at the mesh index 0
        pScene->manageTexture(fbDepthTex);
        pScene->manageTexture(fbColorTex);
        pScene->manageTexture(noiseTex); // test texture at index 2
        
         // initialize the perlin noise texture
        regenerateNoise();
    }
    
    delete pMeshLoader;
    
    return ret;
}

/******************************************************************************
 * regenerate a noise texture
******************************************************************************/
void fbState::regenerateNoise() {
    std::vector<float>&& noiseTable = futureNoise.get();
    
    draw::texture* const pTexture = pScene->getTexture(2);
    pTexture->bind();
    pTexture->modify(0, math::vec2i{TEST_NOISE_RESOLUTION}, draw::COLOR_LAYOUT_R, draw::COLOR_TYPE_FLOAT, noiseTable.data());
    
    pTexture->setParameter(draw::TEX_PARAM_MIN_FILTER,  draw::TEX_FILTER_LINEAR);
    pTexture->setParameter(draw::TEX_PARAM_MAG_FILTER,  draw::TEX_FILTER_LINEAR);
    pTexture->setParameter(draw::TEX_PARAM_WRAP_S,      draw::TEX_PARAM_REPEAT);
    pTexture->setParameter(draw::TEX_PARAM_WRAP_T,      draw::TEX_PARAM_REPEAT);
    pTexture->unbind();
    
    futureNoise = std::move(std::async(
        std::launch::async,
        &generateNoiseTexture,
        (int)TEST_NOISE_RESOLUTION,
        (int)TEST_NOISE_RESOLUTION
    ));
}

/******************************************************************************
 * Initialize the model, view, and projection matrices
******************************************************************************/
bool fbState::initMatrices() {
    const math::vec2&& aspect = (math::vec2)global::pDisplay->getResolution();
    
    // setup the matrix stacks
    pMatStack->loadMatrix(
        draw::MATRIX_USE_PROJECTION,
        math::perspective(
            TEST_PROJECTION_FOV, aspect[0]/aspect[1],
            TEST_PROJECTION_NEAR, TEST_PROJECTION_FAR
        )
    );
    pMatStack->loadMatrix(
        draw::MATRIX_USE_VIEW,
        math::lookAt(math::vec3((float)TEST_MAX_SCENE_OBJECTS), math::vec3{0.f}, math::vec3{0.f, 1.f, 0.f})
    );
    pMatStack->constructVp();
    
    meshProg.bind();
    const GLint mvpId = meshProg.getUniformLocation(VP_MATRIX_UNIFORM);
    LOG_GL_ERR();
    
    if (mvpId == -1) {
        return false;
    }
    else {
        meshProg.setUniformValue(mvpId, pMatStack->getVpMatrix());
    }
    
    // initialize the test mesh translations
    unsigned matIter = 0;
    const int numObjects = TEST_MAX_SCENE_OBJECTS/2;
    for (int i = -numObjects; i < numObjects; ++i) {
        for (int j = -numObjects; j < numObjects; ++j) {
            for (int k = -numObjects; k < numObjects; ++k) {
                pModelMatrices[matIter] = math::translate(math::mat4{TEST_INSTANCE_RADIUS}, math::vec3{(float)i,(float)j,(float)k});
                ++matIter;
            }
        }
    }
    
    return true;
}

/******************************************************************************
 * Initialize the program shaders
******************************************************************************/
bool fbState::initShaders() {
    draw::vertexShader vertShader;
    draw::fragmentShader fragShader;

    if (!vertShader.compile(meshVSData)
    ||  !fragShader.compile(meshFSData)
    ) {
        return false;
    }
    else {
        LOG_GL_ERR();
    }
    
    if (!meshProg.attachShaders(vertShader, fragShader) || !meshProg.link()) {
        return false;
    }
    else {
        LOG_GL_ERR();
    }
    
    return true;
}

/******************************************************************************
 * Create the draw models that will be used for rendering
******************************************************************************/
bool fbState::initDrawModels() {
    draw::meshModel* const pModel = new draw::meshModel{};
    if (pModel == nullptr) {
        LS_LOG_ERR("Unable to generate test draw model");
        return false;
    }
    else {
        draw::mesh* const pMesh = pScene->getMesh(0);
        draw::texture* const pTexture = pScene->getTexture(2);
        pModel->init(*pMesh, *pTexture);
        
        // lights, camera, batch!
        pModel->setNumInstances(TEST_MAX_SCENE_INSTANCES, pModelMatrices);
        pScene->manageModel(pModel);
    }
    
    LOG_GL_ERR();
    
    return true;
}

/******************************************************************************
 * Initialize the framebuffers
******************************************************************************/
bool fbState::initFramebuffers() {
    draw::texture* const pDepthTex = pScene->getTexture(0);
    draw::texture* const pColorTex = pScene->getTexture(1);
    
    // setup the test framebuffer depth texture
    pDepthTex->bind();
        pDepthTex->setParameter(draw::TEX_PARAM_MIN_FILTER, draw::TEX_FILTER_LINEAR);
        pDepthTex->setParameter(draw::TEX_PARAM_MAG_FILTER, draw::TEX_FILTER_LINEAR);
        pDepthTex->setParameter(draw::TEX_PARAM_WRAP_S,     draw::TEX_PARAM_CLAMP_EDGE);
        pDepthTex->setParameter(draw::TEX_PARAM_WRAP_T,     draw::TEX_PARAM_CLAMP_EDGE);
    pDepthTex->unbind();
    
    LOG_GL_ERR();
    
    // framebuffer color texture
    pColorTex->bind();
        pColorTex->setParameter(draw::TEX_PARAM_MIN_FILTER, draw::TEX_FILTER_LINEAR);
        pColorTex->setParameter(draw::TEX_PARAM_MAG_FILTER, draw::TEX_FILTER_LINEAR);
        pColorTex->setParameter(draw::TEX_PARAM_WRAP_S,     draw::TEX_PARAM_CLAMP_EDGE);
        pColorTex->setParameter(draw::TEX_PARAM_WRAP_T,     draw::TEX_PARAM_CLAMP_EDGE);
    pColorTex->unbind();
    
    LOG_GL_ERR();
    
    testFb.bind();
        testFb.attachTexture(draw::FBO_ATTACHMENT_DEPTH,    draw::FBO_2D_TARGET, *pDepthTex);
        testFb.attachTexture(draw::FBO_ATTACHMENT_0,        draw::FBO_2D_TARGET, *pColorTex);
    testFb.unbind();
    
    LOG_GL_ERR();
    
    if (draw::framebuffer::getStatus(testFb) != draw::FBO_COMPLETE) {
        return false;
    }
    
    return true;
}

/******************************************************************************
 * Post-Initialization renderer parameters
******************************************************************************/
void fbState::setRendererParams() {
    constexpr draw::color gray = draw::lsGray;
    glClearColor(gray[0], gray[1], gray[2], gray[3]);
    
    draw::renderer renderer;
    renderer.setDepthTesting(true);
    renderer.setFaceCulling(true);
}

/******************************************************************************
 * Starting state
******************************************************************************/
bool fbState::onStart() {
    if (!initMemory()) {
        LS_LOG_ERR("An error occurred while initializing the batch state.");
        return false;
    }
    
    if (!initFileData()
    ||  !initShaders()
    ||  !initFramebuffers()
    ||  !initMatrices()
    ||  !initDrawModels()
    ) {
        LS_LOG_ERR("An error occurred while initializing the test state's resources");
        return false;
    }
    else {
        setRendererParams();
       global::pDisplay->setFullScreenMode(FULLSCREEN_WINDOW);
    }
    
    return true;
}

/******************************************************************************
 * Stopping state
******************************************************************************/
void fbState::onStop() {
    mouseX = 0;
    mouseY = 0;
    
    meshProg.terminate();
    
    testFb.terminate();
    
    orientation = math::quat{0.f, 0.f, 0.f, 1.f};

    delete pMatStack;
    pMatStack = nullptr;

    delete pScene;
    pScene = nullptr;

    delete [] pKeyStates;
    pKeyStates = nullptr;

    delete [] pModelMatrices;
    pModelMatrices = nullptr;
    
    futureNoise.wait();
    
    fbRes = {TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT};
}

/******************************************************************************
 * Running state
******************************************************************************/
void fbState::onRun() {
    updateKeyStates();
    
    // Meshes all contain their own model matrices. no need to use the ones in
    // the matrix stack. Just greab the view matrix
    pMatStack->pushMatrix(draw::MATRIX_USE_VIEW, math::quatToMat4(orientation));
    pMatStack->constructVp();
    
    const math::mat4& viewDir = pMatStack->getMatrix(draw::MATRIX_USE_VIEW);
    const math::vec3 camPos = math::vec3{viewDir[0][2], viewDir[1][2], viewDir[2][2]};
    
    meshProg.bind();
    const GLuint mvpId = meshProg.getUniformLocation(CAMERA_POSITION_UNIFORM);
    meshProg.setUniformValue(mvpId, camPos);
    
    drawScene();
    
    pMatStack->popMatrix(draw::MATRIX_USE_VIEW);
}

/******************************************************************************
 * Pausing state
******************************************************************************/
void fbState::onPause() {
    updateKeyStates();
    
    pMatStack->pushMatrix(draw::MATRIX_USE_VIEW, math::quatToMat4(orientation));
    pMatStack->constructVp();
    
    drawScene();
    
    pMatStack->popMatrix(draw::MATRIX_USE_VIEW);
}

/******************************************************************************
 * get a 2d viewport for 2d/gui drawing
******************************************************************************/
math::mat4 fbState::get3dViewport() const {
    const math::vec2i displayRes =global::pDisplay->getResolution();
    return math::perspective(
        TEST_PROJECTION_FOV, (float)displayRes[0]/displayRes[1],
        TEST_PROJECTION_NEAR, TEST_PROJECTION_FAR
    );
}

/******************************************************************************
 * Update the renderer's viewport with the current window resolution
******************************************************************************/
void fbState::resetGlViewport() {
    const display& disp = *global::pDisplay;
    draw::renderer renderer;
    renderer.setViewport(math::vec2i{0}, disp.getResolution());
}

/******************************************************************************
 * Drawing a scene
******************************************************************************/
void fbState::drawScene() {
    LOG_GL_ERR();
    
    // setup a viewport for a custom framebuffer
    draw::renderer renderer;
    renderer.setViewport(math::vec2i{0}, fbRes);

    // use render to the framebuffer's color attachment
    static const draw::fbo_attach_t fboDrawAttachments[] = {draw::FBO_ATTACHMENT_0};

    // setup the framebuffer for draw operations
    testFb.setAccessType(draw::FBO_ACCESS_W);
    testFb.bind();
    testFb.setDrawTargets(1, fboDrawAttachments);
    testFb.clear((draw::fbo_mask_t)(draw::FBO_DEPTH_BIT | draw::FBO_COLOR_BIT));
    
    // setup a view matrix for the opaque mesh shader
    meshProg.bind();
    const GLuint mvpId = meshProg.getUniformLocation(VP_MATRIX_UNIFORM);
    meshProg.setUniformValue(mvpId, pMatStack->getVpMatrix());
    
    // draw a test mesh
    draw::meshModel* const pTestModel = pScene->getModelList()[0];
    pTestModel->draw();
    
    // restore draw operations to the default GL framebuffer
    testFb.unbind();
    
    // setup the custom framebuffer for read operations
    testFb.setAccessType(draw::FBO_ACCESS_R);
    testFb.bind();

    // blit the custom framebuffer to OpenGL's backbuffer
    testFb.blit(
        math::vec2i{0}, fbRes,
        math::vec2i{0}, global::pDisplay->getResolution(),
        draw::FBO_COLOR_BIT
    );
    
    // restore framebuffer reads to OpenGL's backbuffer
    testFb.unbind();
    
    // reset the GL viewport back to normal
    resetGlViewport();
}
