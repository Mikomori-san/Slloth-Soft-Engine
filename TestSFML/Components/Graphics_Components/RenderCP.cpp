#include "stdafx.h"
#include "RenderCP.h"
#include "../../DebugDraw.h"
#include "../Collision_Components/RectCollisionCP.h"

void RenderCP::draw()
{
	for (auto& rend : renderComponents)
	{
		auto& sprite = rend->getSprite();
		window->draw(sprite);

		if (!gameObject.expired())
		{
			std::shared_ptr<GameObject> go = gameObject.lock();
			if (go->getId() == "Player")
			{
				DebugDraw::getInstance().drawRectOutline(
					sf::Vector2f(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top),
					static_cast<int>(sprite.getGlobalBounds().width),
					static_cast<int>(sprite.getGlobalBounds().height),
					sf::Color::Red
				);

				std::shared_ptr<RectCollisionCP> collision = std::dynamic_pointer_cast<RectCollisionCP>(go->getComponent("PlayerCollisionCP"));
				DebugDraw::getInstance().drawRectOutline(collision->getCollisionRect(), sf::Color::Green);
			}
		}
	}
}

void RenderCP::update(float deltaTime)
{

}

void RenderCP::init()
{
	if (!gameObject.expired())
	{
		std::shared_ptr<GameObject> go = gameObject.lock();
		renderComponents.push_back(std::dynamic_pointer_cast<GraphicsCP>(go->getComponent("PlayerSpriteCP")));
	}
}
