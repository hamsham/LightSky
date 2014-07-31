/* 
 * File:   fbState.cpp
 * Author: miles
 * 
 * Created on July 30, 2014, 9:50 PM
 */

#include "lsRenderer.h"
#include "fbState.h"

using math::vec2i;
using math::vec2;
using math::vec3;
using math::mat4;
using math::quat;

enum {
    TEST_MAX_SCENE_OBJECTS = 50,
    TEST_MAX_SCENE_INSTANCES = 50*50*50,
    TEST_MAX_KEYBORD_STATES = 512,
    TEST_FRAMEBUFFER_WIDTH = 320,
    TEST_FRAMEBUFFER_HEIGHT = 240
};

#define TEST_INSTANCE_RADIUS 0.5f
#define TEST_FONT_FILE "FiraSans-Regular.otf"

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

// Testing Alpha Masking for font rendering.
static const char meshFSData[] = R"***(
#version 330 core

in vec3 eyeDir;
in vec3 nrmCoords;
in vec2 uvCoords;

out vec4 outFragCol;

void main() {
    float lightIntensity = dot(eyeDir, normalize(nrmCoords));
    outFragCol = vec4(1.0, 1.0, 1.0, 0.0) * lightIntensity;
}
)***";

// Testing Alpha Masking for font rendering.
static const char fontFSData[] = R"***(
#version 330

precision lowp float;

in vec2 uvCoords;
out vec4 outFragCol;

uniform sampler2DRect texSampler;
uniform vec4 fontColor = vec4(0.0, 1.0, 1.0, 1.0);

void main() {
    float mask = texture(texSampler, uvCoords).r;
    outFragCol = fontColor*step(0.5, mask);
}
)***";

