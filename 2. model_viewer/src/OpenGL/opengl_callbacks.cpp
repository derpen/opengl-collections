#include "opengl_callbacks.hpp"

namespace OpenGLCallbacks{
  void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if(OpenGLConfig::Input.firstMouse){
      OpenGLConfig::lastX = xpos;
      OpenGLConfig::lastY = ypos;
      OpenGLConfig::Input.firstMouse = false;
    }

    float xoffset = xpos - OpenGLConfig::lastX;
    float yoffset = OpenGLConfig::lastY - ypos; // Reverse since y go from up to bottom
    OpenGLConfig::lastX = xpos;
    OpenGLConfig::lastY = ypos;

    if(OpenGLConfig::Input.GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
      if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
      OpenGLConfig::cameraClass.processMouseEditor(xoffset, yoffset);
      } 
    } else {
      if(OpenGLConfig::Input.cursorHidden){
        OpenGLConfig::cameraClass.processMouseFPS(xoffset, yoffset);
      }
    }
  }

  void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    OpenGLConfig::cameraClass.ProcessMouseScroll(static_cast<float>(yoffset));
  }

  void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    OpenGLConfig::mainFramebuffer = SceneFramebuffer(width, height);
    OpenGLConfig::pickingFramebuffer = SceneFramebuffer(width, height);
    glViewport(0, 0, width, height);
  }
}
