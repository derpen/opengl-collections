#include "camera.hpp"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Camera {
CameraMode cameraMode = PERSPECTIVE;
glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
float yaw = -90.0f;
float pitch = 0.0f;
float speed = 2.5f;
float sensitivity = 0.0001f;
float fov = 45.0f;

bool firstMouse = true;
// TODO: make this flexible
bool lastX = 800.0f / 2.0;
bool lastY = 600.0f / 2.0;

void InitCamera(){

}

glm::mat4 GetViewMatrix(){
  return glm::lookAt(position, position + front, up);
}

void ProcessKeyboard(MoveDirection direction, float deltaTime){
  float velocity = speed * deltaTime;
  if(direction == FORWARD)
    position += front * velocity;

  if(direction == BACKWARD)
    position -= front * velocity;

  if(direction == RIGHT)
    position += right * velocity;

  if(direction == LEFT)
    position -= right * velocity;
}

void ProcessMouseMovement(float xPosIn, float yPosIn){
  if(firstMouse){
    lastX = xPosIn;
    lastY = yPosIn;
    firstMouse = false;
  }

  float xoffset = xPosIn - lastX;
  float yoffset = lastY - yPosIn;
  lastX = xPosIn;
  lastY = yPosIn;

  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  if(pitch > 89.0f)
    pitch = 89.0f;

  if(pitch < -89.0f)
    pitch = -89.0f;
  
  UpdateCameraVector();
}

void UpdateCameraVector(){
  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(direction);
  right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))); // world up
  up = glm::normalize(glm::cross(right, front));
}

}
