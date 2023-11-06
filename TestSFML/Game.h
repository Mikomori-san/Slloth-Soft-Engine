#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include "GameObjects/GameObject.h"
#include "Manager/AssetManager.h"
#include "Manager/InputManager.h"
#include "DebugDraw.h"
#include "GameObjects/Player.h"
#include "Manager/GameStateManager.h"

#pragma once

class Game
{
public:
	void run();
	Game();
private:
	const int WIDTH = 640;
	const int HEIGHT = 480;
	const char* TITLE = "SLLOTH-SOFT";
	const int TILE_SIZE = 64;
	sf::Color BG_COLOR = sf::Color(50, 50, 50);
	sf::Clock clock;
	sf::VideoMode mode;
	sf::RenderWindow window;
	std::vector<GameObject*> gameObjects;

	Player* player = new Player{};

	void closeGame(const sf::Event& event);
	void initialize();
	void handleEvents();
	void draw();
	void drawFloor(sf::Vector2f position, sf::Vector2i tiles, sf::Vector2i tileSize);
	void update(float deltaTime);
	void checkAreaBorders();
	void respawnPlayer();
};