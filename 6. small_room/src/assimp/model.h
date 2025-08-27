#pragma once

#ifdef _WIN32
	#include <assimp/Importer.hpp>
	#include <assimp/scene.h>
	#include <assimp/postprocess.h>
#elif defined(__linux__)
	#include "../../lib/assimp/Importer.hpp"
	#include "../../lib/assimp/scene.h"
	#include "../../lib/assimp/postprocess.h"
#endif


#include "../shaders/shaders.hpp"
#include "mesh.h"
#include <vector>
#include <unordered_map>

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
