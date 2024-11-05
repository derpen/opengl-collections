#include "scene.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Scene{
  std::vector<ModelDetail> ModelList;

  void AddModelToScene(std::string ModelName, std::string VertexShader, std::string FragmentShader){
    // add model
    ModelDetail _modelDetail;
    _modelDetail.Name = ModelName.c_str();
    
    Model currentModel = Model(ModelName.c_str());
    _modelDetail.ModelMesh = currentModel;

    Shader ayumuShader = Shader();
    ayumuShader.createShaderProgram(VertexShader.c_str(), FragmentShader.c_str());
    _modelDetail.shader = ayumuShader;

    glm::mat4 model = glm::mat4(1.0f);

    _modelDetail.Transform = glm::vec3(1.0f, 1.0f, 1.0f);
    _modelDetail.RotationAxis = glm::vec3(0.0f, 0.0f, 0.0f);
    _modelDetail.Rotation = 0.0f; // Angle
    _modelDetail.Scale = glm::vec3(0.0f, 0.0f, 0.0f);

    _modelDetail.isSelected = false;

    ModelList.push_back(_modelDetail);
  }

  void DrawScene(){
    // draw all
  }
}


