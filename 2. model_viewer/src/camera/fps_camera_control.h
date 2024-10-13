#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

enum cameraDirection {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float CAMERASPEED = 3.0f;
const float CAMERASPRINTSPEED = 2.0f;
const float SENSITIVITY = 0.1f;
const bool FLYINGCAMERA = true;

class Camera{
public:
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Right;
  glm::vec3 Up;
  glm::vec3 WorldUp;

  float MovementSpeed;
  float MouseSensitivity;

  float MouseYaw;
  float MousePitch;

  bool flyingCamera = FLYINGCAMERA;

  //Sprint
  float SprintSpeed = CAMERASPRINTSPEED;
  bool isSprinting = false;

  Camera(glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f), 
         glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 GetViewMatrix();

  void processKeyboard(cameraDirection currentDir, float deltaTime);
  void processMouse(float xoffset, float yoffset, GLboolean constrainPitch = true);
  void updateCameraVectors();

private:

};
