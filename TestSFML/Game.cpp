#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), TITLE)
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
	
	DebugDraw::getInstance().initialize(window);

	gameObjects = std::vector<GameObject*>();

	player->setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2));

	gameObjects.push_back(player);

	AssetManager::loadSound("CompleteSound", "Assets\\Sounds\\completeSound.wav");
	AssetManager::loadMusic("MusicTrack", "Assets\\Music\\musicTrack.ogg");
	AssetManager::Music["MusicTrack"]->play();

	for(auto gameObject : gameObjects)
	{
		gameObject->initialize();
	}
}

void Game::run()
{
	initialize();

	while (window.isOpen())
	{
		auto deltaTime = clock.restart().asMilliseconds();

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
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && sf::Keyboard::Escape))
			window.close();
	}
}

void Game::draw()
{
	window.clear(BG_COLOR);

	drawFloor(sf::Vector2f(0, 0),
		sf::Vector2i(10, 10),
		sf::Vector2i(64, 64)
	);

	for (auto gameObject : gameObjects)
		gameObject->draw(window);

	window.display();
}

void Game::drawFloor(sf::Vector2f position, sf::Vector2i tiles, sf::Vector2i tileSize)
{
	for (auto x = 0; x < tiles.x; x++)
	{
		for (auto y = 0; y < tiles.y; y++)
		{
			auto tilepos = sf::Vector2f(position.x + x * tileSize.x, position.y + y * tileSize.y);
			DebugDraw::getInstance().drawRectangle(tilepos, tileSize.x, tileSize.y, (x + y) % 2 == 0 ? sf::Color::White : sf::Color::Black);
		}
	}
}

void Game::update(float deltaTime)
{
	for (auto gameObject : gameObjects)
		gameObject->update(deltaTime);

	checkAreaBorders();

	InputManager::getInstance().update();
}

void Game::checkAreaBorders()
{
	auto left = 0;
	auto top = 0;
	auto right = 640;
	auto bottom = 480;

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