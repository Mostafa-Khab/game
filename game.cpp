#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <iostream>

#include "game.hpp"
#include "GLFW/glfw3.h"

#define error(X) std::cerr << "ERROR: " << (X) << "\n";

void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param);

bool game::init(int w, int h, bool fullscreen, bool debug, bool vsync_enable)
{
  if(!glfwInit())
  {
    error("failed to init glfw");
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  width  = w;
  height = h;
  vsync  = vsync_enable;

  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  if(fullscreen) {
    width  = mode->width;
    height  = mode->height;
    window = glfwCreateWindow(w, h, "gfx-game", glfwGetPrimaryMonitor(), NULL);
  } else {
    window = glfwCreateWindow(w, h, "gfx-game", NULL, NULL);
  }
  
  if(!window)
  {
    error("failed to create glfw window");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window);

  int glad_version = gladLoadGL(glfwGetProcAddress);
  if(glad_version == 0)
  {
     fprintf(stderr, "ERROR: failed to load opengl context (glad)\n");
     return -1;
  }

  if(debug)
  {
    //enable debug message using the debug msg callback
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(message_callback, nullptr);
  }

  return true;
}

bool game::onSetup()
{
  //no setup for now
  glfwSetWindowUserPointer(window, this);
  glfwSwapInterval(vsync);
  return setup();
}

void game::onUpdate(){
  glfwPollEvents();
  update();
}

void game::onRender(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  render();

  glfwSwapBuffers(window);
}

void game::onShutDown()
{
  shutdown();
  glfwTerminate();
}

void game::run(){
  if(!onSetup())
    error("game setup failed, unexpected behavior may occur");

  while(!glfwWindowShouldClose(window))
  {
    onUpdate();
    onRender();
  }
}

void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
	auto const src_str = [source]() {
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
		}
	}();

	auto const type_str = [type]() {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
		}
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
		}
	}();
	std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}
