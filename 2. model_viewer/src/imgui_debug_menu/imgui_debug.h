#pragma once
#include "../OpenGL/opengl_config.hpp"
#include <GLFW/glfw3.h>
#include <filesystem>
#include <vector>

namespace IMGUI_DEBUG{
  void imguiInit(GLFWwindow* window);
  void imguiStartFrame();
  void imguiDebugMenu(); // <-- Put what needs to be shown here
  void imguiEndFrame();
  void imguiShutdown();
  void HelpMarker(const char* desc);
  std::vector<std::filesystem::directory_entry> _ListDirectoryContent(const std::filesystem::path& path);

  static std::filesystem::path currentDirectory = "assets";
};
