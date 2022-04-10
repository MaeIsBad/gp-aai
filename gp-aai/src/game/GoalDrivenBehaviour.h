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

class FlockGoal : public AtomicGoal {
	public:
		FlockGoal(MovingEntity& entity);
		void Activate();
		int Process();
		void Terminate();
};

class PatrolGoal : public CompositeGoal {
	public:
		PatrolGoal(MovingEntity& entity);
};

class FollowPathGoal : public CompositeGoal {
	public:
		FollowPathGoal(MovingEntity& entity, vector<Vector2D> points);
};

class ShortestPathGoal : public AtomicGoal {
	private:
		Vector2D to;
		FollowPathGoal* followPathGoal;

	public:
		ShortestPathGoal(MovingEntity& entity, Vector2D pos);
		~ShortestPathGoal();
		void Activate();
		int Process();
		void Terminate();
};

#include "MovingEntity.h"
