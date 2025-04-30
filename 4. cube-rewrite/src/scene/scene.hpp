#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <string>
#include <vector>
#include "../shaders/shaders.hpp"
#include "object.hpp"

namespace Scene {
// This will get bigger as time goes, oh god
struct GameObject {
  std::string name;
  unsigned int ObjectVAO;
  unsigned int texture; // assuming we only have one texture per object for now
  Shader ObjectShader;
  Model model;
  Material material; // Where do I set the values for this thing
};

extern std::vector<GameObject> Objects;
void DrawScene();
void AddObjectToScene();
void AddCube(
  std::string name, // TODO: need to automate this
  const std::string& texturePath = std::string(),
  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
  glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
  glm::vec3 scale = glm::vec3(0.0f, 0.0f, 0.0f)
);
void HandleShaderUniforms(GameObject currentObject);

}
