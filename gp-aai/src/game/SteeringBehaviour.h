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
public:
	SeekBehaviour(MovingEntity& me);
	Vector2D calculate() override;
};

class ObstacleAvoidanceBehaviour : public SteeringBehaviour {
public:
	ObstacleAvoidanceBehaviour(MovingEntity& me);
	Vector2D calculate() override;
};

#include "MovingEntity.h"
