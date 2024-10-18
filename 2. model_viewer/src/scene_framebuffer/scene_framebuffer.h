#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class SceneFramebuffer{
public:
  unsigned int m_ScreenTexture;
  SceneFramebuffer();
  SceneFramebuffer(float WIDTH, float HEIGHT);
  void UseFrameBuffer();
  void DeactivateFrameBuffer();

private:
  unsigned int m_Fbo, m_DepthTexture;
  void createFramebufferAttachments(float WIDTH, float HEIGHT);
  void resizeFramebuffer(float WIDTH, float HEIGHT);
  bool m_hasTextureCreatedYet = false;
};
