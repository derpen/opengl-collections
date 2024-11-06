#pragma once

#include "../shaders/shader.h"
#include "../../vendor/im3d/im3d_math.h"

namespace Im3dHandler {

static unsigned int s_Im3dVertexArray;
static unsigned int s_Im3dVertexBuffer;
static Shader s_Im3dShaderPoints;
static Shader s_Im3dShaderLines;
static Shader s_Im3dShaderTriangles;
static Im3d::Mat4 s_camViewProj;

bool Im3d_Init();
void Im3d_Shutdown();
void Im3d_NewFrame();
void Im3d_EndFrame();

}
