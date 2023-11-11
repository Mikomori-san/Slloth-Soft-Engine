#pragma once
#include "Components.h"
#include <SFML/Graphics.hpp>

class Component;
class TransformComponent : public Component
{
public:
	TransformComponent(float width, float hieght, sf::Vector2f location);

	sf::Vector2f& getLocation();

	sf::Vector2f getSize();

	std::string Component::getId()
	{
		return COMPONTEN_ID;
	}

	std::string Component::getSpecificId()
	{
		return COMPONTEN_ID;
	}

	void Component::disableComonent()
	{}

	void Component::enableComponent()
	{}

	bool Component::enabled()
	{
		return false;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self)
	{}

private:
	const std::string COMPONTEN_ID = "transform";
	sf::Vector2f o_location;
	float o_Height;
	float o_Width;
};
