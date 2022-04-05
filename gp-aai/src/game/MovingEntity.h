#pragma once
#include "../util/Shapes.h"
#include "../util/Vector2D.h"
#include "BaseEntity.h"
#include "SteeringBehaviour.h"
#include "GoalDrivenBehaviour.h"

class MovingEntity : public BaseEntity {
	protected:
		Vector2D velocity;
		double mass;
		double maxSpeed;

		vector<SteeringBehaviour*> sbs;
		void updateLines();
		double getAngle();

		Goal* goal;

	public:
		MovingEntity(string n, Vector2D p, World& w, Vector2D v, double m, double ms);
		~MovingEntity();
		void update(float delta) override;

		double getMaxSpeed();
		Vector2D getVelocity();

		const vector<LocalizedEntity> getLocalEntities() override;
		Vector2D toLocalSpace(Vector2D v);
		Vector2D toWorldSpace(Vector2D v);

		void setGoal(Goal* goal);

		void pushSteeringBehaviour(SteeringBehaviour* sb);
		void clearSteeringBehaviours();
};

class Birb : public MovingEntity {
	public:
		Birb(Vector2D p, World& w);
};
