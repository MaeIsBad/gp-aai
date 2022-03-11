#include "SteeringBehaviour.h"
#include "../Vector2D.h"

SteeringBehaviour::SteeringBehaviour(MovingEntity& me) : entity(me) {}
void SteeringBehaviour::calculate() {}

SeekBehaviour::SeekBehaviour(MovingEntity& me) : SteeringBehaviour(me) {}
void SeekBehaviour::calculate() {
	Vector2D pos = entity.getPosition();
	pos.x += 10;
	pos.y += 10;
	entity.setPosition(pos);
}
