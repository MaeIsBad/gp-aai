#pragma once
#include <vector>
#include "../util/Vector2D.h"
class MovingEntity;

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
		MovingEntity& entity;
		AtomicGoal(MovingEntity& entity);

	public:
		virtual void Activate() = 0;
		virtual int Process() = 0;
		virtual void Terminate() = 0;
};

class CompositeGoal : public Goal {
	protected:
		CompositeGoal();
		~CompositeGoal();
		vector<Goal*> subgoals;

		void AddSubGoal(Goal* g);

	public:
		void Activate();
		int Process();
		void Terminate();
};

class SeekGoal : public AtomicGoal {
	protected:
		Vector2D seek_pos;

	public:
		SeekGoal(MovingEntity& entity, Vector2D seek_pos);
		void Activate();
		int Process();
		void Terminate();
};

class PatrolGoal : public CompositeGoal {
	public:
		PatrolGoal(MovingEntity& entity);
};

#include "MovingEntity.h"
