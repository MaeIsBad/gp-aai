#pragma once
#include "../util/Vector2D.h"
#include <SDL.h>
#include <memory>
#include <vector>
class BaseEntity;

using std::vector, std::shared_ptr;

enum WorldEvent { mouseClick };

class World {

    private:
        int width, height;
        vector<shared_ptr<BaseEntity>> entities;
        BaseEntity& seek_pos;
        Vector2D transform, translate;

    public:
        World(int w, int h);
        void update(float delta);
        void render(SDL_Renderer* renderer);
        void event(WorldEvent e, Vector2D pos);

        Vector2D& getSeekPosition();
        const vector<shared_ptr<BaseEntity>> getEntities();

        void generateGraph();
};

