#include "user_input.h"
#include <GLFW/glfw3.h>

UserInput::UserInput(){};

void UserInput::EnableCursor(GLFWwindow* window){
  if(!isHideCursorButtonTriggered){
    firstMouse = true;
    if(cursorHidden){
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      cursorHidden = false;
    } else {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      cursorHidden = true;
    }
    isHideCursorButtonTriggered = true;
  }
}

bool UserInput::isMousePressed(unsigned int mouseButton){
  return true;
}
