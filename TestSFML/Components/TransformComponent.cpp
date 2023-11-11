#include "TransformComponent.h"

TransformComponent::TransformComponent(float width, float height, sf::Vector2f location)
{
	o_Height = height;
	o_Width = width;
	o_location = location;
}

sf::Vector2f& TransformComponent::getLocation()
{
	return o_location;
}

sf::Vector2f TransformComponent::getSize()
{
	return sf::Vector2f(o_Width, o_Height);
}