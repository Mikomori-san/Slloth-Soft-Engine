#include "stdafx.h"
#include "GameplayState.h"
#include "../Components/Graphics_Components/AnimatedGraphicsCP.h"
#include "../Components/Graphics_Components/StandardGraphicsCP.h"
#include "../Components/Transformation_Components/TransformationCP.h"
#include "../Components/Transformation_Components/BackgroundTransformationCP.h"
#include "../Components/Input_Components/MovementInputWASDCP.h"
#include "../Components/Input_Components/MovementInputArrowsCP.h"
#include "../Components/Collision_Components/RectCollisionCP.h"
#include "../Components/Graphics_Components/RenderCP.h"

void GameplayState::init(sf::RenderWindow& rWindow)
{
	this->window.reset(&rWindow, [](sf::RenderWindow*) {}); //Hahaha, ich bin ein böser Hacker :] / Ich nicht :(

	DebugDraw::getInstance().initialize(*window);



	// Create the Bckgrounds
	this->background1 = std::make_shared<GameObject>("Background1");
	this->background2 = std::make_shared<GameObject>("Background2");
	
	addBackgroundComponents(background1);
	addBackgroundComponents(background2);

	std::shared_ptr<BackgroundTransformationCP> background1Transf = std::dynamic_pointer_cast<BackgroundTransformationCP>(background1->getComponent("BackgroundTransformationCP"));
	background1Transf->setPosition(sf::Vector2f(0, 0));
	background1Transf->setDirection(-1, 0);
	background1Transf->setVelocity(150);
	gameObjects.push_back(background1);

	std::shared_ptr<TransformationCP> background2Transf = std::dynamic_pointer_cast<TransformationCP>(background2->getComponent("BackgroundTransformationCP"));
	background2Transf->setPosition(sf::Vector2f(window->getSize().x, 0));
	background2Transf->setDirection(-1, 0);
	background2Transf->setVelocity(150);
	gameObjects.push_back(background2);



	// Create the players
	this->player = std::make_shared<GameObject>("Player");
	this->player2 = std::make_shared<GameObject>("Player2");

	addPlayerComponents(player, true);
	addPlayerComponents(player2, false);

	std::shared_ptr<TransformationCP> playerTransf = std::dynamic_pointer_cast<TransformationCP>(player->getComponent("PlayerTransformationCP"));
	playerTransf->setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
	gameObjects.push_back(player);

	std::shared_ptr<TransformationCP> player2Transf = std::dynamic_pointer_cast<TransformationCP>(player2->getComponent("PlayerTransformationCP"));
	player2Transf->setPosition(sf::Vector2f(window->getSize().x / 3, window->getSize().y / 3));
	gameObjects.push_back(player2);



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

	checkBackgroundPos();
	checkAreaBorders();
}

void GameplayState::checkBackgroundPos()
{
	std::shared_ptr<BackgroundTransformationCP> backgroundTransCP;
	std::shared_ptr<StandardGraphicsCP> backgroundGraphicsCP;

	sf::Vector2f pos;
	sf::Vector2f scale;

	for (auto& gameObject : gameObjects)
	{
		
		auto backgroundTransformations = gameObject->getComponentsOfType<BackgroundTransformationCP>();
		if (backgroundTransformations.size() > 0)
		{
			backgroundTransCP = backgroundTransformations.at(0);
			pos = backgroundTransCP->getPosition();

			auto backgroundGraphicsCP = gameObject->getComponentsOfType<StandardGraphicsCP>();
			if (backgroundGraphicsCP.size() > 0)
			{
				scale = backgroundGraphicsCP.at(0)->getSize();
			}
			std::cout << "X position:           " << pos.x << std::endl;
			std::cout << "width of backgroun:   " << scale.x << std::endl;
			std::cout << "----------------------------------" << std::endl;
			if (pos.x < -(scale.x))
			{
				std::cout << pos.x << std::endl;
				std::cout << scale.x << std::endl;
				backgroundTransCP->setPosition(sf::Vector2f(scale.x, 0));
			}
		}
	}
}


void GameplayState::render()
{
	/*drawFloor(sf::Vector2f(0, 0),
		sf::Vector2i(static_cast<int>(window->getSize().x / TILE_SIZE) + 1, static_cast<int>(window->getSize().y / TILE_SIZE + 1)),
		sf::Vector2i(TILE_SIZE, TILE_SIZE)
	);*/

	for (auto& gameObject : gameObjects)
	{
		for (auto& component : gameObject->getComponentsOfType<RenderCP>())
		{
			component->draw();
		}
	}
}

