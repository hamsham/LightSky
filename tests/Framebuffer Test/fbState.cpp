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

typedef math::perlinNoise_t<float> perlinNoise;

enum {
    TEST_MAX_SCENE_OBJECTS = 10,
    TEST_MAX_SCENE_INSTANCES = TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS*TEST_MAX_SCENE_OBJECTS,
    TEST_NOISE_RESOLUTION = 1024,
    TEST_NOISE_SAMPLES = 32
};


static constexpr float TEST_PROJECTION_FOV = 60.f;
static constexpr float TEST_PROJECTION_NEAR = 0.01f;
static constexpr float TEST_PROJECTION_FAR = 10.f;
static constexpr float TEST_INSTANCE_RADIUS = 0.5f;
static constexpr char TEST_SCENE_FILE[] = "./testmesh.dae";

/*-----------------------------------------------------------------------------
 * Tests for loading perlin noise on another thread
-----------------------------------------------------------------------------*/
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

/*-------------------------------------
 * Constructor & Destructor
-------------------------------------*/
fbState::fbState() :
    gameState()
{}

fbState::fbState(fbState&& state) :
    gameState{}
{    
    *this = std::move(state);
}

fbState::~fbState() {
}

fbState& fbState::operator=(fbState&& state) {
    gameState::operator=(std::move(state));
    
    pControlState = state.pControlState;
    pControlState->setFramebufferState(this);
    state.pControlState = nullptr;
    
    testFb = std::move(state.testFb);
    testRb = std::move(state.testRb);
    
    pScene = state.pScene;
    state.pScene = nullptr;
    
    pScene = state.pScene;
    state.pScene = nullptr;
    
    fbRes = state.fbRes;
    state.fbRes = math::vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT};
    
    orientation = state.orientation;
    state.orientation = math::quat{};
    
    futureNoise = std::move(state.futureNoise);
    
    return *this;
}

/*-------------------------------------
 * Allocate internal class memory
-------------------------------------*/
bool fbState::initMemory() {
    pScene = new draw::sceneGraph{};
    pRenderer = new draw::defaultRenderStage{};
    
    if (!pScene
    ||  !pRenderer
    || !pRenderer->init()
    ||  !testFb.init()
    ) {
        return false;
    }
    
    futureNoise = std::move(
        std::async(std::launch::async, &generateNoiseTexture, TEST_NOISE_RESOLUTION, TEST_NOISE_RESOLUTION)
    );
    
    // prepare an initial perlin noise texture.
    while (futureNoise.wait_for(std::chrono::seconds{0}) != std::future_status::ready) {
        continue;
    }
    
    return true;
}

/*-------------------------------------
 * Initialize resources from files
-------------------------------------*/
bool fbState::initFileData() {
    
    draw::sceneResource* pMeshLoader = new draw::sceneResource{};
    draw::texture* pColorTex = new draw::texture{};
    draw::texture* noiseTex = new draw::texture{};
    bool ret = true;
    
    if (!pMeshLoader
    || !pMeshLoader->loadFile(TEST_SCENE_FILE)
    || !pScene->init(*pMeshLoader)
    || !pColorTex->init(draw::COLOR_FMT_DEFAULT, math::vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT})
    || !noiseTex->init(0, draw::COLOR_FMT_R_32F, math::vec2i{TEST_NOISE_RESOLUTION}, draw::COLOR_LAYOUT_R, draw::COLOR_TYPE_FLOAT, nullptr)
    ) {
        ret = false;
    }
    else {
        pScene->getTextureList().push_back(pColorTex);
        pScene->getTextureList().push_back(noiseTex); // last texture in the scene's texture list.
        
         // initialize the perlin noise texture
        regenerateNoise();
    }
    
    delete pMeshLoader;
    
    return ret;
}

/*-------------------------------------
 * regenerate a noise texture
-------------------------------------*/
void fbState::regenerateNoise() {
    if (futureNoise.wait_for(std::chrono::seconds{0}) != std::future_status::ready) {
        return;
    }
    
    std::vector<float>&& noiseTable = futureNoise.get();
    
    draw::texture* const pPerlinTexture = pScene->getTextureList().back();
    pPerlinTexture->bind();
    pPerlinTexture->modify(0, math::vec2i{TEST_NOISE_RESOLUTION}, draw::COLOR_LAYOUT_R, draw::COLOR_TYPE_FLOAT, noiseTable.data());
    
    pPerlinTexture->setParameter(draw::TEX_PARAM_MIN_FILTER,  draw::TEX_FILTER_LINEAR);
    pPerlinTexture->setParameter(draw::TEX_PARAM_MAG_FILTER,  draw::TEX_FILTER_LINEAR);
    pPerlinTexture->setParameter(draw::TEX_PARAM_WRAP_S,      draw::TEX_PARAM_REPEAT);
    pPerlinTexture->setParameter(draw::TEX_PARAM_WRAP_T,      draw::TEX_PARAM_REPEAT);
    pPerlinTexture->unbind();
    
    futureNoise = std::move(
        std::async(std::launch::async, &generateNoiseTexture, TEST_NOISE_RESOLUTION, TEST_NOISE_RESOLUTION)
    );
}

