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
  int LightIndex;
};

namespace AllLights {
  extern std::vector<LightList> g_LightList;

  void ApplyLights(Shader currentObjectShader);
  void AddLightIntoScene(LightType type, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  void RemoveLight(int lightIndex);
  void _ApplyDirectionalLight(Shader currentObjectShader);
  void _ApplySpotlight(Shader currentObjectShader);
  void _ApplyPointLight(Shader currentObjectShader, LightList currentLight);
}
