#include "fps_camera_control.h"
#include <glm/geometric.hpp>

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp) : MovementSpeed(cameraSpeed) {
  Position = cameraPos;
  Front = cameraFront;
  Up = cameraUp;
}

void Camera::processKeyboard(cameraDirection currentDir, float deltaTime) {
  if(currentDir == FORWARD){
    Position += MovementSpeed * Front * deltaTime;
  }
  if(currentDir == BACKWARD){
    Position -= MovementSpeed * Front * deltaTime;

  }
  if(currentDir == LEFT){
    Position -= glm::normalize(glm::cross(Front, Up)) * MovementSpeed * deltaTime;
  }
  if(currentDir == RIGHT){
    Position += glm::normalize(glm::cross(Front, Up)) * MovementSpeed * deltaTime;
  }
}
