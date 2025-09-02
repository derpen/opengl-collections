#include "model.h"


#ifdef _WIN32
	#include <assimp/Importer.hpp>
	#include <assimp/scene.h>
	#include <assimp/postprocess.h>
	#include <stb/stb_image.h>
#elif defined(__linux__)
	#include "../../lib/assimp/Importer.hpp"
	#include "../../lib/assimp/scene.h"
	#include "../../lib/assimp/postprocess.h"
	#include "../../lib/stb/stb_image.h"
#endif

#include <cstring>
#include <glad/glad.h>

Model::Model(){
  m_modelName = "default";
}

Model::Model(const char* path){
  m_modelName = path;
  loadModel(path);
}

void Model::Draw(Shader &shader){
  for(unsigned int i = 0; i < m_Meshes.size(); i++){
    m_Meshes[i].Draw(shader);
  }
}

void Model::loadModel(std::string path){
  Assimp::Importer import;
  const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
    std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << "\n";
    return;
  }

  // TODO: CHANGE THIS LATER SO MODEL AND TEXTURE ARE SEPARATED
  m_Directory = path.substr(0, path.find_last_of('/')); 

  processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene){
  for(unsigned int i = 0; i < node->mNumMeshes; i++){
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    m_Meshes.push_back(processMesh(mesh, scene));
  }

  for(unsigned int i = 0; i < node->mNumChildren; i++){
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene){
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  for(unsigned int i = 0; i < mesh->mNumVertices; i++){
    Vertex vertex;

    //Process vertex pos
    glm::vec3 vector;
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.Position = vector;

    //Process vertex normals
    if(mesh->HasNormals()){
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.Normal = vector;
    }

    //Process vertex texcoords, just process the first one (because assimp allows up to 8)
    if(mesh->mTextureCoords[0]){
      glm::vec2 texVec;
      texVec.x = mesh->mTextureCoords[0][i].x;
      texVec.y = mesh->mTextureCoords[0][i].y;
      vertex.TexCoords = texVec;
    } else {
      vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    }

    vertices.push_back(vertex);
  }

  //Process indices
  for(unsigned int i = 0; i < mesh->mNumFaces; i++){
    aiFace face = mesh->mFaces[i];
    for(unsigned int j = 0; j < face.mNumIndices; j++){
      indices.push_back(face.mIndices[j]);
    }
  }

  std::vector<Material> materials;
  //Process material
  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
  std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
  textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

  std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
  textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

  //This one is for material without textures
  Material theMat = loadMaterial(material);
  materials.push_back(theMat);

  return Mesh(vertices, indices, textures, materials);
}

Material Model::loadMaterial(aiMaterial* mat){
  Material material;
  aiColor3D color(0.f, 0.f, 0.f);
  float shininess;

  mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
  material.Diffuse = glm::vec3(color.r, color.b, color.g);

  mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
  material.Ambient = glm::vec3(color.r, color.b, color.g);

  mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
  material.Specular = glm::vec3(color.r, color.b, color.g);

  mat->Get(AI_MATKEY_SHININESS, shininess);
  material.Shininess = shininess;

  return material;
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName){
  std::vector<Texture> textures;
  for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){
    aiString str;
    mat->GetTexture(type, i, &str);
    bool skip = false;

    std::string texturePath = str.C_Str();
    if(m_TexturesMap.find(texturePath) != m_TexturesMap.end()){
      textures.push_back(m_TexturesMap[texturePath]);
      skip = true;
      break;
    }

    if(!skip){
      Texture texture;
      texture.id = TextureFromFile(str.C_Str(), m_Directory);
      texture.type = typeName;
      texture.path = str.C_Str();
      textures.push_back(texture);

      m_TexturesMap[texturePath] = texture;
    }
  }

  return textures;
}

unsigned int Model::TextureFromFile(const char *path, const std::string &directory, bool gamma){
  std::string filename = std::string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data)
  {
    GLenum format;
    if (nrComponents == 1)
        format = GL_RED;
    else if (nrComponents == 3)
        format = GL_RGB;
    else if (nrComponents == 4)
        format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  }
  else
  {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}
