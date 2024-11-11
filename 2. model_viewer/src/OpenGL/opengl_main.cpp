#include "opengl_main.hpp"
#include "../imgui_debug_menu/imgui_debug.h"
#include "../im3d/im3d_handler.hpp"
#include "../Scene/scene.hpp"
#include "opengl_config.hpp"
#include <GLFW/glfw3.h>

namespace OpenGLLoop {

float g_DeltaTime = 0.0;
float g_LastFrame = 0.0;

void mainLoop(){
  while(!glfwWindowShouldClose(OpenGLConfig::g_Window)){
    glfwPollEvents();

    //TODO: a bit messy tbh, might wanna group together stuff that are similiar

    IMGUI_DEBUG::imguiStartFrame();
    Im3dHandler::Im3d_NewFrame();

    float currentFrame = glfwGetTime();
    g_DeltaTime = currentFrame - g_LastFrame;
    g_LastFrame = currentFrame;

    Scene::PickModelFromScene();
    Scene::DrawScene();

    Im3dHandler::Im3d_EndFrame();
    IMGUI_DEBUG::imguiEndFrame();

    processInput(OpenGLConfig::g_Window);
    OpenGLConfig::Input.MouseState(OpenGLConfig::g_Window);
    glfwSwapBuffers(OpenGLConfig::g_Window);
  }

  shutdown();
}

void shutdown(){
  //TODO code to do clean up here (remove vbo, vao, etc)
  // All shutdown commands here, possibly taken from every other file in this forsaken source code folder
  IMGUI_DEBUG::imguiShutdown();
  glfwTerminate();
}

void processInput(GLFWwindow* window){
  if(
    glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
    glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS
  ){
    glfwSetWindowShouldClose(window, true);
  }

  if(OpenGLConfig::Input.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)){
    OpenGLConfig::Input.ToggleCursor(window);
  } else if (OpenGLConfig::Input.GetMouseButtonUp(GLFW_MOUSE_BUTTON_RIGHT)){
    OpenGLConfig::Input.ToggleCursor(window);
  }

  OpenGLConfig::Input.FlyingMovement(window, &OpenGLConfig::cameraClass, g_DeltaTime);
}
}
