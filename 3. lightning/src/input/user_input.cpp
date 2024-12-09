#include "user_input.h"
#include <GLFW/glfw3.h>

UserInput::UserInput(){};

bool UserInput::GetMouseButton(unsigned int mouseButton){
  return mousePressed[mouseButton] && !mousePressedLastState[mouseButton];
}

bool UserInput::GetMouseButtonDown(unsigned int mouseButton){
  return mousePressed[mouseButton];
}

// Check if the button was just released
bool UserInput::GetMouseButtonUp(unsigned int mouseButton) {
  return !mousePressed[mouseButton] && mousePressedLastState[mouseButton];
}

void UserInput::MouseState(GLFWwindow* window){
  mousePressedLastState[0] = mousePressed[0];
  mousePressedLastState[1] = mousePressed[1];

  mousePressed[0] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
  mousePressed[1] = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

void UserInput::GetKeyPress(unsigned int keyButton){
  // TODO: ALL KEYBOARD INPUT

}

void UserInput::GetKeyDown(unsigned int keyButton){

}

void UserInput::GetKeyUp(unsigned int keyButton){

}

void UserInput::ToggleCursor(GLFWwindow* window){
  firstMouse = true;
  if(cursorHidden){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    cursorHidden = false;
    enableFlyingMovement = false;
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    cursorHidden = true;
    enableFlyingMovement = true;
  }
}

void UserInput::FlyingMovement(GLFWwindow* window, Camera* cameraClass, float deltaTime){
  if(enableFlyingMovement){
    // Handle these movement so it only applies on mouse right click hold
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
      cameraClass->processKeyboard(FORWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
      cameraClass->processKeyboard(BACKWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
      cameraClass->processKeyboard(LEFT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
      cameraClass->processKeyboard(RIGHT, deltaTime);
    }

    //SHIFT SPRINT FOR FPS CONTROL
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
      cameraClass->isSprinting = true;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
      cameraClass->isSprinting = false;
    }
  }
};
