#include "shape_vertices.h"

// GENERATED BY OPENAI, no way im making this on my own yo

// This is a cube
float vertices[] = {
  // Positions          // Texture Coords
  // Front face
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
  // Back face
  -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
   0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
   0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
};

// Indices for drawing the cube with EBO
unsigned int indices[] = {
  0, 1, 2, 2, 3, 0,  // Front face
  4, 5, 6, 6, 7, 4,  // Back face
};

/*float verticesNoEBO[] = {*/
/*    // Positions          //TexCoor           //Normals*/
/*    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,*/
/*     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,*/
/*     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,*/
/*     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,*/
/*    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,*/
/*    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,*/
/**/
/*    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,*/
/*     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,*/
/*     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,*/
/*     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,*/
/*    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,*/
/*    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,*/
/**/
/*    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,*/
/*    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,*/
/*    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,*/
/*    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,*/
/*    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,*/
/*    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,*/
/**/
/*     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,*/
/*     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,*/
/*     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,*/
/*     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,*/
/*     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,*/
/*     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,*/
/**/
/*    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,*/
/*     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,*/
/*     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,*/
/*     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,*/
/*    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,*/
/*    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,*/
/**/
/*    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,*/
/*     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,*/
/*     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,*/
/*     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,*/
/*    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,*/
/*    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f*/
/*};*/

// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
float screenTextureQuad[] = { 
  // positions   // texCoords
  -1.0f,  1.0f,  0.0f, 1.0f,
  -1.0f, -1.0f,  0.0f, 0.0f,
  1.0f, -1.0f,  1.0f, 0.0f,

  -1.0f,  1.0f,  0.0f, 1.0f,
  1.0f, -1.0f,  1.0f, 0.0f,
  1.0f,  1.0f,  1.0f, 1.0f
};

float verticesNoEBO[] = {
    // Positions          // Normals          // Texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

// Explicit array sizes
size_t vertexCount = sizeof(vertices) / sizeof(vertices[0]);
size_t vertexSize = sizeof(vertices);
size_t indexSize = sizeof(indices);

size_t vertexNOEBOSize = sizeof(verticesNoEBO);
size_t screenTextureQuadSize = sizeof(screenTextureQuad);

namespace shapes{
  unsigned int m_STvao, m_STvbo;
  unsigned int m_CUBEvao, m_CUBEvbo;

  void InitScreenTexture(){
      glGenVertexArrays(1, &m_STvao);
      glGenBuffers(1, &m_STvbo);
      glBindVertexArray(m_STvao);
      glBindBuffer(GL_ARRAY_BUFFER, m_STvbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(screenTextureQuad), &screenTextureQuad, GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
  }

  void InitCube(){
      glGenVertexArrays(1, &m_CUBEvao);
      glGenBuffers(1, &m_CUBEvbo);
      glBindVertexArray(m_CUBEvao);
      glBindBuffer(GL_ARRAY_BUFFER, m_CUBEvbo);
      glBufferData(GL_ARRAY_BUFFER, vertexNOEBOSize, &verticesNoEBO, GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
  }

  void UseCube(){
      glBindVertexArray(m_CUBEvao);
  }

  void DisableCube(){
      glBindVertexArray(0); // Honestly not needed since this is duplciate with DisableScreenTexture()
  }

  void UseScreenTexture(){
      glBindVertexArray(m_STvao);
  }

  void DisableScreenTexture(){
      glBindVertexArray(0);
  }
}
