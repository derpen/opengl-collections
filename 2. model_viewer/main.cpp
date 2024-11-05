#include "src/OpenGL/opengl_main.hpp"
#include "vendor/im3d/im3d_math.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "src/shaders/shader.h"
#include "src/utils/shapes/shape_vertices.h"
#include "src/assimp_model_loader/model.h"
#include "src/OpenGL/opengl_config.hpp"
#include "vendor/stb/stb_image.h"
#include "vendor/im3d/im3d.h"

/*TODO: CLEAN CODE BEFORE MOVING TO NEXT PHASE */
// TODO: FRAMBUFFER RESIZE KIND OF BREAK ?

void processInput(GLFWwindow* window);

float deltaTime = 0.0;
float lastFrame = 0.0;

// All Models
std::vector<Model> ModelsInScene;
Model currentSelected = Model();

int main(){
  std::cout << "The nightmare begins once more.. \n" ;

  int success = OpenGLConfig::Init();
  if(success < 0){
    std::cout << "Init Failed \n";
    return -1;
  }

  /*IMGUI_DEBUG::imguiInit(OpenGLConfig::g_Window);*/

  /*// Sometimes might wanna flip image for texture to work */
  /*stbi_set_flip_vertically_on_load(true);*/

  /*// OSAKA FROM AZUMANGA DAIOH*/
  /*std::string ayumu = "assets/models/osaka/osaka-assimp.obj";*/
  /*Model ayumuModel = Model(ayumu.c_str());*/
  /*ModelsInScene.push_back(ayumuModel);*/
  /*Shader ayumuShader = Shader();*/
  /*ayumuShader.createShaderProgram("shaders/osaka.vert", "shaders/osaka.frag");*/

  /*Shader model_select_shader = Shader();*/
  /*model_select_shader.createShaderProgram("shaders/model_select.vert", "shaders/model_select.frag");*/
  /**/
  /*Shader model_stencil_shader = Shader();*/
  /*model_stencil_shader.createShaderProgram("shaders/model_stencil.vert", "shaders/model_stencil.frag");*/

  /*//Framebuffer, and screen quad*/
  /*OpenGLConfig::mainFramebuffer = SceneFramebuffer(OpenGLConfig::conf.m_width, OpenGLConfig::conf.m_height);*/
  /*shapes::InitScreenTexture();    */
  /*Shader screenTexture = Shader();*/
  /*screenTexture.createShaderProgram("shaders/screentext.vert", "shaders/screentext.frag");*/
  /*screenTexture.setInt("screenTexture", 0);*/
  /**/
  /*//Second framebuffer for picking things*/
  /*OpenGLConfig::pickingFramebuffer = SceneFramebuffer(OpenGLConfig::conf.m_width, OpenGLConfig::conf.m_height);*/

  /*glEnable(GL_DEPTH_TEST);  */
  /*glEnable(GL_STENCIL_TEST);  */

  /*Im3dHandler::Im3d_Init();*/

  OpenGLLoop::mainLoop();

  while(!glfwWindowShouldClose(OpenGLConfig::g_Window)){
    glfwPollEvents();

    /*IMGUI_DEBUG::imguiStartFrame();*/

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // View/Projection Transform
    glm::mat4 view = OpenGLConfig::cameraClass.GetViewMatrix();
    glm::mat4 projection = OpenGLConfig::cameraClass.GetProjMatrix();

    //-----------------------Draw Osaka here-----------------

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    /*glm::mat4 projection = glm::perspective(glm::radians(OpenGLConfig::cameraClass.cameraFOV), (float)OpenGLConfig::conf.m_width / (float)OpenGLConfig::conf.m_height, 0.1f, 100.0f);*/

    // Draw normally to offscreen buffer
    OpenGLConfig::mainFramebuffer.UseFrameBuffer();
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

    // TODO: STENCIL, MIGHT WANNA MOVE SOMEWHERE
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilMask(0x00);

    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    ayumuShader.use();
    ayumuShader.SetMVP(model, view, projection);
    ayumuModel.Draw(ayumuShader);

    if(currentSelected.m_modelName != "default"){
      glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
      glStencilMask(0x00);
      glDisable(GL_DEPTH_TEST);
      model_stencil_shader.use();
      glm::mat4 temp_model = glm::mat4(1.0f);
      float scale = 1.05f;
      temp_model = glm::scale(temp_model, glm::vec3(scale, scale, scale));
      temp_model = glm::translate(temp_model, glm::vec3(0.0f, 0.0f, 0.0f));
      model_stencil_shader.SetMVP(temp_model, view, projection);
      ayumuModel.Draw(model_stencil_shader);
      glStencilMask(0xFF);
      glStencilFunc(GL_ALWAYS, 1, 0xFF);
    }

    OpenGLConfig::mainFramebuffer.DeactivateFrameBuffer();

    // Draw it again, but for the picking framebuffer
    OpenGLConfig::pickingFramebuffer.UseFrameBuffer();
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    model_select_shader.use();
    model_select_shader.SetMVP(model, view, projection);
    model_select_shader.setFloat("modelIndex", 0.5f); /* TODO: Temporary way of storing object index */
    ayumuModel.Draw(model_select_shader);
    OpenGLConfig::pickingFramebuffer.DeactivateFrameBuffer();

    //------------------------Draw done --------------------------

    // Draw texture from offscreen framebuffer to  quad on screen
    screenTexture.use();
    shapes::UseScreenTexture();
    glBindTexture(GL_TEXTURE_2D, OpenGLConfig::mainFramebuffer.m_ScreenTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    shapes::DisableScreenTexture();

    /*IMGUI_DEBUG::imguiEndFrame();*/

    // ----------------------- TODO: IM3DDDDDDDDDDDDDDDDDDDDDDD -----------------
    // TODO: trying im3d, What if I put on the btm
    Im3d::Context& ctx = Im3d::GetContext();
    Im3d::AppData& ad = Im3d::GetAppData();
    int gizmoMode = (int)Im3d::GetContext().m_gizmoMode;
    /*Im3d::GetContext().m_gizmoLocal = 0; // To turn into gizmo into local or global (probably )*/

    // handle which mode
    gizmoMode = Im3d::GizmoMode_Translation;
    /*gizmoMode = Im3d::GizmoMode_Rotation;*/
    /*gizmoMode = Im3d::GizmoMode_Scale;*/

    Im3d::GetContext().m_gizmoMode = (Im3d::GizmoMode)gizmoMode;

    // This part is probably for when a matrix is modified
    static Im3d::Mat4 leTransform(1.0f);
		// The ID passed to Gizmo() should be unique during a frame - to create gizmos in a loop use PushId()/PopId().
    if(Im3d::Gizmo("GizmoUnified", leTransform)){
			// if Gizmo() returns true, the transform was modified
      switch(Im3d::GetContext().m_gizmoMode){
        case Im3d::GizmoMode_Translation:
          {
            Im3d::Vec3 pos = leTransform.getTranslation();
            break;
          }
        case Im3d::GizmoMode_Rotation:
          {
            Im3d::Vec3 euler = Im3d::ToEulerXYZ(leTransform.getRotation());
						break;
					}
					case Im3d::GizmoMode_Scale:
					{
						Im3d::Vec3 scale = leTransform.getScale();
						break;
					}
					default: break;
      }

    }

    // --------------------------- IM3D DONE -------------------------------------

    //Update Mouse
    processInput(OpenGLConfig::g_Window);
    OpenGLConfig::Input.MouseState(OpenGLConfig::g_Window);
    glfwSwapBuffers(OpenGLConfig::g_Window);
  }

  //TODO code to do clean up here (remove vbo, vao, etc)

  /*IMGUI_DEBUG::imguiShutdown();*/

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }

  if(OpenGLConfig::Input.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)){
    OpenGLConfig::Input.ToggleCursor(window);
  } else if (OpenGLConfig::Input.GetMouseButtonUp(GLFW_MOUSE_BUTTON_RIGHT)){
    OpenGLConfig::Input.ToggleCursor(window);
  }

  // Read pixel from picking framebuffer
  if(OpenGLConfig::Input.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT)){
    OpenGLConfig::pickingFramebuffer.UseFrameBuffer();
    unsigned char pixel[3];
    glReadPixels(OpenGLConfig::lastX, OpenGLConfig::conf.m_height - OpenGLConfig::lastY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
    
    // Handle picking
    unsigned long int objectIndex = (int)pixel[0];
    if(objectIndex < ModelsInScene.size()){
      currentSelected = ModelsInScene[objectIndex];
    } else {
      currentSelected = Model();
    }     

    OpenGLConfig::pickingFramebuffer.DeactivateFrameBuffer();
  }

  OpenGLConfig::Input.FlyingMovement(window, &OpenGLConfig::cameraClass, deltaTime);
}
