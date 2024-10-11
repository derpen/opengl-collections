#pragma once

#include <glm/glm.hpp>

enum cameraDirection {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
};

const float cameraSpeed = 3.0f;

class Camera{
public:
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  float MovementSpeed;

  Camera(glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f), 
         glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f), 
         glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f));

  void processKeyboard(cameraDirection currentDir, float deltaTime);

private:

};
