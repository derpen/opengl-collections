#pragma once

#include "../shaders/shader.h"
#include "../../vendor/im3d/im3d_math.h"

namespace Im3dHandler {

inline unsigned int s_Im3dVertexArray;
inline unsigned int s_Im3dVertexBuffer;
inline Shader s_Im3dShaderPoints;
inline Shader s_Im3dShaderLines;
inline Shader s_Im3dShaderTriangles;
inline Im3d::Mat4 s_camViewProj;

// TODO: HAVE A CONVERTER INSTEAD OF DOING THIS SHIT
inline glm::mat4 s_camViewProjGLM;

bool Im3d_Init();
void Im3d_Shutdown();
void Im3d_NewFrame();
void Im3d_EndFrame();
void Im3d_DrawTextDrawListsImgui(const Im3d::TextDrawList _textDrawLists[], Im3d::U32 _count);

}
