#pragma once
#include <vector>
#include <SDL.h>
#include "../Vector2D.h"
#include "World.h"

class BaseEntity {

protected:
    Vector2D position;
    World& world;
    double radius;

public:
    BaseEntity(Vector2D p, World& w);
    virtual void update(float delta);
    virtual void render(SDL_Renderer* renderer);

};
