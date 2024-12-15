#pragma once

#include "../shaders/shader.h"
#include "object.hpp"

enum LightType {
  POINT,
  SPOTLIGHT,
  DIRECTIONAL
};

struct LightList {
  ObjectDetail object_detail;
  LightType light_type;
};

namespace AllLights {
  extern std::vector<LightList> g_LightList;

  void ApplyLights(Shader currentObjectShader);
  void AddLightIntoScene(LightType type, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  void _ApplyDirectionalLight(Shader currentObjectShader);
  void _ApplySpotlight(Shader currentObjectShader);
  void _ApplyPointLight(Shader currentObjectShader, glm::vec3 point_light_position);
}
