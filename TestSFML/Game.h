#include "GameObjects/GameObject.h"
#include "Manager/AssetManager.h"
#include "Manager/InputManager.h"
#include "DebugDraw.h"
#include "GameObjects/Player.h"
#include "Manager/GameStateManager.h"
#include "GameStates/MenuState.h"
#include "GameStates/GameplayState.h"
#include "GameStates/ExitState.h"
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
	sf::Color BG_COLOR = sf::Color(50, 50, 50);
	sf::Clock clock;
	sf::VideoMode mode;
	sf::RenderWindow window;

	void closeGame(const sf::Event& event);
	void initialize();
	void handleEvents();

	void draw();
	void update(float deltaTime);
};