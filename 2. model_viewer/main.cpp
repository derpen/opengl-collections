#include "src/OpenGL/opengl_main.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "src/OpenGL/opengl_config.hpp"
#include "vendor/stb/stb_image.h"

/*TODO: CLEAN CODE BEFORE MOVING TO NEXT PHASE */
// TODO: FRAMBUFFER RESIZE KIND OF BREAK ?

int main(){
  std::cout << "The nightmare begins once more.. \n" ;

  int success = OpenGLConfig::Init();
  if(success < 0){
    std::cout << "Init Failed \n";
    return -1;
  }

  OpenGLLoop::mainLoop();

  return 0;
}
