#include "lights.hpp"
#include "../OpenGL/opengl_config.hpp"
#include <string>

namespace AllLights {
  std::vector<LightList> g_LightList;

  void ApplyLights(Shader currentObjectShader){
    currentObjectShader.use();

    currentObjectShader.setVec3("viewPos", OpenGLConfig::cameraClass.Position);
    currentObjectShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f)); // Colors n shit
    currentObjectShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    currentObjectShader.setFloat("material.shininess", 32.0f);

    // TODO: remove this thing
    //Temporarily add one directional light
    _ApplyDirectionalLight(currentObjectShader);

    for(int i = 0; i < (int)g_LightList.size(); i++){
      if(g_LightList[i].light_type == POINT){
        _ApplyPointLight(currentObjectShader, g_LightList[i].object_detail.transform.position);
      } else if(g_LightList[i].light_type == SPOTLIGHT){
        _ApplySpotlight(currentObjectShader);
      } else {
        _ApplyDirectionalLight(currentObjectShader);
      }
    }
  }

  void AddLightIntoScene(LightType type, glm::vec3 position){
    // add model
    ObjectDetail _modelDetail;
    std::string current_index = std::to_string(g_LightList.size());
    std::string light_type;
    if(type == POINT){
      light_type = "Point Light ";
    } else if (type == SPOTLIGHT){
      light_type = "Spot Light ";
    } else {
      light_type = "Directional Light ";
    }
    _modelDetail.Name = light_type + current_index;

    Model currentModel = Model();
    _modelDetail.ModelMesh = currentModel;

    _modelDetail.transform.position = position;
    _modelDetail.transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f); // TODO: Should be non zero?
    _modelDetail.transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

    _modelDetail.isSelected = false;

    LightList currentLight;
    currentLight.object_detail = _modelDetail;
    currentLight.light_type = type;
    g_LightList.push_back(currentLight);
  }

  // TODO, make this all changeable
  void _ApplyDirectionalLight(Shader currentObjectShader){
    currentObjectShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    currentObjectShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    currentObjectShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    currentObjectShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
  }
  
  void _ApplySpotlight(Shader currentObjectShader){
    currentObjectShader.setVec3("spotLight.position", OpenGLConfig::cameraClass.Position);
    currentObjectShader.setVec3("spotLight.direction", OpenGLConfig::cameraClass.Front);
    currentObjectShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    currentObjectShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    currentObjectShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    currentObjectShader.setFloat("spotLight.constant", 1.0f);
    currentObjectShader.setFloat("spotLight.linear", 0.09f);
    currentObjectShader.setFloat("spotLight.quadratic", 0.032f);
    currentObjectShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    currentObjectShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));     
  }

  void _ApplyPointLight(Shader currentObjectShader, glm::vec3 point_light_position){
    /*std::cout << point_light_position.x << " " << point_light_position.y << " " << point_light_position.z << " \n";*/
    currentObjectShader.setVec3("pointLights.position", point_light_position);
    currentObjectShader.setVec3("pointLights.ambient", 0.05f, 0.05f, 0.05f);
    currentObjectShader.setVec3("pointLights.diffuse", 0.8f, 0.8f, 0.8f);
    currentObjectShader.setVec3("pointLights.specular", 1.0f, 1.0f, 1.0f);
    currentObjectShader.setFloat("pointLights.constant", 1.0f);
    currentObjectShader.setFloat("pointLights.linear", 0.09f);
    currentObjectShader.setFloat("pointLights.quadratic", 0.032f);
  }
}