void GameplayState::checkAreaBorders()
{
	auto left = 0;
	auto top = 0;
	auto right = window->getSize().x;
	auto bottom = window->getSize().y;

	std::shared_ptr<TransformationCP> transf;
	std::shared_ptr<RectCollisionCP> collision;

	for (auto& go : gameObjects)
	{
		//Check for both players
		if ((transf = std::dynamic_pointer_cast<TransformationCP>(go->getComponent("PlayerTransformationCP"))) && (collision = std::dynamic_pointer_cast<RectCollisionCP>(go->getComponent("PlayerCollisionCP"))))
		{
			if (transf && collision)
			{
				if (transf->getPosition().y > bottom - collision->getCollisionRect().height / 2)
					transf->setPosition(sf::Vector2f(transf->getPosition().x, bottom - collision->getCollisionRect().height / 2));

				if (transf->getPosition().y < top + collision->getCollisionRect().height / 2)
					transf->setPosition(sf::Vector2f(transf->getPosition().x, top + collision->getCollisionRect().height / 2));

				if (transf->getPosition().x > right - collision->getCollisionRect().width / 2)
					transf->setPosition(sf::Vector2f(right - collision->getCollisionRect().width / 2, transf->getPosition().y));

				if (transf->getPosition().x < left + collision->getCollisionRect().width / 2)
					transf->setPosition(sf::Vector2f(left + collision->getCollisionRect().width / 2, transf->getPosition().y));
			}
		}
	}
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
	for (auto& comp : player->getComponents())
	{
		if (comp->getComponentId() == "PlayerTransformCP")
		{
			if (std::shared_ptr<TransformationCP> transf = std::dynamic_pointer_cast<TransformationCP>(comp))
			{
				transf->setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
			}
		}
	}
}

void GameplayState::addPlayerComponents(std::shared_ptr<GameObject> player, bool useArrowKeys)
{
	const int PLAYER_ANIMATION_SPEED = 8;
	if (!AssetManager::getInstance().Textures["PlayerTexture"])
	{
		AssetManager::getInstance().loadTexture("PlayerTexture", "Assets\\Textures\\playerSpriteSheet.png");
	}
	std::vector<int> playerSpriteSheetAnimationCounts = { 3, 3, 1, 3, 10, 10, 10, 10 };

	std::shared_ptr<AnimatedGraphicsCP> playerGraphicsCP = std::make_shared<AnimatedGraphicsCP>(
		player, "PlayerSpriteCP", *AssetManager::getInstance().Textures.at("PlayerTexture"), playerSpriteSheetAnimationCounts, PLAYER_ANIMATION_SPEED
	);

	player->addComponent(playerGraphicsCP);

	const float VELOCITY = 8;
	sf::Vector2f pos(window->getSize().x / 2, window->getSize().y / 2);
	std::shared_ptr<TransformationCP> transCP = std::make_shared<TransformationCP>(player, "PlayerTransformationCP", pos, 0, 1);
	transCP->setVelocity(VELOCITY);
	player->addComponent(transCP);


	if (useArrowKeys) {
		std::shared_ptr<MovementInputArrowsCP> movementInputCP = std::make_shared<MovementInputArrowsCP>(
			player, "MovementInputCP", playerGraphicsCP, transCP
		);
		player->addComponent(movementInputCP);
	}
	else {
		std::shared_ptr<MovementInputWASDCP> movementInputCP = std::make_shared<MovementInputWASDCP>(
			player, "MovementInputCP", playerGraphicsCP, transCP
		);
		player->addComponent(movementInputCP);
	}

	std::shared_ptr<RectCollisionCP> playerCollisionCP = std::make_shared<RectCollisionCP>(player, "PlayerCollisionCP");
	player->addComponent(playerCollisionCP);

	std::shared_ptr<RenderCP> playerRenderCP = std::make_shared<RenderCP>(player, "PlayerRenderCP", window);
	player->addComponent(playerRenderCP);
}



void GameplayState::addBackgroundComponents(std::shared_ptr<GameObject> Background)
{
	if (!AssetManager::getInstance().Textures["BackgroundTexture"])
	{
		AssetManager::getInstance().loadTexture("BackgroundTexture", "Assets\\Textures\\background.png");
	}
	std::shared_ptr<StandardGraphicsCP> backgroundGraphicsCP = std::make_shared<StandardGraphicsCP>(Background, "BackgroudTexture", *AssetManager::getInstance().Textures.at("BackgroundTexture"));
	Background->addComponent(backgroundGraphicsCP);

	const float VELOCITY = 8;
	sf::Vector2f pos(0, 0);
	std::shared_ptr<BackgroundTransformationCP> transCP = std::make_shared<BackgroundTransformationCP>(Background, "BackgroundTransformationCP", pos, 0, 1);
	transCP->setVelocity(VELOCITY);
	Background->addComponent(transCP);

	std::shared_ptr<RenderCP> backgroundRenderCP = std::make_shared<RenderCP>(Background, "BackgroundRenderCP", window);
	Background->addComponent(backgroundRenderCP);
}
