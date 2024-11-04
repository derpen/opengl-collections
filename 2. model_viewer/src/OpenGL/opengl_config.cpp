#include "opengl_config.hpp"
#include "opengl_callbacks.hpp"
#include <iostream>

namespace OpenGLConfig{
  Config conf;
  GLFWwindow* g_Window;
  
  // Handle Mouse
  float lastX = conf.m_width / 2.0;
  float lastY = conf.m_height / 2.0;

  // Some other Init
  UserInput Input = UserInput();
  Camera cameraClass = Camera(conf.m_CameraDefaultPos);
  SceneFramebuffer mainFramebuffer = SceneFramebuffer();
  SceneFramebuffer pickingFramebuffer = SceneFramebuffer();

  int Init(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, conf.m_OpenGLVerMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, conf.m_OpenGLVerMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    g_Window = glfwCreateWindow(conf.m_width, conf.m_height, "dEngine", NULL, NULL);
    if(g_Window == NULL){
      std::cout << "OPENGL_CONFIG::ERROR::Failed to create GLFW window\n";
      glfwTerminate();
      return -1;
    }

    glfwMakeContextCurrent(g_Window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
      std::cout << "OPENGL_CONFIG::ERROR::Failed to initialize GLAD\n";
      return -1;
    }

    return 1;
  }

  void SetCallbacks(){
    glfwSetFramebufferSizeCallback(g_Window, OpenGLCallbacks::framebuffer_size_callback);
    glfwSetCursorPosCallback(g_Window, OpenGLCallbacks::mouse_callback);
    glfwSetScrollCallback(g_Window, OpenGLCallbacks::scroll_callback);
  }
}
