#include "Sky.h"
#include "Shapes.h"

#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define PI 3.14159265

// circle for sun
void Circle(float cx, float cy, float r, float red, float green, float blue, float alpha = 1.0f) {
    glColor4f(red, green, blue, alpha);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; ++i) {
        float angle = 2 * PI * i / 100;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}


void drawCloud(float r,float g,float b,float x, float y) {
    static int patternIndex = 0;
    static time_t lastChangeTime = 0;

    const float scale = 0.8f;  

    // x offset, y offset, radius
    const float patterns[3][8][3] = {
        { { -0.12f, 0.00f, 0.09f }, { -0.06f, 0.03f, 0.10f }, { 0.00f, 0.00f, 0.11f },
          { 0.06f, 0.03f, 0.10f }, { 0.12f, 0.00f, 0.09f }, { -0.03f, -0.04f, 0.08f },
          { 0.03f, -0.04f, 0.08f }, { 0.00f, 0.05f, 0.07f } },

        { { -0.10f, 0.01f, 0.08f }, { -0.05f, 0.04f, 0.10f }, { 0.00f, 0.01f, 0.11f },
          { 0.05f, 0.04f, 0.10f }, { 0.10f, 0.01f, 0.08f }, { -0.02f, -0.04f, 0.09f },
          { 0.02f, -0.04f, 0.09f }, { 0.00f, 0.06f, 0.06f } },

        { { -0.11f, 0.00f, 0.10f }, { -0.07f, 0.02f, 0.09f }, { -0.03f, -0.01f, 0.08f },
          { 0.03f, 0.01f, 0.08f }, { 0.07f, 0.02f, 0.09f }, { 0.11f, 0.00f, 0.10f },
          { 0.00f, -0.05f, 0.07f }, { 0.00f, 0.05f, 0.07f } }
    };

    // time control, pattern changes every 8 second
    time_t currentTime = time(NULL);
    if (currentTime - lastChangeTime >= 8) {
        patternIndex = (patternIndex + 1) % 3;
        lastChangeTime = currentTime;
    }

    // x ,cloudscale, alpha (transparency
    const float cloudOffsets[3][4] = {
        { x - 0.5f, y + 0.1f, 0.8f, 0.4f },  
        { x + 0.3f, y + 0.05f, 1.0f, 0.6f }, 
        { x, y, 1.2f, 1.0f }                 
    };

    // 3 different clouds
    for (int c = 0; c < 3; c++) {
        float cx = cloudOffsets[c][0];
        float cy = cloudOffsets[c][1];
        float cloudScale = cloudOffsets[c][2] * scale;
        float alpha = cloudOffsets[c][3];
        // circles if the clouds
        for (int i = 0; i < 8; i++) {
            float offsetX = patterns[patternIndex][i][0] * cloudScale;
            float offsetY = patterns[patternIndex][i][1] * cloudScale;
            float radius = patterns[patternIndex][i][2] * cloudScale;
            drawCircle(cx + offsetX, cy + offsetY, radius, r, g, b, alpha);
        }
    }
}



void drawSun(float x, float y) {
    
    float r = 1.0f;
    float g = 1.0f;
    float b = 0.0f;

    // light effect
    drawCircle(x, y, 0.05f, r, g, b);  
    drawCircle(x, y, 0.12f, r, g, b, 0.3f);  
    drawCircle(x, y, 0.15f, r, g, b, 0.1f);  
}


