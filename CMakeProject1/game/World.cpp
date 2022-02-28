#pragma once
#include "World.h"
#include <vector>

//using namespace World;

World::World(int w, int h) {
   this->width = w;
   this->height = h;
}

void World::update(float delta) {

}

void World::render(SDL_Renderer* renderer){
   for(int entity: this->entities) {
      //entity.Render(renderer);
   }
}
