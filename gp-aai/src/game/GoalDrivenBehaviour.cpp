#include "GoalDrivenBehaviour.h"

/********** Goal **********/

Goal::Goal() {}

/********** AtomicGoal **********/

AtomicGoal::AtomicGoal(MovingEntity& entity) : entity(entity) {}

/********** CompositeGoal **********/

CompositeGoal::CompositeGoal() {}
CompositeGoal::~CompositeGoal() {
	for(auto goal : this->subgoals) {
		delete goal;
	}
}

void CompositeGoal::Activate() {
	if(this->subgoals.size() > 0) {
		this->subgoals.back()->Activate();
	}
}

int CompositeGoal::Process() {
	auto goal = this->subgoals.back();
	auto result = goal->Process();

	if(result > 0) {
		goal->Terminate();
		delete goal;
		this->subgoals.pop_back();

		if(this->subgoals.size() > 0) {
			this->subgoals.back()->Activate();
		}
	}

	if(this->subgoals.size() == 0) {
		// We're empty, commit sudoku
		return 1;
	}

	return 0;
}

void CompositeGoal::Terminate() {
	if(this->subgoals.size() > 0) {
		this->subgoals.back()->Terminate();
	}
}

void CompositeGoal::AddSubGoal(Goal* g) {
	this->subgoals.push_back(g);
}

/********** SeekGoal **********/

SeekGoal::SeekGoal(MovingEntity& entity, Vector2D seek_pos) : AtomicGoal(entity), seek_pos(seek_pos) {}

void SeekGoal::Activate() {
	this->entity.pushSteeringBehaviour(new SeekBehaviour(this->entity, this->seek_pos));
	this->entity.pushSteeringBehaviour(new ArriveBehaviour(this->entity, this->seek_pos));
}

int SeekGoal::Process() {
	if((this->seek_pos - this->entity.getPosition()).length() < 10) {
		// We're done here.
		return 1;
	}
	return 0;
}

void SeekGoal::Terminate() {
	this->entity.clearSteeringBehaviours();
}

/************* PatrolGoal *************/

PatrolGoal::PatrolGoal(MovingEntity& entity) {
	this->AddSubGoal(new SeekGoal(entity, Vector2D(-100, -100)));
	this->AddSubGoal(new SeekGoal(entity, Vector2D(-100, 100)));
	this->AddSubGoal(new SeekGoal(entity, Vector2D(100, 100)));
	this->AddSubGoal(new SeekGoal(entity, Vector2D(100, -100)));
	this->AddSubGoal(new SeekGoal(entity, Vector2D(-100, -100)));
}

