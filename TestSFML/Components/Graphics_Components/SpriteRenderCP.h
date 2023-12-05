#pragma once
#pragma once
#include "../Graphics_Components/RenderCP.h"

class SpriteRenderCP : public RenderCP
{
public:
	SpriteRenderCP(std::weak_ptr<GameObject> gameObject, std::string id, std::weak_ptr<sf::RenderWindow> renderWindow) : RenderCP(gameObject, id, renderWindow) {}
	virtual ~SpriteRenderCP() = default;

	void draw() override;
	void update(float deltaTime) override;
	std::string getComponentId() override { return this->componentId; }
	void setComponentId(std::string id) override { this->componentId = id; }
	void init() override;
private:
	std::vector<std::shared_ptr<GraphicsCP>> renderComponents;
};