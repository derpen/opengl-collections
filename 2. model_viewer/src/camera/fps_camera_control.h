#pragma once

#include <glm/glm.hpp>

enum cameraDirection {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
};

const float YAW = -130.0f;
const float PITCH = -10.0f;
const float FOV = 45.0f;
const float CAMERASPEED = 3.0f;
const float CAMERASPRINTSPEED = 2.0f;
const float FLYINGSENSITIVITY = 0.1f;
const float DRAGGINGSENSITIVITY = 0.01f;
const bool FLYINGCAMERA = true;

class Camera{
public:
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Right;
  glm::vec3 Up;
  glm::vec3 WorldUp;

  float cameraFOV = FOV;
  float MovementSpeed;
  float MouseSensitivity;
  float MouseDraggingSensitivity;

  float MouseYaw;
  float MousePitch;

  bool flyingCamera = FLYINGCAMERA;

  //Sprint
  float SprintSpeed = CAMERASPRINTSPEED;
  bool isSprinting = false;

  Camera(glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f), 
         glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f),
         glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f)
         );

  glm::mat4 GetViewMatrix();
  glm::mat4 GetProjMatrix();

  void processKeyboard(cameraDirection currentDir, float deltaTime);
  void processMouseEditor(float xoffset, float yoffset);
  void processMouseFPS(float xoffset, float yoffset, bool constrainPitch = true);
  void ProcessMouseScroll(float yoffset);
  void updateCameraVectors();

private:

};
