#include "im3d_handler.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>
#include "../../vendor/im3d/im3d.h"
#include "../../vendor/im3d/im3d_math.h"
#include "../shaders/shader.h"
#include "../OpenGL/opengl_main.hpp"
#include "../OpenGL/opengl_config.hpp"
#include "../../vendor/imgui/imgui.h"
#include "../utils/math/math.hpp"
#include "../Scene/scene.hpp"

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

	ad.m_deltaTime     = OpenGLLoop::g_DeltaTime;
	ad.m_viewportSize  = Im3d::Vec2(OpenGLConfig::conf.m_width, OpenGLConfig::conf.m_height);
  glm::vec3 camPos = OpenGLConfig::cameraClass.Position;
	ad.m_viewOrigin    = Im3d::Vec3(camPos.x, camPos.y, camPos.z); // for VR use the head position
  glm::vec3 camDir = OpenGLConfig::cameraClass.Front;
	ad.m_viewDirection = Im3d::Vec3(camDir.x, camDir.y, camDir.z);
	ad.m_worldUp       = Im3d::Vec3(0.0f, 1.0f, 0.0f); // used internally for generating orthonormal bases
	ad.m_projOrtho     = false; // <------------- TODO: this one can be set as always false
	// m_projScaleY controls how gizmos are scaled in world space to maintain a constant screen height
	ad.m_projScaleY = tanf(glm::radians(OpenGLConfig::cameraClass.cameraFOV) * 0.5f) * 2.0f; // or vertical fov for a perspective projection

	// World space cursor ray from mouse position; for VR this might be the position/orientation of the HMD or a tracked controller.
  Im3d::Vec2 cursorPos = Im3d::Vec2(OpenGLConfig::lastX, OpenGLConfig::lastY);
	cursorPos.x = (cursorPos.x / ad.m_viewportSize.x) * 2.0f - 1.0f;
	cursorPos.y = (cursorPos.y / ad.m_viewportSize.y) * 2.0f - 1.0f;
	cursorPos.y = -cursorPos.y; // window origin is top-left, ndc is bottom-left

  // Old code for raycasting
  /*Im3d::Vec3 rayOrigin, rayDirection;*/
  /*rayOrigin = ad.m_viewOrigin;*/

  glm::mat4 currentProjMatrix = OpenGLConfig::cameraClass.GetProjMatrix();

  //Convert to Im3d Mat4, courtesy of OpenAI ChatGPT
  Im3d::Mat4 projMatrix;
  for (int col = 0; col < 4; col++) {
      for (int row = 0; row < 4; row++) {
          projMatrix(col, row) = currentProjMatrix[col][row]; // Column-major order
      }
  }

  /*rayDirection.x  = cursorPos.x / projMatrix(0, 0);*/
  /*rayDirection.y  = cursorPos.y / projMatrix(1, 1);*/
  /*rayDirection.z  = 1.0f;*/

  glm::mat4 currentViewMatrix = OpenGLConfig::cameraClass.GetViewMatrix();

  //Convert to Im3d Mat4, courtesy of OpenAI ChatGPT
  Im3d::Mat4 viewMatrix;
  for (int col = 0; col < 4; col++) {
      for (int row = 0; row < 4; row++) {
          viewMatrix(col, row) = currentViewMatrix[col][row]; // Column-major order
      }
  }

	/* Im3d::Mat4 camWorld = Im3d::Inverse(viewMatrix);*/
	/* rayDirection    = camWorld * Im3d::Vec4(Normalize(rayDirection), 0.0f);*/
	/*ad.m_cursorRayOrigin = rayOrigin;*/
	/*ad.m_cursorRayDirection = rayDirection;*/

  glm::vec3 mouseRay = GetMouseRay(OpenGLConfig::cameraClass.GetProjMatrix(), OpenGLConfig::cameraClass.GetViewMatrix(), OpenGLConfig::conf.m_width, OpenGLConfig::conf.m_height, OpenGLConfig::lastX, OpenGLConfig::lastY);
	ad.m_cursorRayOrigin = { camPos.x, camPos.y, camPos.z };
	ad.m_cursorRayDirection = {mouseRay.x, mouseRay.y, mouseRay.z};

	// Set cull frustum planes. This is only required if IM3D_CULL_GIZMOS or IM3D_CULL_PRIMTIIVES is enable via
	// im3d_config.h, or if any of the IsVisible() functions are called.
  Im3dHandler::s_camViewProj = projMatrix * viewMatrix;
  s_camViewProjGLM = currentProjMatrix * currentViewMatrix;
	/*ad.setCullFrustum(Im3dHandler::s_camViewProj, true);*/

	// Fill the key state array; using GetAsyncKeyState here but this could equally well be done via the window proc.
	// All key states have an equivalent (and more descriptive) 'Action_' enum.
	ad.m_keyDown[Im3d::Mouse_Left] = OpenGLConfig::Input.GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT);
	/*ad.m_keyDown[Im3d::Mouse_Left] = glfwGetKey(OpenGLConfig::g_Window, GLFW_KEY_X) == GLFW_PRESS; */

	// The following key states control which gizmo to use for the generic Gizmo() function. Here using the left ctrl
	// key as an additional predicate.
	bool ctrlDown = glfwGetKey(OpenGLConfig::g_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
	/*ad.m_keyDown[Im3d::Key_L] = ctrlDown && glfwGetKey(OpenGLConfig::g_Window, GLFW_KEY_L) == GLFW_PRESS;*/
	/*ad.m_keyDown[Im3d::Key_T] = ctrlDown && glfwGetKey(OpenGLConfig::g_Window, GLFW_KEY_T) == GLFW_PRESS;*/
	/*ad.m_keyDown[Im3d::Key_R] = ctrlDown && glfwGetKey(OpenGLConfig::g_Window, GLFW_KEY_R) == GLFW_PRESS;*/
	/*ad.m_keyDown[Im3d::Key_S] = ctrlDown && glfwGetKey(OpenGLConfig::g_Window, GLFW_KEY_S) == GLFW_PRESS;*/

	// Enable gizmo snapping by setting the translation/rotation/scale increments to be > 0
	ad.m_snapTranslation = ctrlDown ? 0.5f : 0.0f;
	ad.m_snapRotation    = ctrlDown ? Im3d::Radians(30.0f) : 0.0f;
	ad.m_snapScale       = ctrlDown ? 0.5f : 0.0f;

	Im3d::NewFrame();

  //TODO Handle the transform here and hand data to the appdata or whatever
  // TODO: dont know what this does
  Im3d::Context& ctx = Im3d::GetContext();
  ctx.m_gizmoHeightPixels = 150;
  ctx.m_gizmoSizePixels = 6;
  // Always global transform
  ctx.m_gizmoLocal = false;
  // unknown code over

  // TODO: input system to handle keyboard input
  if(glfwGetKey(OpenGLConfig::g_Window, GLFW_KEY_Q) == GLFW_PRESS){
    ctx.m_gizmoMode = Im3d::GizmoMode::GizmoMode_Translation;
  }
  else if(glfwGetKey(OpenGLConfig::g_Window, GLFW_KEY_W) == GLFW_PRESS && !OpenGLConfig::Input.GetMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT)){
    ctx.m_gizmoMode = Im3d::GizmoMode::GizmoMode_Scale;
  }
  else if(glfwGetKey(OpenGLConfig::g_Window, GLFW_KEY_E) == GLFW_PRESS){
    ctx.m_gizmoMode = Im3d::GizmoMode::GizmoMode_Rotation;
  }

  if(Scene::g_IsSelecting){
    // TODO HANDLE THIS THING PROPERLY MAN
    glm::mat4 object_transform = Scene::g_ModelList[Scene::g_SelectedObjectIndex].GetModelMatrix();
    s_GizmoTransform = glmMat4ToIm3dMat4(object_transform);
    s_GizmoInUse = Im3d::Gizmo("GizmoUnified", s_GizmoTransform);

    if(s_GizmoInUse){
      Im3d::Vec3 pos = s_GizmoTransform.getTranslation();
      Im3d::Vec3 rot = Im3d::ToEulerXYZ(s_GizmoTransform.getRotation());
      Im3d::Vec3 sca = s_GizmoTransform.getScale();

      //TODO: Use the transform here to edit this gizmo transform.
      Transform newTransform;
      newTransform.position = glm::vec3(pos.x, pos.y, pos.z);
      newTransform.rotation = glm::vec3(rot.x, rot.y, rot.z);
      newTransform.scale = glm::vec3(sca.x, sca.y, sca.z);

      Scene::g_ModelList[Scene::g_SelectedObjectIndex].SetModelTransform(newTransform);
      /*s_GizmoTransform = glmMat4ToIm3dMat4(Scene::g_ModelList[Scene::g_SelectedObjectIndex].GetModelMatrix());*/
    }
  }
}

