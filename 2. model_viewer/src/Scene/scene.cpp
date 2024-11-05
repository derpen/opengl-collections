#include "scene.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGL/opengl_config.hpp"
#include "../utils/shapes/shape_vertices.h"

namespace Scene{
  std::vector<ModelDetail> g_ModelList;

  void AddModelToScene(std::string ModelName, std::string VertexShader, std::string FragmentShader){
    // add model
    ModelDetail _modelDetail;
    _modelDetail.Name = ModelName.c_str();
    
    Model currentModel = Model(ModelName.c_str());
    _modelDetail.ModelMesh = currentModel;

    Shader ayumuShader = Shader();
    ayumuShader.createShaderProgram(VertexShader, FragmentShader);
    _modelDetail.shader = ayumuShader;

    _modelDetail.Transform = glm::vec3(1.0f, 1.0f, 1.0f);
    _modelDetail.RotationAxis = glm::vec3(1.0f, 1.0f, 1.0f); // TODO: This should be non zero
    _modelDetail.Rotation = 0.0f; // Angle
    _modelDetail.Scale = glm::vec3(1.0f, 1.0f, 1.0f);

    _modelDetail.isSelected = false;

    g_ModelList.push_back(_modelDetail);
  }

  void InitializeScene(){
    // Sometimes might wanna flip image for texture to work
    // stbi_set_flip_vertically_on_load(true);

    // Add models here
    AddModelToScene("assets/models/osaka/osaka-assimp.obj", "shaders/osaka.vert",  "shaders/osaka.frag");
  }

  void DrawScene(){
    // draw all
    for(int i = 0; i < (int)g_ModelList.size(); i++){
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::scale(model, g_ModelList[i].Scale);
      // model = glm::rotate(model, g_ModelList[i].Rotation, g_ModelList[i].RotationAxis); // TODO: THIS ONE MESSES UP SOMEHOW
      model = glm::translate(model, g_ModelList[i].Transform);

      // Draw normally to offscreen buffer
      OpenGLConfig::mainFramebuffer.UseFrameBuffer();
      glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

      // TODO: STENCIL, MIGHT WANNA MOVE SOMEWHERE
      glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      glStencilMask(0x00);

      glStencilFunc(GL_ALWAYS, 1, 0xFF);
      glStencilMask(0xFF);
      
      Shader currentShader = g_ModelList[i].shader;
      currentShader.use();
      currentShader.SetMVP(model, OpenGLConfig::cameraClass.GetViewMatrix(), OpenGLConfig::cameraClass.GetProjMatrix());
      g_ModelList[i].ModelMesh.Draw(currentShader);

      // If model selected, draw an overline
      if(g_ModelList[i].isSelected){
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        OpenGLConfig::model_stencil_shader.use();
        glm::mat4 temp_model = glm::mat4(1.0f);
        float scale = 1.05f;
        temp_model = glm::scale(temp_model, glm::vec3(scale, scale, scale));
        temp_model = glm::rotate(temp_model, g_ModelList[i].Rotation, g_ModelList[i].RotationAxis);
        temp_model = glm::translate(temp_model, g_ModelList[i].Transform);

        OpenGLConfig::model_stencil_shader.SetMVP(temp_model, OpenGLConfig::cameraClass.GetViewMatrix(), OpenGLConfig::cameraClass.GetProjMatrix());
        g_ModelList[i].ModelMesh.Draw(OpenGLConfig::model_stencil_shader);
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
      }

      OpenGLConfig::mainFramebuffer.DeactivateFrameBuffer();

      // Draw it again, but for the picking framebuffer
      OpenGLConfig::pickingFramebuffer.UseFrameBuffer();
      glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      OpenGLConfig::model_select_shader.use();
      OpenGLConfig::model_select_shader.SetMVP(model, OpenGLConfig::cameraClass.GetViewMatrix(), OpenGLConfig::cameraClass.GetProjMatrix());
      OpenGLConfig::model_select_shader.setFloat("modelIndex", 0.5f); /* TODO: Temporary way of storing object index */
      g_ModelList[i].ModelMesh.Draw(OpenGLConfig::model_select_shader);
      OpenGLConfig::pickingFramebuffer.DeactivateFrameBuffer();

      //------------------------Draw done --------------------------

      // Draw texture from offscreen framebuffer to  quad on screen
      OpenGLConfig::screenTexture.use();
      shapes::UseScreenTexture();
      glBindTexture(GL_TEXTURE_2D, OpenGLConfig::mainFramebuffer.m_ScreenTexture);
      glDrawArrays(GL_TRIANGLES, 0, 6);
      shapes::DisableScreenTexture();
    }
  }
}


