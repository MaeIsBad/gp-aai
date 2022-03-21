#pragma once
#include "Color.h"
#include "Vector2D.h"
#include <SDL.h>
#include <cmath>
#include <iostream>
#include <vector>

using std::cout, std::endl, std::vector;

class Shape {
    protected:
        Color color;
        
    public:
        Shape(Color co);
        virtual void draw(Vector2D& transform, Vector2D& translate, SDL_Renderer* renderer);
        virtual ~Shape();

        virtual void setColor(Color co);
        Color getColor();
};

class Line : public Shape {
    public:
        Vector2D start, end;

        Line(Vector2D s, Vector2D e, Color c);
        ~Line();

        void draw(Vector2D& transform, Vector2D& translate, SDL_Renderer* renderer) override;
};

class Circle : public Shape {
    private:
        double _da;
        vector<Shape*> shapes;
        double radius;
        int sides;
        Vector2D center;

        void updateLines();

    public:
        Circle(Vector2D c, double r, int s, Color co);
        Circle(Vector2D c, double r, Color co);
        ~Circle();

        void draw(Vector2D& transform, Vector2D& translate, SDL_Renderer* renderer) override;
        Circle& setCenter(Vector2D center);
        Circle& setRadius(double r);
        Circle& setSides(int s);
        void setColor(Color co) override;
};
