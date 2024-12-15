#pragma once

#include "../shaders/shader.h"
#include "object.hpp"

enum LightType {
  POINT,
  OMNI,
  DIRECTIONAL
};

struct LightList {
  ObjectDetail object_detail;
  LightType light_type;
};

namespace AllLights {
  extern std::vector<LightList> g_LightList;

  void ApplyLights(Shader currentObjectShader);
  void AddLightIntoScene(LightType type);
  void _ApplyDirectionalLight(Shader currentObjectShader);
  void _ApplySpotlight(Shader currentObjectShader);
  void _ApplyPointLight(Shader currentObjectShader);
}
