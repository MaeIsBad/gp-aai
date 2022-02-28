#pragma once
#include "BaseEntity.h"

BaseEntity::BaseEntity(Vector2D& p, World& w) {
   this->position = p;
   this->world = w;
}


void BaseEntity::update(float delta) {}


void BaseEntity::render(SDL_Renderer* renderer) {
   //TODO: Draw a triangle
}
