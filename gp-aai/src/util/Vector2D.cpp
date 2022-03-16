#include "Vector2D.h"
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using std::cout, std::endl, std::string, std::ostream, std::to_string;

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

Vector2D::Vector2D(const Vector2D& v) : Vector2D(v.x, v.y) {}

Vector2D::Vector2D() : Vector2D(0, 0) {}
Vector2D::~Vector2D() {}

double Vector2D::length() {
    return sqrt(x*x + y*y);
}

Vector2D Vector2D::normalize() {
    Vector2D v = Vector2D(*this);
    double length = v.length();
    if (length != 0) 
        v = v / length;
    return v;
}

Vector2D Vector2D::truncate(double max) {
    Vector2D v = Vector2D(*this);
    if (length() > max) 
        v = v.normalize() * max;
    
    return v;
}

string Vector2D::toString() const {
    return string("Vector2D(" + to_string(this->x) + ", " + to_string(this->y) + ")");
}

Vector2D& Vector2D::operator= (const Vector2D& v) {
    this->x = v.x;
    this->y = v.y;
    return *this;
}

Vector2D operator+ (const Vector2D& v, const Vector2D& v2) {
    return Vector2D(
        v.x + v2.x,
        v.y + v2.y
    );
}

Vector2D operator- (const Vector2D& v, const Vector2D& v2) {
    return Vector2D(
        v.x - v2.x,
        v.y - v2.y
    );
}

Vector2D operator* (const Vector2D& v, const Vector2D& v2) {
    return Vector2D(
        v.x * v2.x,
        v.y * v2.y
    );
}

Vector2D operator/ (const Vector2D& v, const Vector2D& v2) {
    return Vector2D(
        v.x / v2.x,
        v.y / v2.y
    );
}

Vector2D operator* (double v, const Vector2D& v2) {
    return Vector2D(
        v2.x * v,
        v2.y * v
    );
}

Vector2D operator/ (double v, const Vector2D& v2) {
    return v2 * (1 / v);
}

Vector2D operator* (const Vector2D& v, double v2) {
    return v2 * v;
}

Vector2D operator/ (const Vector2D& v, double v2) {
    return v2 / v;
}

ostream& operator<< (ostream& o, const Vector2D& v) {
    return o << v.toString();
}
