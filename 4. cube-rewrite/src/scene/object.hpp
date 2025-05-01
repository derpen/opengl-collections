#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

struct Material {
  unsigned int diffuseMap;
  float object_shininess;
  glm::vec3 object_specular;
  glm::vec3 object_ambient;
  glm::vec3 object_diffuse;
};

struct LightMaterial {
  float light_constant;
  float light_linear;
  float light_quadratic;
  glm::vec3 light_specular;
  glm::vec3 lightColor;
  glm::vec3 diffuseColor;
  glm::vec3 ambientColor;
};

struct Model {
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  //TODO: clean this shit
  glm::mat4 GetModelMatrix(){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, position);
    return model;
  }
};
