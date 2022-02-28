#pragma once
#include <vector>
#include <SDL.h>

using std::vector;

class World {

private:
    int width;
    int height;
    vector<int> entities;

public:
    World(int w, int h);
    void update(float delta);
    void render(SDL_Renderer* renderer);

};
