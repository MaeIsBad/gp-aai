#include "MovingEntity.h"
#include <iostream>
#include "SteeringBehaviour.h"

using std::cout, std::endl;

MovingEntity::MovingEntity(Vector2D p, World& w, Vector2D v, double m, double ms, SteeringBehaviour& sb) : BaseEntity(p, w), velocity(v), mass(m), maxSpeed(ms), sb(sb) {}

void MovingEntity::update(float delta) {
	this->sb.calculate();
}

void MovingEntity::render(SDL_Renderer* renderer) {
	//cout << "MovingEntity render @ " << position.x << ", " << position.y << endl;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, position.x, position.y, position.x + 5, position.y + 15);
	SDL_RenderDrawLine(renderer, position.x - 5, position.y + 15, position.x, position.y);
	SDL_RenderDrawLine(renderer, position.x - 5, position.y + 15, position.x + 5, position.y + 15);
}

Birb::Birb(Vector2D p, World& w) : MovingEntity(p, w, Vector2D(0, 0), 10, 10, *new SeekBehaviour(*this)) {}
