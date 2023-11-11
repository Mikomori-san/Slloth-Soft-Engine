#pragma once
#include "Components.h"
#include "GraphicsComponent.h"
#include <string>

class StandardGraphicsComponent : public GraphicsComponent
{
public:
	std::string Component::getSpecificId()
	{
		return specificComponentId;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self)
	{}

	void draw(sf::RenderWindow& window, std::shared_ptr<TransformComponent> t) override;

	void initializeGraphics(std::shared_ptr<sf::Texture> texture) override;


private:
	sf::Sprite component_Sprite;
	std::string specificComponentId = "standardGraphic";

};
