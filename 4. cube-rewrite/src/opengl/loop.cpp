#include "loop.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <glm/trigonometric.hpp>
#include "config.hpp"
#include "../utils/shapes/shapes.hpp"
#include "../scene/camera.hpp"
#include "../scene/scene.hpp"

namespace gl_loop {

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int init_gl(float width, float height, const char* title){
  std::cout << "Oh..boy, I'm doing OpenGL again... Great... \n";
  std::cout << "Initializing gl...\n";
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  std::cout << "Creating window...\n";
  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
  if(window == NULL){
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }

  Config::SetWindowSize(width, height);

  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glEnable(GL_DEPTH_TEST);

  Scene::AddCube("cube1", "assets/images/yotsuba.jpg");
  Scene::AddPointLight(glm::vec3(5.0f, 0.0f, 0.0f));

  Camera::InitCamera();

  while(!glfwWindowShouldClose(window)){
    process_input(window);
    glfwPollEvents();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Time
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    Scene::DrawScene();

    glfwSwapBuffers(window);
  }

  Shapes::clean_up();

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
  glViewport(0, 0, width, height);

  // TODO: Should I keep it as an int?
  Config::SetWindowSize(static_cast<float>(width), static_cast<float>(height)); 
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos){
  Camera::ProcessMouseMovement(xpos, ypos);
}

void process_input(GLFWwindow *window){
  if(glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  // TODO: handle input in input.cpp
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    Camera::ProcessKeyboard(FORWARD, deltaTime);

  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    Camera::ProcessKeyboard(BACKWARD, deltaTime);

  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    Camera::ProcessKeyboard(LEFT, deltaTime);

  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    Camera::ProcessKeyboard(RIGHT, deltaTime);

}

}

