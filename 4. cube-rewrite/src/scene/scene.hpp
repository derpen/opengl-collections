#pragma once
#include <string>
#include <vector>
#include "../shaders/shaders.hpp"

// This will get bigger as time goes, oh god
struct Object {
  std::string name;
  unsigned int ObjectVAO;
  unsigned int texture; // assuming we only have one texture per object for now
  Shader ObjectShader;
};

namespace Scene {
extern std::vector<Object> Objects;
void DrawScene();
void AddObjectToScene();

}
