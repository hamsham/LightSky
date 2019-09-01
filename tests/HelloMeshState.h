/*
 * File:   HelloMeshState.h
 * Author: miles
 *
 * Created on October 27, 2015, 10:44 PM
 */

#ifndef HELLOMESHSTATE_H
#define HELLOMESHSTATE_H

#include <chrono>
#include <vector>
#include <future>

#include "lightsky/draw/AnimationPlayer.h"
#include "lightsky/draw/SceneGraph.h"
#include "lightsky/draw/SceneFileLoader.h"
#include "lightsky/draw/ShaderProgram.h"
#include "lightsky/draw/UniformBuffer.h"

#include "lightsky/game/GameState.h"



struct Light
{
    ls::math::vec4 pos;
    ls::math::vec4 ambient;
    ls::math::vec4 diffuse;
    ls::math::vec4 specular;
};



struct PointLight
{
    float constant;
    float linear;
    float quadratic;
    float padding;
};



struct SpotLight
{
    float innerCutoff;
    float outerCutoff;
    ls::math::vec4 direction;
};



struct MeshUniforms
{
    ls::math::mat4 mvpMatrix;
    ls::math::mat4 vpMatrix;
    ls::math::mat4 modelMatrix;

    ls::math::vec4 camPos;

    Light light;
    PointLight point;
    SpotLight spot;
};



class HelloMeshState final : public ls::game::GameState {
  private:
    ls::draw::ShaderProgram testShader;

    ls::draw::ShaderProgram enbtShader;
    
    ls::draw::SceneGraph testData;
    
    std::chrono::steady_clock::time_point prevTime;
    
    unsigned currentAnimationId;
    
    ls::draw::AnimationPlayer currentAnimation;
    
    ls::draw::UniformBuffer uniformBlock;
    
    unsigned meshShaderUboIndex;
    
    unsigned enbtShaderUboIndex;

    std::future<ls::draw::SceneFilePreLoader> preloader;
    
  public:
    virtual ~HelloMeshState();

    HelloMeshState();

    HelloMeshState(const HelloMeshState&) = delete;

    HelloMeshState(HelloMeshState&&);

    HelloMeshState& operator=(const HelloMeshState&) = delete;

    HelloMeshState& operator=(HelloMeshState&&);

  private:
    void bind_shader_uniforms(const ls::draw::ShaderProgram& s);
    
    void unbind_shader_uniforms();
    
    void setup_shader(
        ls::draw::ShaderProgram& s,
        const char* const vertData,
        const char* const fragData,
        const char* const geomData = nullptr
    );
    
    void setup_animations();
    
    void setup_uniform_blocks();
    
    uint32_t render_scene_node(uint32_t currentVao, const ls::draw::SceneNode& n);
    
    void render_scene_graph(const ls::draw::ShaderProgram& s, const unsigned uboBindIndex);
    
    void update_animations();

  protected:
    virtual bool on_start() override;

    virtual void on_run() override;

    virtual void on_stop() override;
};



#endif  /* HELLOMESHSTATE_H */
