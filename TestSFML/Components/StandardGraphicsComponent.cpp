#include <iostream>
#include "StandardGraphicsComponent.h"

void StandardGraphicsComponent::initializeGraphics(std::shared_ptr<sf::Texture> texture)
{
	component_Sprite.setTexture(*texture);
}

void StandardGraphicsComponent::draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t)
{
	component_Sprite.setPosition(t->getLocation());
	window.draw(component_Sprite);
}
