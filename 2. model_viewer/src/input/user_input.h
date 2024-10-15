#pragma once
#include <GLFW/glfw3.h>
#include "../camera/fps_camera_control.h"

class UserInput{
public:

  bool mousePressed[2] = {}; //All false by default
  bool mousePressedLastState[2] = {}; //All false by default
  bool cursorHidden = false;
  bool firstMouse = true;
  bool enableFlyingMovement = false;

  UserInput();
  bool GetMouseButton(unsigned int mouseButton);
  bool GetMouseButtonDown(unsigned int mouseButton);
  bool GetMouseButtonUp(unsigned int mouseButton);
  void MouseState(GLFWwindow* window);

  // Everything below this is project specific, every function below this will be different for every project
  void ToggleCursor(GLFWwindow* window);
  void FlyingMovement(GLFWwindow* window, Camera* cameraClass, float deltaTime);
};
