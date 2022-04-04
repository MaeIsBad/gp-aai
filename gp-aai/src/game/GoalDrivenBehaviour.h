#pragma once
#include <vector>
#include "../util/Vector2D.h"

using std::vector;

class Goal {
	protected:
		Goal();

	public:
		virtual void Activate() = 0;
		virtual int Process() = 0;
		virtual void Terminate() = 0;
};

class AtomicGoal : public Goal {
	protected:
		AtomicGoal();

	public:
		virtual void Activate() = 0;
		virtual int Process() = 0;
		virtual void Terminate() = 0;
};

class CompositeGoal : public Goal {
	protected:
		CompositeGoal();
		vector<Goal*> subgoals;
		//vector<Goal*> domgoals;

	public:
		void Activate();
		int Process();
		void Terminate();

		void AddSubGoal(Goal* g);
};

class SeekGoal : public AtomicGoal {
	protected:
		Vector2D seek_pos;

	public:
		SeekGoal(Vector2D seek_pos);
		void Activate();
		int Process();
		void Terminate();
};

