#include "Shapes.h"
#include "Sky.h"
#include "Windmill.h"
#include "Background.h"
#include "NightBackground.h"

#include <cstring>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define PI 3.14159265

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

float cloudPositionXleft = -0.4f;
float cloudPositionYleft = 0.7f;
float cloudPositionXright = 0.5f;
float cloudPositionYright = 0.55f;
float cloudSpeed = 0.0001f;
float minX = -1.2f;
float maxX = 1.2f;

float windmillAngle1 = 0.0f;
float windmillSpeed1 = 0.01f;

float windmillAngle2 = 0.3f;
float windmillSpeed2 = 0.05f;

bool isNight = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        float delta = 0.05f;  // Increase/Decrease amount
        float cloudDelta = 0.0002f;

        if (key == GLFW_KEY_UP) {
            windmillSpeed1 = std::min(windmillSpeed1 + delta, 1.1f);
            windmillSpeed2 = std::min(windmillSpeed2 + delta, 1.1f);
            cloudSpeed = std::min(cloudSpeed + cloudDelta, 0.003f);
        }
        else if (key == GLFW_KEY_DOWN) {
            windmillSpeed1 = std::max(windmillSpeed1 - delta, 0.1f);
            windmillSpeed2 = std::max(windmillSpeed2 - delta, 0.1f);
            cloudSpeed = std::max(cloudSpeed - cloudDelta, 0.0003f);
        }
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        float xNorm = (float)xpos / WINDOW_WIDTH * 2.0f - 1.0f;
        float yNorm = -((float)ypos / WINDOW_HEIGHT * 2.0f - 1.0f);

        if (xNorm >= 0.9f && xNorm <= 0.95f && yNorm >= -0.9f && yNorm <= -0.4f) {
            float t = (yNorm + 0.9f) / 0.5f;
            t = std::max(0.0f, std::min(t, 1.0f));

            windmillSpeed1 = 0.1f + t;
            windmillSpeed2 = 0.1f + t * (1.1f - 0.1f);
            cloudSpeed = 0.0003f + t * 0.002f;
        }

        if (xNorm >= -0.95f && xNorm <= -0.75f && yNorm >= -0.95f && yNorm <= -0.85f) {
            isNight = !isNight;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (!isNight) {
        drawSky();
        drawSun(0.7f, 0.74f);
        drawCloud(1.0f, 1.0f, 1.0f, cloudPositionXleft, cloudPositionYleft);
        drawCloud(1.0f, 1.0f, 1.0f, cloudPositionXright, cloudPositionYright);
        drawHill(-0.3f, -1.0f, 1.0f, 0.5f, 0.0f, 0.65f, 0.0f);
        drawHill(0.5f, -1.0f, 1.2f, 0.6f, 0.0f, 0.55f, 0.0f);
    }
    else {
        drawNightSky();
        drawMoon(0.7f, 0.74f);
        drawStars();
        drawCloud(0.5f, 0.5f, 0.5f, cloudPositionXright, cloudPositionYright);
        drawCloud(0.5f, 0.5f, 0.5f, cloudPositionXleft, cloudPositionYleft);
        drawHill(-0.3f, -1.0f, 1.0f, 0.5f, 0.0f, 0.39f, 0.0f);
        drawHill(0.5f, -1.0f, 1.2f, 0.6f, 0.0f, 0.2f, 0.0f);
    }

    // Windmills
    glPushMatrix();
    drawWindmill(-0.5f, 0.0f, windmillAngle1);
    glPopMatrix();

    glPushMatrix();
    drawWindmill(0.2f, -0.2f, windmillAngle2);
    glPopMatrix();

    windmillAngle1 += windmillSpeed1;
    if (windmillAngle1 > 360.0f) windmillAngle1 -= 360.0f;

    windmillAngle2 += windmillSpeed2;
    if (windmillAngle2 > 360.0f) windmillAngle2 -= 360.0f;

    // cloud movements
    cloudPositionXleft += cloudSpeed;
    cloudPositionXright += cloudSpeed;

    if (cloudPositionXleft > maxX)
        cloudPositionXleft = minX;
    if (cloudPositionXright > maxX)
        cloudPositionXright = minX;

    // Scroll bar
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(0.9f, -0.9f);
    glVertex2f(0.95f, -0.9f);
    glVertex2f(0.95f, -0.4f);
    glVertex2f(0.9f, -0.4f);
    glEnd();

    float clampedSpeed = std::max(0.1f, std::min(windmillSpeed1, 1.1f));
    float t = (clampedSpeed - 0.1f) / (1.1f - 0.1f);
    float handleCenterY = -0.9f + t * 0.5f;

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.9f, handleCenterY - 0.03f);
    glVertex2f(0.95f, handleCenterY - 0.03f);
    glVertex2f(0.95f, handleCenterY + 0.03f);
    glVertex2f(0.9f, handleCenterY + 0.03f);
    glEnd();

    // Scroll bar min/max labels
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(0.85f, -0.91f);
    const char* minLabel = "0.01";
    for (int i = 0; minLabel[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, minLabel[i]);

    glRasterPos2f(0.85f, -0.42f);
    const char* maxLabel = "1";
    for (int i = 0; maxLabel[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, maxLabel[i]);

    // Day-Night
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.95f, -0.95f);
    glVertex2f(-0.75f, -0.95f);
    glVertex2f(-0.75f, -0.85f);
    glVertex2f(-0.95f, -0.85f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.93f, -0.91f);
    const char* label = isNight ? "Change to Day" : "Change to Night";
    int len = strlen(label);
    for (int i = 0; i < len; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[i]);
    }

    glFlush();
}

int main() {
    int dummyArgc = 1;
    char* dummyArgv[] = { (char*)"app" };
    glutInit(&dummyArgc, dummyArgv);

    srand(0);

    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OPENGL Project group 10", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);  


    initStars();

    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
