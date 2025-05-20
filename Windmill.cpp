#include "Windmill.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// center of the wind blades
void drawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * float(i) / float(segments);
        glVertex2f(x + cosf(angle) * radius, y + sinf(angle) * radius);
    }
    glEnd();
}

void drawBlade(float angle) {
    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.015f, 0.18f);
    glVertex2f(-0.006f, 0.36f);
    glVertex2f(0.006f, 0.36f);
    glVertex2f(0.015f, 0.18f);
    glEnd();

    // red triagnle at the tip of the blades
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.006f, 0.36f);
    glVertex2f(0.0f, 0.41f); 
    glVertex2f(0.006f, 0.36f);
    glEnd();

    glPopMatrix();
}

void drawWindmill(float x, float y, float angle) {
    glPushMatrix();
    glTranslatef(x, y + 0.08f, 0.0f); 

    glColor3f(0.65f, 0.65f, 0.65f); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.02f, -0.75f); 
    glVertex2f(0.02f, -0.75f);
    glVertex2f(0.012f, 0.0f);
    glVertex2f(-0.012f, 0.0f);
    glEnd();

    glColor3f(0.9f, 0.2f, 0.2f); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.018f, -0.52f);
    glVertex2f(0.018f, -0.52f);
    glVertex2f(0.015f, -0.45f);
    glVertex2f(-0.015f, -0.45f);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle(0.0f, 0.0f, 0.025f, 100);

    for (int i = 0; i < 3; i++) {
        drawBlade(angle + i * 120.0f);
    }

    glPopMatrix();
}
