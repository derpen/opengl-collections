#include "scene.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGL/opengl_config.hpp"
#include "../utils/shapes/shape_vertices.h"
#include "../../vendor/imgui/imgui.h"
#include "../im3d/im3d_handler.hpp"
#include "../../vendor/im3d/im3d.h"
#include "../../vendor/stb/stb_image.h"
#include "object.hpp"

namespace Scene{
  std::vector<ObjectDetail> g_ModelList;
  bool g_IsSelecting = false;
  unsigned int g_SelectedObjectIndex = 0;

  void AddModelToScene(std::string ModelName, std::string VertexShader, std::string FragmentShader, bool flipImage){
    // add model
    ObjectDetail _modelDetail;
    _modelDetail.Name = ModelName.c_str();
    _modelDetail.Type = OBJECT;
    
    if(flipImage){
      // Sometimes might wanna flip image for texture to work
      stbi_set_flip_vertically_on_load(true);
    }

    Model currentModel = Model(ModelName.c_str());
    _modelDetail.ModelMesh = currentModel;

    Shader ayumuShader = Shader();

    ayumuShader.createShaderProgram(VertexShader, FragmentShader);
    _modelDetail.shader = ayumuShader;

    _modelDetail.transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    _modelDetail.transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f); // TODO: Should be non zero?
    _modelDetail.transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

    _modelDetail.isSelected = false;

    g_ModelList.push_back(_modelDetail);

    if(flipImage){
      // Turn off again after everything
      stbi_set_flip_vertically_on_load(false);
    }
  }

  void AddModelToScene(std::string ModelName, Shader objectShader){
    // add model
    ObjectDetail _modelDetail;
    _modelDetail.Name = ModelName.c_str();
    _modelDetail.Type = OBJECT;

    Model currentModel = Model();
    _modelDetail.ModelMesh = currentModel; // Empty
  //
    _modelDetail.shader = objectShader;

    _modelDetail.transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    _modelDetail.transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f); // TODO: Should be non zero?
    _modelDetail.transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

    _modelDetail.isSelected = false;

    g_ModelList.push_back(_modelDetail);
  }

  void AddOmniLightToScene(std::string LightName){
    // add model
    ObjectDetail _modelDetail;
    _modelDetail.Name = LightName.c_str();
    _modelDetail.Type = LIGHT;

    Model currentModel = Model();
    _modelDetail.ModelMesh = currentModel;

    _modelDetail.shader = OpenGLConfig::light_shader;

    _modelDetail.transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    _modelDetail.transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f); // TODO: Should be non zero?
    _modelDetail.transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

    _modelDetail.isSelected = false;

    g_ModelList.push_back(_modelDetail);
  }

  void InitializeScene(){
    // Add models here
    /*AddModelToScene("assets/models/osaka/osaka-assimp.obj", "shaders/osaka.vert",  "shaders/osaka.frag", false);*/
    /*AddModelToScene("assets/models/testscene/TestScene.obj", "shaders/testscene.vert",  "shaders/testscene.frag", false);*/
    /*AddModelToScene("Cube", OpenGLConfig::cube_shader);*/
    AddOmniLightToScene("OmniLight");
  }

  void DrawScene(){
    // draw all
    // Clear everything from last frame
    // TODO: clean this shit
    OpenGLConfig::mainFramebuffer.UseFrameBuffer();
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    // TODO: STENCIL, MIGHT WANNA MOVE SOMEWHERE
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0x00);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    OpenGLConfig::mainFramebuffer.DeactivateFrameBuffer();

    OpenGLConfig::pickingFramebuffer.UseFrameBuffer();
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    OpenGLConfig::pickingFramebuffer.DeactivateFrameBuffer();

    for(int i = 0; i < (int)g_ModelList.size(); i++){
      bool isModel = false;
      if(g_ModelList[i].ModelMesh.m_modelName != "default"){
        isModel = true;
      }

      // Draw normally to offscreen buffer
      OpenGLConfig::mainFramebuffer.UseFrameBuffer();

      Shader currentShader = g_ModelList[i].shader;
      currentShader.use();
      glm::mat4 model = g_ModelList[i].GetModelMatrix();
      currentShader.SetMVP(model, OpenGLConfig::cameraClass.GetViewMatrix(), OpenGLConfig::cameraClass.GetProjMatrix());

      g_ModelList[i].ModelMesh.Draw(currentShader);
      if(!isModel){
        shapes::UseCube();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        shapes::DisableCube();
      }

      // If model selected, draw an overline
      if(g_ModelList[i].isSelected){
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        OpenGLConfig::model_stencil_shader.use();
        glm::mat4 temp_model = g_ModelList[i].GetModelMatrix();
        OpenGLConfig::model_stencil_shader.SetMVP(temp_model, OpenGLConfig::cameraClass.GetViewMatrix(), OpenGLConfig::cameraClass.GetProjMatrix());
        g_ModelList[i].ModelMesh.Draw(OpenGLConfig::model_stencil_shader);
        if(!isModel){
          shapes::UseCube();
          glDrawArrays(GL_TRIANGLES, 0, 36);
          shapes::DisableCube();
        }
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
      }

      OpenGLConfig::mainFramebuffer.DeactivateFrameBuffer();

      // Draw it again, but for the picking framebuffer
      OpenGLConfig::pickingFramebuffer.UseFrameBuffer();
      OpenGLConfig::model_select_shader.use();

      OpenGLConfig::model_select_shader.SetMVP(model, OpenGLConfig::cameraClass.GetViewMatrix(), OpenGLConfig::cameraClass.GetProjMatrix());

      OpenGLConfig::model_select_shader.setFloat("modelIndex", static_cast<float>(i)); 

      g_ModelList[i].ModelMesh.Draw(OpenGLConfig::model_select_shader);
      if(!isModel){
        shapes::UseCube();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        shapes::DisableCube();
      }
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

  // TODO: need to change this method. This is not extensible
  // Switch to raycasting from mouse and collision instead
  void PickModelFromScene(){
    // Read pixel from picking framebuffer
    if(OpenGLConfig::Input.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT)){

      /* TOOD: dogpee solution to prevent accidental deselecting, find better way soon */
      bool testGizmo;
      if(g_IsSelecting){
        testGizmo = Im3d::Gizmo("GizmoUnified", Im3dHandler::s_GizmoTransform);
      }

      if(testGizmo || ImGui::GetIO().WantCaptureMouse){
        return;
      }
      /* TOOD: dogpee solution done */

      OpenGLConfig::pickingFramebuffer.UseFrameBuffer();
      unsigned char pixel[3];
      glReadPixels(OpenGLConfig::lastX, OpenGLConfig::conf.m_height - OpenGLConfig::lastY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
      
      // Handle picking
      unsigned long int objectIndex = (int)pixel[0];
      if(objectIndex < Scene::g_ModelList.size()){
        Scene::g_ModelList[g_SelectedObjectIndex].isSelected = false;
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



