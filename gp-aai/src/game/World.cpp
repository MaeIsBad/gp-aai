#include "../util/Shapes.h"
#include "../util/VectorMath.hpp"
#include "Astar.h"
#include "BaseEntity.h"
#include "MovingEntity.h"
#include "World.h"
#include <SDL.h>
#include <iostream>
#include <random>
#include <vector>

#include <csignal>

#define WORLD_GRAPH_DENSITY 10

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

    //for(int i=-this->width/2; i<this->width/2; i+=WORLD_GRAPH_DENSITY) {
    //    for(int o=-this->height/2; o<this->height/2; o+=WORLD_GRAPH_DENSITY) {
    //        this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree", Vector2D(i, o), *this)));
    //    }
    //}
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 1", Vector2D(-100, -100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 2", Vector2D(100, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 3", Vector2D(-100, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 4", Vector2D(100, -100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 5", Vector2D(220, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 6", Vector2D(230, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 7", Vector2D(240, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 8", Vector2D(240, 110), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 9", Vector2D(250, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 10", Vector2D(190, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 11", Vector2D(180, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 12", Vector2D(170, 100), *this)));
    //this->entities.push_back(shared_ptr<BaseEntity>(new TreeEntity("Tree 13", Vector2D(70, 60), *this)));

    cout << "--" << endl;
    this->generateGraph();

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
    pos = pos * this->transform - (this->transform * this->translate);
    this->seek_pos.setPosition(pos);
}

Vector2D& World::getSeekPosition() {
    return this->seek_pos.getPosition();
}

const vector<shared_ptr<BaseEntity>> World::getEntities() {
    return this->entities;
}

void World::generateGraph() {
    Graph* graph = new Graph();

    for(int x=0; x<this->width; x+=WORLD_GRAPH_DENSITY) {
        for(int y=0; y<this->height; y+=WORLD_GRAPH_DENSITY) {
            Vertex* v = new Vertex(Vector2D(x, y), 0);
            graph->addVertex(v);

            if(x >= WORLD_GRAPH_DENSITY) {
                Vertex* vp = graph->findClosest(Vector2D(x - WORLD_GRAPH_DENSITY, y));
                v->addEdge(Edge { *vp, WORLD_GRAPH_DENSITY });
                vp->addEdge(Edge { *v, WORLD_GRAPH_DENSITY });
            }

            if(y >= WORLD_GRAPH_DENSITY) {
                Vertex* vp = graph->findClosest(Vector2D(x, y - WORLD_GRAPH_DENSITY));
                v->addEdge(Edge { *vp, WORLD_GRAPH_DENSITY });
                vp->addEdge(Edge { *v, WORLD_GRAPH_DENSITY });
            }
        }
    }

    Vertex* end = graph->findClosest(Vector2D(300, 100));
    Vertex* start = graph->findClosest(Vector2D(-300, -200));

    auto result = graph->shortestPath(start, end);
    for(auto vertex : result) {
        cout << "Vertex with position " << vertex->getPosition() << endl;
    }
}
