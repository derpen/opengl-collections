#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gl_loop {

extern float deltaTime;
extern float lastFrame;

int init_gl(float width, float height, const char* title);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void process_input(GLFWwindow *window);

}
