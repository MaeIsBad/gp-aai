#include "World.h"
#include <vector>
#include "BaseEntity.h"
#include "MovingEntity.h"
#include <iostream>

using std::cout, std::endl, std::shared_ptr;

World::World(int w, int h) : width(w), height(h), seek_pos(*new PointerEntity(Vector2D(w/2, h/2), *this)) {
    this->entities.push_back(shared_ptr<BaseEntity>(&this->seek_pos));
    this->entities.push_back(shared_ptr<BaseEntity>(new Birb(Vector2D(w/2, h/2), *this)));

    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity(Vector2D(200, 200), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity(Vector2D(100, 100), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity(Vector2D(200, 100), *this)));
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

void World::event(WorldEvent e, Vector2D pos) {
    this->seek_pos.setPosition(pos);
}

Vector2D World::getSeekPosition() {
    return this->seek_pos.getPosition();
}

const vector<shared_ptr<BaseEntity>> World::getEntities() {
    return this->entities;
}
