#pragma once
#include "AIState.h"

class PatrolState : public AIState
{
public:
	PatrolState(std::weak_ptr<GameObject> incGameObject, std::vector<std::shared_ptr<GameObject>> incPatrolPoints) : AIState(incGameObject), patrolPoints(incPatrolPoints) {};
	void update(float deltaTime) override;

private:
	std::vector<std::shared_ptr<GameObject>> patrolPoints;
};