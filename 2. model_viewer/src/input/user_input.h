#pragma once
#include <GLFW/glfw3.h>

class UserInput{
public:
  bool cursorHidden = true; // On by default
  bool firstMouse = true;
  bool isHideCursorButtonTriggered = false;

  UserInput();
  void EnableCursor(GLFWwindow* window);
};
