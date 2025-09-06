/*********************************
 * author     : mostafa khaled
 * date       : 
 * desc       : 
 ********************************/
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class camera
{
  public: 
    virtual void update(GLFWwindow* window, float dt);
  
  public:
    glm::vec3 pos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up    = glm::vec3(0.0f, 1.0f,  0.0f);

    glm::mat4 view        = glm::mat4(1.f);
    glm::mat4 projection  = glm::mat4(1.f);

    float     speed = 2.5;

};

#endif /* !CAMERA_HPP */
