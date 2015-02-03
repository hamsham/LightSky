/* 
 * File:   uiState.cpp
 * Author: miles
 * 
 * Created on August 5, 2014, 9:18 PM
 */

#include <utility>

#include "lightsky/draw/atlas.h"
#include "lightsky/draw/geometry.h"
#include "lightsky/draw/sceneGraph.h"
#include "lightsky/draw/sceneMesh.h"
#include "lightsky/draw/sceneNode.h"
#include "lightsky/draw/texture.h"

#include "display.h"
#include "uiState.h"

#define TEST_FONT_FILE L"./FiraSans-Regular.otf"

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
    
    pScene = std::move(state.pScene);
    state.pScene = nullptr;
    
    pRenderer = std::move(state.pRenderer);
    state.pRenderer = nullptr;
    
    return *this;
}

/*-------------------------------------
 * Starting state
 * 
 * Resources that were already allocated are removed during "onStop()"
-------------------------------------*/
bool uiState::onStart() {
    bool ret = true;
    
    pScene = new ls::draw::sceneGraph{};
    pRenderer = new ls::draw::textRenderStage{};
    
    ls::draw::fontResource* pFontLoader = new ls::draw::fontResource{};
    ls::draw::geometry* pGeometry = new ls::draw::geometry{};
    ls::draw::sceneMesh* pMesh = new ls::draw::sceneMesh{};
    
    if (!pScene
    || !pRenderer
    || !pRenderer->init()
    || !pFontLoader
    || !pFontLoader->loadFile(TEST_FONT_FILE, 36)
    || !fontAtlas.init(*pFontLoader)
    || !pGeometry
    || !pGeometry->init(fontAtlas, "Hello World!")
    || !pMesh
    || !pMesh->init(*pGeometry)
    ) {
        LS_LOG_ERR("An error occurred while initializing the test state's resources");
        ret = false;
    }
    else {
        pRenderer->setTextColor(ls::draw::color::cyan);
        
        pScene->getGeometryList().push_back(pGeometry);
        pScene->getMeshList().push_back(pMesh);
        pMesh->addTexture(fontAtlas.getTexture());
        
        pScene->getNodeList().resize(1);
        ls::draw::sceneNode& node = pScene->getNodeList().back();
        node.nodeChildren.clear();
        node.nodeMeshes.push_back(pMesh);
        node.nodeParent = &pScene->getRootNode();
        pScene->update(0);
    }
    
    delete pFontLoader;
    
    global::pDisplay->setFullScreenMode(FULLSCREEN_WINDOW);
    LOG_GL_ERR();
    return ret;
}

/*-------------------------------------
 * Running state
-------------------------------------*/
void uiState::onRun() {
    ls::draw::geometry* pGeometry = pScene->getGeometryList().back();
    
    // Regenerate a string mesh using the frame's timing information.
    secondTimer += getParentSystem().getTickTime();
    
    if (secondTimer >= 1000) {
        const std::string&& timingStr = getTimingStr();
        pGeometry->init(fontAtlas, timingStr);
        secondTimer = 0;
    }
    
    pScene->update(getParentSystem().getTickTime());
    
    // Make sure that the current mesh contains all relevant text vertices.
    ls::draw::sceneMesh* pMesh = pScene->getMeshList().back();
    pMesh->setIndices(pGeometry->getSubGeometry().front());
    
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
    secondTimer = 0;
    
    fontAtlas.terminate();
    
    delete pScene;
    pScene = nullptr;
    
    delete pRenderer;
    pRenderer = nullptr;
}

/*-------------------------------------
 * Get a string representing the current Ms/s and F/s
-------------------------------------*/
std::string uiState::getTimingStr() const {
    const uint64_t tickTime = getParentSystem().getTickTime();
    return
        "MPS:  " + std::to_string(tickTime) +
        "\nFPS:   " + std::to_string(1000/tickTime);
}

/*-------------------------------------
 * get a 2d viewport for 2d/gui drawing
-------------------------------------*/
void uiState::reset2dViewport() const {
    const display& display = *global::pDisplay;
    const math::vec2&& displayRes = (math::vec2)display.getResolution();
    
    ls::draw::camera& mainCam = pScene->getMainCamera();
    mainCam.setProjectionParams(60.f, displayRes[0], displayRes[1], 0.f, 10.f);
    mainCam.makeOrtho();
}

/*-------------------------------------
 * Drawing a scene
-------------------------------------*/
void uiState::drawScene() {
    LOG_GL_ERR();
    reset2dViewport();
    
    // setup some UI parameters with a resolution-independent model matrix
    const display* const disp   = global::pDisplay;
    const math::vec2&& res      = (math::vec2)disp->getResolution();
    const math::mat4&& modelMat = math::translate(math::mat4{1.f}, math::vec3{0.f, res[1], 0.f});
    ls::draw::sceneNode& node   = pScene->getNodeList().back();
    
    node.nodeTransform.setTransform(math::scale(modelMat, math::vec3{math::length(res)*fontAtlas.getPixelRatio()}));
    
    // setup parameters to draw a transparent mesh as a screen overlay/UI
    pRenderer->bind();
    pRenderer->draw(*pScene);
    pRenderer->unbind();
    
    LOG_GL_ERR();
}
