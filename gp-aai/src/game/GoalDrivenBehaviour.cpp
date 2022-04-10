#include "GoalDrivenBehaviour.h"

/********** Goal **********/

Goal::Goal(string name) : name(name) {}

/********** AtomicGoal **********/

AtomicGoal::AtomicGoal(string name, MovingEntity& entity) : Goal(name), entity(entity) {}
string AtomicGoal::getName() {
	return this->name;
}

/********** CompositeGoal **********/

CompositeGoal::CompositeGoal(string name) : Goal(name) {}
CompositeGoal::~CompositeGoal() {
	cout << "CompositeGoal::~CompositeGoal()" << endl;
	this->subgoalsLock.lock();
	for(auto goal : this->subgoals) {
		delete goal;
	}
	this->subgoalsLock.unlock();
}

void CompositeGoal::Activate() {
	cout << "CompositeGoal::Activate()" << endl;
	this->subgoalsLock.lock();
	if(this->subgoals.size() > 0) {
		this->subgoals.back()->Activate();
	}
	this->subgoalsLock.unlock();
}

int CompositeGoal::Process() {
	cout << "CompositeGoal::Process()" << endl;
	this->subgoalsLock.lock();
	if(this->subgoals.size() == 0) {
		// We're empty, commit sudoku
		this->subgoalsLock.unlock();
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

	this->subgoalsLock.unlock();
	return 0;
}

void CompositeGoal::Terminate() {
	cout << "CompositeGoal::Terminate()" << endl;
	this->subgoalsLock.lock();
	if(this->subgoals.size() > 0) {
		this->subgoals.back()->Terminate();
	}
	this->subgoalsLock.unlock();
}

void CompositeGoal::AddSubGoal(Goal* g) {
	cout << "CompositeGoal::AddSubGoal() " << g << endl;
	this->subgoalsLock.lock();
	this->subgoals.push_back(g);
	this->subgoalsLock.unlock();
}

string CompositeGoal::getName() {
	cout << "CompositeGoal::getName() " << endl;
	this->subgoalsLock.lock();
	string name = this->name + "\n";
	if(this->subgoals.size() > 0)
		name += this->subgoals.back()->getName();
	this->subgoalsLock.unlock();
	return name;
}

/********** SeekGoal **********/

SeekGoal::SeekGoal(MovingEntity& entity, Vector2D seek_pos) : AtomicGoal("Seek", entity), seek_pos(seek_pos) {}

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

FlockGoal::FlockGoal(MovingEntity& entity) : AtomicGoal("Flock", entity) {}

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

RedPatrolGoal::RedPatrolGoal(MovingEntity& entity) : CompositeGoal("Red Patrol") {
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(-50, 50)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(-140, 120)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(-120, 280)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(-320, 220)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(-360, 0)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(-220, -100)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(-320, -220)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(-100, -220)));
}
BluePatrolGoal::BluePatrolGoal(MovingEntity& entity) : CompositeGoal("Blue Patrol") {
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(90, -210)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(290, -220)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(320, -25)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(320, 250)));
	this->AddSubGoal(new ShortestPathGoal(entity, Vector2D(180, 210)));
}

/************* FollowPathGoal *************/

FollowPathGoal::FollowPathGoal(MovingEntity& entity, vector<Vector2D> points) : CompositeGoal("Follow Path") {
	for(auto vec : points) {
		this->AddSubGoal(new SeekGoal(entity, vec));
	}
}


/************** ShortestPathGoal ************/

ShortestPathGoal::ShortestPathGoal(MovingEntity& entity, Vector2D to) : AtomicGoal("Shortest Path", entity), to(to), followPathGoal(nullptr) {}
ShortestPathGoal::~ShortestPathGoal() {
	this->followPathGoalLock.lock();
	if(this->followPathGoal != nullptr)
		delete this->followPathGoal;
	this->followPathGoalLock.unlock();
}

void ShortestPathGoal::Activate() {
	this->followPathGoalLock.lock();
	if(this->followPathGoal != nullptr)
		delete this->followPathGoal;

    auto shortest_path = entity.getWorld()->shortestPath(entity.getPosition(), to);
	this->followPathGoal = new FollowPathGoal(entity, shortest_path);
	this->followPathGoal->Activate();
	this->followPathGoalLock.unlock();
}
int ShortestPathGoal::Process() {
	this->followPathGoalLock.lock();
	auto result = this->followPathGoal->Process();
	this->followPathGoalLock.unlock();
	return result;
}
void ShortestPathGoal::Terminate() {
	this->followPathGoalLock.lock();
	this->followPathGoal->Terminate();
	this->followPathGoalLock.unlock();
}

string ShortestPathGoal::getName() {
	this->followPathGoalLock.lock();
	string a = "Shortest Path\n" + this->followPathGoal->getName();
	this->followPathGoalLock.unlock();
	return a;
}

/******** Think *************/

RedThink::RedThink(MovingEntity& entity) : AtomicGoal("Red Think", entity), goal(nullptr) {}
RedThink::~RedThink() {
	if(this->goal != nullptr)
		delete this->goal;
}

void RedThink::Activate() {
	if(this->goal != nullptr)
		delete this->goal;

	this->goal = new RedPatrolGoal(entity);
	this->goal->Activate();
}

int RedThink::Process() {
	auto result = this->goal->Process();
	if(result == 0)
		return 0;

	this->goal->Terminate();
	delete this->goal;
	this->goal = new RedPatrolGoal(entity);
	this->goal->Activate();

	return 0;
}

void RedThink::Terminate() {
	
}

string RedThink::getName() {
	return "Red Think\n" + this->goal->getName(); 
}

BlueThink::BlueThink(MovingEntity& entity) : AtomicGoal("Blue Think", entity), goal(nullptr) {}
BlueThink::~BlueThink() {
	if(this->goal != nullptr)
		delete this->goal;
}

void BlueThink::Activate() {
	if(this->goal != nullptr)
		delete this->goal;

	this->goal = new BluePatrolGoal(entity);
	this->goal->Activate();
}

int BlueThink::Process() {
	auto result = this->goal->Process();
	if(result == 0)
		return 0;

	this->goal->Terminate();
	delete this->goal;
	this->goal = new BluePatrolGoal(entity);
	this->goal->Activate();

	return 0;
}

void BlueThink::Terminate() {
	
}

string BlueThink::getName() {
	return "Blue Think\n" + this->goal->getName(); 
}
