/* 
 * File:   testState.cpp
 * Author: hammy
 * 
 * Created on January 19, 2014, 4:19 PM
 */

#include <string>
#include <utility>
#include <GL/glew.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <cmath>
#include "testState.h"
#include "display.h"
#include "imageResource.h"
#include "fontResource.h"
#include "meshResource.h"
#include "mesh.h"

bool GAME_KEYS[512] = {false};

using math::vec2i;
using math::vec2;
using math::vec3;
using math::mat4;
using math::quat;

template <typename numType>
math::quat_t<numType> lookAt(const math::vec3_t<numType>& v1, const math::vec3_t<numType>& v2){
    const math::vec3_t<numType>&& a = math::normalize<numType>(v1);
    const math::vec3_t<numType>&& b = math::normalize<numType>(v2);
    
    const math::vec3_t<numType>&& w = math::cross<numType>(a, b);
    
    const math::quat_t<numType> q{
        w[0], w[1], w[2], numType{1} + math::dot<numType>(a, b)
    };
    
	return math::normalize<numType>(q);
}

const char testTextFile[] = {
    //"liberationmono.ttf"
    "testfont.ttf"
    //"DejaVuSansMono.ttf"
};

const char testTextString[] = R"***(x
abcdefghijklmnopqrstuvwxyz
ABCDEFGHIJKLMNOPQRSTUVWXYZ
01234    56789
~!@#$%^&*()_+
`{}|:\<>?
[];',./

The [quick] (brown) fox
jumped over the slow, lazy dog! :)

)***";

/*
 * This shader uses a Logarithmic Z-Buffer, thanks to
 * http://www.gamasutra.com/blogs/BranoKemen/20090812/2725/Logarithmic_Depth_Buffer.php
 */
const char vertShaderData[] = R"***(
#version 330 core

layout (location = 0) in vec3 inPosVerts;
layout (location = 1) in vec2 inUv;

uniform mat4 mvpMatrix;

out vec2 uvCoords;

void main() {
    vec4 p = mvpMatrix * vec4(inPosVerts, 1.0);
    const float C = 1.0;
    const float FAR = 100.0;
    float pz = -log(C * p.z + 1.0) / log(C * FAR + 1.0);
    
    gl_Position = vec4(p.xy, pz, p.w);
    
    uvCoords = inUv;
}
)***";

const char fragShaderData[] = R"***(
#version 330 core

uniform sampler2D tex;

in vec2 uvCoords;
out vec4 outFragCol;

void main() {
    outFragCol = texture(tex, uvCoords);
}
)***";

// Testing Signed-Distance-Fields for font rendering (SDF by texture mask).
const char fontFS[] = R"***(
#version 330

precision lowp float;

in vec2 uvCoords;
out vec4 outFragCol;

uniform sampler2DRect texSampler;
uniform vec4 fontColor = vec4(0.0, 1.0, 1.0, 1.0);

void main() {
    float mask = texture(texSampler, uvCoords).r;
    outFragCol = fontColor*step(0.5, mask);
    //outFragCol = fontColor*smoothstep(0.49, 0.51, mask);
}
)***";

shaderProgram fontProgram;

/******************************************************************************
 * Constructor & Destructor
******************************************************************************/
testState::testState() {
    SDL_StopTextInput();
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

testState::~testState() {
}

/******************************************************************************
 * Hardware Events
******************************************************************************/
/******************************************************************************
 * Key Up Event
******************************************************************************/
void testState::onKeyboardUpEvent(const SDL_KeyboardEvent* e) {
    const SDL_Keycode key = e->keysym.sym;
    
    if (key < 0 || (unsigned)key >= LS_ARRAY_SIZE(GAME_KEYS)) {
        return;
    }
    
    if (key == SDLK_ESCAPE) {
        this->setState(state_type::GAME_STOPPED);
    }
    else {
        GAME_KEYS[key] = false;
    }
}

/******************************************************************************
 * Key Down Event
******************************************************************************/
void testState::onKeyboardDownEvent(const SDL_KeyboardEvent* e) {
    const SDL_Keycode key = e->keysym.sym;
    
    if (key < 0 || (unsigned)key >= LS_ARRAY_SIZE(GAME_KEYS)) {
        return;
    }
    
    GAME_KEYS[key] = true;
}

/******************************************************************************
 * Keyboard States
******************************************************************************/
void testState::updateKeyStates() {
    const float moveSpeed = 0.1f;
    vec3 pos = {0.f};
    
    if (GAME_KEYS[SDLK_w]) {
        pos[2] += moveSpeed;
    }
    if (GAME_KEYS[SDLK_s]) {
        pos[2] -= moveSpeed;
    }
    if (GAME_KEYS[SDLK_a]) {
        pos[0] += moveSpeed;
    }
    if (GAME_KEYS[SDLK_d]) {
        pos[0] -= moveSpeed;
    }
    
    const vec3 translation{
        math::dot(math::getAxisX(orientation), pos),
        math::dot(math::getAxisY(orientation), pos),
        math::dot(math::getAxisZ(orientation), pos)
    };
    
    const mat4& viewMatrix = matStack->getMatrix(matrix_type::VIEW_MATRIX);
    const mat4&& movement = math::translate(viewMatrix, translation);
    matStack->loadMatrix(matrix_type::VIEW_MATRIX, movement);
}

/******************************************************************************
 * Text Events
******************************************************************************/
void testState::onKeyboardTextEvent(const SDL_TextInputEvent*) {
}

/******************************************************************************
 * Window Event
******************************************************************************/
void testState::onWindowEvent(const SDL_WindowEvent* pEvent) {
    switch (pEvent->event) {
        case SDL_WINDOWEVENT_CLOSE:
            this->setState(state_type::GAME_STOPPED);
            break;
        default:
            break;
    }
}

/******************************************************************************
 * Mouse Move Event
******************************************************************************/
void testState::onMouseMoveEvent(const SDL_MouseMotionEvent* e) {
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
    
    const vec2i& res        = global::pDisplay->getResolution();
    const vec2&& fRes       = {(float)res[0], (float)res[1]};
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
void testState::onMouseButtonUpEvent(const SDL_MouseButtonEvent*) {
}

/******************************************************************************
 * Mouse Button Down Event
******************************************************************************/
void testState::onMouseButtonDownEvent(const SDL_MouseButtonEvent*) {
}

/******************************************************************************
 * Mouse Wheel Event
******************************************************************************/
void testState::onMouseWheelEvent(const SDL_MouseWheelEvent*) {
}

/******************************************************************************
 * Starting state
******************************************************************************/
bool testState::onStart() {
    meshResource* pLoader = new meshResource{};
    matStack = new matrixStack();
    imageResource imgFile;
    fontResource font;
    
    if (    pLoader == nullptr
    ||      !pLoader->loadTriangle()
    ||      !primMesh.init(*pLoader, 0)
    ||      matStack == nullptr
    ||      !imgFile.loadFile("test_img.jpg")
    ||      !tex.init(0, GL_RGB, imgFile.getPixelSize(), GL_BGR, GL_UNSIGNED_BYTE, imgFile.getData())
    ||      !font.loadFile(testTextFile, LS_DEFAULT_FONT_SIZE)
    ||      !atlas.load(font)
    ||      !pLoader->loadText(atlas, testTextString)
    ||      !textMesh.init(*pLoader, 0)
    ) {
        delete pLoader;
        pLoader = nullptr;
        
        delete matStack;
        matStack = nullptr;
        
        return false;
    }
    
    tex.bind();
    tex.setParameter(TEX_MAG_FILTER, LINEAR_FILTER);
    tex.setParameter(TEX_MIN_FILTER, NEAREST_FILTER);
    
    LOG_GL_ERR();
    
    // Initialize the shaders
    {
        vertexShader vertShader;
        fragmentShader fragShader;
        
        vertShader.compile(vertShaderData);
        fragShader.compile(fragShaderData);
        program.attachShaders(vertShader, fragShader);
        program.link();
        
        fragShader.terminate();
        fragShader.compile(fontFS);
        fontProgram.attachShaders(vertShader, fragShader);
        fontProgram.link();

        // Initialize the matrix stacks
        matStack->loadMatrix(
            matrix_type::PROJECTION_MATRIX,
            math::perspective(60.f, 4.f/3.f, 0.01f, 100.f)
        );
        matStack->loadMatrix(
            matrix_type::VIEW_MATRIX,
            math::lookAt(vec3(3.f), vec3(2.f, -2.f, -2.f), vec3(0.f, 1.f, 0.f))
        );
        matStack->constructMvp();
        
        program.bind();
        GLuint mvpId = program.getUniformLocation("mvpMatrix");
        program.setUniformValue(mvpId, matStack->getMvpMatrix());
        LOG_GL_ERR();
        
        fontProgram.bind();
        mvpId = fontProgram.getUniformLocation("mvpMatrix");
        program.setUniformValue(mvpId, matStack->getMvpMatrix());
        LOG_GL_ERR();
    }
    LOG_GL_ERR();
    
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    
    return true;
}

/******************************************************************************
 * Stopping state
******************************************************************************/
void testState::onStop() {
    delete matStack;
    matStack = nullptr;
    primMesh.terminate();
    textMesh.terminate();
    tex.terminate();
}

/******************************************************************************
 * Running state
******************************************************************************/
void testState::onRun(float dt) {
    (void)dt;
    
    updateKeyStates();
    drawScene();
}

/******************************************************************************
 * Pausing state
******************************************************************************/
void testState::onPause(float dt) {
    (void)dt;
    
    drawScene();
}

/******************************************************************************
 * Drawing a scene
******************************************************************************/
void testState::drawScene() {
    LOG_GL_ERR();
    
    const mat4& viewMat = matStack->getMatrix(matrix_type::VIEW_MATRIX);
    const mat4&& rotatedView = viewMat * math::quatToMat4(orientation);
    matStack->emplaceMatrix(matrix_type::VIEW_MATRIX, rotatedView);
    
    {
        /* Billboarding Test */
        const vec3 camPos = {-viewMat[3][0], 0.f, viewMat[3][2]};
        const mat4&& modelMat = math::lookAt(vec3{0.f}, camPos, vec3{0.f, 1.f, 0.f});
        
        matStack->emplaceMatrix(matrix_type::MODEL_MATRIX, modelMat);
        matStack->constructMvp();

        program.bind();
        GLuint mvpId = 0;
        mvpId = program.getUniformLocation("mvpMatrix");
        program.setUniformValue(mvpId, matStack->getMvpMatrix());
        tex.bind();
        primMesh.draw();
        tex.unbind();

        matStack->popMatrix(matrix_type::MODEL_MATRIX);
        matStack->constructMvp();

        /* Premultiplied alpha */
        glEnable(GL_BLEND);
        glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
        glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
        
        fontProgram.bind();
        mvpId = fontProgram.getUniformLocation("mvpMatrix");
        program.setUniformValue(mvpId, matStack->getMvpMatrix());
        atlas.getTexture().bind();
        textMesh.draw();
        atlas.getTexture().unbind();
        glDisable(GL_BLEND);
    }
    matStack->popMatrix(matrix_type::VIEW_MATRIX);
}
