#include "stdafx.h"
#include "GameplayState.h"
#include "../Components/Graphics_Components/AnimatedGraphicsCP.h"
#include "../Components/Transformation_Components/TransformationCP.h"
#include "../Components/Input_Components/MovementInputCP.h"

void GameplayState::init(sf::RenderWindow& rWindow)
{
	this->window.reset(&rWindow, [](sf::RenderWindow*) {}); //Hahaha, ich bin ein böser Hacker :]

	this->player = std::make_shared<GameObject>();
	
	addPlayerComponents();
	
	DebugDraw::getInstance().initialize(*window);

	player->setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));

	gameObjects.push_back(player);

	AssetManager::getInstance().loadSound("CompleteSound", "Assets\\Sounds\\completeSound.wav");
	AssetManager::getInstance().loadMusic("MusicTrack", "Assets\\Music\\musicTrack.ogg");
	AssetManager::Music["MusicTrack"]->play();

	for (auto& gameObject : gameObjects)
	{
		gameObject->init();
	}
}

void GameplayState::exit()
{
	for (auto gameObject : gameObjects)
	{
		gameObject.reset();
	}
	gameObjects.clear();

	this->player.reset();
	this->window.reset();
	DebugDraw::getInstance().unload();

	AssetManager::getInstance().unloadAssets();
}

void GameplayState::update(float deltaTime)
{
	for (auto gameObject : gameObjects)
		gameObject->update(deltaTime);

	checkAreaBorders();
}

void GameplayState::render()
{
	drawFloor(sf::Vector2f(0, 0),
		sf::Vector2i(static_cast<int>(window->getSize().x / TILE_SIZE) + 1, static_cast<int>(window->getSize().y / TILE_SIZE + 1)),
		sf::Vector2i(TILE_SIZE, TILE_SIZE)
	);

	for (auto& gameObject : gameObjects)
	{
		for (auto& component : gameObject->getComponents())
		{
			if (std::shared_ptr<AnimatedGraphicsCP> aniGraphCP = std::dynamic_pointer_cast<AnimatedGraphicsCP>(component))
			{
				aniGraphCP->draw();
			}
		}
	}	
}

void GameplayState::checkAreaBorders()
{
	auto left = 0;
	auto top = 0;
	auto right = window->getSize().x;
	auto bottom = window->getSize().y;

	if (player->getPosition().y > bottom - player->getCollisionRect().height / 2)
		player->setPosition(sf::Vector2f(player->getPosition().x, bottom - player->getCollisionRect().height / 2));

	if (player->getPosition().y < top + player->getPlayerCollisionRect().height / 2)
		player->setPosition(sf::Vector2f(player->getPosition().x, top + player->getCollisionRect().height / 2));

	if (player->getPosition().x > right - player->getCollisionRect().width / 2)
		player->setPosition(sf::Vector2f(right - player->getCollisionRect().width / 2, player->getPosition().y));

	if (player->getPosition().x < left + player->getCollisionRect().width / 2)
		player->setPosition(sf::Vector2f(left + player->getCollisionRect().width / 2, player->getPosition().y));
}

void GameplayState::drawFloor(sf::Vector2f position, sf::Vector2i tiles, sf::Vector2i tileSize)
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

void GameplayState::respawnPlayer()
{
	player->setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
}

void GameplayState::addPlayerComponents()
{
	const int PLAYER_ANIMATION_SPEED = 8;
	AssetManager::getInstance().loadTexture("PlayerTexture", "Assets\\Textures\\playerSpriteSheet.png");
	std::vector<int> playerSpriteSheetAnimationCounts = { 3, 3, 1, 3, 10, 10, 10, 10 };

	AnimatedGraphicsCP playerGraphicsCP(player, "PlayerSpriteCP", *window, *AssetManager::getInstance().Textures["PlayerTexture"], playerSpriteSheetAnimationCounts, PLAYER_ANIMATION_SPEED);
	player->addComponent(std::make_shared<Component>(playerGraphicsCP));

	const float VELOCITY = 8;
	TransformationCP transCP(player, "PlayerTransformation");
	transCP.setVelocity(VELOCITY);
	player->addComponent(std::make_shared<Component>(transCP));

	MovementInputCP movementInputCP(player, "MovementInputCP", std::make_shared<AnimatedGraphicsCP>(playerGraphicsCP), std::make_shared<TransformationCP>(transCP));
	player->addComponent(std::make_shared<Component>(movementInputCP));

}
