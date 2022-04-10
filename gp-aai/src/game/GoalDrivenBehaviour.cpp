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
	if(this->subgoals.size() == 0) {
		// We're empty, commit sudoku
		return 1;
	}

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


/************* FlockGoal **************/

FlockGoal::FlockGoal(MovingEntity& entity) : AtomicGoal(entity) {}

void FlockGoal::Activate() {
	this->entity.pushSteeringBehaviour(new FlockingBehaviour(this->entity, 100));
}

int FlockGoal::Process() {
	return 0;
}

void FlockGoal::Terminate() {
	this->entity.clearSteeringBehaviours();
}

/************* PatrolGoal *************/

PatrolGoal::PatrolGoal(MovingEntity& entity) {
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(300, -200)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(300, 200)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(-300, 200)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(-300, -200)));
}

/************* FollowPathGoal *************/

FollowPathGoal::FollowPathGoal(MovingEntity& entity, vector<Vector2D> points) {
	for(auto vec : points) {
		this->AddSubGoal(new SeekGoal(entity, vec));
	}
}


/************** ShortestPathGoal ************/

ShortestPathGoal::ShortestPathGoal(MovingEntity& entity, Vector2D to) : AtomicGoal(entity), to(to), followPathGoal(nullptr) {}
ShortestPathGoal::~ShortestPathGoal() {
	if(this->followPathGoal != nullptr)
		delete this->followPathGoal;
}

void ShortestPathGoal::Activate() {
	if(this->followPathGoal != nullptr)
		delete this->followPathGoal;

    auto shortest_path = entity.getWorld()->shortestPath(entity.getPosition(), to);
	this->followPathGoal = new FollowPathGoal(entity, shortest_path);
	this->followPathGoal->Activate();
}
int ShortestPathGoal::Process() {
	return this->followPathGoal->Process();
}
void ShortestPathGoal::Terminate() {
	this->followPathGoal->Terminate();
}
