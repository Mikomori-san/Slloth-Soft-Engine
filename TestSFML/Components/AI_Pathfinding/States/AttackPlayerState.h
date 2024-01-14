#pragma once
#include "AIState.h"

class AttackPlayerState : public AIState
{
public:
	AttackPlayerState(std::shared_ptr<GameObject> incPlayer) : player(incPlayer) {};
	void update(float deltaTime) override;

private:
	std::shared_ptr<GameObject> player;
};