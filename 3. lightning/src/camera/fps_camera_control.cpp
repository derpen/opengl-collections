#include "fps_camera_control.h"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGL/opengl_config.hpp"
#include <iostream>

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraUp, glm::vec3 cameraFront) : MovementSpeed(CAMERASPEED), MouseSensitivity(FLYINGSENSITIVITY), MouseDraggingSensitivity(DRAGGINGSENSITIVITY), MouseYaw(YAW),  MousePitch(PITCH) {
  Position = cameraPos;
  WorldUp = cameraUp;
  Front = cameraFront;
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

  /*if(!flyingCamera){*/
  /*  Position.y = 0.0f;*/
  /*}*/
}

glm::mat4 Camera::GetViewMatrix(){
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::GetProjMatrix(){
    //TODO: change far plane properly
    return glm::perspective(glm::radians(cameraFOV), (float)OpenGLConfig::conf.m_width / (float)OpenGLConfig::conf.m_height, 0.1f, 100000.0f);
}

void Camera::ProcessMouseScroll(float yoffset){
	cameraFOV -= (float)yoffset;
	if (cameraFOV < 1.0f)
		cameraFOV = 1.0f;
	if (cameraFOV > 90.0f)
		cameraFOV = 90.0f;
}

void Camera::processMouseEditor(float xoffset, float yoffset){
  xoffset *= MouseDraggingSensitivity;
  yoffset *= MouseDraggingSensitivity;

  Position -= Right * xoffset;
  Position -= Up * yoffset;  
}

void Camera::processMouseFPS(float xoffset, float yoffset, bool constrainPitch){
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
