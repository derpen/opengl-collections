#include "fps_camera_control.h"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraUp) : MovementSpeed(CAMERASPEED), MouseSensitivity(SENSITIVITY), MouseYaw(YAW),  MousePitch(PITCH) {
  Position = cameraPos;
  WorldUp = cameraUp;
  updateCameraVectors();
}

void Camera::processKeyboard(cameraDirection currentDir, float deltaTime) {
  float currentSpeed = MovementSpeed;
  if(isSprinting){
    currentSpeed = MovementSpeed * SprintSpeed;
  }

  float velocity = currentSpeed * deltaTime;

  if(currentDir == FORWARD){
    Position += Front * velocity;
  }
  if(currentDir == BACKWARD){
    Position -= Front * velocity;
  }
  if(currentDir == LEFT){
    Position -= glm::normalize(glm::cross(Front, Up)) * velocity;
  }
  if(currentDir == RIGHT){
    Position += glm::normalize(glm::cross(Front, Up)) * velocity;
  }

  if(!flyingCamera){
    Position.y = 0.0f;
  }
}

glm::mat4 Camera::GetViewMatrix(){
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processMouse(float xoffset, float yoffset, GLboolean constrainPitch){
  xoffset *= MouseSensitivity;
  yoffset *= MouseSensitivity;

  MouseYaw += xoffset;
  MousePitch += yoffset;

  if(constrainPitch){
    if(MousePitch > 89.0f){
      MousePitch = 89.0f;
    }
    if(MousePitch < -89.0f){
      MousePitch = -89.0f;
    }
  }

  updateCameraVectors();
}

void Camera::updateCameraVectors(){
  glm::vec3 front;
	front.x = cos(glm::radians(MouseYaw)) * cos(glm::radians(MousePitch));
	front.y = sin(glm::radians(MousePitch));
	front.z = sin(glm::radians(MouseYaw)) * cos(glm::radians(MousePitch));
  Front = glm::normalize(front);
  Right = glm::normalize(glm::cross(Front, WorldUp));
  Up = glm::normalize(glm::cross(Right, Front));
}
