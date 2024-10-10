#include <glm/trigonometric.hpp>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "libs/textures/texture_loader.h"
#include "libs/shaders/shader.h"
#include "utils/shapes/shape_vertices.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(){
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
  unsigned int texture = loadTexture("assets/textures/osaka.jpg");

  /*// Wireframe*/
  /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

  glEnable(GL_DEPTH_TEST);  

  while(!glfwWindowShouldClose(window)){
    processInput(window);

    // BG color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glm::mat4 model = glm::mat4(1.0);
    float timeValue = glfwGetTime();
    model = glm::rotate(model, glm::radians(timeValue * 50.0f), glm::vec3(0.3f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    /*glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);*/
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);

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
}
