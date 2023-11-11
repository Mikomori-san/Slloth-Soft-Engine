#pragma once
#include "Components.h"
#include "TransformComponent.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "../GameObjects/GameObjectSharer.h"
#include <iostream>

class GraphicsComponent : public Component
{
public:
	virtual void draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t) = 0;

	virtual void initializeGraphics(std::string bitmapName, sf::Vector2f objectSize) = 0;

	std::string Component::getId()
	{
		return component_id;
	}

	void Component::disableComonent()
	{
		m_Enabled = true;
	}

	void Component::enableComponent()
	{
		m_Enabled = false;
	}

	bool Component::enabled()
	{
		return m_Enabled;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self)
	{}

private:
	std::string component_id = "graphics";
	bool m_Enabled = false;
};
