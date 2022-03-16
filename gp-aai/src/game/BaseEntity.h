#pragma once
#include <vector>
#include <SDL.h>
#include "../util/Vector2D.h"
#include "World.h"
#include "../util/Color.h"
#include <memory>

using std::vector, std::shared_ptr;

struct LocalizedEntity {
    Vector2D local_position;
    shared_ptr<BaseEntity> entity;
};

class BaseEntity {

protected:
    Vector2D position;
    World& world;
    double radius;
    Color color;

public:
    BaseEntity(Vector2D p, World& w);
    BaseEntity(Vector2D p, World& w, Color c);

    // Rule of 3
    BaseEntity(BaseEntity& b);
    BaseEntity& operator=(const BaseEntity& b);
    ~BaseEntity();

    virtual void update(float delta);
    virtual void render(SDL_Renderer* renderer);

    void setPosition(int x, int y);
    void setPosition(const Vector2D pos);
    Vector2D getPosition();

    void setColor(Color c);
    World& getWorld();

    virtual const vector<LocalizedEntity> getLocalEntities();

};

class PointerEntity : public BaseEntity {
public:
    PointerEntity(Vector2D p, World& w);
};

class TreeEntity : public BaseEntity {
public:
    TreeEntity(Vector2D p, World& w);
};

