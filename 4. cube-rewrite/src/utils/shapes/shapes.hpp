#pragma once

namespace shapes {
extern float triangles_vertices[];

extern unsigned int triangle_VAO;
extern unsigned int triangle_VBO;

unsigned int init_triangle();
void clean_up();
}
