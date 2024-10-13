#include "texture_loader.h"
#include <iostream>
#include <glad/glad.h>
#include "../../include/stb/stb_image.h"

unsigned int loadTexture(const char* path){
  unsigned int textureId;

  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Flip image before loading
  stbi_set_flip_vertically_on_load(true);

  int width, height, nrChannel;
  unsigned char *data = stbi_load(path, &width, &height, &nrChannel, 0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "ERROR::TEXTURE_LOADER::FAILED TO LOAD TEXTURE \n";
  }

  stbi_image_free(data);

  return textureId;
}
