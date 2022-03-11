#pragma once

class Vector2D {

public:
    double x, y;

    Vector2D(double x, double y);
    Vector2D(const Vector2D& v);
    Vector2D();
    ~Vector2D();
    Vector2D& operator+ (const Vector2D& v);
    Vector2D& operator= (const Vector2D& v);
};
