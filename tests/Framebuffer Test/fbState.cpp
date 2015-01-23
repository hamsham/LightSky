/* 
 * File:   fbState.cpp
 * Author: miles
 * 
 * Created on July 30, 2014, 9:50 PM
 */

#include <chrono>
#include <utility>

#include "main.h"
#include "controlState.h"
#include "display.h"
#include "fbState.h"

namespace draw = ls::draw;

enum {
    TEST_MAX_SCENE_OBJECTS = 10,
    TEST_MAX_SCENE_INSTANCES = TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS
};


static constexpr float TEST_PROJECTION_FOV = 60.f;
static constexpr float TEST_PROJECTION_NEAR = 0.1f;
static constexpr float TEST_PROJECTION_FAR = 100.f;
static constexpr float TEST_INSTANCE_RADIUS = 0.5f;
static constexpr char TEST_SCENE_FILE[] = "./testmesh.dae";

/*-------------------------------------
 * Destructor
-------------------------------------*/
fbState::~fbState() {
}

/*-------------------------------------
 * Constructor & Destructor
-------------------------------------*/
fbState::fbState() :
    gameState()
{}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
fbState::fbState(fbState&& state) :
    gameState{}
{    
    *this = std::move(state);
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
fbState& fbState::operator=(fbState&& state) {
    gameState::operator=(std::move(state));
    
    pControlState = state.pControlState;
    pControlState->setFramebufferState(this);
    state.pControlState = nullptr;
    
    testFb = std::move(state.testFb);
    testRb = std::move(state.testRb);
    
    pScene = state.pScene;
    state.pScene = nullptr;
    
    pRenderer = state.pRenderer;
    state.pRenderer = nullptr;
    
    fbRes = state.fbRes;
    state.fbRes = math::vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT};
    
    return *this;
}

/*-------------------------------------
 * Allocate internal class memory
-------------------------------------*/
bool fbState::initMemory() {
    draw::sceneResource* const pMeshLoader = new draw::sceneResource{};
    pScene = new draw::sceneGraph{};
    pRenderer = new draw::defaultRenderStage{};
    draw::texture* pColorTex = new draw::texture{};
    bool ret = true;
    
    pScene->getTextureList().push_back(pColorTex);
    
    if (!ret
    || !pMeshLoader->loadFile(TEST_SCENE_FILE)
    //|| !pMeshLoader->loadSphere(32)
    || !pScene->init(*pMeshLoader, true)
    || !pColorTex->init(draw::COLOR_FMT_DEFAULT, math::vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT})
    || !pRenderer->init()
    ) {
        ret = false;
    }
    
    if (ret) {
        pColorTex->bind();
        pColorTex->setParameter(draw::TEX_PARAM_MIN_FILTER, draw::TEX_FILTER_LINEAR);
        pColorTex->setParameter(draw::TEX_PARAM_MAG_FILTER, draw::TEX_FILTER_LINEAR);
        pColorTex->setParameter(draw::TEX_PARAM_WRAP_S,     draw::TEX_PARAM_CLAMP_EDGE);
        pColorTex->setParameter(draw::TEX_PARAM_WRAP_T,     draw::TEX_PARAM_CLAMP_EDGE);
        pColorTex->unbind();
    }
    
    delete pMeshLoader;
    return ret;
}

/*-------------------------------------
 * Initialize the framebuffers
-------------------------------------*/
bool fbState::initFramebuffers() {
    if (!testFb.init()
    ||  !testRb.init(draw::rbo_format_t::RBO_FMT_DEPTH_32, math::vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT})
    ) {
        LS_LOG_ERR("An Error occurred while creating the test depth buffer.");
        return false;
    }
    
    scaleFramebuffer(0);
    
    return true;
}

