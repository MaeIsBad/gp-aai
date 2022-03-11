#pragma once
class MovingEntity;

class SteeringBehaviour {
protected:
	MovingEntity& entity;

public:
	SteeringBehaviour(MovingEntity& me);
	virtual void calculate();
};

class SeekBehaviour : public SteeringBehaviour {
public:
	SeekBehaviour(MovingEntity& me);
	void calculate();
};

#include "MovingEntity.h"
