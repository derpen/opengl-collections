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
  void AddModelToScene(std::string ModelName, std::string VertexShader, std::string FragmentShader, bool flipImage); // ADD ALL MODELS HERE
  void RemoveModelFromScene(std::string ModelName); 
  void PickModelFromScene();
  void InitializeScene(); // TODO: is this needed?
  void DrawScene();
}
