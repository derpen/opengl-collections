#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <string>
#include "../utils/math/math.hpp"
#include "../shaders/shader.h"
#include "../assimp_model_loader/model.h"

struct ObjectDetail {
  std::string Name;
  Transform transform;
  float Rotation; // TODO: needed ?
  Model ModelMesh;
  Shader shader;
  bool isSelected;

  inline glm::mat4 GetModelMatrix(){
    glm::mat4 model = glm::mat4(1.0);
    glm::vec3 scaleVec = transform.scale;
    glm::vec3 rotationVec = transform.rotation;
    glm::vec3 positionVec = transform.position;
    model = glm::scale(model, scaleVec);
    model = glm::rotate(model, rotationVec.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotationVec.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotationVec.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, positionVec);
    return model;
  };

  inline void SetModelTransform(Transform model){
    transform.position = model.position;
    transform.rotation = model.rotation;
    transform.scale = model.scale;
  }
};
