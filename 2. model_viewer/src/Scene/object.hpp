#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/glm.hpp>
#include <string>
#include "../utils/math/math.hpp"
#include "../shaders/shader.h"
#include "../assimp_model_loader/model.h"

struct ObjectDetail {
  std::string Name;
  Transform transform;

  //TODO: clean this up, move from scene.hpp

  glm::vec3 Transform;
  glm::vec3 Scale;
  glm::vec3 RotationAxis;

  glm::mat4 modelMatrix;
  float Rotation;
  Model ModelMesh;
  Shader shader;
  bool isSelected;
};