/*-------------------------------------
 * Post-Initialization renderer parameters
-------------------------------------*/
void fbState::setRendererParams() {
    draw::camera& mainCam = pScene->getMainCamera();
    mainCam.setProjectionParams(TEST_PROJECTION_FOV, TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT, TEST_PROJECTION_NEAR, TEST_PROJECTION_FAR);
    mainCam.makePerspective();
    mainCam.lockYAxis(true);
    mainCam.setViewMode(draw::camera_view_t::VIEW_NORMAL);
    mainCam.lookAt(math::vec3{10.f}, math::vec3{0.f});
    
    constexpr draw::color::color gray = draw::color::gray;
    glClearColor(gray[0], gray[1], gray[2], gray[3]);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

/*-------------------------------------
 * Starting state
-------------------------------------*/
bool fbState::onStart() {
    pControlState = new controlState{};
    if (!pControlState) {
        LS_LOG_ERR("Error: Unable to create a framebuffer control state.");
        return false;
    }
    else {
        pControlState->setFramebufferState(this);
        ls::game::gameSystem& sys = getParentSystem();
        if (!sys.pushGameState(pControlState)) {
            LS_LOG_ERR("Error: Unable to start the framebuffer control state.");
            delete pControlState;
            return false;
        }
    }
    
    if (!initMemory()
    ||  !initFramebuffers()
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

/*-------------------------------------
 * Running state
-------------------------------------*/
void fbState::onRun() {
    pScene->update(this->getParentSystem().getTickTime());
    drawScene();
}

/*-------------------------------------
 * Pausing state
-------------------------------------*/
void fbState::onPause() {
    drawScene();
}

/*-------------------------------------
 * Stopping state
-------------------------------------*/
void fbState::onStop() {
    if (pControlState) {
        pControlState->setStateStatus(ls::game::game_state_t::STOPPED);
        pControlState = nullptr;
    }
    
    testRb.terminate();
    testFb.terminate();
    
    delete pScene;
    pScene = nullptr;
    
    delete pRenderer;
    pRenderer = nullptr;
    
    fbRes = {TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT};
}

/*-------------------------------------
 * get a 2d viewport for 2d/gui drawing
-------------------------------------*/
math::mat4 fbState::get3dViewport() const {
    const math::vec2i displayRes =global::pDisplay->getResolution();
    return math::perspective(
        TEST_PROJECTION_FOV, (float)displayRes[0]/displayRes[1],
        TEST_PROJECTION_NEAR, TEST_PROJECTION_FAR
    );
}

/*-------------------------------------
 * Drawing a scene
-------------------------------------*/
void fbState::drawScene() {
    LOG_GL_ERR();
    
    // setup a viewport for a custom framebuffer
    glViewport(0, 0, fbRes[0], fbRes[1]);

    // use render to the framebuffer's color attachment
    static constexpr draw::fbo_attach_t fboDrawAttachments[] = {draw::FBO_ATTACHMENT_0};

    // setup the framebuffer for draw operations
    testFb.setAccessType(draw::FBO_ACCESS_W);
    testFb.bind();
    testFb.setDrawTargets(1, fboDrawAttachments);
    testFb.clear((draw::fbo_mask_t)(draw::FBO_DEPTH_BIT | draw::FBO_COLOR_BIT));
    
    // draw a test mesh
    pRenderer->bind();
    pRenderer->draw(*pScene);
    pRenderer->unbind();
    
    // restore draw operations to the default GL framebuffer, bind it for
    // reading, then blit
    testFb.unbind();
    testFb.setAccessType(draw::FBO_ACCESS_R);
    testFb.bind();
    testFb.blit(math::vec2i{0}, fbRes, math::vec2i{0}, global::pDisplay->getResolution(), draw::FBO_COLOR_BIT);
    testFb.unbind();
    
    LOG_GL_ERR();
}

/*-------------------------------------
 * Camera movement
-------------------------------------*/
void fbState::moveCamera(const math::vec3& deltaPos) {
    draw::camera& mainCam = pScene->getMainCamera();
    mainCam.move(deltaPos);
}

/*-------------------------------------
 * Update the renderer's viewport with the current window resolution
-------------------------------------*/
void fbState::resizeFramebuffer(const math::vec2i& res) {
    glViewport(0, 0, res[0], res[1]);
    
    draw::camera& mainCam = pScene->getMainCamera();
    mainCam.setProjectionParams(TEST_PROJECTION_FOV, res[0], res[1], TEST_PROJECTION_NEAR, TEST_PROJECTION_FAR);
    mainCam.makePerspective();
}

/*-------------------------------------
 * Mouse Wheel Event
-------------------------------------*/
void fbState::scaleFramebuffer(const int deltaScale) {
    fbRes += deltaScale;
    
    const math::vec2i displayRes = global::pDisplay->getResolution();
    fbRes[0] = math::clamp(fbRes[0], (int)TEST_FRAMEBUFFER_WIDTH, displayRes[0]);
    fbRes[1] = math::clamp(fbRes[1], (int)TEST_FRAMEBUFFER_HEIGHT, displayRes[1]);
    
    std::vector<draw::texture*>& texList = pScene->getTextureList();
    draw::texture* pColorTex = texList.front();
    
    testFb.bind();
    LOG_GL_ERR();
    
    if (pColorTex->init(draw::COLOR_FMT_DEFAULT, fbRes)) {
        testFb.attachRenderTarget(draw::FBO_ATTACHMENT_0, *pColorTex);
        pColorTex->unbind();
    }
    LOG_GL_ERR();
    
    if (testRb.init(draw::rbo_format_t::RBO_FMT_DEPTH_32, fbRes)) {
        testFb.attachRenderTarget(draw::FBO_ATTACHMENT_DEPTH, testRb);
        testRb.unbind();
    }
    LOG_GL_ERR();
    
    LS_DEBUG_ASSERT(draw::framebuffer::getStatus(testFb) == draw::FBO_COMPLETE);
    
    testFb.unbind();
    LOG_GL_ERR();
}

/*-------------------------------------
 * Mouse Move Event
-------------------------------------*/
void fbState::rotateCamera(const math::vec3& deltaAngle) {
    draw::camera& mainCam = pScene->getMainCamera();
    mainCam.rotate(deltaAngle);
}
