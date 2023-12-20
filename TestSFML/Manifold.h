#pragma once
#include "Components/Collision_Components/RigidBodyCP.h"

struct Manifold
{
	std::shared_ptr<RigidBodyCP> body1{};
	std::shared_ptr<RigidBodyCP> body2{};

	float penetration{};
	sf::Vector2f normal;
};