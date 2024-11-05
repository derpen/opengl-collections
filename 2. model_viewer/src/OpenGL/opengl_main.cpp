#include "opengl_main.hpp"
#include "opengl_config.hpp"
#include "../imgui_debug_menu/imgui_debug.h"
#include <iostream>

namespace OpenGLLoop {

float g_DeltaTime = 0.0;
float g_LastFrame = 0.0;

void mainLoop(){
  while(!glfwWindowShouldClose(OpenGLConfig::g_Window)){
    glfwPollEvents();

    IMGUI_DEBUG::imguiStartFrame();

    float currentFrame = glfwGetTime();
    g_DeltaTime = currentFrame - g_LastFrame;
    g_LastFrame = currentFrame;

    glm::mat4 view = OpenGLConfig::cameraClass.GetViewMatrix();
    glm::mat4 projection = OpenGLConfig::cameraClass.GetProjMatrix();

  }

  shutdown();
}

void shutdown(){
  std::cout << "Shutdown called\n";

}

}
