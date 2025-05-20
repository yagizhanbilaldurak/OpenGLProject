#include "NightBackground.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdlib>
#include <ctime>
#include "Shapes.h"

const int STAR_COUNT = 100;
float starX[STAR_COUNT];
float starY[STAR_COUNT];

void drawNightSky() {
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.2f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void drawMoon(float x, float y) {
    float radius = 0.12f;
    drawCircle(x, y, radius, 0.85f, 0.85f, 0.85f);
    glColor4f(0.1f, 0.1f, 0.1f, 0.4f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 100; ++i) {
        float angle = 3.14159f * i / 100.0f;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
    drawCircle(x - 0.03f, y + 0.02f, 0.008f, 0.7f, 0.7f, 0.7f);
    drawCircle(x + 0.04f, y - 0.025f, 0.006f, 0.65f, 0.65f, 0.65f);
    drawCircle(x - 0.02f, y - 0.04f, 0.0055f, 0.75f, 0.75f, 0.75f);
}

void initStars() {
    srand((unsigned int)time(0));
    for (int i = 0; i < STAR_COUNT; ++i) {
        starX[i] = -1.0f + static_cast<float>(rand()) / RAND_MAX * 2.0f;
        starY[i] = 0.0f + static_cast<float>(rand()) / RAND_MAX;
    }
}

void drawStars() {
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 0.8f);
    for (int i = 0; i < STAR_COUNT; ++i) {
        glVertex2f(starX[i], starY[i]);
    }
    glEnd();
}
