#pragma once
#include "../Component.h"
#include "../../Manager/InputManager.h"


class TransformationCP : protected Component
{
public:
	TransformationCP(std::weak_ptr<GameObject> gameObject, std::string id)
		: Component(gameObject, id)
	{}

	virtual ~TransformationCP() = default;

	virtual std::string getComponentId() override { return this->componentId; }
	virtual void setComponentId(std::string id) override { this->componentId = id; }
	virtual void update(float deltaTime) override;											//TODO: Implement Move in Update
	virtual void setVelocity(float vel) { this->velocity = vel; }
	virtual void setDirection(sf::Vector2f dir) { this->direction = dir; }
	virtual void setDirection(float x, float y) { this->direction = sf::Vector2f(x, y); }
	void init() override;

protected:
	float velocity = 0;
	sf::Vector2f direction = sf::Vector2f(0, 0);
};