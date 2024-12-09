#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(){
  m_Im3dType = NONE;
};

Shader::Shader(Im3dType value){
  m_Im3dType = value;
}

void Shader::use(){
	glUseProgram(ShaderID);
}

void Shader::createShaderProgram(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath){
  std::string vertexShaderSource = readShaderSource(vertexPath);
  std::string fragmentShaderSource = readShaderSource(fragmentPath);
  std::string geometryShaderSource;

  if(!geometryPath.empty()){
    geometryShaderSource = readShaderSource(geometryPath);
  }

  // ALL THIS GARBAGE BELOW IS TO HANDLE IM3D ------------------------
  // This is to handle Im3d default glsl shader code which have lots of ifdefs
  // An alternative solution would be to separate the code into multiple files
  // TODO, optional, separate im3d.glsl file into their respective shader type and shader shapes
  // TODO, medium prio, move these code somehow to im3d_handler.cpp, and also the enums on the constructor
  if(m_Im3dType == LINES){
    std::string shaderShape = "#define LINES\n";
    vertexShaderSource.insert(0, shaderShape);
    fragmentShaderSource.insert(0, shaderShape);
    if(!geometryPath.empty()){
      geometryShaderSource.insert(0, shaderShape);
    }
  }

  if(m_Im3dType == POINTS){
    std::string shaderShape = "#define POINTS\n";
    vertexShaderSource.insert(0, shaderShape);
    fragmentShaderSource.insert(0, shaderShape);
    if(!geometryPath.empty()){
      geometryShaderSource.insert(0, shaderShape);
    }
  }

  if(m_Im3dType == TRIANGLES){
    std::string shaderShape = "#define TRIANGLES\n";
    vertexShaderSource.insert(0, shaderShape);
    fragmentShaderSource.insert(0, shaderShape);
    if(!geometryPath.empty()){
      geometryShaderSource.insert(0, shaderShape);
    }
  }

  if(m_Im3dType != NONE){
    vertexShaderSource.insert(0, "#define VERTEX_SHADER\n");
    fragmentShaderSource.insert(0, "#define FRAGMENT_SHADER\n");
    if(!geometryPath.empty()){
      geometryShaderSource.insert(0, "#define GEOMETRY_SHADER\n");
    }

    // Add version
    vertexShaderSource.insert(0, "#version 460 core\n");
    fragmentShaderSource.insert(0, "#version 460 core\n");
    if(!geometryPath.empty()){
      geometryShaderSource.insert(0, "#version 460 core\n");
    }
  }

  // ALL THIS GARBAGE ABOVE IS TO HANDLE IM3D ------------------------

  unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
  unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  unsigned int geometryShader;

  if(!geometryPath.empty()){
    geometryShader = compileShader(GL_GEOMETRY_SHADER, geometryShaderSource);
  }

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  if(!geometryPath.empty()){
    glAttachShader(shaderProgram, geometryShader);
  }

  glLinkProgram(shaderProgram);

  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
      std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  if(!geometryPath.empty()){
    glDeleteShader(geometryShader);
  }

  ShaderID = shaderProgram;
}

std::string Shader::readShaderSource(const std::string &filepath){
  std::ifstream file;
  file.open(filepath);
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  return buffer.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source){
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int success;
  char infoLog[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
      glGetShaderInfoLog(id, 512, nullptr, infoLog);
      std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  return id;
}

void Shader::SetMVP(
    glm::mat4 model,
    glm::mat4 view,
    glm::mat4 projection
){
    setMat4("model", model);
    setMat4("view", view);
    setMat4("projection", projection);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ShaderID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ShaderID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ShaderID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
	glUniform2fv(glGetUniformLocation(ShaderID, name.c_str()), 1, &value[0]); 
}
void Shader::setVec2(const std::string &name, float x, float y) const
{ 
	glUniform2f(glGetUniformLocation(ShaderID, name.c_str()), x, y); 
}
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
	glUniform3fv(glGetUniformLocation(ShaderID, name.c_str()), 1, &value[0]); 
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{ 
	glUniform3f(glGetUniformLocation(ShaderID, name.c_str()), x, y, z); 
}
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
	glUniform4fv(glGetUniformLocation(ShaderID, name.c_str()), 1, &value[0]); 
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{ 
	glUniform4f(glGetUniformLocation(ShaderID, name.c_str()), x, y, z, w); 
}
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
