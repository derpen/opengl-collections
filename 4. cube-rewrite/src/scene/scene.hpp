#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <string>
#include <vector>
#include "../shaders/shaders.hpp"
#include "object.hpp"

namespace Scene {
// This will get bigger as time goes, oh god
struct GameObject {
  // Should have an ID so I can modify existing object on runtime
  // Should probably learn some naming conventions
  bool enabled = true;
  std::string name;
  unsigned int ObjectVAO;
  Shader ObjectShader;
  Model model;
  Material material; // Where do I set the values for this thing
  void Update();
};

struct Light {
  // Should have an ID so I can modify existing light on runtime
  /*Model model;*/
  /*Shader lightShader; // Probably not exactly important, ideally light is not rendered as cube*/
  /*LightMaterial material;*/

  // THIS IS BASICALLY JUST GameObject, but instead in a different vector
  // VERY DIRTY HACK UNTIL I LEARN HOW TO MAKE SCENETREE PROPERLY
  bool enabled = true;
  std::string name;
  unsigned int ObjectVAO;
  Shader ObjectShader;
  Model model;
  LightMaterial material;
};

extern std::vector<GameObject> Objects;
extern std::vector<Light> Lights;

void DrawScene();
void AddObjectToScene(); // Preferably this one is used for everything, but we'll hold on to that
void AddCube(
  std::string name, // TODO: need to automate this
  const std::string& texturePath = std::string(),
  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
  glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
  glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
);

void AddPointLight(
  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)
);

void DrawObjects();
void HandleLights();

void HandleShaderUniforms(GameObject currentObject);
void HandleShaderUniforms(Light currentLight);

void HandleLightingUniforms(Shader currentShader, Light currentLight, GameObject currentObject);
}
