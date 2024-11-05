#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "../shaders/shader.h"
#include "../assimp_model_loader/model.h"

namespace Scene{
  struct ModelDetail {
    std::string Name;
    glm::vec3 Transform;
    glm::vec3 Scale;
    glm::vec3 RotationAxis;
    float Rotation;
    Model ModelMesh;
    Shader shader;
    bool isSelected;
  };

  extern std::vector<ModelDetail> ModelList;

  void AddModelToScene(std::string ModelName, std::string VertexShader, std::string FragmentShader);
  void DrawScene();
}
