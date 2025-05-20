#include <GL/glut.h>
#include <cmath>

enum {};
void drawSky() {
    glBegin(GL_QUADS);
    glColor3f(0.529f, 0.808f, 0.922f);  // Sky blue
    glVertex2f(-1.0f, 1.0f);    
    glVertex2f(1.0f, 1.0f);     
    glVertex2f(1.0f, -1.0f);    
    glVertex2f(-1.0f, -1.0f);   
    glEnd();
}


void drawHill(float cx, float baseY, float rx, float height, float r, float g, float b) {
    const int segments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b);
    glVertex2f(cx, baseY);
    for (int i = 0; i <= segments; ++i) {
        float t = i / (float)segments;
        float angle = (t - 0.5f) * 2.0f;  // -1..1
        float x = cx + rx * angle;
        float y = baseY + height * (1.0f - angle * angle);
        glColor3f(r * 0.9f + 0.05f, g * 0.9f + 0.05f, b * 0.9f + 0.05f);
        glVertex2f(x, y);
    }
    glEnd();
}

