#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <glm/glm.hpp>

#include "game.hpp"
#include "mesh.hpp"
#include "shader.hpp"

struct vertex{
  float x, y, z;
  float r, g, b, a;
  float u, v;
};

class mymesh: public mesh
{
  public:
    virtual void setup() override;
};

void mymesh::setup()
{
  //must be the first line in any mesh::setup
  glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(vertex));

  glEnableVertexArrayAttrib(vao, 0);
  glEnableVertexArrayAttrib(vao, 1);
  glEnableVertexArrayAttrib(vao, 2);

  glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, offsetof(vertex, r));
  glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(vertex, u));

  glVertexArrayAttribBinding(vao, 0, 0);
  glVertexArrayAttribBinding(vao, 1, 0);
  glVertexArrayAttribBinding(vao, 2, 0);
}

class mygame: public game 
{
    void render() override;
    bool setup()  override;

    mymesh msh;
    unsigned int shader_prg;

    friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

};


bool mygame::setup()
{
  std::vector<float> vdata({
    -0.5f, 0.5f, 0.f,    1.f, 0.f, 0.f, 1.f,   0.f, 0.f,   
     0.5f, 0.5f, 0.f,    0.f, 1.f, 0.f, 1.f,   0.5, 0.f,
    -0.5f,-0.5f, 0.f,    0.f, 0.f, 1.f, 1.f,   0.f, 1.f,
     0.5f,-0.5f, 0.f,    1.f, 0.f, 0.f, 1.f,   0.5, 1.f,
   });

  std::vector<unsigned int> edata({
    0, 1, 2,
    1, 2, 3,
  });

  Image img;

  msh.create(vdata, edata, GL_STATIC_DRAW);
  msh.setup();

  Image_load(&img, "./bird64.png");
  msh.add_texture(img, GL_REPEAT, GL_LINEAR);
  Image_load(&img, "./background.png");
  msh.add_texture(img, GL_REPEAT, GL_LINEAR);

  shader_prg = create_shader_program("./shaders/shader.vert", "./shaders/shader.frag");

  return true;
}

void mygame::render() {
  glClearColor(0.2, 0.2, 0.2, 1.0);
  msh.draw(GL_TRIANGLES, shader_prg);
}

int main(int argc, const char* argv[])
{
  mygame g;
  g.init(800, 800, argc > 1, true, true);
  g.run();
}
