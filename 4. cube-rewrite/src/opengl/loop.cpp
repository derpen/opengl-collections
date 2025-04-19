#include "loop.hpp"
#include "iostream"
#include <GLFW/glfw3.h>
#include "../shaders/shaders.hpp"
#include "../utils/shapes/shapes.hpp"

namespace gl_loop {

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

  Shader triangle_shader("src/utils/shapes/shaders/triangle.vert", "src/utils/shapes/shaders/triangle.frag"); // This path sucks
  unsigned int triangle = shapes::init_triangle();

  while(!glfwWindowShouldClose(window)){
    process_input(window);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //render triangle
    triangle_shader.use();
    glBindVertexArray(triangle);
    glDrawArrays(GL_TRIANGLES, 0, 3);

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

void process_input(GLFWwindow *window){
  if(glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

}

