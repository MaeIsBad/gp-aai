#include "GoalDrivenBehaviour.h"

/********** Goal **********/

Goal::Goal() {}

/********** AtomicGoal **********/

AtomicGoal::AtomicGoal() {}

/********** CompositeGoal **********/

CompositeGoal::CompositeGoal() {}

void CompositeGoal::Activate() {
	for(auto goal: this->subgoals) {
		goal->Activate();
	}
}

int CompositeGoal::Process() {
	for(auto goal: this->subgoals) {
		goal->Process();
	}

	return 0;
}

void CompositeGoal::Terminate() {
	for(auto goal: this->subgoals) {
		goal->Terminate();
	}
}

void CompositeGoal::AddSubGoal(Goal* g) {
	this->subgoals.push_back(g);
}

/********** SeekGoal **********/

SeekGoal::SeekGoal(Vector2D seek_pos) : AtomicGoal(), seek_pos(seek_pos) {}

void SeekGoal::Activate() {
	
}

int SeekGoal::Process() {

	return 0;
}

void SeekGoal::Terminate() {

}


