#include "camera.hpp"
#include <iostream>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../opengl/config.hpp"

namespace Camera {
CameraMode Mode = PERSPECTIVE;
glm::vec3 Position = glm::vec3(0.0f, 3.0f, 5.0f);
glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
float Yaw = -90.0f;
float Pitch = -30.0f;
float Speed = 2.5f;
float Sensitivity = 0.1f;
float FOV = 45.0f;

bool FirstMouse = true;
// TODO: make this flexible
float LastX = 800.0f / 2.0f;
float LastY = 600.0f / 2.0f;

void InitCamera(){
  LastX = Config::Height / 2.0f;
  LastY = Config::Width / 2.0f;
  UpdateCameraVector();
}

glm::mat4 GetViewMatrix(){
  return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 GetProjectionMatrix(){
    return glm::perspective(glm::radians(Camera::FOV), (float)Config::Height / (float)Config::Width, 0.001f, 100000.0f);
}

void ProcessKeyboard(MoveDirection direction, float deltaTime){
  float velocity = Speed * deltaTime;
  if(direction == FORWARD)
    Position += Front * velocity;

  if(direction == BACKWARD)
    Position -= Front * velocity;

  if(direction == RIGHT)
    Position += Right * velocity;

  if(direction == LEFT)
    Position -= Right * velocity;
}

void ProcessMouseMovement(double xPosIn, double yPosIn){
  float xpos = static_cast<float>(xPosIn);
  float ypos = static_cast<float>(yPosIn);

  if(FirstMouse){
    LastX = xpos;
    LastY = ypos;
    FirstMouse = false;
  }

  float xoffset = xpos - LastX;
  float yoffset = LastY - ypos;
  LastX = xpos;
  LastY = ypos;

  xoffset *= Sensitivity;
  yoffset *= Sensitivity;

  Yaw += xoffset;
  Pitch += yoffset;

  /*std::cout << "-----    \n";*/
  /*std::cout << xoffset << " " << yoffset << "\n";*/
  /*std::cout << Yaw << " " << Pitch << "\n";*/

  if(Pitch > 89.0f){
    Pitch = 89.0f;
  }

  if(Pitch < -89.0f){
    Pitch = -89.0f;
  }
  
  UpdateCameraVector();
}

void UpdateCameraVector(){
  glm::vec3 direction;
  direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  direction.y = sin(glm::radians(Pitch));
  direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  Front = glm::normalize(direction);
  Right = glm::normalize(glm::cross(Front, glm::vec3(0.0f, 1.0f, 0.0f))); // world up
  Up = glm::normalize(glm::cross(Right, Front));
}

}
