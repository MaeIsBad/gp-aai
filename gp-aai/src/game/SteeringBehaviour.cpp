#include "../util/Vector2D.h"
#include "../util/debug.hpp"
#include "../util/instanceof.hpp"
#include "SteeringBehaviour.h"
#include <cmath>
#include <iostream>
#include <limits>

using std::cout, std::endl, std::numeric_limits;

SteeringBehaviour::SteeringBehaviour(MovingEntity& me) : entity(me) {}
Vector2D SteeringBehaviour::calculate() {
	return Vector2D();
}

SeekBehaviour::SeekBehaviour(MovingEntity& me, Vector2D& seek_pos) : SteeringBehaviour(me), seek_pos(seek_pos) {}
Vector2D SeekBehaviour::calculate() {
	Vector2D pos = entity.getPosition();
	Vector2D force = (this->seek_pos - pos);

	return force - entity.getVelocity();
}

ArriveBehaviour::ArriveBehaviour(MovingEntity& me, Vector2D& seek_pos) : SteeringBehaviour(me), seek_pos(seek_pos) {}
Vector2D ArriveBehaviour::calculate() {
	Vector2D pos = entity.getPosition();
	double length = (this->seek_pos - pos).length();
	Vector2D force = (this->seek_pos - pos) * (1 - length / 200) * -1;

	return force - entity.getVelocity();
}

ObstacleAvoidanceBehaviour::ObstacleAvoidanceBehaviour(MovingEntity& me, double detection_radius) : SteeringBehaviour(me), detection_radius(detection_radius) {}
Vector2D ObstacleAvoidanceBehaviour::calculate() {
	Vector2D pos = entity.getPosition();
	auto entities = entity.getLocalEntities();
	shared_ptr<BaseEntity> closest;
	double closest_intersection = numeric_limits<double>::max();
	Vector2D closest_position = Vector2D(); 

	for(auto e : entities) {
		// Filter out other stuffs
		if(instanceof<PointerEntity>(e.entity.get())) 
			continue;
		if(instanceof<Birb>(e.entity.get())) 
			continue;

		e.entity->setColor({80, 80, 80});
		// If it's outside the radius, ignore it
		if(e.local_position.length() > this->detection_radius) 
			continue;

		// If it's behind us, ignore it
		if(e.local_position.y < 0) 
			continue;

		// If it's outside the bounding area, ignore it.
		if((e.local_position.x - e.entity->getRadius() >  entity.getRadius() || 
			//e.local_position.x - __OBSTACLEAVOIDANCE_DETECTION < -__OBSTACLEAVOIDANCE_BOUNDING) &&
			//(e.local_position.x + __OBSTACLEAVOIDANCE_DETECTION > __OBSTACLEAVOIDANCE_BOUNDING || 
			e.local_position.x + e.entity->getRadius() < -entity.getRadius())) 
			continue;

		// Calculate intersections with the y axis
		double expandedRadius = e.entity->getRadius() + entity.getRadius(); 
		double squarePart = sqrt(expandedRadius*expandedRadius - e.local_position.x*e.local_position.x);
		double intersection = e.local_position.y - squarePart;
		if(intersection <= 0) {
			intersection = e.local_position.y + squarePart;
		}

		if(intersection < closest_intersection) {
			closest_intersection = intersection;
			closest = e.entity;
			closest_position = e.local_position;
		}

		e.entity->setColor({150, 150, 255});

	}

	// Nothing to do! Don't change the current force.
	if(!closest) {
		return Vector2D();
	}

	closest->setColor({150, 0, 0});
	Vector2D steering_force = Vector2D();

	double multiplier = (1.0 + (this->detection_radius - closest_position.y) / this->detection_radius) * 1;

	steering_force.x = (closest->getRadius() - closest_position.x) * multiplier;
	steering_force.y = (closest->getRadius() - closest_position.x) * 0.2;

	return entity.toWorldSpace(steering_force);
}

FlockingBehaviour::FlockingBehaviour(MovingEntity& me, vector<MovingEntity*>& group) : SteeringBehaviour(me), group(group) {}

Vector2D FlockingBehaviour::calculate() {
	

	return Vector2D();
}
