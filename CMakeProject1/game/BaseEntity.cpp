#include "BaseEntity.h"
#include <SDL.h>
#include <iostream>

using std::cout, std::endl;

BaseEntity::BaseEntity(Vector2D p, World& w) : position(p), world(w) {}

void BaseEntity::update(float delta) {}

void BaseEntity::render(SDL_Renderer* renderer) {
	//cout << "BaseEntity render @ " << position.x << ", " << position.y << endl;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, position.x, position.y, position.x + 5, position.y + 15);
	SDL_RenderDrawLine(renderer, position.x - 5, position.y + 15, position.x, position.y);
	SDL_RenderDrawLine(renderer, position.x - 5, position.y + 15, position.x + 5, position.y + 15);
}
