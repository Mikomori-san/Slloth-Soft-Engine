#pragma once
#include "../Graphics_Components/GraphicsCP.h"

class RenderCP : public Component
{
public:
	RenderCP(std::weak_ptr<GameObject> gameObject, std::string id, std::weak_ptr<sf::RenderWindow> renderWindow) : Component(gameObject, id), window(renderWindow){}
	virtual ~RenderCP() = default;

	virtual void draw() = 0;
	virtual void update (float deltaTime) override = 0;
	virtual std::string getComponentId() override = 0;
	virtual void setComponentId(std::string id) override = 0;
	virtual void init() override = 0;

protected:
	std::shared_ptr<sf::RenderWindow> window;
};