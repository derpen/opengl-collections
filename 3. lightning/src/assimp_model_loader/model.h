#pragma once
#include "../../vendor/assimp/Importer.hpp"
#include "../../vendor/assimp/scene.h"
#include "../../vendor/assimp/postprocess.h"
#include "mesh.h"
#include "../shaders/shader.h"
#include <vector>
#include <unordered_map>

struct Material {
  glm::vec3 Diffuse;
  glm::vec3 Specular;
  glm::vec3 Highlight;
  float Shininess;
};

class Model{
public:
  std::vector<Mesh> m_Meshes;

  /*std::vector<Texture> m_TexturesLoaded;*/

  std::unordered_map<std::string, Texture> m_TexturesMap;
  std::string m_Directory;
  std::string m_modelName;

  Model();
  Model(const char* path);
  void Draw(Shader &shader);

private:
  void loadModel(std::string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
  Material loadMaterial(aiMaterial* mat);
  unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = true);
};
