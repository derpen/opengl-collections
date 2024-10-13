#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "src/textures/texture_loader.h"
#include "src/shaders/shader.h"
#include "src/camera/fps_camera_control.h"
#include "src/imgui_debug_menu/imgui_debug.h"
#include "src/input/user_input.h"
#include "src/utils/shapes/shape_vertices.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/backends/imgui_impl_glfw.h"
#include "vendor/imgui/backends/imgui_impl_opengl3.h"
 
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

int main(){
  std::cout << "The nightmare begins once more.. \n" ;
    
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

  glEnable(GL_DEPTH_TEST);  

  while(!glfwWindowShouldClose(window)){
    processInput(window);
    glfwPollEvents();

    // BG color
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
  /*if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){*/
  if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }
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
