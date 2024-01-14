#pragma once
#include "../../../GameObject.h"
class AIState
{
public:
	AIState(std::weak_ptr<GameObject> incGameObject) : gameObject(incGameObject) {};
	virtual void update(float deltaTime) = 0;

private:
	std::weak_ptr<GameObject> gameObject;
};