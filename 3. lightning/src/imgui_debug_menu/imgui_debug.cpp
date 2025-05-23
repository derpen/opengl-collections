#include "imgui_debug.h"
#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../../vendor/imgui/backends/imgui_impl_opengl3.h"
#include "../utils/logs/performance_log.h"
#include "../Scene/scene.hpp"
#include "../Scene/object.hpp"
#include "../Scene/lighting_setting.hpp"
#include "../utils/math/math.hpp"
#include <algorithm>
#include <filesystem>

void IMGUI_DEBUG::imguiInit(GLFWwindow* window){
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOther(window, true);
  ImGui_ImplOpenGL3_Init();
}

void IMGUI_DEBUG::imguiStartFrame(){
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  imguiDebugMenu();
}

// Example on how to create menus
void IMGUI_DEBUG::imguiDebugMenu(){
  ImGui::Begin("Debug Area", NULL, ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::SliderFloat("Mouse Sensitivity", &OpenGLConfig::cameraClass.MouseSensitivity, 0.0f, 2.0f);

  ImGui::SliderFloat("Movement Speed", &OpenGLConfig::cameraClass.MovementSpeed, 0.0f, 100.0f);

  glm::vec3 camPos = OpenGLConfig::cameraClass.Position;
  ImGui::Text("Camera Position  x: %.3f y: %.3f, z: %.3f", camPos.x, camPos.y, camPos.z);

  glm::vec3 camFront = OpenGLConfig::cameraClass.Front;
  ImGui::Text("Camera Front  x: %.3f y: %.3f, z: %.3f", camFront.x, camFront.y, camFront.z);

  glm::vec3 camUp = OpenGLConfig::cameraClass.Up;
  ImGui::Text("Camera Up  x: %.3f y: %.3f, z: %.3f", camUp.x, camUp.y, camUp.z);

  PerformanceLog::FrameMetric fm = PerformanceLog::GetTimePerFrame(glfwGetTime());
  ImGui::Text("%.2f ms/frame (%d fps)", fm.sec_per_frame, fm.frames_per_sec);

  ImGui::SeparatorText("Transform");
  ObjectDetail currentModel = Scene::g_ModelList[Scene::g_SelectedObjectIndex];
  std::string objectName;
  if(Scene::g_IsSelecting){
    objectName = currentModel.Name;
  } else {
    objectName = "None";
  }

  Transform modelTransform = currentModel.transform;

  ImGui::Text("Currently Selected Model: %s", objectName.c_str());
  static ImGuiSliderFlags flags = ImGuiSliderFlags_None;

  if(Scene::g_IsSelecting){
    ImGui::Text("Position");

    glm::vec3 modelPos = modelTransform.position;
    glm::vec3 modelRot = modelTransform.rotation;
    glm::vec3 modelSca = modelTransform.scale;
    /*Transform newTransform = Im3dHandler::s_ObjectTransform;*/

    ImGui::DragFloat("Position X", &modelPos.x, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
    ImGui::DragFloat("Position Y", &modelPos.y, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
    ImGui::DragFloat("Position Z", &modelPos.z, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);

    ImGui::Text("Rotation");
    ImGui::DragFloat("Rotation X", &modelRot.x, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
    ImGui::DragFloat("Rotation Y", &modelRot.y, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
    ImGui::DragFloat("Rotation Z", &modelRot.z, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);

    ImGui::Text("Scale");
    ImGui::DragFloat("Scale X", &modelSca.x, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
    ImGui::DragFloat("Scale Y", &modelSca.y, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
    ImGui::DragFloat("Scale Z", &modelSca.z, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
  }

  /*ImGui::Text("Current Selected Model: %s", currentSelected.m_modelName.c_str());*/
  /**/
  /*ImGui::Text("Total Model In Scene: %lu", ModelsInScene.size());*/

  ImGui::End();

  // New Window for directory listing
  ImGui::Begin("Directory");

  ImGui::Text("Current directory: %s", currentDirectory.string().c_str());

  if(currentDirectory.has_parent_path() && ImGui::Button("..")){
    currentDirectory = currentDirectory.parent_path();
  }

  auto entries = _ListDirectoryContent(currentDirectory);

  for(const auto& entry : entries) {
    if(entry.is_directory()){
      if(ImGui::TreeNode(entry.path().filename().string().c_str())){
        if(ImGui::IsItemClicked()){
          currentDirectory = entry.path();
        }

        ImGui::TreePop();
      }
    } else if (entry.is_regular_file()) {
      if(ImGui::Selectable(entry.path().filename().string().c_str())){
        std::string selectedFile = entry.path().string();
        ImGui::Text("Selected File: %s", selectedFile.c_str());
        /*Scene::AddModelToScene(selectedFile, "shaders/osaka.vert",  "shaders/osaka.frag");*/
      }
    }
  }

  ImGui::End();

  // New Window for Lightning
  ImGui::Begin("Lightning");

  //TODO: Wishlist
  // Enable spotlight
  // Change global ambient light / directional light attributes
  // Change selected object materials (diffuse, specular, shininess)
  // Enable fog (done)
  // Add more point light into the scene (will require shader to dynamically change to accomodate multiple point lights)
  // Remove point light from scene
  // Change point light attributes
  // Toggle visibility of selected light cube

  ImGui::Checkbox("Enable Depth Shader (Fog)", &LightingSetting::depthShaderEnabled);

  ImGui::End();
}

std::vector<std::filesystem::directory_entry> IMGUI_DEBUG::_ListDirectoryContent(const std::filesystem::path& path){
  std::vector<std::filesystem::directory_entry> entries;
  for(const auto& entry : std::filesystem::directory_iterator(path)){
    if(entry.is_directory()){
      entries.push_back(entry);
    } else if (entry.is_regular_file()) {
      std::string extension = entry.path().extension().string();
      std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower); // Turn into lower case

      if(allowedExtensions.find(extension) != allowedExtensions.end()){
        entries.push_back(entry);
      }
    }
  }
  return entries;
}

void IMGUI_DEBUG::imguiEndFrame(){
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void IMGUI_DEBUG::imguiShutdown(){
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void IMGUI_DEBUG::HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
