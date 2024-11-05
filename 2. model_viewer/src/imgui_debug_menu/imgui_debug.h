#pragma once
#include "../OpenGL/opengl_config.hpp"
#include <GLFW/glfw3.h>

namespace IMGUI_DEBUG{
  void imguiInit(GLFWwindow* window);
  void imguiStartFrame();
  void imguiDebugMenu(); // <-- Put what needs to be shown here
  void imguiEndFrame();
  void imguiShutdown();
  void HelpMarker(const char* desc);

};
