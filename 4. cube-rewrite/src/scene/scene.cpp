#include "scene.hpp"
#include <glad/glad.h>
#include "../utils/glm_utils/utils.hpp"
#include "../utils/shapes/shapes.hpp"
#include "../utils/textures/textures.hpp"

namespace Scene {

std::vector<GameObject> Objects;
void DrawScene(){

  for(int i=0; i<Objects.size(); i++){
    GameObject currentObject = Objects[i];
    currentObject.ObjectShader.use();
    HandleShaderUniforms(currentObject);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, currentObject.texture);
    glBindVertexArray(currentObject.ObjectVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36); // TODO: handle this shit, for now we just draw cubes
    /*glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
  }

}

void AddObjectToScene(){

}

void AddCube(
  std::string name, // TODO: need to automate this
  const std::string& texturePath,
  glm::vec3 position,
  glm::vec3 rotation,
  glm::vec3 scale
){
  // If not initialized
  if(Shapes::cube_VAO == 0){
    (void)Shapes::init_cube(); // return value not used
  }

  bool useTexture;
  if(!texturePath.empty()) {
    useTexture = true;
  }

  Shader new_shader("src/utils/shapes/shaders/cube.vert", "src/utils/shapes/shaders/cube.frag");
  unsigned int texture1;
  if(useTexture){
    texture1 = Texture::read_texture(texturePath.c_str());
  }

  Model model;
  model.position = position;
  model.rotation = rotation;
  model.scale = scale;

  GameObject new_object;

  if(name.empty()){
    new_object.name = "cube";
  } else {
    new_object.name = name;
  }

  new_object.ObjectVAO = Shapes::cube_VAO;
  new_object.texture = texture1;
  new_object.ObjectShader = new_shader;
  new_object.model = model;

  Objects.push_back(new_object);
}

void HandleShaderUniforms(GameObject currentObject){

}

}
