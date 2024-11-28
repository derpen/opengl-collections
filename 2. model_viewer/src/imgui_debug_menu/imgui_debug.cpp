#include "imgui_debug.h"
#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../../vendor/imgui/backends/imgui_impl_opengl3.h"
#include "../utils/logs/performance_log.h"

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
  ImGui::Text("Currently Selected Model: Osaka");
  ImGui::Text("Position");
  static ImGuiSliderFlags flags = ImGuiSliderFlags_None;
  static float drag_f = 0.5f;
  ImGui::DragFloat("X", &drag_f, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
  ImGui::DragFloat("Y", &drag_f, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
  ImGui::DragFloat("Z", &drag_f, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);

  ImGui::Text("Rotation");
  ImGui::DragFloat("X", &drag_f, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
  ImGui::DragFloat("Y", &drag_f, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
  ImGui::DragFloat("Z", &drag_f, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);

  ImGui::Text("Scale");
  ImGui::DragFloat("X", &drag_f, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
  ImGui::DragFloat("Y", &drag_f, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
  ImGui::DragFloat("Z", &drag_f, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);

  /*ImGui::Text("Current Selected Model: %s", currentSelected.m_modelName.c_str());*/
  /**/
  /*ImGui::Text("Total Model In Scene: %lu", ModelsInScene.size());*/

  ImGui::End();
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
