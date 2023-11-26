#pragma once
#include "../Graphics_Components/GraphicsCP.h"

class RenderCP : public Component
{
public:
	RenderCP(std::weak_ptr<GameObject> gameObject, std::string id, std::weak_ptr<sf::RenderWindow> renderWindow) : Component(gameObject, id), window(renderWindow){}
	void draw();
	void update (float deltaTime) override;
	std::string getComponentId() override { return this->componentId; }
	void setComponentId(std::string id) override { this->componentId = id; }
	void init() override;
private:
	std::vector<std::shared_ptr<GraphicsCP>> renderComponents;
	std::shared_ptr<sf::RenderWindow> window;
};