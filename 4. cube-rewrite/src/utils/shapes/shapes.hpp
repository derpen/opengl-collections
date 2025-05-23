#pragma once

namespace Shapes {
extern float triangles_vertices[];
extern unsigned int triangle_VAO;
extern unsigned int triangle_VBO;
unsigned int init_triangle();

extern float plane_vertices[];
extern unsigned int plane_VAO;
extern unsigned int plane_VBO;
extern unsigned int plane_EBO;
unsigned int init_plane();

extern float cube_vertices[];
extern unsigned int cube_VAO;
extern unsigned int cube_VBO;
unsigned int init_cube();

void clean_up();
}
