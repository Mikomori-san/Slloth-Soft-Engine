#pragma once
#include "../../../GameObject.h"
class AIState
{
public:
	AIState() = default;
	virtual void update(float deltaTime) = 0;
};