#include "im3d_handler.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../vendor/im3d/im3d.h"
#include "../shaders/shader.h"

bool Im3dHandler::Im3d_Init(){
  s_Im3dShaderPoints = Shader(Shader::POINTS);
  s_Im3dShaderPoints.createShaderProgram("vendor/im3d/im3d.glsl", "vendor/im3d/im3d.glsl");

  s_Im3dShaderLines = Shader(Shader::LINES);
  s_Im3dShaderLines.createShaderProgram("vendor/im3d/im3d.glsl", "vendor/im3d/im3d.glsl", "vendor/im3d/im3d.glsl");

  s_Im3dShaderTriangles = Shader(Shader::TRIANGLES);
  s_Im3dShaderTriangles.createShaderProgram("vendor/im3d/im3d.glsl", "vendor/im3d/im3d.glsl");
  
	glGenBuffers(1, &s_Im3dVertexBuffer);
	glGenVertexArrays(1, &s_Im3dVertexArray);	
	glBindVertexArray(s_Im3dVertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, s_Im3dVertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Im3d::VertexData), (GLvoid*)offsetof(Im3d::VertexData, m_positionSize));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Im3d::VertexData), (GLvoid*)offsetof(Im3d::VertexData, m_color));
	glBindVertexArray(0);

  return true;
}

void Im3dHandler::Im3d_Shutdown(){
	glDeleteVertexArrays(1, &s_Im3dVertexArray);
	glDeleteBuffers(1, &s_Im3dVertexBuffer);

  // TODO, deleteprogram properly
	/*glDeleteProgram(s_Im3dShaderPoints);*/
	/*glDeleteProgram(s_Im3dShaderLines);*/
	/*glDeleteProgram(s_Im3dShaderTriangles);*/
}

void Im3dHandler::Im3d_NewFrame(){
  Im3d::AppData& ad = Im3d::GetAppData();

	/*ad.m_deltaTime     = g_Example->m_deltaTime;*/
	/*ad.m_viewportSize  = Vec2((float)g_Example->m_width, (float)g_Example->m_height);*/
	/*ad.m_viewOrigin    = g_Example->m_camPos; // for VR use the head position*/
	/*ad.m_viewDirection = g_Example->m_camDir;*/
	/*ad.m_worldUp       = Vec3(0.0f, 1.0f, 0.0f); // used internally for generating orthonormal bases*/
	/**/
	/*ad.m_projOrtho     = g_Example->m_camOrtho; // <------------- TODO: this one can be set as always false*/
	/**/
	/*// m_projScaleY controls how gizmos are scaled in world space to maintain a constant screen height*/
	/*ad.m_projScaleY = g_Example->m_camOrtho*/
	/*	? 2.0f / g_Example->m_camProj(1, 1) // use far plane height for an ortho projection*/
	/*	: tanf(g_Example->m_camFovRad * 0.5f) * 2.0f // or vertical fov for a perspective projection*/
	/*	;  */
	/**/
	/*// World space cursor ray from mouse position; for VR this might be the position/orientation of the HMD or a tracked controller.*/
	/*Vec2 cursorPos = g_Example->getWindowRelativeCursor();*/
	/*cursorPos = (cursorPos / ad.m_viewportSize) * 2.0f - 1.0f;*/
	/*cursorPos.y = -cursorPos.y; // window origin is top-left, ndc is bottom-left*/
	/*Vec3 rayOrigin, rayDirection;*/
	/**/
	/*if (g_Example->m_camOrtho)*/
	/*{*/
	/*	rayOrigin.x  = cursorPos.x / g_Example->m_camProj(0, 0);*/
	/*	rayOrigin.y  = cursorPos.y / g_Example->m_camProj(1, 1);*/
	/*	rayOrigin.z  = 0.0f;*/
	/*	rayOrigin    = g_Example->m_camWorld * Vec4(rayOrigin, 1.0f);*/
	/*	rayDirection = g_Example->m_camWorld * Vec4(0.0f, 0.0f, -1.0f, 0.0f);*/
	/**/
	/*}*/
	/*else*/
	/*{*/
	/*	rayOrigin = ad.m_viewOrigin;*/
	/*	rayDirection.x  = cursorPos.x / g_Example->m_camProj(0, 0);*/
	/*	rayDirection.y  = cursorPos.y / g_Example->m_camProj(1, 1);*/
	/*	rayDirection.z  = -1.0f;*/
	/*	rayDirection    = g_Example->m_camWorld * Vec4(Normalize(rayDirection), 0.0f);*/
	/*}*/
	/**/
	/*ad.m_cursorRayOrigin = rayOrigin;*/
	/*ad.m_cursorRayDirection = rayDirection;*/
	/**/
	/*// Set cull frustum planes. This is only required if IM3D_CULL_GIZMOS or IM3D_CULL_PRIMTIIVES is enable via*/
	/*// im3d_config.h, or if any of the IsVisible() functions are called.*/
	/*ad.setCullFrustum(g_Example->m_camViewProj, true);*/
	/**/
	/*// Fill the key state array; using GetAsyncKeyState here but this could equally well be done via the window proc.*/
	/*// All key states have an equivalent (and more descriptive) 'Action_' enum.*/
	/*ad.m_keyDown[Im3d::Mouse_Left] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0; // Im3d::Action_Select*/
	/**/
	/*// The following key states control which gizmo to use for the generic Gizmo() function. Here using the left ctrl*/
	/*// key as an additional predicate.*/
	/*bool ctrlDown = (GetAsyncKeyState(VK_LCONTROL) & 0x8000) != 0;*/
	/*ad.m_keyDown[Im3d::Key_L] = ctrlDown && (GetAsyncKeyState(0x4c) & 0x8000) != 0; // Action_GizmoLocal*/
	/*ad.m_keyDown[Im3d::Key_T] = ctrlDown && (GetAsyncKeyState(0x54) & 0x8000) != 0; // Action_GizmoTranslation*/
	/*ad.m_keyDown[Im3d::Key_R] = ctrlDown && (GetAsyncKeyState(0x52) & 0x8000) != 0; // Action_GizmoRotation*/
	/*ad.m_keyDown[Im3d::Key_S] = ctrlDown && (GetAsyncKeyState(0x53) & 0x8000) != 0; // Action_GizmoScale*/
	/**/
	/*// Enable gizmo snapping by setting the translation/rotation/scale increments to be > 0*/
	/*ad.m_snapTranslation = ctrlDown ? 0.5f : 0.0f;*/
	/*ad.m_snapRotation    = ctrlDown ? Im3d::Radians(30.0f) : 0.0f;*/
	/*ad.m_snapScale       = ctrlDown ? 0.5f : 0.0f;*/

	Im3d::NewFrame();
}

