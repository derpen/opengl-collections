#ifndef SHADER_H
#define SHADER_H

#include <string>

unsigned int createShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);
std::string readShaderSource(const std::string &filepath);
unsigned int compileShader(unsigned int type, const std::string &source);

#endif
