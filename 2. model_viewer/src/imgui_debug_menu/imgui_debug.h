#pragma once
#include <GLFW/glfw3.h>

class IMGUI_DEBUG{
public:

  IMGUI_DEBUG();
  void imguiInit(GLFWwindow* window);
  void imguiEndFrame();
  void imguiShutdown();
  void HelpMarker(const char* desc);

};
