#include "opengl_main.hpp"
#include "../imgui_debug_menu/imgui_debug.h"
#include "../Scene/scene.hpp"
#include "opengl_config.hpp"

namespace OpenGLLoop {

float g_DeltaTime = 0.0;
float g_LastFrame = 0.0;
int g_lastIndex = 0;

void mainLoop(){
  while(!glfwWindowShouldClose(OpenGLConfig::g_Window)){
    glfwPollEvents();

    IMGUI_DEBUG::imguiStartFrame();

    float currentFrame = glfwGetTime();
    g_DeltaTime = currentFrame - g_LastFrame;
    g_LastFrame = currentFrame;

    Scene::DrawScene();

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
  if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }

  if(OpenGLConfig::Input.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)){
    OpenGLConfig::Input.ToggleCursor(window);
  } else if (OpenGLConfig::Input.GetMouseButtonUp(GLFW_MOUSE_BUTTON_RIGHT)){
    OpenGLConfig::Input.ToggleCursor(window);
  }

  // Read pixel from picking framebuffer
  if(OpenGLConfig::Input.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT)){
    OpenGLConfig::pickingFramebuffer.UseFrameBuffer();
    unsigned char pixel[3];
    glReadPixels(OpenGLConfig::lastX, OpenGLConfig::conf.m_height - OpenGLConfig::lastY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
    
    // Handle picking
    unsigned long int objectIndex = (int)pixel[0];
    std::cout << (int)pixel[0] << (int)pixel[1] << (int)pixel[2] << "\n";
    if(objectIndex < Scene::g_ModelList.size()){
      Scene::g_ModelList[objectIndex].isSelected = true;
      g_lastIndex = objectIndex;
    } else {
      Scene::g_ModelList[g_lastIndex].isSelected = false;
    }     

    OpenGLConfig::pickingFramebuffer.DeactivateFrameBuffer();
  }

  OpenGLConfig::Input.FlyingMovement(window, &OpenGLConfig::cameraClass, g_DeltaTime);
}
}
