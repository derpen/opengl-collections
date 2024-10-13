#include "imgui_debug.h"
#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../../vendor/imgui/backends/imgui_impl_opengl3.h"

IMGUI_DEBUG::IMGUI_DEBUG(){};

void IMGUI_DEBUG::imguiInit(GLFWwindow* window){
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOther(window, true);
  ImGui_ImplOpenGL3_Init();
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
