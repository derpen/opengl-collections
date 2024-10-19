#pragma once
#include <glm/glm.hpp>
#include "../shaders/shader.h"
#include <iostream>
#include <vector>

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture{
  unsigned int id;
  std::string type;
  std::string path;
};

class Mesh{
public:
  std::vector<Vertex> Vertices;
  std::vector<unsigned int> Indices;
  std::vector<Texture> Textures;

  Mesh(
    std::vector<Vertex> vertices,
    std::vector<unsigned int> indices,
    std::vector<Texture> textures
  );

  void Draw(Shader &shader, bool mainFramebuffer);

private:
  // render data
  unsigned int m_VAO, m_VBO, m_EBO;

  void setupMesh();

private:
};
