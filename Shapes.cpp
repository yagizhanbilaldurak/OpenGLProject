#include "Shapes.h"

#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define PI 3.14159265 

// circle func for sun
void drawCircle(float cx, float cy, float r, float red, float green, float blue, float alpha) {
    glColor4f(red, green, blue, alpha);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; ++i) {
        float angle = 2 * 3.14159f * i / 100;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}


void drawTriangle(float x, float y, float size, float angle) {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {       
        float theta = angle + i * 2.0f * 3.14159f / 3.0f;  
        glVertex2f(x + cos(theta) * size, y + sin(theta) * size);
    }
    glEnd();
}

// windmill center circle
void drawStaticCircle() {
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);  
    for (int i = 0; i < 100; i++) {
        float angle = 2 * PI * i / 100;
        glVertex2f(0.05f * cos(angle), 0.05f * sin(angle)); 
    }
    glEnd();
}