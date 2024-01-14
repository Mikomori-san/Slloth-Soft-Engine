#pragma once
#include "Component.h"
class StatsCP : public Component
{
public:

	StatsCP(std::weak_ptr<GameObject> gameObject, std::string id, int hp) : Component(gameObject, id), health(hp) {};

	void update(float deltaTime) override;

	std::string getComponentId() override
	{
		return this->componentId;
	}

	void setComponentId(std::string id) override
	{
		this->componentId = id;
	}

	void init() override;

	void subtracktHealth(int dmg) { health -= dmg; }
	void addHealth(int healing) { health += healing; }
	int getHealth() { return health; }
	void setHealth(int newHealth) { health = newHealth; }

private:
	int health = 100;
};