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

struct Material {
  glm::vec3 Diffuse;
  glm::vec3 Specular;
  glm::vec3 Highlight;
  float Shininess;
};

class Mesh{
public:
  std::vector<Vertex> Vertices;
  std::vector<unsigned int> Indices;
  std::vector<Texture> Textures;
  std::vector<Material> Materials;

  Mesh(
    std::vector<Vertex> vertices,
    std::vector<unsigned int> indices,
    std::vector<Texture> textures,
    std::vector<Material> materials
  );

  void Draw(Shader &shader);

private:
  // render data
  unsigned int m_VAO, m_VBO, m_EBO;

  void setupMesh();

private:
};
