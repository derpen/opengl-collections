#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/trigonometric.hpp>
#include <string>
#include "../utils/math/math.hpp"
#include "../shaders/shader.h"
#include "../assimp_model_loader/model.h"

enum ObjectType {
  OBJECT,
  LIGHT
};

struct ObjectDetail {
  std::string Name;
  ObjectType Type;

  bool visible = true;
  Transform transform;
  float Rotation; // TODO: needed ?
  Model ModelMesh;
  Shader shader;
  bool isSelected;

  inline glm::mat4 GetModelMatrix(){
    glm::mat4 model = glm::mat4(1.0);
    glm::vec3 scaleVec = transform.scale;

    /*glm::vec3 rotationVec = transform.rotation;*/
    glm::vec3 rotationVec = glm::radians(transform.rotation); // Radianso

    glm::vec3 positionVec = transform.position;

    model = glm::translate(model, positionVec);

    /*// Euler angle sucks!*/
    /*model = glm::rotate(model, glm::radians(rotationVec.x), glm::vec3(1.0f, 0.0f, 0.0f));*/
    /*model = glm::rotate(model, glm::radians(rotationVec.y), glm::vec3(0.0f, 1.0f, 0.0f));*/
    /*model = glm::rotate(model, glm::radians(rotationVec.z), glm::vec3(0.0f, 0.0f, 1.0f));*/

    // Trying quaternion
    glm::quat rotationQuat = glm::quat(rotationVec);
    model *= glm::mat4_cast(rotationQuat);

    model = glm::scale(model, scaleVec);
    return model;
  };

  inline void SetModelTransform(Transform model){
    transform.position = model.position;
    transform.rotation = model.rotation;
    transform.scale = model.scale;
  }
};
