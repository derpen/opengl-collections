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
#include "src/assimp_model_loader/model.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/backends/imgui_impl_glfw.h"
#include "vendor/imgui/backends/imgui_impl_opengl3.h"
#include "vendor/stb/stb_image.h"
 
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Cam controls
Camera cameraClass = Camera(); // Default is at vec3(0.0, 0.0, 3.0)
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

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // le mouz
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  /*// Wireframe*/
  /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

  debugMenu.imguiInit(window);

  stbi_set_flip_vertically_on_load(true);

  // Load model
  /*std::filesystem::path backpack_path = "model/backpack/backpack.obj";*/
  std::string backpack_path = "assets/models/backpack/backpack.obj";
  Model backpackModel = Model(backpack_path.c_str());
  Shader backpackShader = Shader();
  backpackShader.createShaderProgram("shaders/backpack.vert", "shaders/backpack.frag");
  backpackShader.use();

  glEnable(GL_DEPTH_TEST);  

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
  backpackShader.setMat4("projection", projection);

  while(!glfwWindowShouldClose(window)){
    processInput(window);
    glfwPollEvents();

    // BG color
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    imguiStartFrame();

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    //-----------------------Draw backpack here-----------------
    backpackShader.use();

    // View/Projection Transform
    glm::mat4 view = cameraClass.GetViewMatrix();
    backpackShader.setMat4("view", view);

    // Render
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    backpackShader.setMat4("model", model);
    backpackModel.Draw(backpackShader);
    //------------------------Draw done --------------------------

    debugMenu.imguiEndFrame();
    glfwSwapBuffers(window);
  }

  debugMenu.imguiShutdown();

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }

  // Handle these movement so it only applies on mouse right click hold
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    cameraClass.processKeyboard(FORWARD, deltaTime);
  }
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    cameraClass.processKeyboard(BACKWARD, deltaTime);
  }
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    cameraClass.processKeyboard(LEFT, deltaTime);
  }
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    cameraClass.processKeyboard(RIGHT, deltaTime);
  }

  //Toggle Cursor
  if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
    if(!Input.isHideCursorButtonTriggered){
      Input.EnableCursor(window);
    }
  } else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE){
      Input.isHideCursorButtonTriggered = false;
  }

  //SHIFT SPRINT
  if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
    cameraClass.isSprinting = true;
  }
  if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
    cameraClass.isSprinting = false;
  }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
  if(Input.cursorHidden){
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

    cameraClass.processMouse(xoffset, yoffset);
  }
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
  ImGui::Text("x:%.3f y:%.3f, z:%.3f", camPos.x, camPos.y, camPos.z);

  pl::FrameMetric fm = pl::GetTimePerFrame(glfwGetTime());
  ImGui::Text("%.2f ms/frame (%d fps)", fm.sec_per_frame, fm.frames_per_sec);

  ImGui::End();
}
