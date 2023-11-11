#pragma once
#include "ColliderComponent.h"
#include <SFML/Graphics.hpp>

class RectColliderComponent : public ColliderComponent
{
public:
	RectColliderComponent(std::string name);

	std::string getColliderTag();

	void setOrMoveCollider
	(
		float x, float y, float width, float hiegt
	);

	sf::FloatRect& getColliderRectF();

	std::string getSepcificId()
	{
		return specificComponentId;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self)
	{

	}

private:
	std::string specificComponentId = "rect";
	sf::FloatRect rect_Collider;
	std::string collider_Tag = "";
};
