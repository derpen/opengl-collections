#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//Temporary Shader code
const char* vertexShaderSource = R"(
  #version 330 core
  layout (location = 0) in vec3 aPos;

  void main(){
    gl_Position = vec4(aPos, 1.0);
  }
)";

const char* colorOneFragmentShaderSource = R"(
  #version 330 core
  out vec4 FragColor;

  void main(){
    FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange
  }
)";

const char* colorTwoFragmentShaderSource = R"(
  #version 330 core
  out vec4 FragColor;

  void main(){
    FragColor = vec4(0.3, 0.3, 1.0, 1.0); // Idk what color this is lol
  }
)";

unsigned int compileShader(unsigned int type, const char* source);
unsigned int createShaderProgram(const char* vShader, const char* fShader);
void bindVertexes(unsigned int VAO, unsigned int VBO, float *vertices, size_t size);

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
  
  // Creating F
  float firstTriangle[] = {
      -0.5f, 0.5f, 0.0f,  
      -0.3f, 0.5f, 0.0f,  
      -0.5f, -0.9f, 0.0f, 
  };

  float secondTriangle[] = {
      -0.3f, 0.5f, 0.0f, 
      -0.5f, -0.9f, 0.0f,
      -0.3f, -0.9f, 0.0f 
  };

  float thirdTriangle[] = {
      0.2f, 0.5f, 0.0f,
      -0.3f, 0.5f, 0.0f,
      -0.3f, 0.2f, 0.0f,
  };

  float fourthTriangle[] = {
      0.2f, -0.1f, 0.0f,
      -0.3f, -0.4f, 0.0f,
      -0.3f, -0.1f, 0.0f,
  };

  float fifthTriangle[] = {
      0.2f, 0.5f, 0.0f,
      0.2f, 0.2f, 0.0f,
      -0.3f, 0.2f, 0.0f,
  };

  float sixthTriangle[] = {
      0.2f, -0.1f, 0.0f,
      -0.3f, -0.4f, 0.0f,
      0.2f, -0.4f, 0.0f,
  };
  
  unsigned int shaderProgramColorOne = createShaderProgram(vertexShaderSource, colorOneFragmentShaderSource);
  unsigned int shaderProgramColorTwo = createShaderProgram(vertexShaderSource, colorTwoFragmentShaderSource);

  unsigned int VBOs[6], VAOs[6];
  glGenVertexArrays(6, VAOs);
  glGenBuffers(6, VBOs);

  bindVertexes(VAOs[0], VBOs[0], firstTriangle, sizeof(firstTriangle));
  bindVertexes(VAOs[1], VBOs[1], secondTriangle, sizeof(secondTriangle));
  bindVertexes(VAOs[2], VBOs[2], thirdTriangle, sizeof(thirdTriangle));
  bindVertexes(VAOs[3], VBOs[3], fourthTriangle, sizeof(fourthTriangle));
  bindVertexes(VAOs[4], VBOs[4], fifthTriangle, sizeof(fifthTriangle));
  bindVertexes(VAOs[5], VBOs[5], sixthTriangle, sizeof(sixthTriangle));

  /*// Wireframe*/
  /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

  while(!glfwWindowShouldClose(window)){
    processInput(window);

    // BG color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgramColorOne);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAOs[2]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAOs[3]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgramColorTwo);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAOs[4]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAOs[5]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Clean up
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteProgram(shaderProgramColorOne);
  glDeleteProgram(shaderProgramColorTwo);

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

void bindVertexes(unsigned int VAO, unsigned int VBO, float *vertices, size_t size){
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}

unsigned int compileShader(unsigned int type, const char* source){
  unsigned int id = glCreateShader(type);
  glShaderSource(id, 1, &source, nullptr);
  glCompileShader(id);

  // Check for errors
  int success;
  char infoLog[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(id, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::Shader compilation failed " << infoLog << "\n";
  }

  return id;
}

unsigned int createShaderProgram(const char* vShader, const char* fShader){
  unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vShader);
  unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fShader);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success){
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING FAILED " << infoLog << "\n";
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}
