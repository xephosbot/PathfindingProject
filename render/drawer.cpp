#include "drawer.h"

void drawQuad(float originX, float originY, float sizeX, float sizeY, color col, bool centered) {
    glBegin(GL_QUADS);
    glColor4f(col.r, col.g, col.b, col.a);
    if (centered) {
        glVertex2f(originX - sizeX / 2, originY - sizeY / 2);
        glVertex2f(originX - sizeX / 2, originY + sizeY / 2);
        glVertex2f(originX + sizeX / 2, originY + sizeY / 2);
        glVertex2f(originX + sizeX / 2, originY - sizeY / 2);
    } else {
        glVertex2f(originX, originY);
        glVertex2f(originX, originY + sizeY);
        glVertex2f(originX + sizeX, originY + sizeY);
        glVertex2f(originX + sizeX, originY);
    }
    glEnd();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

float remap(float value, float low1, float high1, float low2, float high2) {
    return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}
