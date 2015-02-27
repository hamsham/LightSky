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
//static constexpr char TEST_SCENE_FILE[] = "./testmesh.dae";
static constexpr char TEST_SCENE_FILE[] = "./Bob.md5mesh";

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
    
    pScene = state.pScene;
    state.pScene = nullptr;
    
    pRenderer = state.pRenderer;
    state.pRenderer = nullptr;
    
    return *this;
}

/*-------------------------------------
 * Allocate internal class memory
-------------------------------------*/
bool fbState::initMemory() {
    draw::sceneResource* const pMeshLoader = new draw::sceneResource{};
    pScene = new draw::sceneGraph{};
    pRenderer = new draw::defaultRenderStage{};
    bool ret = true;
    
    if (!ret
    || !pMeshLoader->loadFile(TEST_SCENE_FILE)
    //|| !pMeshLoader->loadSphere(32)
    || !pScene->init(*pMeshLoader)
    || !pRenderer->init()
    ) {
        ret = false;
    }
    
    delete pMeshLoader;
    return ret;
}

/*-------------------------------------
 * Starting state
-------------------------------------*/
bool fbState::onStart() {
    pControlState = new controlState{};
    if (!pControlState) {
        LS_LOG_ERR("Error: Unable to create a hardware control state.");
        return false;
    }
    else {
        pControlState->setFramebufferState(this);
        ls::game::gameSystem& sys = getParentSystem();
        if (!sys.pushGameState(pControlState)) {
            LS_LOG_ERR("Error: Unable to start the hardware control state.");
            delete pControlState;
            return false;
        }
    }
    
    if (!initMemory()) {
        LS_LOG_ERR("An error occurred while initializing the test state's resources");
        return false;
    }
    
    draw::camera& mainCam = pScene->getMainCamera();
    mainCam.setProjectionParams(TEST_PROJECTION_FOV, TEST_FRAMEBUFFER_WIDTH, TEST_FRAMEBUFFER_HEIGHT, TEST_PROJECTION_NEAR, TEST_PROJECTION_FAR);
    mainCam.makePerspective();
    mainCam.lockYAxis(true);
    //mainCam.lockYAxis(false);
    //mainCam.setViewMode(ls::draw::camera_mode_t::ARCBALL);
    mainCam.setViewMode(ls::draw::camera_mode_t::FIRST_PERSON);
    mainCam.lookAt(math::vec3{25.f, 25.f, 25.f}, math::vec3{0.f, 50.f, 0.f});
    
    constexpr draw::color::color gray = draw::color::gray;
    glClearColor(gray[0], gray[1], gray[2], gray[3]);
    
    return true;
}

/*-------------------------------------
 * Running state
-------------------------------------*/
void fbState::onRun() {
    pScene->update(this->getParentSystem().getTickTime());
    LOG_GL_ERR();
    
    // draw a test mesh
    pRenderer->bind();
    pRenderer->draw(*pScene);
    pRenderer->unbind();
    
    LOG_GL_ERR();
}

/*-------------------------------------
 * Pausing state
-------------------------------------*/
void fbState::onPause() {
    onRun();
}

/*-------------------------------------
 * Stopping state
-------------------------------------*/
void fbState::onStop() {
    if (pControlState) {
        pControlState->setStateStatus(ls::game::game_state_t::STOPPED);
        pControlState = nullptr;
    }
    
    delete pScene;
    pScene = nullptr;
    
    delete pRenderer;
    pRenderer = nullptr;
}

/*-------------------------------------
 * Camera movement
-------------------------------------*/
void fbState::moveCamera(const math::vec3& deltaPos) {
    draw::camera& mainCam = pScene->getMainCamera();
    mainCam.move(deltaPos);
}

/*-------------------------------------
 * Mouse Move Event
-------------------------------------*/
void fbState::rotateCamera(const math::vec3& deltaAngle) {
    draw::camera& mainCam = pScene->getMainCamera();
    mainCam.rotate(deltaAngle);
}
