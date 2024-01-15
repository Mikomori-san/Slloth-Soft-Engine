#include "stdafx.h"
#include "TransformationCP.h"
#include "../Graphics_Components/GraphicsCP.h"
#include "../Collision_Components/RigidBodyCP.h"

void TransformationCP::update(float deltaTime)
{
	oldPos = position - direction * 50.f * deltaTime;
	position = position + direction * velocity * deltaTime;
	if (rigid)
	{
		rigid->setPos(position);
	}
}

void TransformationCP::init()
{
	if (!gameObject.expired())
	{
		std::shared_ptr<GameObject> go = gameObject.lock();
		if (go->getComponentsOfType<GraphicsCP>().size() != 0)
		{
			std::shared_ptr<GraphicsCP> ani = go->getComponentsOfType<GraphicsCP>().at(0);
			sf::Vector2f origin(ani->getSprite().getTextureRect().width / 2, ani->getSprite().getTextureRect().height / 2);
			setOrigin(origin);
		}
		
		if (go->getComponentsOfType<RigidBodyCP>().size() != 0)
		{
			rigid = go->getComponentsOfType<RigidBodyCP>().at(0);
		}
	}
}