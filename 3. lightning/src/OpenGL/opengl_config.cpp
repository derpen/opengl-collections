#include "opengl_config.hpp"
#include "opengl_callbacks.hpp"
#include <iostream>
#include "../imgui_debug_menu/imgui_debug.h"
#include "../im3d/im3d_handler.hpp"
#include "../utils/shapes/shape_vertices.h"
#include "../Scene/scene.hpp"

namespace OpenGLConfig{
  Config conf;
  GLFWwindow* g_Window;
  
  // Handle Mouse
  float lastX = conf.m_width / 2.0;
  float lastY = conf.m_height / 2.0;

  // Some other Init
  UserInput Input = UserInput();
  Camera cameraClass = Camera(conf.m_CameraDefaultPos);
  Shader screenTexture = Shader();
  Shader model_select_shader = Shader();
  Shader model_stencil_shader = Shader();
  Shader cube_shader = Shader();
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
    
    SetCallbacks();

    glEnable(GL_DEPTH_TEST);  
    glEnable(GL_STENCIL_TEST);  

    IMGUI_DEBUG::imguiInit(OpenGLConfig::g_Window);
    Im3dHandler::Im3d_Init();

    SetFrameBuffers();
    SetGlobalShaders();

    shapes::InitCube();    
    Scene::InitializeScene();

    return 1;
  }

  void SetCallbacks(){
    glfwSetFramebufferSizeCallback(g_Window, OpenGLCallbacks::framebuffer_size_callback);
    glfwSetCursorPosCallback(g_Window, OpenGLCallbacks::mouse_callback);
    glfwSetScrollCallback(g_Window, OpenGLCallbacks::scroll_callback);
  }

  void SetFrameBuffers(){
    //Framebuffer, and screen quad
    mainFramebuffer = SceneFramebuffer(OpenGLConfig::conf.m_width, OpenGLConfig::conf.m_height);

    shapes::InitScreenTexture();    
    screenTexture.createShaderProgram("shaders/screentext.vert", "shaders/screentext.frag");
    screenTexture.setInt("screenTexture", 0);

    //Second framebuffer for picking things
    pickingFramebuffer = SceneFramebuffer(OpenGLConfig::conf.m_width, OpenGLConfig::conf.m_height);
  }

  void SetGlobalShaders(){
    model_select_shader.createShaderProgram("shaders/model_select.vert", "shaders/model_select.frag");
    model_stencil_shader.createShaderProgram("shaders/model_stencil.vert", "shaders/model_stencil.frag");
    cube_shader.createShaderProgram("shaders/cube.vert", "shaders/cube.frag");
  }
}
