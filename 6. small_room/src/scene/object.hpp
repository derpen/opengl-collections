#pragma once
#include <glm/ext/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <glm/glm.hpp>

// TODO:
// Rename this shit properly since it clashes with 'Material' in model
struct ObjectMaterial {
  unsigned int diffuseMap;
  float object_shininess;
  glm::vec3 object_specular;
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

struct Transform {
  glm::vec3 position; // TODO: should have call this a translation
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

  // This thing is broken
  // Fix me
  // Or not... maybe I should have just figure out something else
  void setModelMatrix(glm::mat4 newModelMatrix) {
      glm::quat rotate;
      glm::vec3 skew;
      glm::vec4 perspective;

      glm::decompose(newModelMatrix, scale, rotate, position, skew, perspective); // Not actually using last two value

      // How do I turn a quaternion into a vec3??
      // https://stackoverflow.com/questions/17918033/glm-decompose-mat4-into-translation-and-rotation
      rotate = glm::conjugate(rotate); 
      rotation = glm::eulerAngles(rotate);
  }
};
