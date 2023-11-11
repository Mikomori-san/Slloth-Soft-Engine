#include "RectColliderComponent.h"

RectColliderComponent::RectColliderComponent(std::string name)
{
	collider_Tag = "" + name;
}

std::string RectColliderComponent::getColliderTag()
{
	return collider_Tag;
}

void RectColliderComponent::setOrMoveCollider(float x, float y, float width, float height)
{
	rect_Collider.left = x;
	rect_Collider.top = y;
	rect_Collider.width = width;
	rect_Collider.height = height;
}

sf::FloatRect& RectColliderComponent::getColliderRectF()
{
	return rect_Collider;
}