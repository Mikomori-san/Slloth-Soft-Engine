<<<<<<< HEAD
#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
=======
>>>>>>> GameState_Implementing
#include "GameObjects/GameObject.h"
#include "Manager/AssetManager.h"
#include "Manager/InputManager.h"
#include "DebugDraw.h"
#include "GameObjects/GameObject.h"
#include "Manager/GameStateManager.h"
<<<<<<< HEAD

=======
#include "GameStates/MenuState.h"
#include "GameStates/GameplayState.h"
#include "GameStates/ExitState.h"
#pragma once
>>>>>>> GameState_Implementing

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
<<<<<<< HEAD
	std::vector<GameObject*> gameObjects;
=======
>>>>>>> GameState_Implementing

	void closeGame(const sf::Event& event);
	void initialize();
	void handleEvents();

	void draw();
	void update(float deltaTime);
<<<<<<< HEAD
	void checkAreaBorders();
	void respawnPlayer();
};
=======
};
>>>>>>> GameState_Implementing
