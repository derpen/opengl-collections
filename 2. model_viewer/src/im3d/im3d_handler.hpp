#pragma once

#include "../shaders/shader.h"

namespace Im3dHandler {

static unsigned int s_Im3dVertexArray;
static unsigned int s_Im3dVertexBuffer;
static Shader s_Im3dShaderPoints;
static Shader s_Im3dShaderLines;
static Shader s_Im3dShaderTriangles;

bool Im3d_Init();
void Im3d_Shutdown();
void Im3d_NewFrame();
void Im3d_EndFrame();

}
