#include "mesh.h"
#include <glad/glad.h>
#include <string>
#include <vector>

Mesh::Mesh(
    std::vector<Vertex> vertices,
    std::vector<unsigned int> indices,
    std::vector<Texture> textures,
    std::vector<Material> material
){
  Vertices = vertices;
  Indices = indices;
  Textures = textures;
  Materials = material;

  setupMesh();
}

void Mesh::Draw(Shader &shader){
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;

  if(Textures.size() > 0){
    for(unsigned int i = 0; i < Textures.size(); i++){
      glActiveTexture(GL_TEXTURE0 + i);

      std::string number;
      std::string name = Textures[i].type;
      if(name == "texture_diffuse"){
        number = std::to_string(diffuseNr++);
      }
      else if(name == "texture_specular"){
        number = std::to_string(specularNr++);
      }

      glUniform1i(glGetUniformLocation(shader.ShaderID, (name + number).c_str()), i);

      // Another way of setting the le shader
      /*shader.setInt((name + number).c_str(), i);*/
      /*shader.setInt(("material." + name + number).c_str(), i); //Use this if using struct in model's shader */

      glBindTexture(GL_TEXTURE_2D, Textures[i].id);
    }
  } else {
    // Right now, assuming everything is array of size 1
    shader.setVec3("Diffuse", Materials[0].Diffuse);
    shader.setVec3("Specular", Materials[0].Specular);
    shader.setVec3("Highlight", Materials[0].Highlight);
    shader.setFloat("Shininess", Materials[0].Shininess);
  }

  //Draw le Mesh
  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(Indices.size()), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh(){
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

  //Vertex pos
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  //Vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

  //Vertex tex coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

  glBindVertexArray(0);
}
