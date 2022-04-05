#pragma once
class MovingEntity;
#include "../util/Vector2D.h"

class SteeringBehaviour {
	protected:
		MovingEntity& entity;

	public:
		SteeringBehaviour(MovingEntity& me);
		virtual Vector2D calculate();
};

class SeekBehaviour : public SteeringBehaviour {
	private:
		Vector2D& seek_pos;

	public:
		SeekBehaviour(MovingEntity& me, Vector2D& seek_pos);
		Vector2D calculate() override;
};

class ArriveBehaviour : public SteeringBehaviour {
	private:
		Vector2D& seek_pos;

	public:
		ArriveBehaviour(MovingEntity& me, Vector2D& seek_pos);
		Vector2D calculate() override;
};

class ObstacleAvoidanceBehaviour : public SteeringBehaviour {
	private:
		double detection_radius;
	public:
		ObstacleAvoidanceBehaviour(MovingEntity& me, double detection_radius);
		Vector2D calculate() override;
};

#include "MovingEntity.h"
