#pragma once
#include <vector>
#include <SDL.h>
#include <memory>
#include "../Vector2D.h"
class BaseEntity;

using std::vector, std::shared_ptr;

enum WorldEvent { mouseClick };

class World {

private:
    int width;
    int height;
    vector<shared_ptr<BaseEntity>> entities;

public:
    World(int w, int h);
    void update(float delta);
    void render(SDL_Renderer* renderer);
    void event(WorldEvent e, Vector2D pos);

};