/******************************************************************************
 * Constructor & Destructor
******************************************************************************/
fbState::fbState() {
    SDL_StopTextInput();
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

/******************************************************************************
 * Hardware Events
******************************************************************************/
/******************************************************************************
 * Key Up Event
******************************************************************************/
void fbState::onKeyboardUpEvent(const SDL_KeyboardEvent* e) {
    const SDL_Keycode key = e->keysym.sym;
    
    if (key < 0 || (unsigned)key >= TEST_MAX_KEYBORD_STATES) {
        return;
    }
    
    if (key == SDLK_ESCAPE) {
        this->setState(LS_GAME_STOPPED);
    }
    else {
        pKeyStates[key] = false;
    }
}

/******************************************************************************
 * Key Down Event
******************************************************************************/
void fbState::onKeyboardDownEvent(const SDL_KeyboardEvent* e) {
    const SDL_Keycode key = e->keysym.sym;
    
    if (key < 0 || (unsigned)key >= TEST_MAX_KEYBORD_STATES) {
        return;
    }
    
    if (key == SDLK_SPACE) {
        if (getState() == LS_GAME_RUNNING) {
            setState(LS_GAME_PAUSED);
        }
        else  {
            setState(LS_GAME_RUNNING);
        }
    }
    
    pKeyStates[key] = true;
}

/******************************************************************************
 * Keyboard States
******************************************************************************/
void fbState::updateKeyStates(float dt) {
    const float moveSpeed = 0.05f * dt;
    vec3 pos = {0.f};
    
    if (pKeyStates[SDLK_w]) {
        pos[2] += moveSpeed;
    }
    if (pKeyStates[SDLK_s]) {
        pos[2] -= moveSpeed;
    }
    if (pKeyStates[SDLK_a]) {
        pos[0] += moveSpeed;
    }
    if (pKeyStates[SDLK_d]) {
        pos[0] -= moveSpeed;
    }
    
    const vec3 translation = {
        math::dot(math::getAxisX(orientation), pos),
        math::dot(math::getAxisY(orientation), pos),
        math::dot(math::getAxisZ(orientation), pos)
    };
    
    const mat4& viewMatrix = pMatStack->getMatrix(LS_VIEW_MATRIX);
    const mat4&& movement = math::translate(viewMatrix, translation);
    pMatStack->loadMatrix(LS_VIEW_MATRIX, movement);
}

/******************************************************************************
 * Text Events
******************************************************************************/
void fbState::onKeyboardTextEvent(const SDL_TextInputEvent*) {
}

/******************************************************************************
 * Window Event
******************************************************************************/
void fbState::onWindowEvent(const SDL_WindowEvent* pEvent) {
    switch (pEvent->event) {
        case SDL_WINDOWEVENT_CLOSE:
            this->setState(LS_GAME_STOPPED);
            break;
        default:
            break;
    }
}

/******************************************************************************
 * Mouse Move Event
******************************************************************************/
void fbState::onMouseMoveEvent(const SDL_MouseMotionEvent* e) {
    // Prevent the orientation from drifting by keeping track of the relative mouse offset
    if (mouseX == e->xrel && mouseY == e->yrel) {
        // I would rather quit the function than have unnecessary LERPs and
        // quaternion multiplications.
        return;
    }
    
    mouseX = e->xrel;
    mouseY = e->yrel;
    
    // Get the current mouse position and LERP from the previous mouse position.
    // The mouse position is divided by the window's resolution in order to normalize
    // the mouse delta between 0 and 1. This allows for the camera's orientation to
    // be LERPed without the need for multiplying it by the last time delta.
    // As a result, the camera's movement becomes as smooth and natural as possible.
    
    const vec2&& fRes       = (vec2)getParentSystem().getDisplay().getResolution();
    const vec2&& mouseDelta = vec2{(float)mouseX, (float)mouseY} / fRes;
    
    // Always lerp to the 
    const quat&& lerpX = math::lerp(
        quat{0.f, 0.f, 0.f, 1.f}, quat{mouseDelta[1], 0.f, 0.f, 1.f}, 1.f
    );
    
    const quat&& lerpY = math::lerp(
        quat{0.f, 0.f, 0.f, 1.f}, quat{0.f, mouseDelta[0], 0.f, 1.f}, 1.f
    );
        
    orientation *= lerpY * lerpX;
    orientation = math::normalize(orientation);
}

/******************************************************************************
 * Mouse Button Up Event
******************************************************************************/
void fbState::onMouseButtonUpEvent(const SDL_MouseButtonEvent*) {
}

/******************************************************************************
 * Mouse Button Down Event
******************************************************************************/
void fbState::onMouseButtonDownEvent(const SDL_MouseButtonEvent*) {
}

/******************************************************************************
 * Mouse Wheel Event
******************************************************************************/
void fbState::onMouseWheelEvent(const SDL_MouseWheelEvent*) {
}

/******************************************************************************
 * termination assistant
******************************************************************************/
void fbState::terminate() {
    mouseX = 0;
    mouseY = 0;
    
    meshProg.terminate();
    fontProg.terminate();
    
    testFb.terminate();
    
    orientation = quat{0.f, 0.f, 0.f, 1.f};

    delete pMatStack;
    pMatStack = nullptr;

    delete pScene;
    pScene = nullptr;

    delete [] pKeyStates;
    pKeyStates = nullptr;

    delete [] pModelMatrices;
    pModelMatrices = nullptr;
}

/******************************************************************************
 * Allocate internal class memory
******************************************************************************/
bool fbState::initMemory() {
    pMatStack       = new lsMatrixStack{};
    pScene          = new lsSceneManager{};
    pKeyStates      = new bool[TEST_MAX_KEYBORD_STATES];
    pModelMatrices  = new mat4[TEST_MAX_SCENE_INSTANCES];
    
    if (pMatStack == nullptr
    ||  pScene == nullptr
    ||  pKeyStates == nullptr
    ||  pModelMatrices == nullptr
    ||  !testFb.init()
    ) {
        terminate();
        return false;
    }
    
    // initialize the ball translations and velocities
    unsigned matIter = 0;
    const int numObjects = TEST_MAX_SCENE_OBJECTS/2;
    for (int i = -numObjects; i < numObjects; ++i) {
        for (int j = -numObjects; j < numObjects; ++j) {
            for (int k = -numObjects; k < numObjects; ++k) {
                pModelMatrices[matIter] = math::translate(mat4{TEST_INSTANCE_RADIUS}, vec3{(float)i,(float)j,(float)k});
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
    vertexShader vertShader;
    fragmentShader fragShader;
    fragmentShader fontFragShader;

    if (!vertShader.compile(meshVSData)
    ||  !fragShader.compile(meshFSData)
    ||  !fontFragShader.compile(fontFSData)
    ) {
        return false;
    }
    
    LOG_GL_ERR();
    
    meshProg.attachShaders(vertShader, fragShader);
    meshProg.link();
    fontProg.attachShaders(vertShader, fontFragShader);
    fontProg.link();
    
    LOG_GL_ERR();
    
    return true;
}

/******************************************************************************
 * Create the draw models that will be used for rendering
******************************************************************************/
bool fbState::initDrawModels() {
    // test model 1
    lsDrawModel* const pModel = new lsDrawModel{};
    lsMesh* pMesh = nullptr;
    if (pModel == nullptr) {
        LS_LOG_ERR("Unable to generate test draw model 1");
        return false;
    }
    else {
        pScene->manageModel(pModel);
        pMesh = pScene->getMeshList()[0];
        pModel->setMesh(pMesh);
        pModel->setTexture(&pScene->getDefaultTexture());

         // lights, camera, batch!
        pModel->setNumInstances(TEST_MAX_SCENE_INSTANCES, pModelMatrices);
    }
    
    // font/text model
    lsDrawModel* const pTextModel = new lsDrawModel{};
    lsMesh* pTextMesh = nullptr;
    if (pTextModel == nullptr) {
        LS_LOG_ERR("Unable to generate test draw model 1");
        return false;
    }
    else {
        pScene->manageModel(pTextModel);
        pTextMesh = pScene->getMeshList()[1];
        pTextModel->setMesh(pTextMesh);
        pTextModel->setTexture(&(pScene->getAtlas(0)->getTexture()));

        mat4 modelMat = {1.f};
        pTextModel->setNumInstances(1, &modelMat);
    }
    
    LOG_GL_ERR();
    
    return true;
}

/******************************************************************************
 * Initialize the framebuffesr
******************************************************************************/
bool fbState::initFramebuffers() {
    lsTexture* const pDepthTex = pScene->getTexture(0);
    lsTexture* const pColorTex = pScene->getTexture(1);
    
    // setup the test framebuffer depth texture
    pDepthTex->bind();
        pDepthTex->setParameter(LS_TEX_MIN_FILTER, LS_LINEAR_FILTER);
        pDepthTex->setParameter(LS_TEX_MAG_FILTER, LS_LINEAR_FILTER);
        pDepthTex->setParameter(LS_TEX_WRAP_S, LS_TEX_CLAMP);
        pDepthTex->setParameter(LS_TEX_WRAP_T, LS_TEX_CLAMP);
    pDepthTex->unbind();
    
    LOG_GL_ERR();
    
    // framebuffer color texture
    pColorTex->bind();
        pColorTex->setParameter(LS_TEX_MIN_FILTER, LS_LINEAR_FILTER);
        pColorTex->setParameter(LS_TEX_MAG_FILTER, LS_LINEAR_FILTER);
        pColorTex->setParameter(LS_TEX_WRAP_S, LS_TEX_CLAMP);
        pColorTex->setParameter(LS_TEX_WRAP_T, LS_TEX_CLAMP);
    pColorTex->unbind();
    
    LOG_GL_ERR();
    
    testFb.bind();
        testFb.attachTexture(LS_DEPTH_ATTACHMENT, LS_FBO_2D_TARGET, *pDepthTex);
        testFb.attachTexture(LS_COLOR_ATTACHMENT0, LS_FBO_2D_TARGET, *pColorTex);
    testFb.unbind();
    
    LOG_GL_ERR();
    
    if (lsFramebuffer::getStatus(testFb) != LS_FBO_COMPLETE) {
        return false;
    }
    
    return true;
}

/******************************************************************************
 * Starting state
******************************************************************************/
bool fbState::onStart() {
    if (!initMemory()) {
        LS_LOG_ERR("An error occurred while initializing the batch state.");
        terminate();
        return false;
    }
    
    lsMeshResource* pMeshLoader = new lsMeshResource{};
    lsFontResource* pFontLoader = new lsFontResource{};
    lsMesh* pSphereMesh         = new lsMesh{};
    lsMesh* pFontMesh           = new lsMesh{};
    lsAtlas* pAtlas             = new lsAtlas{};
    lsTexture* fbDepthTex       = new lsTexture{};
    lsTexture* fbColorTex       = new lsTexture{};
    bool ret                    = true;
    
    if (!pMeshLoader
    || !pFontLoader
    || !pSphereMesh
    || !pFontMesh
    || !pAtlas
    || !pMeshLoader->loadSphere(16)
    || !pSphereMesh->init(*pMeshLoader)
    || !pFontLoader->loadFile(TEST_FONT_FILE)
    || !pAtlas->init(*pFontLoader)
    || !pFontMesh->init(*pAtlas, "Hello World")
    || !fbDepthTex->init(0, GL_DEPTH_COMPONENT, vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT}, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr)
    || !fbColorTex->init(0, GL_RGB, vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT}, GL_BGR, GL_UNSIGNED_BYTE, nullptr)
    ) {
        ret = false;
    }
    
    if (ret) {
        pScene->manageMesh(pSphereMesh); // test data at the mesh index 0
        pScene->manageMesh(pFontMesh);
        pScene->manageAtlas(pAtlas);
        pScene->manageTexture(fbDepthTex);
        pScene->manageTexture(fbColorTex);
    }
    
    delete pMeshLoader;
    delete pFontLoader;
    
    if (!ret || !initDrawModels() || !initFramebuffers() || !initShaders()) {
        LS_LOG_ERR("An error occurred while initializing the test state's resources");
        terminate();
        return false;
    }
    
    LOG_GL_ERR();

    // Initialize the matrix stacks
    pMatStack->loadMatrix(LS_PROJECTION_MATRIX, math::perspective(60.f, 4.f/3.f, 0.01f, 10.f));
    pMatStack->loadMatrix(LS_VIEW_MATRIX, math::lookAt(vec3(50.f), vec3(0.f), vec3(0.f, 1.f, 0.f)));
    pMatStack->constructVp();
    
    meshProg.bind();
    const GLuint mvpId = meshProg.getUniformLocation("vpMatrix");
    meshProg.setUniformValue(mvpId, pMatStack->getVpMatrix());
    
    LOG_GL_ERR();
    
    lsRenderer& pRenderer = getParentSystem().getDisplay().getRenderer();
    pRenderer.setDepthTesting(true);
    pRenderer.setFaceCulling(true);
    
    return true;
}

/******************************************************************************
 * Stopping state
******************************************************************************/
void fbState::onStop() {
    terminate();
}

/******************************************************************************
 * Running state
******************************************************************************/
void fbState::onRun(float dt) {
    updateKeyStates(dt);
    
    // Meshes all contain their own model matrices. no need to use the ones in
    // the matrix stack. Just greab the view matrix
    pMatStack->pushMatrix(LS_VIEW_MATRIX, math::quatToMat4(orientation));
    pMatStack->constructVp();
    
    const math::mat4& viewDir = pMatStack->getMatrix(LS_VIEW_MATRIX);
    const math::vec3 camPos = vec3{viewDir[0][2], viewDir[1][2], viewDir[2][2]};
    
    meshProg.bind();
    const GLuint mvpId = meshProg.getUniformLocation("camPos");
    meshProg.setUniformValue(mvpId, camPos);
    
    drawScene();
    
    pMatStack->popMatrix(LS_VIEW_MATRIX);
}

/******************************************************************************
 * Pausing state
******************************************************************************/
void fbState::onPause(float dt) {
    updateKeyStates(dt);
    
    pMatStack->pushMatrix(LS_VIEW_MATRIX, math::quatToMat4(orientation));
    pMatStack->constructVp();
    
    drawScene();
    
    pMatStack->popMatrix(LS_VIEW_MATRIX);
}

/******************************************************************************
 * Get a string representing the current Ms/s and F/s
******************************************************************************/
std::string fbState::getTimingStr() const {
    const float tickTime = getParentSystem().getTickTime() * 0.001f;
    return util::toString(tickTime) + "MS\n" + util::toString(1.f/tickTime) + "FPS";
}

/******************************************************************************
 * get a 2d viewport for 2d/gui drawing
******************************************************************************/
mat4 fbState::get2dViewport() const {
    return math::ortho(
        0.f, (float)getParentSystem().getDisplay().getResolution()[0],
        0.f, (float)getParentSystem().getDisplay().getResolution()[1],
        -1.f, 1.f
    );
}


/******************************************************************************
 * Drawing a scene
******************************************************************************/
void fbState::drawScene() {
    LOG_GL_ERR();
    const mat4& vpMat = pMatStack->getVpMatrix();
    lsDrawModel* pModel = nullptr;
    
    // shader setup
    {
        lsRenderer& renderer = getParentSystem().getDisplay().getRenderer();
        renderer.setViewport(vec2i{0,0}, vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT});
        
        static ls_fbo_attach_t fboDrawAttachments[] = {LS_COLOR_ATTACHMENT0};
        
        testFb.setAccessType(LS_DRAW_FRAMEBUFFER);
        testFb.bind();
        testFb.setDrawTargets(1, fboDrawAttachments);
        testFb.clear((ls_fbo_mask_t)(LS_DEPTH_MASK | LS_COLOR_MASK));
        
        meshProg.bind();
        const GLuint mvpId = meshProg.getUniformLocation("vpMatrix");
        meshProg.setUniformValue(mvpId, vpMat);
        
        // get the mesh to draw
        pModel = pScene->getModelList()[0];
        pModel->draw();
        
        testFb.unbind(); // restore draw operations to the default framebuffer
        testFb.setAccessType(LS_READ_FRAMEBUFFER);
        testFb.bind();
        
        // blit the rendered framebuffer to the screen
        testFb.blit(
            vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT}, vec2i{0,0},
            this->getParentSystem().getDisplay().getResolution(), vec2i{0,0},
            LS_COLOR_MASK
        );
        testFb.unbind();
        renderer.setViewport(vec2i{0,0}, getParentSystem().getDisplay().getResolution());
    }
    
    {
        fontProg.bind();
        const GLuint fontMvpId = meshProg.getUniformLocation("vpMatrix");
        const mat4 orthoProj = get2dViewport();
        meshProg.setUniformValue(fontMvpId, orthoProj);
        
        const float screenResY = (float)getParentSystem().getDisplay().getResolution()[1];
        mat4 modelMat = math::translate(mat4{1.f}, vec3{0.f, screenResY, 0.f});
        modelMat = math::scale(modelMat, vec3{10.f});
        
        pScene->getMesh(1)->init(*pScene->getAtlas(0), getTimingStr());
        pModel = pScene->getModelList()[1];
        pModel->setNumInstances(1, &modelMat);
        
        lsRenderer& renderer = getParentSystem().getDisplay().getRenderer();
        renderer.setDepthTesting(false);
        renderer.setBlending(true);
        renderer.setBlendEquationSeparate(LS_BLEND_ADD, LS_BLEND_ADD);
        renderer.setBlendFunctionSeparate(LS_ONE, LS_ONE_MINUS_SRC_ALPHA, LS_ONE, LS_ZERO);
        pModel->draw();
        renderer.setBlending(false);
        renderer.setDepthTesting(true);
    }
}
