#include "MovingEntity.h"
#include "SteeringBehaviour.h"
#include <cmath>
#include <iostream>
#include <string>

using std::cout, std::endl, std::string;

MovingEntity::MovingEntity(string n, Vector2D p, World& w, Vector2D v, double m, double ms, SteeringBehaviour& sb) : BaseEntity(n, p, w), velocity(v), mass(m), maxSpeed(ms), sb(sb) {
	this->shapes.pop_back();


	this->shapes.push_back(new Line(Vector2D(), Vector2D(), this->color));
	this->shapes.push_back(new Line(Vector2D(), Vector2D(), this->color));
	this->shapes.push_back(new Line(Vector2D(), Vector2D(), this->color));
	this->updateLines();
}

double MovingEntity::getAngle() {
	Vector2D angle = this->velocity.normalize();
	double h = asin(angle.y) + M_PI / 2;
	if(angle.x < 0) h = 2 * M_PI - h;
	return h;
}

void MovingEntity::updateLines() {
	double h = this->getAngle();

	Vector2D p1 = Vector2D(0, -10).rotate(h) + position;
	Vector2D p2 = Vector2D(4, 10).rotate(h) + position;
	Vector2D p3 = Vector2D(-4, 10).rotate(h) + position;

	dynamic_cast<Line*>(this->shapes[0])->start = p1;
	dynamic_cast<Line*>(this->shapes[0])->end = p2;

	dynamic_cast<Line*>(this->shapes[1])->start = p2;
	dynamic_cast<Line*>(this->shapes[1])->end = p3;
	
	dynamic_cast<Line*>(this->shapes[2])->start = p3;
	dynamic_cast<Line*>(this->shapes[2])->end = p1;
}

void MovingEntity::update(float delta) {
	Vector2D force = Vector2D(velocity);

	SeekBehaviour ssb = SeekBehaviour(*this);

	force = force + (this->sb.calculate() + ssb.calculate()) / this->mass * delta;
	force = force.truncate(this->getMaxSpeed());
	this->position = this->position + force;
	this->velocity = force;
	this->updateLines();
}

double MovingEntity::getMaxSpeed() { 
	return this->maxSpeed;
}

Vector2D MovingEntity::getVelocity() {
	return Vector2D(this->velocity);
}
const vector<LocalizedEntity> MovingEntity::getLocalEntities() {
	auto local_entities = vector<LocalizedEntity>();
	
	for(auto entity : this->world.getEntities()) {
		local_entities.push_back(LocalizedEntity {
			this->toLocalSpace(entity->getPosition()),
			entity
		});
	}

	return local_entities;
}

Vector2D MovingEntity::toLocalSpace(Vector2D v) {
	double a = this->getAngle();
	Vector2D new_pos = v - this->position;
	return new_pos.rotate(a);
}

Vector2D MovingEntity::toWorldSpace(Vector2D v) {
	double a = this->getAngle();
	Vector2D new_pos = v - this->position;
	return new_pos.rotate(-a);
}


Birb::Birb(Vector2D p, World& w) : MovingEntity("BIRB", p, w, Vector2D(), 50, 2, *new ObstacleAvoidanceBehaviour(*this, 100)) {}
