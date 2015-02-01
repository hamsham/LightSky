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
 * Font Vertex Shader
 */
static constexpr char meshVSData[] = u8R"***(
#version 300 es

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inUv;
layout (location = 2) in vec3 inNorm;

uniform mat4 mvpMatrix;

out vec2 uvCoords;

void main() {
    gl_Position = mvpMatrix * vec4(inPos, 1.0);
    uvCoords = inUv;
}
)***";

/*
 * Font Fragment Shader
 */
static constexpr char fontFSData[] = u8R"***(
#version 300 es

precision lowp float;

in vec2 uvCoords;

out vec4 outFragCol;

uniform sampler2D texSampler;
uniform vec4 fontColor = vec4(0.0, 1.0, 1.0, 1.0);

void main() {
    float mask = texture(texSampler, uvCoords).r;
    outFragCol = fontColor*step(0.5, mask);
}
)***";

/*-------------------------------------
 * Constructor & Destructor
-------------------------------------*/
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
    
    fontAtlas = std::move(state.fontAtlas);
    fontGeom = std::move(state.fontGeom);
    fontProg = std::move(state.fontProg);
    
    pBlender = std::move(state.pBlender);
    
    return *this;
}

/*-------------------------------------
 * Starting state
 * 
 * Resources that were already allocated are removed during "onStop()"
-------------------------------------*/
bool uiState::onStart() {
    bool ret = true;
    ls::draw::vertexShader vertShader;
    ls::draw::fragmentShader fontFragShader;
    
    ls::draw::fontResource* pFontLoader = new ls::draw::fontResource{};
    pBlender = new ls::draw::blendObject{};
    
    if (!pFontLoader
    || !pFontLoader->loadFile(TEST_FONT_FILE, 36)
    || !fontAtlas.init(*pFontLoader)
    || !fontGeom.init(fontAtlas, "Hello World")
    || !pBlender
    || !vertShader.init(meshVSData)
    || !fontFragShader.init(fontFSData)
    || !fontProg.init(vertShader, fontFragShader)
    || !fontProg.link()
    ) {
        LS_LOG_ERR("An error occurred while initializing the test state's resources");
        ret = false;
    }
    else {
        pBlender->setState(true);
        pBlender->setBlendEquation(ls::draw::BLEND_EQU_ADD, ls::draw::BLEND_EQU_ADD);
        pBlender->setBlendFunction(ls::draw::BLEND_FNC_ONE, ls::draw::BLEND_FNC_1_SUB_SRC_ALPHA, ls::draw::BLEND_FNC_ONE, ls::draw::BLEND_FNC_ZERO);
    }
    
    delete pFontLoader;
    
    fontProg.unbind();
    global::pDisplay->setFullScreenMode(FULLSCREEN_WINDOW);
    LOG_GL_ERR();
    return ret;
}

/*-------------------------------------
 * Running state
-------------------------------------*/
void uiState::onRun() {
    // Regenerate a string mesh using the frame's timing information.
    secondTimer += getParentSystem().getTickTime();
    if (secondTimer >= 1000) {
        const std::string&& timingStr = getTimingStr();
        fontGeom.init(fontAtlas, timingStr);
        secondTimer = 0;
    }
    
    drawScene();
}

/*-------------------------------------
 * Pausing state
-------------------------------------*/
void uiState::onPause() {
    onRun();
}

/*-------------------------------------
 * Stopping state
-------------------------------------*/
void uiState::onStop() {
    secondTimer = 0.f;
    
    fontAtlas.terminate();
    fontGeom.terminate();
    fontProg.terminate();
    
    delete pBlender;
    pBlender = nullptr;
}

/*-------------------------------------
 * Get a string representing the current Ms/s and F/s
-------------------------------------*/
std::string uiState::getTimingStr() const {
    const float tickTime = (float)getParentSystem().getTickTime();
    return
        "MPS: " + std::to_string(tickTime) +
        "\nFPS:  " + std::to_string(1000.f/tickTime);
}

/*-------------------------------------
 * get a 2d viewport for 2d/gui drawing
-------------------------------------*/
math::mat4 uiState::get2dViewport() const {
    const display& display = *global::pDisplay;
    const math::vec2&& displayRes = (math::vec2)display.getResolution();
    
    return math::ortho(
        0.f, displayRes[0],
        0.f, displayRes[1],
        0.f, 1.f
    );
}

/*-------------------------------------
 * Drawing a scene
-------------------------------------*/
void uiState::drawScene() {
    LOG_GL_ERR();
    
    // setup some UI parameters with a resolution-independent model matrix
    const display* const disp   = global::pDisplay;
    const math::vec2&& res      = (math::vec2)disp->getResolution();
    math::mat4&& modelMat       = math::translate(math::mat4{1.f}, math::vec3{0.f, res[1], 0.f});
    modelMat                    = math::scale(modelMat, math::vec3{math::length(res)*fontAtlas.getPixelRatio()});
    modelMat                    = get2dViewport() * modelMat;
    
    fontProg.bind();
    fontProg.setUniformValue    (fontProg.getUniformLocation("mvpMatrix"), modelMat);

    // setup parameters to draw a transparent mesh as a screen overlay/UI
    glDisable(GL_DEPTH_TEST);
    pBlender->bind();
    fontAtlas.getTexture().bind();
    fontGeom.draw();
    fontAtlas.getTexture().unbind();
    pBlender->unbind();
    glEnable(GL_DEPTH_TEST);
    
    fontProg.unbind();
    LOG_GL_ERR();
}
