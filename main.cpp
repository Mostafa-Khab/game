#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

#include "game.hpp"

class mygame: public game 
{
    void render() override;
    bool setup()  override;

    unsigned int vbo, ebo, vao;
    unsigned int vshader, fshader, shader_prg;

    friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

};

struct vertex{
  float x, y, z;
  float r, g, b, a;
};

vertex points[] = {
  -0.5f, 0.5f, 0.f,    1.f, 0.f, 0.f, 1.f,
   0.5f, 0.5f, 0.f,    0.f, 1.f, 0.f, 1.f,
  -0.5f,-0.5f, 0.f,    0.f, 0.f, 1.f, 1.f,
   0.5f,-0.5f, 0.f,    1.f, 0.f, 0.f, 1.f,
};

unsigned int indecies[] = {
  0, 1, 2,
  1, 2, 3,
};


bool loadfile(std::string filepath, std::string& src)
{
  std::ifstream file(filepath, std::fstream::binary);
  std::string line;

  src = "";

  if(!file.is_open())
  {
    std::cerr << ("ERROR:\n\tfailed to load file from specified path\n");
    return false;
  }

  while(std::getline(file, line))
  {
    src += line;
  }

  return true;
}

bool mygame::setup()
{
  glCreateVertexArrays(1, &vao);

  glCreateBuffers(1, &vbo);
  glNamedBufferData(vbo, sizeof(vertex) * 4, &points, GL_STATIC_DRAW);

  glCreateBuffers(1, &ebo);
  glNamedBufferData(ebo, sizeof(unsigned int) * 6, &indecies, GL_STATIC_DRAW);

  glVertexArrayElementBuffer(vao, ebo);
  glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(vertex));

  glEnableVertexArrayAttrib(vao, 0);
  glEnableVertexArrayAttrib(vao, 1);

  glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, offsetof(vertex, r));

  glVertexArrayAttribBinding(vao, 0, 0);
  glVertexArrayAttribBinding(vao, 1, 0);

  std::string vs_src_string, fs_src_string;

  loadfile("shaders/shader.vert", vs_src_string);
  loadfile("shaders/shader.frag", fs_src_string);

  const char* vshader_src = vs_src_string.data();
  const char* fshader_src = fs_src_string.data();

  vshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vshader, 1, &vshader_src, NULL);
  glCompileShader(vshader);

  fshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fshader, 1, &fshader_src, NULL);
  glCompileShader(fshader);

  shader_prg = glCreateProgram();
  glAttachShader(shader_prg, vshader);
  glAttachShader(shader_prg, fshader);
  glLinkProgram(shader_prg);

  glDeleteShader(vshader);
  glDeleteShader(fshader);

  return true;
}

void mygame::render() {
  glClearColor(0.2, 0.2, 0.2, 1.0);
  glUseProgram(shader_prg);
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

int main(int argc, const char* argv[])
{
  mygame g;
  g.init(800, 800, argc > 1, true, true);
  g.run();
}
