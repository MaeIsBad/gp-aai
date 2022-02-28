#pragma once

class Vector2D {

public:
    double x, y;

    Vector2D(double x, double y);
    Vector2D& operator+ (Vector2D v);
};
