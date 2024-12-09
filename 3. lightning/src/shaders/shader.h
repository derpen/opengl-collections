#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
	unsigned int ShaderID;
  enum Im3dType {
    NONE,
    POINTS,
    LINES,
    TRIANGLES
  };

  Shader();
  Shader(Im3dType value); /* Only used for Im3d */

	void use();
  void createShaderProgram(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath = "");
  std::string readShaderSource(const std::string &filepath);
  unsigned int compileShader(unsigned int type, const std::string &source);
  void SetMVP(
      glm::mat4 model,
      glm::mat4 view,
      glm::mat4 projection
  );

  //UniformSetterz
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
  Im3dType m_Im3dType;
};
