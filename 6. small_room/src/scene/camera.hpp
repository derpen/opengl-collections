#pragma once
#include <glm/glm.hpp>

enum CameraMode {
  ORTOGRAPHIC,
  PERSPECTIVE
};

enum MoveDirection {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

namespace Camera {

extern CameraMode Mode;
extern glm::vec3 Position;
extern glm::vec3 Front;
extern glm::vec3 Right;
extern glm::vec3 Up;

extern float Yaw;
extern float Pitch;
extern float Speed;
extern float Sensitivity;
extern float FOV;

extern bool FirstMouse;
extern float LastX;
extern float LastY;

void InitCamera();
glm::mat4 GetViewMatrix();
glm::mat4 GetProjectionMatrix();

void ProcessKeyboard(MoveDirection direction, float deltaTime);
void ProcessMouseMovement(double xoffset, double yoffset);
void UpdateCameraVector();

}
