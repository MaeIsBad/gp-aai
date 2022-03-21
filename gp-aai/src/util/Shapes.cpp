#include "Shapes.h"
#include <SDL.h>

using std::cout, std::endl, std::vector;

void Shape::draw(Vector2D& transform, Vector2D& translate, SDL_Renderer* renderer) {}
Shape::Shape(Color c) : color(c) {}
Shape::~Shape() {}
void Shape::setColor(Color c) {
    this->color = c;
}
Color Shape::getColor() {
    return this->color;
}

Line::Line(Vector2D s, Vector2D e, Color c) : Shape(c), start(s), end(e) {}
Line::~Line() {}

void Line::draw(Vector2D& transform, Vector2D& translate, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, SDL_ALPHA_OPAQUE);

    // Apply viewport transform
    Vector2D new_start = start * transform + (translate),
             new_end = end * transform + (translate);

    SDL_RenderDrawLine(renderer, new_start.x, new_start.y, new_end.x, new_end.y);
}

void Circle::updateLines() {
    for(auto shape: this->shapes) {
        delete shape;
    }
    shapes = vector<Shape*>();

    float angle = this->_da;
    Vector2D start, end;

    end.x = this->radius;
    end.y = 0.0f;
    end = end + this->center;
    for (int i=0; i!=this->sides; i++) {
        start = end;
        end.x = cos(angle) * this->radius;
        end.y = sin(angle) * this->radius;
        end = end + center;
        angle += this->_da;

        shapes.push_back(new Line(start, end, this->color));
    }
}

Circle::Circle(Vector2D c, double r, int s, Color co) : Shape(co), center(c), radius(r), sides(s), _da(M_PI * 2 / s)  {
    this->updateLines();
}
Circle::Circle(Vector2D c, double r, Color co) : Circle(c, r, 25, co) {}
Circle::~Circle() {
    for(auto shape: this->shapes) {
        delete shape;
    }
}

void Circle::setColor(Color c) {
    for(auto shape: this->shapes) {
        shape->setColor(c);
    }
}
void Circle::draw(Vector2D& transform, Vector2D& translate, SDL_Renderer* renderer) {
    for(auto shape: shapes){
        shape->draw(transform, translate, renderer);
    }
}
Circle& Circle::setCenter(Vector2D center) {
    this->center = center;
    this->updateLines();
    return *this;
}
Circle& Circle::setRadius(double r) {
    this->radius = r;
    this->updateLines();
    return *this;
}
Circle& Circle::setSides(int s) {
    this->sides = s;
    this->updateLines();
    return *this;
}
