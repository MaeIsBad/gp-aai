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
	//cout << "MovingEntity render @ " << position.x << ", " << position.y << endl;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, position.x, position.y, position.x + 5, position.y + 15);
	SDL_RenderDrawLine(renderer, position.x - 5, position.y + 15, position.x, position.y);
	SDL_RenderDrawLine(renderer, position.x - 5, position.y + 15, position.x + 5, position.y + 15);

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
	
	double a = M_PI / 2 - acos(this->velocity.normalize().x); // get angle
	double cos_a = cos(a);
	double sin_a = sin(a);

	for(auto entity : this->world.getEntities()) {
		Vector2D new_pos = entity->getPosition() - this->position;

		// Get product of (not making a matrix class for this one time)
		// ⌜ cos ɑ  -sin ɑ ⌝   ⌜ x ⌝
		// ⌞ sin ɑ  cos ɑ  ⌟ x ⌞ y ⌟

		double tmp_x = cos_a * new_pos.x  +  -sin_a * new_pos.y;
		double tmp_y = sin_a * new_pos.x  +  cos_a * new_pos.y;

		local_entities.push_back(LocalizedEntity {
			Vector2D(tmp_x, tmp_y),
			entity
		});
	}

	return local_entities;
}


Birb::Birb(Vector2D p, World& w) : MovingEntity(p, w, Vector2D(-1, -1), 1000, 2, *new ObstacleAvoidanceBehaviour(*this)) {}
