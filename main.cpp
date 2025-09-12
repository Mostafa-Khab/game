#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "game.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "manager.hpp"
#include "texture.hpp"

extern "C" {
#include <image.h>
}

struct vertex{
  float x, y, z;
  float r, g, b, a;
  float u, v;
  float nx, ny, nz;
};

struct light_vertex{
  float x, y, z;
  float r, g, b, a;
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
  glEnableVertexArrayAttrib(vao, 3);

  glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, offsetof(vertex, r));
  glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(vertex, u));
  glVertexArrayAttribFormat(vao, 3, 3, GL_FLOAT, GL_FALSE, offsetof(vertex, nx));

  glVertexArrayAttribBinding(vao, 0, 0);
  glVertexArrayAttribBinding(vao, 1, 0);
  glVertexArrayAttribBinding(vao, 2, 0);
  glVertexArrayAttribBinding(vao, 3, 0);

}

class light_mesh: public mesh
{
  public:
    virtual void setup() override;
};

void light_mesh::setup()
{
  //must be the first line in any mesh::setup
  glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(light_vertex));

  glEnableVertexArrayAttrib(vao, 0);
  glEnableVertexArrayAttrib(vao, 1);

  glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, offsetof(light_vertex, r));

  glVertexArrayAttribBinding(vao, 0, 0);
  glVertexArrayAttribBinding(vao, 1, 0);

}


class mygame: public game 
{
    void render()   override;
    bool setup()    override;
    void shutdown() override;
    void update(float dt) override;

    manager    man;
    mymesh     msh;
    light_mesh lamp;
    camera     cam;

    double xoffset = 0, yoffset = 0;
    double xlast = 0, ylast = 0;

    float fov = 45.f;
    float lightColor[3] = {1, 1, 1};

    friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    friend void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

};

void scroll_callback(GLFWwindow*, double, double);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

bool mygame::setup()
{
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, cursor_pos_callback);

  std::vector<float> vdata({
     //position             //color              //uv         //normals
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,    
     0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
                                                                                 
    -0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 1.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
                                                                                 
    -0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
                                                                                 
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
                                                                                 
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
                                                                                 
    -0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
   });

  std::vector<float> light_vdata({
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
                        
    -0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
                       
    -0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
                      
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
                     
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
                    
    -0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
     0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,
    -0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,
   });

  std::vector<unsigned int> edata; //({ 0, 1, 2, 1, 2, 3, });

  msh.create(vdata, edata, GL_STATIC_DRAW);
  msh.setup();

  lamp.create(light_vdata, edata, GL_STATIC_DRAW);
  lamp.setup();

  msh.add_texture("./bird64.png", GL_REPEAT, GL_LINEAR, GL_LINEAR);
  msh.add_texture("./background.png", GL_REPEAT, GL_LINEAR, GL_LINEAR);
  //msh.add_texture("./background.png", GL_REPEAT, GL_LINEAR, GL_LINEAR);

  man.add_shader("cube", "./shaders/shader.vert", "./shaders/shader.frag");
  man.add_shader("light", "./shaders/light.vert", "./shaders/light.frag");

  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);

  //glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
  return true;
}

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};

void mygame::update(float dt)
{
  cam.projection = glm::perspective(glm::radians(fov), width / (float)height, 0.1f, 100.f);

  cam.update(window, dt);
  cam.front.x += xoffset * dt * 0.04;
  cam.front.y += yoffset * dt * 0.04;

  glUseProgram(man.get_shader("cube"));
  glUniform3f(glGetUniformLocation(man.get_shader("cube"), "lightPos"), 0, 1, 0);
  glUniform3fv(glGetUniformLocation(man.get_shader("cube"), "viewPos"), 1, (const float*)&cam.pos);
  glUniform3fv(glGetUniformLocation(man.get_shader("cube"), "lightColor"), 1, (const float*)&lightColor);
  glUniformMatrix4fv(
      glGetUniformLocation(man.get_shader("cube"), "projection"), 1, GL_FALSE, glm::value_ptr(cam.projection)
  );
  glUniformMatrix4fv(
      glGetUniformLocation(man.get_shader("cube"), "view"), 1, GL_FALSE, glm::value_ptr(cam.view)
  );

  glUseProgram(man.get_shader("light"));
  glUniform3fv(glGetUniformLocation(man.get_shader("light"), "lightColor"), 1, (const float*)&lightColor);
  glUniformMatrix4fv(
      glGetUniformLocation(man.get_shader("light"), "projection"), 1, GL_FALSE, glm::value_ptr(cam.projection)
  );
  glUniformMatrix4fv(
      glGetUniformLocation(man.get_shader("light"), "view"), 1, GL_FALSE, glm::value_ptr(cam.view)
  );

  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if(glfwGetKey(window, GLFW_KEY_DOWN))
  {
    if(glfwGetKey(window, GLFW_KEY_1))
      lightColor[0] -= dt * 5;

    if(glfwGetKey(window, GLFW_KEY_2))
      lightColor[1] -= dt * 5;

    if(glfwGetKey(window, GLFW_KEY_3))
      lightColor[2] -= dt * 5;
  }

  if(glfwGetKey(window, GLFW_KEY_UP))
  {
    if(glfwGetKey(window, GLFW_KEY_1))
      lightColor[0] += dt * 5;

    if(glfwGetKey(window, GLFW_KEY_2))
      lightColor[1] += dt * 5;

    if(glfwGetKey(window, GLFW_KEY_3))
      lightColor[2] += dt * 5;
  }
}

void mygame::render() {
  glClearColor(0.2, 0.2, 0.2, 1.0);
  
  glUseProgram(man.get_shader("cube"));
  for(int i = 0; i < 10; ++i)
  {
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, cubePositions[i]);
    model = glm::rotate(model, (float)glfwGetTime() * 4 / i + i * i * 10, glm::vec3(i, 10 - i, 1.f));
    glUniformMatrix4fv(glGetUniformLocation(man.get_shader("cube"), "model"), 1 ,GL_FALSE , glm::value_ptr(model));

    msh.draw(GL_TRIANGLES, man.get_shader("cube"));
  }

  glUseProgram(man.get_shader("light"));
  glm::mat4 model = glm::mat4(1.f);
  glUniformMatrix4fv(glGetUniformLocation(man.get_shader("light"), "model"), 1 ,GL_FALSE , glm::value_ptr(model));
  lamp.draw(GL_TRIANGLES, man.get_shader("light"));
}

void mygame::shutdown()
{
  msh.nuke();
  lamp.nuke();
  std::cout << "this is running on shtudown\n";
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  mygame* g = (mygame*)glfwGetWindowUserPointer(window);
  g->fov += yoffset;

  if(g->fov < 1)
    g->fov = 1;
  if(g->fov > 60)
    g->fov = 60;
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{

  mygame* g = (mygame*)glfwGetWindowUserPointer(window);

  if(!g->xlast)
    g->xlast = xpos;
  if(!g->ylast)
    g->ylast = ypos;

  g->xoffset = xpos - g->xlast;
  g->yoffset = -(ypos - g->ylast);

  g->xlast = xpos;
  g->ylast = ypos;
}

int main(int argc, const char* argv[])
{
  mygame g;
  g.init(800, 800, argc > 1, true, true);
  g.run();
}
