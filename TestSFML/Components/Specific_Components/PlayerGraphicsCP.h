#pragma once
#include "../Graphics_Components/GraphicsCP.h"
class PlayerGraphicsCP : public GraphicsCP 
{
public:
	PlayerGraphicsCP(std::weak_ptr<GameObject> gameObject, const sf::Sprite& sprite) : GraphicsCP(gameObject, sprite) {}
	
	~PlayerGraphicsCP() = default;

	std::string Component::getComponentId() { return componentId; }

private:
	std::string componentId = "PlayerGraphics";
	sf::Sprite sprite;
};