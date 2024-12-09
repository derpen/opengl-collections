#pragma once

#include "opengl_config.hpp"

namespace OpenGLCallbacks {
  // Callbacks
  void mouse_callback(GLFWwindow* window, double xpos, double ypos);
  void scroll_callback(GLFWwindow* window, double xpos, double ypos);
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
}
