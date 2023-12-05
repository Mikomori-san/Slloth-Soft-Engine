#pragma once
#include "../Graphics_Components/RenderCP.h"
#include <unordered_map>

class LayerCP : public RenderCP
{
public:
	LayerCP(std::weak_ptr<GameObject> go, std::string id, std::weak_ptr<sf::RenderWindow> renderWindow, int layerNum, std::vector<std::shared_ptr<sf::Sprite>> incLayer) : RenderCP(go, id, renderWindow), layerNr(layerNum), layer(incLayer) {};
	virtual ~LayerCP() = default;

	void init() override;
	void draw() override;
	void update(float deltaTime) override;
	
	std::string getComponentId() override { return this->componentId; }
	void setComponentId(std::string id) override { this->componentId = id; }
private:
	std::vector<std::shared_ptr<sf::Sprite>> layer;
	int layerNr;
};