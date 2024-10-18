#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "src/shaders/shader.h"
#include "src/camera/fps_camera_control.h"
#include "src/imgui_debug_menu/imgui_debug.h"
#include "src/input/user_input.h"
#include "src/utils/logs/performance_log.h"
#include "src/utils/shapes/shape_vertices.h"
#include "src/assimp_model_loader/model.h"
#include "src/scene_framebuffer/scene_framebuffer.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/backends/imgui_impl_glfw.h"
#include "vendor/imgui/backends/imgui_impl_opengl3.h"
#include "vendor/stb/stb_image.h"
 
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Cam controls
Camera cameraClass = Camera(
  glm::vec3(6.27f, 2.89f, 6.86f)
);
float lastX = WIDTH / 2.0;
float lastY = HEIGHT / 2.0;

// Cube modifiers
float cubeSize = 1.5f;
float spacing = 0.6f;
float cubeRotateSpeed = 50.0f;
int gridSize = 10;

float deltaTime = 0.0;
float lastFrame = 0.0;

//Input
UserInput Input = UserInput();

//Imgui initialize
void imguiStartFrame();
void imguiDebugMenu();
IMGUI_DEBUG debugMenu = IMGUI_DEBUG();

// Framebuffer?
SceneFramebuffer pickingFramebuffer = SceneFramebuffer();

int main(){
  std::cout << "The nightmare begins once more.. \n" ;
    
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "dEngine", NULL, NULL);
  if(window == NULL){
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }

  //le callbacks
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  debugMenu.imguiInit(window);

  /*// Sometimes might wanna flip image for texture to work */
  /*stbi_set_flip_vertically_on_load(true);*/

  // OSAKA FROM AZUMANGA DAIOH
  std::string ayumu = "assets/models/osaka/osaka-assimp.obj";
  Model ayumuModel = Model(ayumu.c_str());
  Shader ayumuShader = Shader();
  ayumuShader.createShaderProgram("shaders/osaka.vert", "shaders/osaka.frag");

  //Framebuffer, and screen quad
  pickingFramebuffer = SceneFramebuffer(WIDTH, HEIGHT);
  shapes::InitScreenTexture();    
  Shader screenTexture = Shader();
  screenTexture.createShaderProgram("shaders/screentext.vert", "shaders/screentext.frag");
  screenTexture.setInt("screenTexture", 0);

  glEnable(GL_DEPTH_TEST);  

  while(!glfwWindowShouldClose(window)){
    processInput(window);
    glfwPollEvents();

    imguiStartFrame();

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    //Draw to new framebuffer
    pickingFramebuffer.UseFrameBuffer();

    // BG color
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //-----------------------Draw backpack here-----------------
    ayumuShader.use();
    // View/Projection Transform
    glm::mat4 view = cameraClass.GetViewMatrix();
    ayumuShader.setMat4("view", view);

    // Render
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    ayumuShader.setMat4("model", model);

    /*glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);*/
    glm::mat4 projection = glm::perspective(glm::radians(cameraClass.cameraFOV), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    ayumuShader.setMat4("projection", projection);

    ayumuModel.Draw(ayumuShader);
    //------------------------Draw done --------------------------

    //Unuse framebuffer
    pickingFramebuffer.DeactivateFrameBuffer();

    // BG color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Show texture on quad on screen
    screenTexture.use();
    shapes::UseScreenTexture();
    glBindTexture(GL_TEXTURE_2D, pickingFramebuffer.m_ScreenTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    shapes::DisableScreenTexture();

    debugMenu.imguiEndFrame();

    //Update Mouse
    Input.MouseState(window);
    glfwSwapBuffers(window);
  }

  //TODO code to do clean up here (remove vbo, vao, etc)

  debugMenu.imguiShutdown();

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  pickingFramebuffer = SceneFramebuffer(width, height);
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }

  if(Input.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)){
    Input.ToggleCursor(window);
  } else if (Input.GetMouseButtonUp(GLFW_MOUSE_BUTTON_RIGHT)){
    Input.ToggleCursor(window);
  }

  Input.FlyingMovement(window, &cameraClass, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if(Input.firstMouse){
    lastX = xpos;
    lastY = ypos;
    Input.firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // Reverse since y go from up to bottom
  lastX = xpos;
  lastY = ypos;

  if(Input.GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
      cameraClass.processMouseEditor(xoffset, yoffset);
    }
  } else {
    if(Input.cursorHidden){
      cameraClass.processMouseFPS(xoffset, yoffset);
    }
  }

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
  cameraClass.ProcessMouseScroll(static_cast<float>(yoffset));
}

//Everything below is an example on how to make a menu
void imguiStartFrame(){
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  imguiDebugMenu();
}

// This one is the real shit that creates the menu
void imguiDebugMenu(){
  ImGui::Begin("Debug Area", NULL, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::SliderFloat("Mouse Sensitivity", &cameraClass.MouseSensitivity, 0.0f, 2.0f);

  ImGui::SliderFloat("Movement Speed", &cameraClass.MovementSpeed, 0.0f, 100.0f);

  glm::vec3 camPos = cameraClass.Position;
  ImGui::Text("Camera Position  x: %.3f y: %.3f, z: %.3f", camPos.x, camPos.y, camPos.z);

  glm::vec3 camFront = cameraClass.Front;
  ImGui::Text("Camera Front  x: %.3f y: %.3f, z: %.3f", camFront.x, camFront.y, camFront.z);

  glm::vec3 camUp = cameraClass.Up;
  ImGui::Text("Camera Up  x: %.3f y: %.3f, z: %.3f", camUp.x, camUp.y, camUp.z);

  pl::FrameMetric fm = pl::GetTimePerFrame(glfwGetTime());
  ImGui::Text("%.2f ms/frame (%d fps)", fm.sec_per_frame, fm.frames_per_sec);

  ImGui::End();
}
