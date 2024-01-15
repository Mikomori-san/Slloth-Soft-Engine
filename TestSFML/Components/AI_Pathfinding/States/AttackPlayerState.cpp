#include "stdafx.h"
#include "AttackPlayerState.h"
#include "../SteeringCP.h"
#include "../../Transformation_Components/TransformationCP.h"

void AttackPlayerState::update(float deltaTime)
{
	if (!gameObject.expired())
	{
		std::shared_ptr<GameObject> go = gameObject.lock();
		//steer to player
		go->getComponentsOfType<SteeringCP>().at(0)->setDestination(player->getComponentsOfType<TransformationCP>().at(0)->getPosition());
	}
}
