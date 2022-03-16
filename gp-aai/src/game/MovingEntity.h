#pragma once
#include "BaseEntity.h"
#include "../util/Vector2D.h"
#include "SteeringBehaviour.h"

class MovingEntity : public BaseEntity {
protected:
	Vector2D velocity;
	double mass;
	double maxSpeed;

	SteeringBehaviour& sb;
public:
	MovingEntity(Vector2D p, World& w, Vector2D v, double m, double ms, SteeringBehaviour& sb);
    void update(float delta) override;
	void render(SDL_Renderer* renderer) override;

	double getMaxSpeed();
	Vector2D getVelocity();

    const vector<LocalizedEntity> getLocalEntities() override;
};

class Birb : public MovingEntity {
public:
	Birb(Vector2D p, World& w);
};
