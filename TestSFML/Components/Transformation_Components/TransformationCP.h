#pragma once
#include "../Component.h"
#include "../../Manager/InputManager.h"


class TransformationCP : public Component
{
public:
	TransformationCP(std::weak_ptr<GameObject> gameObject, std::string id, sf::Vector2f& pos, float rotation, float scale)
		: Component(gameObject, id), position(pos), origin(pos)
	{}

	virtual ~TransformationCP() = default;

	void init() override;
	virtual void update(float deltaTime) override;

	virtual std::string getComponentId() override { return this->componentId; }
	virtual void setComponentId(std::string id) override { this->componentId = id; }											//TODO: Implement Move in Update
	virtual void setVelocity(float vel) { this->velocity = vel; }
	virtual float getVelocity() { return velocity; }
	virtual void setDirection(sf::Vector2f dir) { this->direction = dir; }
	virtual void setDirection(float x, float y) { this->direction = sf::Vector2f(x, y); }
	virtual sf::Vector2f& getDirection() { return direction; }
	virtual float getRotation() { return rotation; }
	virtual void setRotation(float rot) { rotation = rot; }
	virtual float getScale() { return scale; }
	virtual void setScale(float scale) { this->scale = scale; }
	sf::Vector2f& getOrigin() { return origin; }
	void setOrigin(sf::Vector2f ori) { origin = ori; }
	void setPosition(sf::Vector2f newPosition) { position = position; }
	sf::Vector2f& getPosition() { return position; }

protected:
	sf::Vector2f position;
	sf::Vector2f origin;
	float velocity = 0;
	sf::Vector2f direction = sf::Vector2f(0, 0);
	float rotation = 0;
	float scale = 1;
};