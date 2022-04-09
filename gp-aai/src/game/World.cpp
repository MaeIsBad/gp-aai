#include "../util/Shapes.h"
#include "../util/VectorMath.hpp"
#include "Astar.h"
#include "BaseEntity.h"
#include "MovingEntity.h"
#include "World.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <random>
#include <vector>

#include <csignal>
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#define path(x) x
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#define path(x) "gp-aai/" x
#endif

#define WORLD_GRAPH_DENSITY 30

#define breakpoint std::raise(SIGINT)
using std::cout, std::endl, std::shared_ptr;

World::World(int w, int h) : width(w), height(h), seek_pos(*new PointerEntity(Vector2D(-w/2, -h/2), *this)), soldierSprite(nullptr), commander(*new Commander(&soldierSprite, Vector2D(0, 0), *this)), graph(nullptr) {



    this->entities.push_back(shared_ptr<BaseEntity>(&this->seek_pos));
    this->entities.push_back(shared_ptr<BaseEntity>(&this->commander));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(-10, -10), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(-10, 10), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(10, -10), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(11, 12), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(12, 12), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(13, 13), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(14, 12), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(15, 15), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(16, 25), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(17, 21), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(18, 24), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(24, 22), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(37, 43), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(30, 29), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(26, 28), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(31, 26), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(10, 25), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(31, 27), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(19, 22), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(24, 20), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(22, 29), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(37, 26), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(68, 47), *this)));
    this->entities.push_back(shared_ptr<BaseEntity>(new Soldier(&soldierSprite, Vector2D(27, 12), *this)));


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
    //this->generateGraph();

}

void World::update(float delta) {
    for(auto entity: this->entities) {
        entity->update(delta);
    }
}

void World::render(SDL_Renderer* renderer){
    if(this->soldierSprite == nullptr){
        SDL_Surface* Loading_Surf = IMG_Load(path("PlayerShooting.png"));
        this->soldierSprite = SDL_CreateTextureFromSurface(renderer, Loading_Surf);
        SDL_FreeSurface(Loading_Surf); 
    }

    vector<Shape*> shapes;

    if(this->graph != nullptr)
        shapes += this->graph->render();

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
    auto shortest_path = this->shortestPath(pos, this->commander.getPosition());
    this->commander.setGoal(new FollowPathGoal(commander, shortest_path));
}

Vector2D& World::getSeekPosition() {
    return this->seek_pos.getPosition();
}

const vector<shared_ptr<BaseEntity>> World::getEntities() {
    return this->entities;
}

vector<Vector2D> World::shortestPath(Vector2D start, Vector2D end) {
    if(this->graph != nullptr)
        delete this->graph;

    graph = new Graph();

    for(int x=-this->width/2; x<=this->width/2; x+=WORLD_GRAPH_DENSITY) {
        for(int y=-this->height/2; y<=this->height/2; y+=WORLD_GRAPH_DENSITY) {
            Vertex* v = new Vertex(Vector2D(x, y), (end - Vector2D(x, y)).length());

            if(x >= -this->width/2 + WORLD_GRAPH_DENSITY) {
                Vertex* vp = graph->vertexAt(Vector2D(x - WORLD_GRAPH_DENSITY, y));
                if(vp != nullptr) {
                    v->addEdge(Edge { *vp, WORLD_GRAPH_DENSITY });
                    vp->addEdge(Edge { *v, WORLD_GRAPH_DENSITY });
                    graph->addShape(new Line(v->getPosition(), vp->getPosition(), {58, 83, 57}));
                }
            }

            if(y >= -this->height/2 + WORLD_GRAPH_DENSITY) {
                Vertex* vp = graph->vertexAt(Vector2D(x, y - WORLD_GRAPH_DENSITY));
                if(vp != nullptr) {
                    v->addEdge(Edge { *vp, WORLD_GRAPH_DENSITY });
                    vp->addEdge(Edge { *v, WORLD_GRAPH_DENSITY });
                    graph->addShape(new Line(v->getPosition(), vp->getPosition(), {58, 83, 57}));
                }
            }

            graph->addVertex(v);
        }
    }

    Vertex* v_end = graph->findClosest(start);
    Vertex* v_start = graph->findClosest(end);

    auto result = graph->shortestPath(v_start, v_end);
    vector<Vector2D> result_return;
    Vector2D last_point = result[0]->getPosition();
    for(auto vertex : result) {
        cout << "Vertex with position " << vertex->getPosition() << endl;
        result_return.push_back(vertex->getPosition());
        graph->addShape(new Line(vertex->getPosition(), last_point, {255, 255, 255}));
        last_point = vertex->getPosition();
    }
    return result_return;
}
