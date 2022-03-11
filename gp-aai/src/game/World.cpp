#include "World.h"
#include <vector>
#include "BaseEntity.h"
#include "MovingEntity.h"
#include <iostream>

using std::cout, std::endl, std::shared_ptr;

World::World(int w, int h) : width(w), height(h) {
    this->entities.push_back(shared_ptr<BaseEntity>(new BaseEntity(Vector2D(100, 100), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new BaseEntity(Vector2D(200, 100), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new MovingEntity(Vector2D(100, 200), *this, Vector2D(0, 0), 0, 0)));
    this->entities.push_back(shared_ptr<BaseEntity>(new BaseEntity(Vector2D(200, 200), *this)));
}

void World::update(float delta) {
    for(auto entity: this->entities) {
        entity->update(delta);
    }
}

void World::render(SDL_Renderer* renderer){
    for(auto entity: this->entities) {
        entity->render(renderer);
    }
}
