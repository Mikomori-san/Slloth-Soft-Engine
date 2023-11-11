#include "stdafx.h"
#include "Game.h"

Game::Game() : window(sf::VideoMode(WIDTH, HEIGHT), TITLE)
{
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
}

void Game::closeGame(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		window.close();
}

void Game::initialize()
{
	InputManager::getInstance().init(window);
<<<<<<< HEAD

	DebugDraw::getInstance().initialize(window);
=======
>>>>>>> GameState_Implementing

	GameStateManager::getInstance().reg("Start", std::make_shared<MenuState>());
	GameStateManager::getInstance().reg("Gameplay", std::make_shared<GameplayState>());
	GameStateManager::getInstance().reg("Exit", std::make_shared<ExitState>());

<<<<<<< HEAD
	player->setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2));

	AssetManager::getInstance().loadTexture("PlayerTexture", "Assets\\Textures\\playerSpriteSheet.png");

	player->setSprite(AssetManager::getInstance().Textures["PlayerTexture"]);
	gameObjects.push_back(player);

	AssetManager::getInstance().loadSound("CompleteSound", "Assets\\Sounds\\completeSound.wav");
	AssetManager::getInstance().loadMusic("MusicTrack", "Assets\\Music\\musicTrack.ogg");
	AssetManager::Music["MusicTrack"]->play();

	for (auto gameObject : gameObjects)
	{
		gameObject->initialize();
	}
=======
	GameStateManager::getInstance().setState("Gameplay", window);
>>>>>>> GameState_Implementing
}

void Game::run()
{
	initialize();

	while (window.isOpen())
	{
		auto deltaTime = clock.restart().asSeconds();

		handleEvents();
		update(deltaTime);
		draw();
	}
}

void Game::handleEvents()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape))
			window.close();
<<<<<<< HEAD

=======
		
>>>>>>> GameState_Implementing
		InputManager::getInstance().handleEvents(event);
	}
}

void Game::draw()
{
	window.clear(BG_COLOR);

	GameStateManager::getInstance().render();
	
	window.display();
}

void Game::update(float deltaTime)
{
	if (InputManager::getInstance().getKeyDown(sf::Keyboard::Num1))
		GameStateManager::getInstance().setState("Gameplay", window);
	else if (InputManager::getInstance().getKeyDown(sf::Keyboard::Num2))
		GameStateManager::getInstance().setState("Start", window);

	GameStateManager::getInstance().update(deltaTime);

	InputManager::getInstance().update();
<<<<<<< HEAD
}

void Game::checkAreaBorders()
{
	auto left = 0;
	auto top = 0;
	auto right = window.getSize().x;
	auto bottom = window.getSize().y;

	if (player->getPosition().y > bottom - player->getCollisionRect().height / 2)
		player->setPosition(sf::Vector2f(player->getPosition().x, bottom - player->getCollisionRect().height / 2));

	if (player->getPosition().y < top + player->getPlayerCollisionRect().height / 2)
		player->setPosition(sf::Vector2f(player->getPosition().x, top + player->getCollisionRect().height / 2));

	if (player->getPosition().x > right - player->getCollisionRect().width / 2)
		player->setPosition(sf::Vector2f(right - player->getCollisionRect().width / 2, player->getPosition().y));

	if (player->getPosition().x < left + player->getCollisionRect().width / 2)
		player->setPosition(sf::Vector2f(left + player->getCollisionRect().width / 2, player->getPosition().y));
}

void Game::respawnPlayer()
{
	player->setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2));
}
=======
}
>>>>>>> GameState_Implementing
