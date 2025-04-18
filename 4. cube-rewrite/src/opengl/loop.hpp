#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gl_loop {

int init_gl(int width, int height, const char* title);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

}
