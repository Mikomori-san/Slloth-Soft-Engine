#pragma once
#include "AIState.h"

class PatrolState : public AIState
{
public:
	PatrolState(std::vector<std::shared_ptr<GameObject>> incPatrolPoints) : patrolPoints(incPatrolPoints) {};
	void update(float deltaTime) override;

private:
	std::vector<std::shared_ptr<GameObject>> patrolPoints;
};