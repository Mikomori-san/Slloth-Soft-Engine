#include<SFML/Graphics.hpp>
#pragma once

class GameObject : public sf::Transformable
{
public:
	virtual void initialize() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};