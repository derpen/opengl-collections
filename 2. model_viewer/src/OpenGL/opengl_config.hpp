#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../input/user_input.h"
#include "../camera/fps_camera_control.h"
#include "../scene_framebuffer/scene_framebuffer.h"

namespace OpenGLConfig{
  struct Config {
    // Using OpenGL 4.6
    int m_OpenGLVerMajor = 4;
    int m_OpenGLVerMinor = 6;

    //default width and height
    int m_width = 800;
    int m_height = 600;
    const char* m_windowTitle = "dEngine";

    // Cam Default Pos
    glm::vec3 m_CameraDefaultPos = glm::vec3(6.27f, 2.89f, 6.86f);

    // Vec2 cursorPos();
    int cursor_x;
    int cursor_y;

    float m_deltaTime;

    // Vec3 m_camPos;
    // Vec3 m_camDir;
    // float m_camFOVRad;
    // float m_camFOVDeg;
    // Mat4 m_camWorld;
    // Mat4 m_camView;
    // Mat4 m_camProj;
    // Mat4 m_camViewProj; // <-- TODO: tf is this ?
  };

  extern Config conf;
  extern GLFWwindow* g_Window;
  extern float lastX;
  extern float lastY;
  extern UserInput Input;
  extern Camera cameraClass;

  // Framebuffer?
  extern SceneFramebuffer mainFramebuffer;
  extern SceneFramebuffer pickingFramebuffer;

  int Init();
  void SetCallbacks();
}
