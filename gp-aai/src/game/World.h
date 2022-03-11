#pragma once
#include <vector>
#include <SDL.h>
#include <memory>
class BaseEntity;

using std::vector, std::shared_ptr;
class World {

private:
    int width;
    int height;
    vector<shared_ptr<BaseEntity>> entities;

public:
    World(int w, int h);
    void update(float delta);
    virtual void render(SDL_Renderer* renderer);

};
