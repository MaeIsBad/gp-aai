#include "SteeringBehaviour.h"
#include "../util/Vector2D.h"
#include <cmath>
#include <iostream>
#include "../util/instanceof.hpp"

#define __OBSTACLEAVOIDANCE_RADIUS 50
#define __OBSTACLEAVOIDANCE_BOUNDING 10

using std::cout, std::endl;

SteeringBehaviour::SteeringBehaviour(MovingEntity& me) : entity(me) {}
Vector2D SteeringBehaviour::calculate() {
	return Vector2D();
}

SeekBehaviour::SeekBehaviour(MovingEntity& me) : SteeringBehaviour(me) {}
Vector2D SeekBehaviour::calculate() {
	Vector2D pos = entity.getPosition();
	Vector2D goal = entity.getWorld().getSeekPosition();
	Vector2D force = (goal - pos);

	return force - entity.getVelocity();
}

ObstacleAvoidanceBehaviour::ObstacleAvoidanceBehaviour(MovingEntity& me) : SteeringBehaviour(me) {}
Vector2D ObstacleAvoidanceBehaviour::calculate() {
	Vector2D pos = entity.getPosition();
	auto entities = entity.getLocalEntities();

	for(auto entity : entities) {
		if(instanceof<PointerEntity>(entity.entity.get()))
			continue;

		if(instanceof<Birb>(entity.entity.get()))
			continue;

		if((pos - entity.entity->getPosition()).length() > __OBSTACLEAVOIDANCE_RADIUS)
			continue;

		cout << "Entity at " << entity.local_position.x << ", " << entity.local_position.y << " and distance of " << (pos - entity.entity->getPosition()).length() << endl;

	}

	return Vector2D();
}
