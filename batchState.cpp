/* 
 * File:   batchState.cpp
 * Author: miles
 * 
 * Created on June 14, 2014, 3:19 AM
 */

#include "batchState.h"

using math::vec2i;
using math::vec2;
using math::vec3;
using math::mat4;
using math::quat;

enum {
    TEST_MAX_SCENE_OBJECTS = 50,
    TEST_MAX_KEYBORD_STATES = 512
};

static const char testImageFile[] = "test_img.jpg";

/*
 * This shader uses a Logarithmic Z-Buffer, thanks to
 * http://www.gamasutra.com/blogs/BranoKemen/20090812/2725/Logarithmic_Depth_Buffer.php
 */
static const char meshVertShader[] = R"***(
#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inUv;
layout (location = 2) in vec3 inNorm;
layout (location = 3) in mat4 inModelMat;

uniform mat4 vpMatrix;

out vec2 uvCoords;

void main() {
    mat4 mvpMatrix = vpMatrix * inModelMat;
    vec4 p = mvpMatrix * vec4(inPos, 1.0);
    const float C = 1.0;
    const float FAR = 10.0;
    float pz = -log(C * p.z + 1.0) / log(C * FAR + 1.0);
    
    gl_Position = vec4(p.xy, pz, p.w);
    
    uvCoords = inUv;
}
)***";

// Testing Alpha Masking for font rendering.
static const char meshFragShader[] = R"***(
#version 330 core

uniform sampler2D tex;

in vec2 uvCoords;
out vec4 outFragCol;

void main() {
    outFragCol = texture(tex, uvCoords);
}
)***";

