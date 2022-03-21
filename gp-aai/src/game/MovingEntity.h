#pragma once
#include "../util/Shapes.h"
#include "../util/Vector2D.h"
#include "BaseEntity.h"
#include "SteeringBehaviour.h"

class MovingEntity : public BaseEntity {
	protected:
		Vector2D velocity;
		double mass;
		double maxSpeed;

		SteeringBehaviour& sb;
		void updateLines();
		double getAngle();

	public:
		MovingEntity(string n, Vector2D p, World& w, Vector2D v, double m, double ms, SteeringBehaviour& sb);
		void update(float delta) override;

		double getMaxSpeed();
		Vector2D getVelocity();

		const vector<LocalizedEntity> getLocalEntities() override;
		Vector2D toLocalSpace(Vector2D v);
		Vector2D toWorldSpace(Vector2D v);
};

class Birb : public MovingEntity {
	public:
		Birb(Vector2D p, World& w);
};
