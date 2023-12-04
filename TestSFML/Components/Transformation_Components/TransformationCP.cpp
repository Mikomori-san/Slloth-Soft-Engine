#include "stdafx.h"
#include "TransformationCP.h"
#include "../Graphics_Components/AnimatedGraphicsCP.h"

void TransformationCP::update(float deltaTime)
{
	position = position + direction * velocity * deltaTime;
}

void TransformationCP::init()
{
	if (!gameObject.expired())
	{
		std::shared_ptr<GameObject> go = gameObject.lock();
		std::shared_ptr<AnimatedGraphicsCP> ani = std::dynamic_pointer_cast<AnimatedGraphicsCP>(go->getComponentsOfType<AnimatedGraphicsCP>().at(0));
		sf::Vector2f origin(ani->getSprite().getTextureRect().width / 2, ani->getSprite().getTextureRect().height / 2);
		setOrigin(origin);
	}
	
}