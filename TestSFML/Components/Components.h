#pragma once
#include "../GameObjects/GameObjectSharer.h"
#include <string>

class GameObject;

class Component
{
public:
	virtual std::string getId() = 0;
	virtual std::string getSpecificId() = 0;
	virtual void disableComonent() = 0;
	virtual void enableComponent() = 0;
	virtual bool enabled() = 0;
	virtual void start(GameObjectSharer* gos, GameObject* self) = 0;

};