/******************************************************************************
 * Constructor & Destructor
******************************************************************************/
batchState::batchState() {
    SDL_StopTextInput();
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

/******************************************************************************
 * Hardware Events
******************************************************************************/
/******************************************************************************
 * Key Up Event
******************************************************************************/
void batchState::onKeyboardUpEvent(const SDL_KeyboardEvent* e) {
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
void batchState::onKeyboardDownEvent(const SDL_KeyboardEvent* e) {
    const SDL_Keycode key = e->keysym.sym;
    
    if (key < 0 || (unsigned)key >= TEST_MAX_KEYBORD_STATES) {
        return;
    }
    
    pKeyStates[key] = true;
}

/******************************************************************************
 * Keyboard States
******************************************************************************/
void batchState::updateKeyStates() {
    const float moveSpeed = 0.5f;
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
    
    const vec3 translation{
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
void batchState::onKeyboardTextEvent(const SDL_TextInputEvent*) {
}

/******************************************************************************
 * Window Event
******************************************************************************/
void batchState::onWindowEvent(const SDL_WindowEvent* pEvent) {
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
void batchState::onMouseMoveEvent(const SDL_MouseMotionEvent* e) {
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
    
    const vec2&& fRes       = (vec2)lsGlobal::pDisplay->getResolution();
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
void batchState::onMouseButtonUpEvent(const SDL_MouseButtonEvent*) {
}

/******************************************************************************
 * Mouse Button Down Event
******************************************************************************/
void batchState::onMouseButtonDownEvent(const SDL_MouseButtonEvent*) {
}

/******************************************************************************
 * Mouse Wheel Event
******************************************************************************/
void batchState::onMouseWheelEvent(const SDL_MouseWheelEvent*) {
}

/******************************************************************************
 * termination assistant
******************************************************************************/
void batchState::terminate() {
    mouseX = 0;
    mouseY = 0;
    shaderProg.terminate();
    orientation = quat{0.f, 0.f, 0.f, 1.f};

    delete pMatStack;
    pMatStack = nullptr;

    delete pScene;
    pScene = nullptr;

    delete [] pPositions;
    pPositions = nullptr;

    delete [] pKeyStates;
    pKeyStates = nullptr;

    delete [] pModelMatrices;
    pModelMatrices = nullptr;
}

/******************************************************************************
 * Allocate internal class memory
******************************************************************************/
bool batchState::initMemory() {
    const int instanceCount = TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS;
    pMatStack       = new lsMatrixStack{};
    pScene          = new lsSceneManager{};
    pPositions      = new vec3[instanceCount];
    pKeyStates      = new bool[TEST_MAX_KEYBORD_STATES];
    pModelMatrices  = new mat4[instanceCount];
    
    if (pMatStack == nullptr
    ||  pScene == nullptr
    ||  pPositions == nullptr
    ||  pKeyStates == nullptr
    ||  pModelMatrices == nullptr
    ) {
        terminate();
        return false;
    }
    
    return true;
}

/******************************************************************************
 * Create the draw models that will be used for rendering
******************************************************************************/
bool batchState::generateDrawModels() {
    lsTexture* pTexture = nullptr;
    lsMesh* pMesh = nullptr;
    
    // test model 1
    lsDrawModel* const pModel = new lsDrawModel{};
    if (pModel == nullptr) {
        LS_LOG_ERR("Unable to generate test draw model 1");
        return false;
    }
    else {
        const int instanceCount = TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS;
        pScene->manageModel(pModel);
        pMesh = pScene->getMeshList()[0];
        pTexture = pScene->getTextureList()[0];
        pModel->setMesh(pMesh);
        pModel->setTexture(pTexture);
        pModel->setNumInstances(instanceCount, pModelMatrices);
    }
    
    unsigned matIter = 0;
    const int numObjects = TEST_MAX_SCENE_OBJECTS/2;
    for (int i = -numObjects; i < numObjects; ++i) {
        for (int j = -numObjects; j < numObjects; ++j) {
            for (int k = -numObjects; k < numObjects; ++k) {
                pModelMatrices[matIter] = math::translate(mat4{1.f}, vec3{(float)i,(float)j,(float)k});
                ++matIter;
            }
        }
    }
    
    return true;
}

/******************************************************************************
 * Starting state
******************************************************************************/
bool batchState::onStart() {
    if (!initMemory()) {
        LS_LOG_ERR("An error occurred while initializing the batch state.");
        terminate();
        return false;
    }
    
    lsMeshResource* pMeshLoader = new lsMeshResource{};
    lsImageResource* pImgLoader = new lsImageResource{};
    lsMesh* paddleMesh          = new lsMesh{};
    lsTexture* pTexture         = new lsTexture{};
    bool ret                    = true;
    
    if (!pImgLoader
    || !pImgLoader->loadFile(testImageFile)
    || !pTexture->init(0, GL_RGB, pImgLoader->getPixelSize(), GL_BGR, GL_UNSIGNED_BYTE, pImgLoader->getData())
    || !pMeshLoader
    || !pMeshLoader->loadSphere(32)
    || !paddleMesh->init(*pMeshLoader)
    ) {
        ret = false;
    }
    
    if (ret) {
        pTexture->bind();
        pTexture->setParameter(LS_TEX_MAG_FILTER, LS_LINEAR_FILTER);
        pTexture->setParameter(LS_TEX_MIN_FILTER, LS_NEAREST_FILTER);
        pTexture->unbind();
        
        pScene->manageMesh(paddleMesh); // test data at the mesh index 0
        pScene->manageTexture(pTexture); // test atlas at the mesh index 0
    }
    
    delete pMeshLoader;
    delete pImgLoader;
    
    if (!ret || !generateDrawModels()) {
        LS_LOG_ERR("An error occurred while initializing the test state's resources");
        terminate();
        return false;
    }
    
    LOG_GL_ERR();
    
    // Initialize the shaders
    {
        vertexShader vertShader;
        fragmentShader fragShader;
        
        vertShader.compile(meshVertShader);
        fragShader.compile(meshFragShader);
        shaderProg.attachShaders(vertShader, fragShader);
        shaderProg.link();
    }
    
    LOG_GL_ERR();

    // Initialize the matrix stacks
    pMatStack->loadMatrix(LS_PROJECTION_MATRIX, math::perspective(60.f, 4.f/3.f, 0.01f, 10.f));
    pMatStack->loadMatrix(LS_VIEW_MATRIX, math::lookAt(vec3(50.f), vec3(0.f), vec3(0.f, 1.f, 0.f)));
    pMatStack->constructVp();
    
    shaderProg.bind();
    const GLuint mvpId = shaderProg.getUniformLocation("vpMatrix");
    shaderProg.setUniformValue(mvpId, pMatStack->getVpMatrix());
    
    LOG_GL_ERR();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    return true;
}

/******************************************************************************
 * Stopping state
******************************************************************************/
void batchState::onStop() {
    terminate();
}

/******************************************************************************
 * Running state
******************************************************************************/
void batchState::onRun(float dt) {
    (void)dt;
    updateKeyStates();
    drawScene();
}

/******************************************************************************
 * Pausing state
******************************************************************************/
void batchState::onPause(float dt) {
    (void)dt;
    
    drawScene();
}

/******************************************************************************
 * Drawing a scene
******************************************************************************/
void batchState::drawScene() {
    LOG_GL_ERR();
    
    // Meshes all contain their own model matrices. no need to use the ones in
    // the matrix stack.
    pMatStack->pushMatrix(LS_VIEW_MATRIX, math::quatToMat4(orientation));
    pMatStack->constructVp();
    
    // text draw model
    // shader setup
    shaderProg.bind();
    const GLuint mvpId = shaderProg.getUniformLocation("vpMatrix");
    shaderProg.setUniformValue(mvpId, pMatStack->getVpMatrix());
    
    // model matrix setup
    unsigned matIter = 0;
    const int numObjects = TEST_MAX_SCENE_OBJECTS/2;
    for (int i = -numObjects; i < numObjects; ++i) {
        for (int j = -numObjects; j < numObjects; ++j) {
            for (int k = -numObjects; k < numObjects; ++k) {
                const vec3 instancePos = vec3{(float)i,(float)j,(float)k};
                const mat4& vpMat = pMatStack->getMatrix(LS_VIEW_MATRIX);
                pModelMatrices[matIter] = math::billboard(instancePos, vpMat);
                ++matIter;
            }
        }
    }
    
    lsDrawModel* pModel;

    pModel = pScene->getModelList()[0];
    const int instanceCount = TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS;
    pModel->setNumInstances(instanceCount, pModelMatrices);
    pModel->draw();
    
    pMatStack->popMatrix(LS_VIEW_MATRIX);
}

