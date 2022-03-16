#include "BaseEntity.h"
#include <SDL.h>
#include <iostream>
#include <cmath>

#define __BASEENTITY_SIDES 100
#define __BASEENTITY_2PI 6.283185307
#define __BASEENTITY_RADIUS 8
#define __BASEENTITY_DA __BASEENTITY_2PI/__BASEENTITY_SIDES

using std::cout, std::endl;

BaseEntity::BaseEntity(Vector2D p, World& w) : BaseEntity(p, w, {255, 255, 255}) {}
BaseEntity::BaseEntity(Vector2D p, World& w, Color c) : position(p), world(w), color(c) {}

// Rule of three
BaseEntity::BaseEntity(BaseEntity& b) : BaseEntity(b.position, b.world, b.color) {}
BaseEntity& BaseEntity::operator=(const BaseEntity& b) {
	this->position = b.position;
	this->color = b.color;

	return *this;
}
BaseEntity::~BaseEntity() {};

void BaseEntity::update(float delta) {}

void BaseEntity::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(renderer, position.x, position.y);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);

	float angle = __BASEENTITY_DA;
	Vector2D center = Vector2D(position);
	Vector2D start, end;

	end.x = __BASEENTITY_RADIUS;
	end.y = 0.0f;
	end = end + center;
	for (int i=0; i!=__BASEENTITY_SIDES; i++) {
		start = end;
		end.x = cos(angle) * __BASEENTITY_RADIUS;
		end.y = sin(angle) * __BASEENTITY_RADIUS;
		end = end + center;
		angle += __BASEENTITY_DA;
		SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
	}
}

void BaseEntity::setPosition(int x, int y) {
	this->position.x = x;
	this->position.y = y;
}

void BaseEntity::setPosition(const Vector2D pos) {
	return setPosition(pos.x, pos.y);
}

Vector2D BaseEntity::getPosition() {
	return Vector2D(this->position);
}

void BaseEntity::setColor(Color c) {
	this->color = c;
}

World& BaseEntity::getWorld() {
	return this->world;
}

const vector<LocalizedEntity> BaseEntity::getLocalEntities() {
	auto local_entities = vector<LocalizedEntity>();

	for(auto entity : this->world.getEntities()) {
		local_entities.push_back(LocalizedEntity {
			entity->getPosition() - this->position,
			entity
		});
	}

	return local_entities;
}

PointerEntity::PointerEntity(Vector2D p, World& w) : BaseEntity(p, w, {255, 255, 0}) {};
TreeEntity::TreeEntity(Vector2D p, World& w): BaseEntity(p, w, {0, 255, 0}) {};
