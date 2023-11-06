#pragma once
#include "../Manager/GameStateManager.h"

class GameState
{
public:
	virtual void init() = 0;
	virtual void exit() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
};