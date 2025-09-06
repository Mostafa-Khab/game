#include <glm/ext.hpp>
#include "camera.hpp"

void camera::update(GLFWwindow* window, float dt) {
    const float speed = this->speed * dt; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += speed * glm::normalize(front);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= speed * glm::normalize(front);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= glm::normalize(glm::cross(front, up)) * speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += glm::normalize(glm::cross(front, up)) * speed;

    view = glm::lookAt(pos, pos + front, up);
}
