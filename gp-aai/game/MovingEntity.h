#pragma once
#include "BaseEntity.h"
#include "../Vector2D.h"

class MovingEntity : public BaseEntity {
protected:
	Vector2D velocity;
	double mass;
	double maxSpeed;
public:
	MovingEntity(Vector2D p, World& w, Vector2D v, double m, double ms);
    void update(float delta);
	void render(SDL_Renderer* renderer) override;
};