void Im3dHandler::Im3d_EndFrame(){
  Im3d::EndFrame();

	// Primitive rendering.

	// Typical pipeline state: enable alpha blending, disable depth test and backface culling.
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glViewport(0, 0, (GLsizei)OpenGLConfig::conf.m_width, (GLsizei)OpenGLConfig::conf.m_height); // TODO <-- REMOVE THIS ??

	for (Im3d::U32 i = 0, n = Im3d::GetDrawListCount(); i < n; ++i)
	{
		const Im3d::DrawList& drawList = Im3d::GetDrawLists()[i];

		/*if (drawList.m_layerId == Im3d::MakeId("NamedLayer"))*/
		/*{*/
		/* // The application may group primitives into layers, which can be used to change the draw state (e.g. enable depth testing, use a different shader)*/
		/*}*/

		GLenum prim;
		/*GLuint sh;*/
    Shader* shader;
		switch (drawList.m_primType)
		{
			case Im3d::DrawPrimitive_Points:
				prim = GL_POINTS;
				/*sh = s_Im3dShaderPoints.ShaderID;*/
        shader = &s_Im3dShaderPoints;
				glDisable(GL_CULL_FACE); // points are view-aligned
				break;
			case Im3d::DrawPrimitive_Lines:
				prim = GL_LINES;
				/*sh = s_Im3dShaderLines.ShaderID;*/
        shader = &s_Im3dShaderLines;
				glDisable(GL_CULL_FACE); // lines are view-aligned
				break;
			case Im3d::DrawPrimitive_Triangles:
				prim = GL_TRIANGLES;
				/*sh = s_Im3dShaderTriangles.ShaderID;*/
        shader = &s_Im3dShaderTriangles;
				//glAssert(glEnable(GL_CULL_FACE)); // culling valid for triangles, but optional
				break;
			default:
				IM3D_ASSERT(false);
				return;
		};

		glBindVertexArray(s_Im3dVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, s_Im3dVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)drawList.m_vertexCount * sizeof(Im3d::VertexData), (GLvoid*)drawList.m_vertexData, GL_STREAM_DRAW);

	  /*Im3d::AppData& ad = Im3d::GetAppData();*/
		/*glUseProgram(sh);*/
		/*glUniform2f(glGetUniformLocation(sh, "uViewport"), ad.m_viewportSize.x, ad.m_viewportSize.y);*/
		/*glUniformMatrix4fv(glGetUniformLocation(sh, "uViewProjMatrix"), 1, false, (const GLfloat*)Im3dHandler::s_camViewProj);*/

    shader->use();
    shader->setVec2("uViewport", glm::vec2(OpenGLConfig::conf.m_width, OpenGLConfig::conf.m_height));
    shader->setMat4("uViewProjMatrix", Im3dHandler::s_camViewProjGLM);

		glDrawArrays(prim, 0, (GLsizei)drawList.m_vertexCount);
	}
}

