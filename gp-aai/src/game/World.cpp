#include "../util/Shapes.h"
#include "../util/VectorMath.hpp"
#include "BaseEntity.h"
#include "MovingEntity.h"
#include "World.h"
#include <SDL.h>
#include <iostream>
#include <random>
#include <vector>

#include <csignal>

#define breakpoint std::raise(SIGINT)
using std::cout, std::endl, std::shared_ptr;

World::World(int w, int h) : width(w), height(h), seek_pos(*new PointerEntity(Vector2D(0, 0), *this)) {
    this->entities.push_back(shared_ptr<BaseEntity>(&this->seek_pos));
    this->entities.push_back(shared_ptr<BaseEntity>(new Birb(Vector2D(0, 0), *this)));


    this->transform = *new Vector2D(1, -1);
    this->translate = *new Vector2D(this->width/2, this->height/2);

    //std::random_device dev;
    //std::mt19937 rng(dev());
    //std::uniform_int_distribution<std::mt19937::result_type> dist6(0,200);

    //for(int i=0; i<30; i++) {
    //    this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree", Vector2D(dist6(rng), dist6(rng)), *this)));
    //}

    //for(int i=0; i<800/20; i++) {
    //    for(int o=0; o<800/10; o++) {
    //        this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree", Vector2D(o*10, 100), *this)));
    //    }
    //}
    this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 1", Vector2D(-100, -100), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 2", Vector2D(100, 100), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 3", Vector2D(-100, 100), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 4", Vector2D(100, -100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 5", Vector2D(220, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 6", Vector2D(230, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 7", Vector2D(240, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 8", Vector2D(240, 110), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 9", Vector2D(250, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 10", Vector2D(190, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 11", Vector2D(180, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 12", Vector2D(170, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 13", Vector2D(70, 60), *this)));

}

void World::update(float delta) {
    for(auto entity: this->entities) {
        entity->update(delta);
    }
}

void World::render(SDL_Renderer* renderer){
    vector<Shape*> shapes;

    for(auto entity: this->entities) {
        shapes += entity->render();
    }

    //breakpoint;
    // Create viewport transformation vector

    for(auto shape: shapes) {
        shape->draw(this->transform, this->translate, renderer);
    }
}

void World::event(WorldEvent e, Vector2D pos) {
    cout << "Click at " << pos << endl;
    pos = pos * this->transform - (this->transform * this->translate);
    cout << "Click at " << pos << endl;
    this->seek_pos.setPosition(pos);
}

Vector2D& World::getSeekPosition() {
    return this->seek_pos.getPosition();
}

const vector<shared_ptr<BaseEntity>> World::getEntities() {
    return this->entities;
}
