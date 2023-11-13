#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../Components/Component.h"

class GameObject
{
public:
	GameObject(sf::Vector2f initPosition, std::string id)
		: position(initPosition), GameObjectId(id)
	{}

	~GameObject()
	{}

	void addComponent(std::shared_ptr<Component> component);
	void update();

	void setVelocity(float newVelocity);
	void setPosition(sf::Vector2f newPosition);
	void setDirectin(sf::Vector2f newDirection);

private:
	float velocity;

	sf::Vector2f position;
	sf::Vector2f direction;

	std::string GameObjectId;
	
	std::vector<std::shared_ptr<Component>> components;
};


