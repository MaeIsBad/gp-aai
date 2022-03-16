#include "MovingEntity.h"
#include <iostream>
#include "SteeringBehaviour.h"
#include <cmath>

using std::cout, std::endl;

MovingEntity::MovingEntity(Vector2D p, World& w, Vector2D v, double m, double ms, SteeringBehaviour& sb) : BaseEntity(p, w), velocity(v), mass(m), maxSpeed(ms), sb(sb) {}

void MovingEntity::update(float delta) {
	Vector2D force = Vector2D(velocity);
	force = force + this->sb.calculate() / this->mass * delta;
	force = force.truncate(this->getMaxSpeed());
	this->position = this->position + force;
	this->velocity = force;
}

void MovingEntity::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	double h = acos(this->velocity.normalize().x);
	Vector2D p1 = Vector2D(0, -10).rotate(h) + position;
	Vector2D p2 = Vector2D(4, 10).rotate(h) + position;
	Vector2D p3 = Vector2D(-4, 10).rotate(h) + position;

	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
	SDL_RenderDrawLine(renderer, p2.x, p2.y, p3.x, p3.y);
	SDL_RenderDrawLine(renderer, p3.x, p3.y, p1.x, p1.y);
	
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, position.x, position.y, position.x + (velocity.x * 10), position.y + (velocity.y * 10));
}

double MovingEntity::getMaxSpeed() { 
	return this->maxSpeed;
}

Vector2D MovingEntity::getVelocity() {
	return Vector2D(this->velocity);
}
const vector<LocalizedEntity> MovingEntity::getLocalEntities() {
	auto local_entities = vector<LocalizedEntity>();
	
	double a = M_PI * 2 - acos(this->velocity.normalize().x); // get angle

	for(auto entity : this->world.getEntities()) {
		Vector2D new_pos = entity->getPosition() - this->position;

		local_entities.push_back(LocalizedEntity {
			new_pos.rotate(a),
			entity
		});
	}

	return local_entities;
}


Birb::Birb(Vector2D p, World& w) : MovingEntity(p, w, Vector2D(-1, -1), 1000, 2, *new SeekBehaviour(*this)) {}
