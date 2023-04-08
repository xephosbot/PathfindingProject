#ifndef PATHFINDING_DRAWER_H
#define PATHFINDING_DRAWER_H

#include <GLFW/glfw3.h>
#include "color.h"

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

const float MAX_RENDER_RANGE = 2.0f;

const color WHITE = color(0xFFFFFFFF);
const color BLACK = color(0x000000FF);
const color TRANSPARENT = color(0x00000000);
const color RED = color(0xFF0000FF);
const color GREEN = color(0x8BAD84FF);
const color BLUE = color(0x0000FFFF);
const color BEIGE = color(0xCBBFB2FF);
const color PURPLE = color(0xBF3FAAFF);
const color GRAY = color(0x858579FF);

void drawQuad(float originX, float originY, float sizeX, float sizeY, color col, bool centered = true);

float remap(float value, float low1, float high1, float low2, float high2);

#endif //PATHFINDING_DRAWER_H