#pragma once
#include "GameState.h"
#include "../GameObjects/GameObject.h"
#include "../Manager/AssetManager.h"
#include "../DebugDraw.h"

class GameplayState : public GameState
{
public:
	void init(sf::RenderWindow& rWindow) override;
	void exit() override;
	void update(float deltaTime) override;
	void render() override;

private:
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::shared_ptr<GameObject> player;
	std::shared_ptr<sf::RenderWindow> window;
	const int TILE_SIZE = 64;

	void checkAreaBorders();
	void drawFloor(sf::Vector2f position, sf::Vector2i tiles, sf::Vector2i tileSize);
	void respawnPlayer();
};