#pragma once
#include "GameState.h"
#include <unordered_map>

class GameObject;

using GameObjectPtr = std::shared_ptr<GameObject>;
using TexturePtr = std::shared_ptr<sf::Texture>;
using SpritePtr = std::shared_ptr<sf::Sprite>;

class MenuState : public GameState
{
public:
	void init(sf::RenderWindow& rWindow) override;
	void exit() override;
	void update(float deltaTime) override;
	void render() override;
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::shared_ptr<GameObject> map;

	void loadMap(std::string name, const sf::Vector2f& offset);

	std::unordered_map<std::string, TexturePtr> m_tileSetTexture;
	const std::filesystem::path m_resourcePath{ "Assets" };

	std::vector<std::vector<SpritePtr>> m_layers;
	std::unordered_map<std::string, GameObjectPtr> m_objects;
};