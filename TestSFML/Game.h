#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include "GameObjects/GameObject.h"
#include "Manager/AssetManager.h"
#include "Manager/InputManager.h"

#pragma once

using namespace sf;

class Game
{
public:
	Game();
	void run();
private:
	const int WIDTH = 640;
	const int HEIGHT = 480;
	const char* TITLE = "SLLOTH-SOFT";
	Color BG_COLOR = Color(50, 50, 50);
	Clock clock;
	VideoMode mode;
	RenderWindow* window;
	std::vector<GameObject*> gameObjects;

	void closeGame(const Event& event);
	void initialize();
	void handleEvents();
	void draw();
	void drawFloor(Vector2f position, Vector2i tiles, Vector2i tileSize);
	void update(float deltaTime);
	void checkAreaBorders();
	void respawnPlayer();
};