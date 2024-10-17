#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class SceneFramebuffer{
public:
  unsigned int m_ScreenTexture;
  SceneFramebuffer(float WIDTH, float HEIGHT);
  void UseFrameBuffer();
  void DeactivateFrameBuffer();

private:
  unsigned int m_Fbo, m_DepthTexture;

};
