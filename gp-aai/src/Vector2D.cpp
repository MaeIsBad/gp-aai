#include "Vector2D.h"
#include <iostream>

using std::cout, std::endl;

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

Vector2D::Vector2D(const Vector2D& v) : Vector2D(v.x, v.y) {}

Vector2D::Vector2D() : Vector2D(0, 0) {}
Vector2D::~Vector2D() {}

Vector2D& Vector2D::operator+ (const Vector2D& v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}
Vector2D& Vector2D::operator= (const Vector2D& v) {
    this->x = v.x;
    this->y = v.y;
    return *this;
}
