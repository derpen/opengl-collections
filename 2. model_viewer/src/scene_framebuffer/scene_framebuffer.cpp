#include "scene_framebuffer.h"
#include <iostream>

SceneFramebuffer::SceneFramebuffer(){
  // Just create empty
};

SceneFramebuffer::SceneFramebuffer(float WIDTH, float HEIGHT){
  // If the framebuffer was not created yet, generate it
  if (!m_hasTextureCreatedYet) {
    glGenFramebuffers(1, &m_Fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
    createFramebufferAttachments(WIDTH, HEIGHT);
    m_hasTextureCreatedYet = true;
  } else {
    // If the framebuffer exists, just update its attachments
    resizeFramebuffer(WIDTH, HEIGHT);
  }

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SceneFramebuffer::UseFrameBuffer(){
  glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
}

void SceneFramebuffer::DeactivateFrameBuffer(){
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_DEPTH_TEST);
}

void SceneFramebuffer::createFramebufferAttachments(float WIDTH, float HEIGHT){
  glGenTextures(1, &m_ScreenTexture);
  glBindTexture(GL_TEXTURE_2D, m_ScreenTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ScreenTexture, 0);

  // Create depth and stencil renderbuffer
  glGenRenderbuffers(1, &m_DepthTexture);
  glBindRenderbuffer(GL_RENDERBUFFER, m_DepthTexture);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthTexture);
}

void SceneFramebuffer::resizeFramebuffer(float WIDTH, float HEIGHT){
  glDeleteTextures(1, &m_ScreenTexture);
  glDeleteRenderbuffers(1, &m_DepthTexture);

  glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
  createFramebufferAttachments(WIDTH, HEIGHT);
}
