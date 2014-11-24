/* 
 * File:   uiState.cpp
 * Author: miles
 * 
 * Created on August 5, 2014, 9:18 PM
 */

#include <utility>

#include "display.h"
#include "uiState.h"

#define TEST_FONT_FILE L"./FiraSans-Regular.otf"

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

out vec2 uvCoords;

void main() {
    gl_Position = vpMatrix * inModelMat * vec4(inPos, 1.0);
    uvCoords = inUv;
}
)***";

/*
 * Testing Alpha Masking for font rendering.
 */
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
uiState::uiState() {
}

uiState::uiState(uiState&& state) :
    gameState{}
{
    *this = std::move(state);
}

uiState::~uiState() {
}

uiState& uiState::operator=(uiState&& state) {
    gameState::operator=(std::move(state));
    
    fontProg = std::move(state.fontProg);
    
    pScene = state.pScene;
    state.pScene = nullptr;
    
    pBlender = std::move(state.pBlender);
    
    return *this;
}

/******************************************************************************
 * Allocate internal class memory
******************************************************************************/
bool uiState::initMemory() {
    pScene          = new ls::draw::sceneManager{};
    pBlender        = new ls::draw::blendObject{};
    
    if (pScene == nullptr
    ||  !pScene->init()
    ||  !pBlender
    ) {
        return false;
    }
    
    return true;
}

/******************************************************************************
 * Initialize resources from files
******************************************************************************/
bool uiState::initFileData() {
    
    ls::draw::fontResource* pFontLoader = new ls::draw::fontResource{};
    ls::draw::mesh* pFontMesh           = new ls::draw::mesh{};
    ls::draw::atlas* pAtlas             = new ls::draw::atlas{};
    bool ret                            = true;
    
    if (!pFontLoader
    || !pFontMesh
    || !pAtlas
    || !pFontLoader->loadFile(TEST_FONT_FILE)
    || !pAtlas->init(*pFontLoader)
    || !pFontMesh->init(*pAtlas, "Hello World")
    ) {
        ret = false;
    }
    else {
        pScene->manageMesh(pFontMesh);
        pScene->manageAtlas(pAtlas);
    }
    
    delete pFontLoader;
    
    return ret;
}

/******************************************************************************
 * Initialize the program shaders
******************************************************************************/
bool uiState::initShaders() {
    ls::draw::vertexShader vertShader;
    ls::draw::fragmentShader fontFragShader;

    if (!vertShader.compile(meshVSData)
    ||  !fontFragShader.compile(fontFSData)
    ) {
        return false;
    }
    else {
        LOG_GL_ERR();
    }
    
    if (!fontProg.attachShaders(vertShader, fontFragShader)
    || !fontProg.link()) {
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
bool uiState::initDrawModels() {
    // font/text model
    ls::draw::meshModel* const pTextModel = new ls::draw::meshModel{};
    
    if (pTextModel == nullptr) {
        LS_LOG_ERR("Unable to generate test text model");
        return false;
    }
    else {
        pScene->manageModel(pTextModel);
        ls::draw::mesh* const pTextMesh = pScene->getMeshList()[0];
        pTextModel->init(*pTextMesh, pScene->getAtlas(0)->getTexture());

        math::mat4 modelMat = {1.f};
        pTextModel->setNumInstances(1, &modelMat);
    }
    
    LOG_GL_ERR();
    
    return true;
}

/******************************************************************************
 * Post-Initialization renderer parameters
******************************************************************************/
void uiState::setRendererParams() {
    pBlender->setState(true);
    pBlender->setBlendEquation(ls::draw::BLEND_EQU_ADD, ls::draw::BLEND_EQU_ADD);
    pBlender->setBlendFunction(ls::draw::BLEND_FNC_ONE, ls::draw::BLEND_FNC_1_SUB_SRC_ALPHA, ls::draw::BLEND_FNC_ONE, ls::draw::BLEND_FNC_ZERO);
}

/******************************************************************************
 * Starting state
 * 
 * Resources that were already allocated are removed during "onStop()"
******************************************************************************/
bool uiState::onStart() {
    if (!initMemory()) {
        LS_LOG_ERR("An error occurred while initializing the batch state.");
        return false;
    }
    
    if (!initFileData()
    ||  !initShaders()
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
void uiState::onStop() {
    secondTimer = 0.f;
    
    fontProg.terminate();
    
    delete pScene;
    pScene = nullptr;
    
    delete pBlender;
    pBlender = nullptr;
}

/******************************************************************************
 * Running state
******************************************************************************/
void uiState::onRun() {
    // Regenerate a string mesh using the frame's timing information.
    secondTimer += getTickTime();
    if (secondTimer >= 1000) {
        ls::draw::atlas* const pStringAtlas = pScene->getAtlas(0);
        ls::draw::mesh* const pStringMesh = pScene->getMesh(0);
        const std::string&& timingStr = getTimingStr();
        pStringMesh->init(*pStringAtlas, timingStr);
        secondTimer = 0;
    }
    
    drawScene();
}

/******************************************************************************
 * Pausing state
******************************************************************************/
void uiState::onPause() {
    onRun();
}

/******************************************************************************
 * Get a string representing the current Ms/s and F/s
******************************************************************************/
std::string uiState::getTimingStr() const {
    const float tickTime = getParentSystem().getTickTime();// * 0.001f;
    return std::to_string(tickTime) + "MS\n" + std::to_string(1/tickTime) + "FPS";
}

/******************************************************************************
 * get a 2d viewport for 2d/gui drawing
******************************************************************************/
math::mat4 uiState::get2dViewport() const {
    const display& display = *global::pDisplay;
    const math::vec2&& displayRes = (math::vec2)display.getResolution();
    
    return math::ortho(
        0.f, displayRes[0],
        0.f, displayRes[1],
        0.f, 1.f
    );
}

/******************************************************************************
 * Update the renderer's viewport with the current window resolution
******************************************************************************/
void uiState::resetGlViewport() {
    ls::draw::renderer renderer;
    renderer.setViewport(math::vec2i{0},global::pDisplay->getResolution());
}

/******************************************************************************
 * Drawing a scene
******************************************************************************/
void uiState::drawScene() {
    LOG_GL_ERR();
    resetGlViewport();
    
    fontProg.bind();
    const GLint fontMvpId           = fontProg.getUniformLocation("vpMatrix");
    const math::mat4&& orthoProj    = get2dViewport();
    fontProg.setUniformValue(fontMvpId, orthoProj);
    
    // setup some UI parameters with a resolution-independent model matrix
    const display& disp = *global::pDisplay;
    const math::vec2&& res  = (math::vec2)disp.getResolution();
    math::mat4 modelMat     = math::translate(math::mat4{1.f}, math::vec3{0.f, res[1], 0.f});
    modelMat                = math::scale(modelMat, math::vec3{math::length(res)*0.01f});
    
    // model 1 has the string mesh already bound
    ls::draw::meshModel* const pStringModel = pScene->getModelList()[0];
    pStringModel->setNumInstances(1, &modelMat);

    // setup parameters to draw a transparent mesh as a screen overlay/UI
    ls::draw::renderer renderer;
    renderer.setDepthTesting(false);
    pBlender->bind();
    pStringModel->draw();
    pBlender->unbind();
    renderer.setDepthTesting(true);
}
