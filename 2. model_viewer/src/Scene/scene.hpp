#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "../shaders/shader.h"
#include "../assimp_model_loader/model.h"

namespace Scene{
  struct ModelDetail {

    //TODO: clean this up, move to object.hpp

    std::string Name;
    glm::vec3 Transform;
    glm::vec3 Scale;
    glm::vec3 RotationAxis;
    float Rotation;
    Model ModelMesh;
    Shader shader;
    bool isSelected;
  };

  extern std::vector<ModelDetail> g_ModelList;

  //TODO: do a little renaming for these functions
  void AddModelToScene(std::string ModelName, std::string VertexShader, std::string FragmentShader); // ADD ALL MODELS HERE
  void RemoveModelFromScene(std::string ModelName); 
  void InitializeScene(); // TODO: is this needed?
  void DrawScene();
}
