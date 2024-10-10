#ifndef SHAPE_VERTICES_H
#define SHAPE_VERTICES_H
#include <stdio.h>

extern float vertices[];  // Vertex data
extern unsigned int indices[];  // Index data
extern size_t vertexCount;
extern size_t vertexSize;
extern size_t indexSize;

extern float verticesNoEBO[];
extern size_t vertexNOEBOSize;

#endif