/*-------------------------------------
 * Initialize the framebuffers
-------------------------------------*/
bool fbState::initFramebuffers() {
    if (!testRb.init(draw::rbo_format_t::RBO_FMT_DEPTH_32, math::vec2i{TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT})) {
        LS_LOG_ERR("An Error occurred while creating the test depth buffer.");
        return false;
    }
    
    std::vector<draw::texture*>& texList = pScene->getTextureList();
    draw::texture* const pColorTex = texList[texList.size()-2];
    
    // setup the test framebuffer depth texture
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
    testFb.attachRenderTarget(draw::FBO_ATTACHMENT_DEPTH, testRb);
    testFb.attachRenderTarget(draw::FBO_ATTACHMENT_0, *pColorTex);
    
    LOG_GL_ERR();
    
    if (draw::framebuffer::getStatus(testFb) != draw::FBO_COMPLETE) {
        testFb.unbind();
        return false;
    }
    
    testFb.unbind();
    
    return true;
}

/*-------------------------------------
 * Post-Initialization renderer parameters
-------------------------------------*/
void fbState::setRendererParams() {
    draw::camera* const pMainCam = pScene->getCameraList().front();
    pMainCam->setProjectionParams(TEST_PROJECTION_FOV, TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT, TEST_PROJECTION_NEAR, TEST_PROJECTION_FAR);
    pMainCam->makePerspective();
    
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
    ||  !initFileData()
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
    draw::camera* pMainCam = pScene->getCameraList().front();
    pMainCam->setOrientation(orientation);
    
    pScene->update(this->getParentSystem().getTickTime());
    drawScene();
}

/*-------------------------------------
 * Pausing state
-------------------------------------*/
void fbState::onPause() {
    draw::camera* pMainCam = pScene->getCameraList().front();
    pMainCam->setOrientation(orientation);
    
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
    orientation = math::quat{0.f, 0.f, 0.f, 1.f};
    
    futureNoise.wait();
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
    static const draw::fbo_attach_t fboDrawAttachments[] = {draw::FBO_ATTACHMENT_0};

    // setup the framebuffer for draw operations
    testFb.setAccessType(draw::FBO_ACCESS_W);
    testFb.bind();
    testFb.setDrawTargets(1, fboDrawAttachments);
    testFb.clear((draw::fbo_mask_t)(draw::FBO_DEPTH_BIT | draw::FBO_COLOR_BIT));
    
    // draw a test mesh
    pRenderer->draw(*pScene);
    
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
    LOG_GL_ERR();
}

/*-------------------------------------
 * Camera movement
-------------------------------------*/
void fbState::moveCamera(const math::vec3& deltaPos) {    
    const math::vec3&& translation = {
        math::dot(math::getAxisX(orientation), deltaPos),
        math::dot(math::getAxisY(orientation), deltaPos),
        math::dot(math::getAxisZ(orientation), deltaPos)
    };
    
    draw::camera* pMainCam = pScene->getCameraList().front();
    pMainCam->move(translation);
}

/*-------------------------------------
 * Update the renderer's viewport with the current window resolution
-------------------------------------*/
void fbState::resizeFramebuffer(const math::vec2i& res) {
    glViewport(0, 0, res[0], res[1]);
    
    draw::camera* pMainCam = pScene->getCameraList().front();
    pMainCam->setProjectionParams(TEST_PROJECTION_FOV, res[0], res[1], TEST_PROJECTION_NEAR, TEST_PROJECTION_FAR);
    pMainCam->makePerspective();
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
    draw::texture* pColorTex = texList[texList.size()-2];
    
    testFb.bind();
    LOG_GL_ERR();
    
    if (!testRb.init(draw::rbo_format_t::RBO_FMT_DEPTH_32, fbRes)) {
        LS_LOG_ERR("Error: Failed to resize the depth buffer.");
        return;
    }
    LOG_GL_ERR();
    
    pColorTex->init(draw::COLOR_FMT_DEFAULT, fbRes);
    LOG_GL_ERR();
    
    testFb.attachRenderTarget(draw::FBO_ATTACHMENT_0, *pColorTex);
    LOG_GL_ERR();
    testFb.attachRenderTarget(draw::FBO_ATTACHMENT_DEPTH, testRb);
    LOG_GL_ERR();
    draw::framebuffer::getStatus(testFb);
    testFb.unbind();
    
    LOG_GL_ERR();
}

/*-------------------------------------
 * Mouse Move Event
-------------------------------------*/
void fbState::rotateCamera(const math::vec3& deltaAngle) {
    // Always lerp to the new mouse position
    const math::quat&& lerpX = math::lerp(
        math::quat{0.f, 0.f, 0.f, 1.f}, math::quat{deltaAngle[1], 0.f, 0.f, 1.f}, 1.f
    );
    
    const math::quat&& lerpY = math::lerp(
        math::quat{0.f, 0.f, 0.f, 1.f}, math::quat{0.f, deltaAngle[0], 0.f, 1.f}, 1.f
    );
        
    orientation *= lerpY * lerpX;
    orientation = math::normalize(orientation);
}
