/*
 * File:   HelloPrimState.h
 * Author: miles
 *
 * Created on October 27, 2015, 10:44 PM
 */

#ifndef HELLOPRIMSTATE_H
#define HELLOPRIMSTATE_H



#include <memory>

#include "lightsky/draw/VertexBuffer.h"
#include "lightsky/draw/ShaderProgram.h"
#include "lightsky/draw/VertexArray.h"

#include "lightsky/game/GameState.h"



class ControlState;



class HelloPrimState final : public ls::game::GameState {
  private:
    ls::draw::ShaderProgram shader;

    ls::draw::VertexBuffer vbo;

    ls::draw::VertexArray vao;

    void update_vert_color(const unsigned vertPos, const bool isVisible);

    std::unique_ptr<char[]> gen_vertex_data();
    
    void setup_uniforms(const ls::draw::ShaderProgram& s);

  public:
    virtual ~HelloPrimState();

    HelloPrimState();

    HelloPrimState(const HelloPrimState&) = delete;

    HelloPrimState(HelloPrimState&&);

    HelloPrimState& operator=(const HelloPrimState&) = delete;

    HelloPrimState& operator=(HelloPrimState&&);

  private:
    void setup_shaders();

    void setup_prims();

  protected:
    virtual bool on_start() override;

    virtual void on_run() override;

    virtual void on_stop() override;
};



#endif  /* HELLOPRIMSTATE_H */
