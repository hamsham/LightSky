/* 
 * File:   batchState.cpp
 * Author: miles
 * 
 * Created on June 14, 2014, 3:19 AM
 */

#include "lsRenderer.h"
#include "batchState.h"

using math::vec2i;
using math::vec2;
using math::vec3;
using math::mat4;
using math::quat;

enum {
    TEST_MAX_SCENE_OBJECTS = 50,
    TEST_MAX_SCENE_INSTANCES = 50*50*50,
    TEST_MAX_KEYBORD_STATES = 512
};

#define TEST_INSTANCE_RADIUS 0.5f

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

const float NEAR = 1.0;
const float FAR = 10.0;

void main() {
    mat4 mvpMatrix = vpMatrix * inModelMat;
    gl_Position = mvpMatrix * vec4(inPos, 1.0);
    gl_Position.z = -log(NEAR * gl_Position.z + 1.0) / log(NEAR * FAR + 1.0);
    
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
void batchState::updateKeyStates(float dt) {
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

    delete [] pKeyStates;
    pKeyStates = nullptr;

    delete [] pModelMatrices;
    pModelMatrices = nullptr;
}

/******************************************************************************
 * Allocate internal class memory
******************************************************************************/
bool batchState::initMemory() {
    pMatStack       = new lsMatrixStack{};
    pScene          = new lsSceneManager{};
    pKeyStates      = new bool[TEST_MAX_KEYBORD_STATES];
    pModelMatrices  = new mat4[TEST_MAX_SCENE_INSTANCES];
    
    if (pMatStack == nullptr
    ||  pScene == nullptr
    ||  pKeyStates == nullptr
    ||  pModelMatrices == nullptr
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
    
    pScene->manageModel(pModel);
    pMesh = pScene->getMeshList()[0];
    pTexture = pScene->getTextureList()[0];
    pModel->setMesh(pMesh);
    pModel->setTexture(pTexture);
    
     // lights, camera, batch!
    pModel->setNumInstances(TEST_MAX_SCENE_INSTANCES, pModelMatrices);
    
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
    lsMesh* pMesh          = new lsMesh{};
    lsTexture* pTexture         = new lsTexture{};
    bool ret                    = true;
    
    if (!pImgLoader
    || !pImgLoader->loadFile(testImageFile)
    || !pTexture->init(0, pImgLoader->getPixelSize(), *pImgLoader)
    || !pMeshLoader
    || !pMeshLoader->loadSphere(16)
    || !pMesh->init(*pMeshLoader)
    ) {
        ret = false;
    }
    
    if (ret) {
        pTexture->bind();
        pTexture->setParameter(LS_TEX_MAG_FILTER, LS_LINEAR_FILTER);
        pTexture->setParameter(LS_TEX_MIN_FILTER, LS_NEAREST_FILTER);
        pTexture->unbind();
        
        pScene->manageMesh(pMesh); // test data at the mesh index 0
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
    pMatStack->loadMatrix(LS_PROJECTION_MATRIX, math::infinitePerspective(60.f, 4.f/3.f, 0.01f));
    pMatStack->loadMatrix(LS_VIEW_MATRIX, math::lookAt(vec3(50.f), vec3(0.f), vec3(0.f, 1.f, 0.f)));
    pMatStack->constructVp();
    
    shaderProg.bind();
    const GLuint mvpId = shaderProg.getUniformLocation("vpMatrix");
    shaderProg.setUniformValue(mvpId, pMatStack->getVpMatrix());
    
    LOG_GL_ERR();
    
    lsGlobal::pDisplay->getRenderer().setDepthTesting(true);
    lsGlobal::pDisplay->getRenderer().setFaceCulling(true);
    
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
    updateKeyStates(dt);
    
    // Meshes all contain their own model matrices. no need to use the ones in
    // the matrix stack. Just greab the view matrix
    pMatStack->pushMatrix(LS_VIEW_MATRIX, math::quatToMat4(orientation));
    pMatStack->constructVp();
    
    // Rotate each sphere so it's acting like a billboard against the camera
    const mat4& viewMat = pMatStack->getMatrix(LS_VIEW_MATRIX);
    
    unsigned matIter = 0;
    const int numObjects = TEST_MAX_SCENE_OBJECTS/2;
    for (int i = -numObjects; i < numObjects; ++i) {
        for (int j = -numObjects; j < numObjects; ++j) {
            for (int k = -numObjects; k < numObjects; ++k) {
                // scale the view matrix so no spheres overlap
                pModelMatrices[matIter] = math::billboard(vec3{(float)i,(float)j,(float)k}, mat4{TEST_INSTANCE_RADIUS}*viewMat);
                ++matIter;
            }
        }
    }
    
    // get the mesh to draw
    lsDrawModel* const pModel = pScene->getModelList()[0];
    
    // render!
    pModel->setNumInstances(TEST_MAX_SCENE_INSTANCES, pModelMatrices);
    
    drawScene();
    
    pMatStack->popMatrix(LS_VIEW_MATRIX);
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
    
    // shader setup
    shaderProg.bind();
    const GLuint mvpId = shaderProg.getUniformLocation("vpMatrix");
    shaderProg.setUniformValue(mvpId, pMatStack->getVpMatrix());
    
    // get the mesh to draw
    const lsDrawModel* const pModel = pScene->getModelList()[0];
   
    pModel->draw();
}
