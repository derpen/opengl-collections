#include "scene.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGL/opengl_config.hpp"
#include "../utils/shapes/shape_vertices.h"

namespace Scene{
  std::vector<ObjectDetail> g_ModelList;
  bool g_IsSelecting = false;
  unsigned int g_SelectedObjectIndex = 0;

  void AddModelToScene(std::string ModelName, std::string VertexShader, std::string FragmentShader){
    // add model
    ObjectDetail _modelDetail;
    _modelDetail.Name = ModelName.c_str();
    
    Model currentModel = Model(ModelName.c_str());
    _modelDetail.ModelMesh = currentModel;

    Shader ayumuShader = Shader();
    ayumuShader.createShaderProgram(VertexShader, FragmentShader);
    _modelDetail.shader = ayumuShader;

    _modelDetail.transform.position = glm::vec3(1.0f, 1.0f, 1.0f);
    _modelDetail.transform.rotation = glm::vec3(1.0f, 1.0f, 1.0f); // TODO: This should be non zero
    _modelDetail.Rotation = 0.0f; // Angle
    _modelDetail.transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

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
      glm::mat4 model = g_ModelList[i].GetModelMatrix();
      currentShader.SetMVP(model, OpenGLConfig::cameraClass.GetViewMatrix(), OpenGLConfig::cameraClass.GetProjMatrix());
      g_ModelList[i].ModelMesh.Draw(currentShader);

      // If model selected, draw an overline
      if(g_ModelList[i].isSelected){
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        OpenGLConfig::model_stencil_shader.use();

        float scale = 1.00f;
        g_ModelList[i].transform.scale = glm::vec3(scale);
        glm::mat4 temp_model = g_ModelList[i].GetModelMatrix();

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
      OpenGLConfig::model_select_shader.setFloat("modelIndex", 0.0f); /* TODO: Temporary way of storing object index */
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

  void PickModelFromScene(){
    // Read pixel from picking framebuffer
    if(OpenGLConfig::Input.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT)){
      OpenGLConfig::pickingFramebuffer.UseFrameBuffer();
      unsigned char pixel[3];
      glReadPixels(OpenGLConfig::lastX, OpenGLConfig::conf.m_height - OpenGLConfig::lastY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
      
      // Handle picking
      unsigned long int objectIndex = (int)pixel[0];
      if(objectIndex < Scene::g_ModelList.size()){
        Scene::g_ModelList[objectIndex].isSelected = true;
        Scene::g_IsSelecting = true;
        Scene::g_SelectedObjectIndex = objectIndex;
      } else {
        Scene::g_ModelList[g_SelectedObjectIndex].isSelected = false;
        Scene::g_IsSelecting = false;
      }     

      OpenGLConfig::pickingFramebuffer.DeactivateFrameBuffer();
    }
  }
}



