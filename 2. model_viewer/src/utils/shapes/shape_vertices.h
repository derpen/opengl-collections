#pragma once
#include <stdio.h>
#include <glad/glad.h>

extern float vertices[];  // Vertex data
extern unsigned int indices[];  // Index data
extern size_t vertexCount;
extern size_t vertexSize;
extern size_t indexSize;

extern float verticesNoEBO[];
extern float screenTextureQuad[];
extern size_t vertexNOEBOSize;
extern size_t screenTextureQuadSize;

namespace shapes{
  extern unsigned int m_STvao, m_STvbo;

  void InitScreenTexture();
  void UseScreenTexture();
  void DisableScreenTexture();
}

