#pragma once
#include <glm/glm.hpp>

struct Model {
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  //TODO: clean this shit
  glm::mat4 GetModelMatrix(){
    return glm::mat4(1.0);
  }
};
