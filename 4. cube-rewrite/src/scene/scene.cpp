#include "scene.hpp"
#include <glad/glad.h>

namespace Scene {

std::vector<Object> Objects;
void DrawScene(){

  for(int i=0; i<Objects.size(); i++){
    Object currentObject = Objects[i];
    currentObject.ObjectShader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, currentObject.texture);
    glBindVertexArray(currentObject.ObjectVAO);

    /*glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
  }

}

void AddObjectToScene(){

}

}
