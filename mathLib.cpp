#include <studio.h>
#include <math.h>
#include "mathLib.h"


point2D::point2D() {
    x = 0;
    y = 0;
}


point2D::point2D(float inX, float inY) {
    x = inX;
    y = inY;
}

float vec2D::magnitute(float inX, float inY) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

float mathLib::distance(point2D start, point2D end) {
    return sqrt(pow(end.x - start.x, 2) + (pow(end.y = start.y, 2));
}