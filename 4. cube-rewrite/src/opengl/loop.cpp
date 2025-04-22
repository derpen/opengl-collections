#include "loop.hpp"
#include "iostream"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../shaders/shaders.hpp"
#include "../utils/shapes/shapes.hpp"
#include "../utils/textures/textures.hpp"
#include "../scene/camera.hpp"

namespace gl_loop {

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int init_gl(int width, int height, const char* title){
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

  Shader plane_shader("src/utils/shapes/shaders/planes.vert", "src/utils/shapes/shaders/planes.frag"); // This path sucks
  unsigned int plane = shapes::init_plane();
  unsigned int texture1 = texture::read_texture("assets/images/yotsuba.jpg");

  plane_shader.use();
  plane_shader.setInt("texture1", 0);

  while(!glfwWindowShouldClose(window)){
    process_input(window);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(Camera::fov), (float)width / (float)height, 0.1f, 100.0f);
    plane_shader.setMat4("projection", projection);

    // camera/view transformation
    glm::mat4 view = Camera::GetViewMatrix();
    plane_shader.setMat4("view", view);
    
    // Model matrix
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    plane_shader.setMat4("model", model);

    // render triangle
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glBindVertexArray(plane);
    /*glDrawArrays(GL_TRIANGLES, 0, 6);*/
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  shapes::clean_up();

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
  glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos){
  Camera::ProcessMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos));
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

