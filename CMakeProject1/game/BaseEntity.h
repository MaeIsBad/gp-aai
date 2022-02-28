#pragma once
#include <vector>
#include <SDL.h>
#include "../Vector2D.h"
#include "World.h"

class BaseEntity {

private:
   Vector2D& position;
   World& world;
   double radius;

public:
   BaseEntity(Vector2D& p, World& w);
   void update(float delta);
   void render(SDL_Renderer* renderer);

};
