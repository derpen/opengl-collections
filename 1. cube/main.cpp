#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "libs/textures/texture_loader.h"
#include "libs/shaders/shader.h"
#include "libs/camera/fps_camera_control.h"
#include "libs/imgui_debug_menu/imgui_debug.h"
#include "libs/input/user_input.h"
#include "utils/shapes/shape_vertices.h"
#include "include/imgui/imgui.h"
#include "include/imgui/backends/imgui_impl_glfw.h"
#include "include/imgui/backends/imgui_impl_opengl3.h"
 
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

//Create debug menu
IMGUI_DEBUG debugMenu = IMGUI_DEBUG();
void imguiStartFrame();
void imguiSimpleCubeDebugMenu(float* mouseSens, float* movementSpeed, float* cubeRotateSpeed, float* cubeSize, float* cubeSpacing, bool* flyingCamera, int* gridSize);

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

  unsigned int shaderProgram = createShaderProgram("shaders/cube.vert", "shaders/cube.frag");

  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  /*glGenBuffers(1, &EBO);*/

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertexNOEBOSize, verticesNoEBO, GL_STATIC_DRAW);

  /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/
  /*glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);*/

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
  unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
  unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

  // Le Perspective/Projection
  glUseProgram(shaderProgram);
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 1000000.0f);
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

  unsigned int texture = loadTexture("assets/textures/osaka.jpg");

  /*// Wireframe*/
  /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

  glEnable(GL_DEPTH_TEST);  

  debugMenu.imguiInit(window);

  while(!glfwWindowShouldClose(window)){
    processInput(window);
    glfwPollEvents();

    // BG color
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    imguiStartFrame();

    glUseProgram(shaderProgram);

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Set view
    glm::mat4 view = glm::mat4(1.0);
    /*view = glm::translate(view, glm::vec3(0.0f, -0.0f, -10.0f));*/
    view = cameraClass.GetViewMatrix();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

    for(int x = -gridSize; x < gridSize; x++){
      for(int z = -gridSize; z < gridSize; z++){
        glm::mat4 model = glm::mat4(1.0);
        model = glm::scale(model, glm::vec3(cubeSize));
        model = glm::translate(model, glm::vec3(x * (cubeSize + spacing), -1.5f, z * (cubeSize + spacing)));

        // To rotate
        float timeValue = glfwGetTime();
        model = glm::rotate(model, glm::radians(timeValue * cubeRotateSpeed), glm::vec3(0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);

        /*glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);*/
        glDrawArrays(GL_TRIANGLES, 0, 36);
      }
    }

    debugMenu.imguiEndFrame();

    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);
  debugMenu.imguiShutdown();

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

void imguiStartFrame(){
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  /*ImGui::ShowDemoWindow();*/
  imguiSimpleCubeDebugMenu(
    &cameraClass.MouseSensitivity, 
    &cameraClass.MovementSpeed, 
    &cubeRotateSpeed, 
    &cubeSize, 
    &spacing,
    &cameraClass.flyingCamera,
    &gridSize
  );
}

// This one is the real shit that creates the menu
void imguiSimpleCubeDebugMenu(float* mouseSens, float* movementSpeed, float* cubeRotateSpeed, float* cubeSize, float* cubeSpacing, bool* flyingCamera, int* gridSize){
  ImGui::Begin("Debug Area", NULL, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::SliderFloat("Mouse Sensitivity", mouseSens, 0.0f, 2.0f);

  ImGui::SliderFloat("Movement Speed", movementSpeed, 0.0f, 100.0f);

  ImGui::SliderFloat("Cube rotate speed", cubeRotateSpeed, 0.0f, 100.0f);

  ImGui::SliderFloat("Cube Size", cubeSize, 0.0f, 100.0f);

  ImGui::SliderFloat("Cube spacing", cubeSpacing, 0.0f, 10.0f);

  ImGui::SliderInt("Grid Size", gridSize, 0, 50);

  ImGui::Checkbox("Flying Camera", flyingCamera);
  ImGui::SameLine();
  debugMenu.HelpMarker("If turned off, FPS camera style is used");

  ImGui::End();
}
