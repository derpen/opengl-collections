#pragma once

#include "opengl_config.hpp"

// Main loop will be put here
namespace OpenGLLoop {
extern float g_DeltaTime;
extern float g_LastFrame;
extern int g_lastIndex;

void mainLoop();
void shutdown();
void processInput(GLFWwindow* window);

}
