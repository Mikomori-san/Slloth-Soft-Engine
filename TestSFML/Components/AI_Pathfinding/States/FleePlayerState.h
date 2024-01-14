#pragma once
#include "AIState.h"
#include "../../../GameObject.h"

class FleePlayerState : public AIState
{
public:
	FleePlayerState(std::shared_ptr<GameObject> incPlayer) : player(incPlayer) {};
	void update(float deltaTime) override;
	
private:
	std::shared_ptr<GameObject> player;
};