glm::mat4 Im3dHandler::im3dMat4toGlmMat4(Im3d::Mat4 transform){
  glm::mat4 glmMat(1.0f); 
  for (int col = 0; col < 4; ++col) {
    for (int row = 0; row < 4; ++row) {
      glmMat[col][row] = transform.m[col * 4 + row];
    }
  }
  return glmMat;
}

Im3d::Mat4 Im3dHandler::glmMat4ToIm3dMat4(glm::mat4 transform){
  Im3d::Mat4 matrix;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      matrix.m[i * 4 + j] = transform[i][j];
    }
  }

  return matrix;
}

glm::vec3 Im3dHandler::GetMouseRay(glm::mat4 projection, glm::mat4 view, int windowWidth, int windowHeight, int mouseX, int mouseY) {
  // Thank you tokyospliff
  // https://github.com/livinamuk/Hell2024/blob/main/Hell2024/Hell2024/src/Editor/Gizmo.hpp#L162
  float x = (2.0f * mouseX) / (float)windowWidth - 1.0f;
  float y = 1.0f - (2.0f * mouseY) / (float)windowHeight;
  float z = 1.0f;
  glm::vec3 ray_nds = glm::vec3(x, y, z);
  glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, ray_nds.z, 1.0f);
  glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;
  ray_eye = glm::vec4(ray_eye.x, ray_eye.y, ray_eye.z, 0.0f);
  glm::vec4 inv_ray_wor = (inverse(view) * ray_eye);
  glm::vec3 ray_wor = glm::vec3(inv_ray_wor.x, inv_ray_wor.y, inv_ray_wor.z);
  ray_wor = normalize(ray_wor);
  return ray_wor;
}
