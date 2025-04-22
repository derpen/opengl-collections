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

extern CameraMode cameraMode;
extern glm::vec3 position;
extern glm::vec3 front;
extern glm::vec3 right;
extern glm::vec3 up;

extern float yaw;
extern float pitch;
extern float speed;
extern float sensitivity;
extern float fov;

extern bool firstMouse;
extern bool lastX;
extern bool lastY;

void InitCamera();
glm::mat4 GetViewMatrix();
void ProcessKeyboard(MoveDirection direction, float deltaTime);
void ProcessMouseMovement(float xPosIn, float yPosIn);
void UpdateCameraVector();

}
