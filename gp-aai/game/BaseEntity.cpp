#include "BaseEntity.h"
#include <SDL.h>
#include <iostream>
#include <cmath>

using std::cout, std::endl;

BaseEntity::BaseEntity(Vector2D p, World& w) : position(p), world(w) {}

void BaseEntity::update(float delta) {}

void BaseEntity::render(SDL_Renderer* renderer) {
	//cout << "BaseEntity render @ " << position.x << ", " << position.y << endl;
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(renderer, position.x, position.y);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	int sides = 10;
	float _2PI = 6.283185307;
	float d_a = _2PI/sides,
		angle = d_a,
		radius = 8;
	Vector2D center = Vector2D(position);

	Vector2D start, end;
	end.x = radius;
	end.y = 0.0f;
	end = end + center;
	for (int i=0; i!=sides; i++) {
		start = end;
		end.x = cos(angle) * radius;
		end.y = sin(angle) * radius;
		end = end + center;
		angle += d_a;
		SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
	}
}
