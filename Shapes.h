#ifndef SHAPES_H
#define SHAPES_H

#include <GLFW/glfw3.h>
#include <GL/glut.h>

void drawCircle(float x, float y, float radius, float r, float g, float b, float alpha = 1.0f);

void drawTriangle(float x, float y, float size, float angle);

void drawStaticCircle();

#endif 