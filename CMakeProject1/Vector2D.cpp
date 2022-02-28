#pragma once
#include "Vector2D.h"

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::operator+ (Vector2D v) {
    this->x += v.x;
    this->y += v.y;
    return this;
}
