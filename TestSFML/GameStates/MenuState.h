#pragma once
#include "GameState.h"
class MenuState : public GameState
{
public:
	void init() override;
	void exit() override;
	void update(float deltaTime) override;
	void render() override;
};