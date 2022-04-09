#pragma once
#include "../util/Vector2D.h"
#include <SDL.h>
#include <memory>
#include <vector>
#include "Astar.h"
class BaseEntity;
class Commander;

using std::vector, std::shared_ptr;

enum WorldEvent { mouseClick };

class World {

    private:
        int width, height;
        vector<shared_ptr<BaseEntity>> entities;
        BaseEntity& seek_pos;
        Commander& commander;

        Vector2D transform, translate;
        SDL_Texture* soldierSprite;
        Graph* graph;

    public:
        World(int w, int h);
        void update(float delta);
        void render(SDL_Renderer* renderer);
        void event(WorldEvent e, Vector2D pos);

        Vector2D& getSeekPosition();
        const vector<shared_ptr<BaseEntity>> getEntities();

        vector<Vector2D> shortestPath(Vector2D start, Vector2D end);
};

