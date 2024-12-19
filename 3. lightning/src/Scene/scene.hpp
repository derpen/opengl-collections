#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "object.hpp"

namespace Scene{
  /*struct ObjectsInScene {*/
  /*  ObjectDetail object;*/
  /*};*/

  extern std::vector<ObjectDetail> g_ModelList;

  //TODO:  multiple object selected is wanted
  extern bool g_IsSelecting;
  extern unsigned int g_SelectedObjectIndex;

  //TODO: do a little renaming for these functions
//
  // ADD ALL MODELS HERE
  void AddModelToScene(std::string ModelName, std::string VertexShader, std::string FragmentShader, bool flipImage);

  // This one is for objects that is already defined in shapes_vertices.cpp
  void AddModelToScene(std::string ModelName, Shader objectShader); 

  // Make light naming convention automatic
  void AddOmniLightToScene(
    std::string LightName,
    glm::vec3 position = glm::vec3(0.0f),
    glm::vec3 rotation = glm::vec3(0.0f),
    glm::vec3 scale = glm::vec3(1.0f)
  );
  void AddDirectionalLightToScene(std::string LightName);
  void AddFlashLightToScene(std::string LightName);

  void RemoveModelFromScene(std::string ModelName); 
  void PickModelFromScene();
  void LightningShaderHandler(Shader lightShader);
  void InitializeScene(); // TODO: is this needed?
  void DrawScene();
  void DrawShader(Shader currentShader);
}
