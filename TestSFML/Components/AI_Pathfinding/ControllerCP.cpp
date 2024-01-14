#include "stdafx.h"
#include "States/AIState.h"
#include "ControllerCP.h"
#include "../../GameObject.h"
#include "../StatsCP.h"
#include "../Transformation_Components/TransformationCP.h"
#include "States/FleePlayerState.h"
#include "States/AttackPlayerState.h"
#include "States/PatrolState.h"

void ControllerCP::update(float deltaTime)
{
	if (!gameObject.expired())
	{
		std::shared_ptr<GameObject> go = gameObject.lock();
		health = go->getComponentsOfType<StatsCP>().at(0)->getHealth();

		float nearestDistance = std::numeric_limits<float>::max();
		sf::Vector2f myPos = go->getComponentsOfType<TransformationCP>().at(0)->getPosition();
		std::shared_ptr<GameObject> nearestPlayer;

		for (auto& player : players)
		{
			sf::Vector2f playerPos = player->getComponentsOfType<TransformationCP>().at(0)->getPosition();
			
			float distance = (playerPos.x - myPos.x) * (playerPos.x - myPos.x) + (playerPos.y - myPos.y) * (playerPos.y - myPos.y);

			if (nearestDistance > distance)
			{
				nearestDistance = distance;
				nearestPlayer = player;
			}
		}

		if ((health / maxHealth) * 100 < 20)
		{
			if (!std::dynamic_pointer_cast<FleePlayerState>(currentState))
			{
				currentState = std::make_shared<FleePlayerState>(nearestPlayer);
			}
		}
		else if (nearestDistance < 500)
		{
			if (!std::dynamic_pointer_cast<AttackPlayerState>(currentState))
			{
				currentState = std::make_shared<AttackPlayerState>(nearestPlayer);
			}
		}
		else
		{
			if (!std::dynamic_pointer_cast<PatrolState>(currentState))
			{
				currentState = std::make_shared<PatrolState>(patrolPoints);
			}
		}
	}

	currentState->update(deltaTime);

}

void ControllerCP::init()
{
	if (!gameObject.expired())
	{
		std::shared_ptr<GameObject> go = gameObject.lock();
		maxHealth = go->getComponentsOfType<StatsCP>().at(0)->getHealth();
	}
}
