#include "stdafx.h"
#include "TransformationCP.h"

void TransformationCP::update(float deltaTime)
{
	if (!gameObject.expired())
	{
		std::shared_ptr<GameObject> go = gameObject.lock();

		go->setPosition(go->getPosition() + direction * velocity * deltaTime);
	}
}

void TransformationCP::init()
{
	
}