void Im3dHandler::Im3d_EndFrame(){
  Im3d::EndFrame();

	/*// Primitive rendering.*/
	/**/
	/*// Typical pipeline state: enable alpha blending, disable depth test and backface culling.*/
	/*glEnable(GL_BLEND);*/
	/*glBlendEquation(GL_FUNC_ADD);*/
	/*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	/*glEnable(GL_PROGRAM_POINT_SIZE);*/
	/*glDisable(GL_DEPTH_TEST);*/
	/*glDisable(GL_CULL_FACE);*/
	/**/
	/*glViewport(0, 0, (GLsizei)g_Example->m_width, (GLsizei)g_Example->m_height);*/
	/**/
	/*for (Im3d::U32 i = 0, n = Im3d::GetDrawListCount(); i < n; ++i)*/
	/*{*/
	/*	const Im3d::DrawList& drawList = Im3d::GetDrawLists()[i];*/
	/**/
	/*	if (drawList.m_layerId == Im3d::MakeId("NamedLayer"))*/
	/*	{*/
	/*	 // The application may group primitives into layers, which can be used to change the draw state (e.g. enable depth testing, use a different shader)*/
	/*	}*/
	/**/
	/*	GLenum prim;*/
	/*	GLuint sh;*/
	/*	switch (drawList.m_primType)*/
	/*	{*/
	/*		case Im3d::DrawPrimitive_Points:*/
	/*			prim = GL_POINTS;*/
	/*			sh = s_Im3dShaderPoints.ShaderID;*/
	/*			glDisable(GL_CULL_FACE); // points are view-aligned*/
	/*			break;*/
	/*		case Im3d::DrawPrimitive_Lines:*/
	/*			prim = GL_LINES;*/
	/*			sh = s_Im3dShaderLines.ShaderID;*/
	/*			glDisable(GL_CULL_FACE); // lines are view-aligned*/
	/*			break;*/
	/*		case Im3d::DrawPrimitive_Triangles:*/
	/*			prim = GL_TRIANGLES;*/
	/*			sh = s_Im3dShaderTriangles.ShaderID;*/
	/*			//glAssert(glEnable(GL_CULL_FACE)); // culling valid for triangles, but optional*/
	/*			break;*/
	/*		default:*/
	/*			IM3D_ASSERT(false);*/
	/*			return;*/
	/*	};*/
	/**/
	/*	glBindVertexArray(s_Im3dVertexArray);*/
	/*	glBindBuffer(GL_ARRAY_BUFFER, s_Im3dVertexBuffer);*/
	/*	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)drawList.m_vertexCount * sizeof(Im3d::VertexData), (GLvoid*)drawList.m_vertexData, GL_STREAM_DRAW);*/
	/**/
	/*   Im3d::AppData& ad = Im3d::GetAppData();*/
	/*	glUseProgram(sh);*/
	/*	glUniform2f(glGetUniformLocation(sh, "uViewport"), ad.m_viewportSize.x, ad.m_viewportSize.y);*/
	/*	glUniformMatrix4fv(glGetUniformLocation(sh, "uViewProjMatrix"), 1, false, (const GLfloat*)g_Example->m_camViewProj);*/
	/*	glDrawArrays(prim, 0, (GLsizei)drawList.m_vertexCount);*/
	/*}*/
	/**/
	/*// Text rendering. TODO: NOT SURE IF THIS ONE IS NEEDED*/
	/*// This is common to all examples since we're using ImGui to draw the text lists, see im3d_example.cpp.*/
	/*g_Example->drawTextDrawListsImGui(Im3d::GetTextDrawLists(), Im3d::GetTextDrawListCount());*/

}
