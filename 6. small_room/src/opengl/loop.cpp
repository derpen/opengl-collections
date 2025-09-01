#include "loop.hpp"

#ifdef _WIN32
    #include <glfw/glfw3.h>
#elif defined(__linux__)
	#include <GLFW/glfw3.h>
#endif


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
  std::cout << "Sometimes, I felt like killing myself than use Visual Studio again... \n";
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

  // TODO:
  // Plz move this somewhere else
  // Why tf don't I have a way to move around objects easily lol
  /*Scene::AddCube("cube1");*/
#ifdef _WIN32
  //Scene::AddModelToScene("Osaka", PROJECT_DIR"../assets/models/osaka/osaka-assimp.obj", PROJECT_DIR"../assets/shaders/osaka.vert", PROJECT_DIR"../assets/shaders/osaka.frag");
  //Scene::AddModelToScene("Room", PROJECT_DIR"../assets/models/room/small_jp_apartment.glb", PROJECT_DIR"../assets/shaders/osaka.vert", PROJECT_DIR"../assets/shaders/osaka.frag");
  //Scene::AddModelToScene("TrapRoom", PROJECT_DIR"../assets/models/trap_room/room_one.glb", PROJECT_DIR"../assets/shaders/osaka.vert", PROJECT_DIR"../assets/shaders/osaka.frag");
  Scene::AddModelToScene("Chair", PROJECT_DIR"../assets/models/trap_room/just_chair.glb", PROJECT_DIR"../assets/shaders/osaka.vert", PROJECT_DIR"../assets/shaders/osaka.frag");
#else
  // TODO
  // Handle this for GNU/Linux
  Scene::AddModelToScene("assets/models/osaka/osaka-assimp.obj", "src/utils/shapes/shaders/osaka.vert", "src/utils/shapes/shaders/osaka.frag");
#endif

  Scene::AddPointLight(glm::vec3(0.0f, 0.0f, 0.0f));
  Scene::Objects["Chair"].transform.position = glm::vec3(5.0f, 0.0f, 0.0f);

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

    Scene::DrawScene(deltaTime);

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
   if(glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS ||
     glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
      )
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

