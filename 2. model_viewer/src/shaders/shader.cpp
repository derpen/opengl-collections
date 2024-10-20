#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Shader::use(){
	glUseProgram(ShaderID);
}

void Shader::createShaderProgram(const std::string &vertexPath, const std::string &fragmentPath){
  std::string vertexShaderSource = readShaderSource(vertexPath);
  std::string fragmentShaderSource = readShaderSource(fragmentPath);

  unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
  unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
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
